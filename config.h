/*
 * config.h
 * Configuration file for the BLE Gamepad project
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============ Device Information ============
#define DEVICE_NAME "ESP32 Gamepad+Mouse"
#define DEVICE_MANUFACTURER "Custom Controller"
#define BATTERY_LEVEL 100  // Initial battery level (0-100)

// ============ Debug Settings ============
#define DEBUG_ENABLED true        // Set to false to disable serial debug output
#define SERIAL_BAUD_RATE 115200   // Serial port baud rate

// ============ Matrix Keyboard Configuration ============
// Matrix size
#define KEYBOARD_ROWS 5
#define KEYBOARD_COLS 5

// Matrix pins
// Adjust these pin numbers based on your actual wiring
#define ROW_PIN_0 10
#define ROW_PIN_1 11
#define ROW_PIN_2 12
#define ROW_PIN_3 13
#define ROW_PIN_4 14

#define COL_PIN_0 15
#define COL_PIN_1 16
#define COL_PIN_2 17
#define COL_PIN_3 18
#define COL_PIN_4 19

// ============ Joystick Configuration ============
#define JOYSTICK_X_PIN 1  // X-axis analog pin
#define JOYSTICK_Y_PIN 2  // Y-axis analog pin
#define JOYSTICK_DEADZONE 50  // Deadzone value (0-4095)

// ============ ADNS5050 Mouse Sensor Configuration ============
#define ADNS_SCLK_PIN 7   // Clock pin
#define ADNS_SDIO_PIN 6   // Data pin
#define ADNS_NCS_PIN 5    // Chip select pin
#define ADNS_NRESET_PIN 4 // Reset pin

#define MOUSE_UPDATE_INTERVAL 8 // Mouse update interval in milliseconds (~125 Hz)

// ============ Button Mapping ============
// Define the gamepad button mapping here
// This maps each key in the matrix to a specific gamepad button

// Row 0
#define KEY_00_BUTTON BUTTON_1
#define KEY_01_BUTTON BUTTON_2
#define KEY_02_BUTTON BUTTON_3
#define KEY_03_BUTTON BUTTON_4
#define KEY_04_BUTTON BUTTON_5

// Row 1
#define KEY_10_BUTTON BUTTON_6
#define KEY_11_BUTTON BUTTON_7
#define KEY_12_BUTTON BUTTON_8
#define KEY_13_BUTTON BUTTON_9
#define KEY_14_BUTTON BUTTON_10

// Row 2
#define KEY_20_BUTTON BUTTON_11
#define KEY_21_BUTTON BUTTON_12
#define KEY_22_BUTTON BUTTON_13
#define KEY_23_BUTTON BUTTON_14
#define KEY_24_BUTTON BUTTON_15

// Row 3
#define KEY_30_BUTTON BUTTON_16
#define KEY_31_BUTTON BUTTON_17
#define KEY_32_BUTTON BUTTON_18
#define KEY_33_BUTTON BUTTON_16  // This appears to be unused in your matrix
#define KEY_34_BUTTON 0  // Unused position

// Row 4
#define KEY_40_BUTTON BUTTON_19
#define KEY_41_BUTTON BUTTON_20
#define KEY_42_BUTTON BUTTON_21
#define KEY_43_BUTTON 0  // Unused position
#define KEY_44_BUTTON 0  // Unused position

#endif // CONFIG_H