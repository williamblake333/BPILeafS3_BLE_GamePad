/*
 * BLE Gamepad with 5x5 Matrix Keyboard and ADNS5050 Mouse Sensor
 * For BPI Leaf S3 (ESP32-S3)
 * 
 * This implementation uses the ESP32-BLE-CompositeHID library to create a composite
 * device with gamepad and mouse functionality.
 */

#include <Arduino.h>
#include <BleCompositeHID.h>
#include <GamepadDevice.h>
#include <MouseDevice.h>
#include <Keypad.h>

// Include our custom class headers
#include "ADNS5050.h"
#include "MatrixKeyboard.h"
#include "AnalogJoystick.h"
#include "config.h"  // Load configuration

// Matrix Keyboard Configuration
// Define the keypad size
const byte ROWS = KEYBOARD_ROWS;
const byte COLS = KEYBOARD_COLS;

// Define the pins connected to the rows and columns
byte rowPins[ROWS] = {ROW_PIN_0, ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4};
byte colPins[COLS] = {COL_PIN_0, COL_PIN_1, COL_PIN_2, COL_PIN_3, COL_PIN_4};

// Define the button mapping
// The 5x5 matrix allows for 25 buttons, but you're using 21
// We'll map the buttons to gamepad buttons
char keyMap[ROWS][COLS] = {
  {'1', '2', '3', '4', '5'},  // Row 0: buttons 1-5
  {'6', '7', '8', '9', 'A'},  // Row 1: buttons 6-10
  {'B', 'C', 'D', 'E', 'F'},  // Row 2: buttons 11-15
  {'G', 'H', 'I', 'J', ' '},  // Row 3: buttons 16-18 (19 unused)
  {'K', 'L', 'M', ' ', ' '}   // Row 4: buttons 19-21 (22-25 unused)
};

// BLE HID Devices
BleCompositeHID compositeHID(DEVICE_NAME, DEVICE_MANUFACTURER, BATTERY_LEVEL);
GamepadDevice gamepad;
MouseDevice mouse;

// Create instances of our custom classes
ADNS5050* mouseSensor;
MatrixKeyboard* matrixKeyboard;
AnalogJoystick* analogJoystick;

// Mouse update interval
unsigned long lastMouseUpdate = 0;
const unsigned long mouseUpdateInterval = MOUSE_UPDATE_INTERVAL;

void setup() {
  // Initialize serial for debugging
  if (DEBUG_ENABLED) {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("BLE Gamepad + Mouse starting...");
  }
  
  // Initialize the mouse sensor
  mouseSensor = new ADNS5050(ADNS_SCLK_PIN, ADNS_SDIO_PIN, ADNS_NCS_PIN, ADNS_NRESET_PIN);
  mouseSensor->begin();
  
  // Check if the mouse sensor is properly connected
  if (DEBUG_ENABLED) {
    if (mouseSensor->checkConnection()) {
      Serial.println("ADNS5050 sensor found and initialized.");
    } else {
      Serial.println("ADNS5050 sensor not found or initialization failed!");
    }
  }
  
  // Initialize the matrix keyboard
  // Convert our 2D array to pointer-to-pointer format for the MatrixKeyboard class
  char** keyMapPtr = new char*[ROWS];
  for (int i = 0; i < ROWS; i++) {
    keyMapPtr[i] = new char[COLS];
    for (int j = 0; j < COLS; j++) {
      keyMapPtr[i][j] = keyMap[i][j];
    }
  }
  
  matrixKeyboard = new MatrixKeyboard(ROWS, COLS, rowPins, colPins, keyMapPtr, &gamepad);
  matrixKeyboard->begin();
  
  // Initialize the analog joystick
  analogJoystick = new AnalogJoystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, JOYSTICK_DEADZONE, &gamepad);
  analogJoystick->begin();
  
  // Add devices to composite HID
  compositeHID.addDevice(&gamepad);
  compositeHID.addDevice(&mouse);
  
  // Start the BLE HID service
  compositeHID.begin();
  
  if (DEBUG_ENABLED) {
    Serial.println("BLE Gamepad service started. Waiting for connection...");
  }
}

void loop() {
  static bool lastConnectionState = false;
  bool currentConnectionState = compositeHID.isConnected();
  
  // Connection state change detection
  if (DEBUG_ENABLED && currentConnectionState != lastConnectionState) {
    if (currentConnectionState) {
      Serial.println("BLE device connected!");
    } else {
      Serial.println("BLE device disconnected!");
    }
    lastConnectionState = currentConnectionState;
  }
  
  // Check BLE connection
  if (currentConnectionState) {
    // Handle matrix keyboard input
    matrixKeyboard->update();
    
    // Handle joystick input
    analogJoystick->update();
    
    // Handle mouse sensor input - only update at the specified interval
    unsigned long currentTime = millis();
    if (currentTime - lastMouseUpdate >= mouseUpdateInterval) {
      lastMouseUpdate = currentTime;
      
      // Check if motion has been detected
      int16_t deltaX = 0;
      int16_t deltaY = 0;
      
      // Get the motion delta values
      mouseSensor->getMotion(&deltaX, &deltaY);
      
      // Send mouse movement if detected
      if (deltaX != 0 || deltaY != 0) {
        mouse.move(deltaX, deltaY);
        
        // Debug output
        if (DEBUG_ENABLED) {
          Serial.print("Mouse X: ");
          Serial.print(deltaX);
          Serial.print(", Y: ");
          Serial.println(deltaY);
        }
      }
    }
  }
  
  // Small delay to prevent CPU hogging
  delay(5);
}