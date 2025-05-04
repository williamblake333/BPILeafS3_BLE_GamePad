/*
 * MatrixKeyboard.cpp
 * Implementation of the 5x5 matrix keyboard class
 */

#include "MatrixKeyboard.h"

// Constructor
MatrixKeyboard::MatrixKeyboard(const byte rows, const byte cols, byte* rowPins, byte* colPins, 
                              char** keyMap, GamepadDevice* gamepad)
  : _rows(rows), _cols(cols) {
  
  // Store pin arrays
  _rowPins = rowPins;
  _colPins = colPins;
  
  // Store key mapping
  _keyMap = keyMap;
  
  // Store gamepad reference
  _gamepad = gamepad;
  
  // Create the keypad instance
  _keypad = new Keypad(makeKeymap(_keyMap), _rowPins, _colPins, _rows, _cols);
}

// Destructor
MatrixKeyboard::~MatrixKeyboard() {
  // Free allocated memory
  delete _keypad;
}

// Initialize the keypad
void MatrixKeyboard::begin() {
  // Set debounce time (optional)
  _keypad->setDebounceTime(10);
}

// Update the keypad state and send gamepad button presses/releases
void MatrixKeyboard::update() {
  // Check if any key is pressed
  if (_keypad->getKeys()) {
    // Scan the key list for key changes
    for (int i = 0; i < LIST_MAX; i++) {
      // If the key has changed state
      if (_keypad->key[i].stateChanged) {
        char key = _keypad->key[i].kchar;
        if (key != ' ') { // Skip unused positions
          int buttonIndex = mapKeyToButton(key);
          
          // Handle button press or release
          if (_keypad->key[i].kstate == PRESSED) {
            _gamepad->press(buttonIndex);
            Serial.print("Button pressed: ");
            Serial.println(buttonIndex);
          } else if (_keypad->key[i].kstate == RELEASED) {
            _gamepad->release(buttonIndex);
            Serial.print("Button released: ");
            Serial.println(buttonIndex);
          }
        }
      }
    }
  }
}

// Map a key character to a gamepad button index
int MatrixKeyboard::mapKeyToButton(char key) {
  // Map the key to a button index (1-21)
  switch (key) {
    case '1': return BUTTON_1;
    case '2': return BUTTON_2;
    case '3': return BUTTON_3;
    case '4': return BUTTON_4;
    case '5': return BUTTON_5;
    case '6': return BUTTON_6;
    case '7': return BUTTON_7;
    case '8': return BUTTON_8;
    case '9': return BUTTON_9;
    case 'A': return BUTTON_10;
    case 'B': return BUTTON_11;
    case 'C': return BUTTON_12;
    case 'D': return BUTTON_13;
    case 'E': return BUTTON_14;
    case 'F': return BUTTON_15;
    case 'G': return BUTTON_16;
    case 'H': return BUTTON_17;
    case 'I': return BUTTON_18;
    case 'J': return BUTTON_16; // This appears to be unused in your matrix
    case 'K': return BUTTON_19;
    case 'L': return BUTTON_20;
    case 'M': return BUTTON_21;
    default: return 0; // Return 0 for unused keys
  }
}