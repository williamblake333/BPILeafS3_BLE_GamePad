/*
 * AnalogJoystick.cpp
 * Implementation of the analog joystick class
 */

#include "AnalogJoystick.h"

// Constructor
AnalogJoystick::AnalogJoystick(uint8_t xPin, uint8_t yPin, int deadzone, GamepadDevice* gamepad) {
  _xPin = xPin;
  _yPin = yPin;
  _deadzone = deadzone;
  _gamepad = gamepad;
  
  // Initialize last values
  _lastX = 0;
  _lastY = 0;
}

// Initialize the joystick
void AnalogJoystick::begin() {
  // Configure analog pins
  pinMode(_xPin, INPUT);
  pinMode(_yPin, INPUT);
  
  // Perform initial calibration
  calibrate();
}

// Calibrate the joystick (center position)
void AnalogJoystick::calibrate() {
  // Read the current position as center
  _xCenter = analogRead(_xPin);
  _yCenter = analogRead(_yPin);
  
  Serial.println("Joystick calibrated:");
  Serial.print("X center: ");
  Serial.print(_xCenter);
  Serial.print(", Y center: ");
  Serial.println(_yCenter);
}

// Update the joystick state and send axis values to the gamepad
void AnalogJoystick::update() {
  // Get the mapped joystick values
  int16_t axisX, axisY;
  getMappedValues(&axisX, &axisY);
  
  // Check if the joystick is outside the deadzone
  if (abs(axisX) > 0 || abs(axisY) > 0) {
    // Update the gamepad axes
    _gamepad->leftXAxis(axisX);
    _gamepad->leftYAxis(axisY);
    
    // Store the last values
    _lastX = axisX;
    _lastY = axisY;
    
    // Debug output if values changed significantly
    if (abs(_lastX - axisX) > 5 || abs(_lastY - axisY) > 5) {
      Serial.print("Joystick X: ");
      Serial.print(axisX);
      Serial.print(", Y: ");
      Serial.println(axisY);
    }
  } else if (_lastX != 0 || _lastY != 0) {
    // If within deadzone but was previously outside, reset to zero
    _gamepad->leftXAxis(0);
    _gamepad->leftYAxis(0);
    _lastX = 0;
    _lastY = 0;
    
    Serial.println("Joystick centered");
  }
}

// Get the raw joystick values
void AnalogJoystick::getRawValues(int* x, int* y) {
  *x = analogRead(_xPin);
  *y = analogRead(_yPin);
}

// Get the mapped joystick values (-127 to 127)
void AnalogJoystick::getMappedValues(int16_t* x, int16_t* y) {
  // Read the raw analog values
  int rawX, rawY;
  getRawValues(&rawX, &rawY);
  
  // Calculate the offset from center
  int xOffset = rawX - _xCenter;
  int yOffset = rawY - _yCenter;
  
  // Apply deadzone
  if (abs(xOffset) <= _deadzone) {
    xOffset = 0;
  }
  
  if (abs(yOffset) <= _deadzone) {
    yOffset = 0;
  }
  
  // Map the values to the gamepad axis range (-127 to 127)
  // ESP32-S3 has 12-bit ADC (0-4095)
  if (xOffset == 0) {
    *x = 0;
  } else {
    *x = map(rawX, 0, 4095, -127, 127);
  }
  
  if (yOffset == 0) {
    *y = 0;
  } else {
    *y = map(rawY, 0, 4095, -127, 127);
  }
}