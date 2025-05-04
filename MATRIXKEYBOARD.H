/*
 * MatrixKeyboard.h
 * Header file for the 5x5 matrix keyboard
 */

#ifndef MATRIX_KEYBOARD_H
#define MATRIX_KEYBOARD_H

#include <Arduino.h>
#include <Keypad.h>
#include <GamepadDevice.h>

class MatrixKeyboard {
  private:
    // Matrix dimensions
    const byte _rows;
    const byte _cols;
    
    // Pin arrays
    byte* _rowPins;
    byte* _colPins;
    
    // Key mapping
    char** _keyMap;
    
    // Keypad instance
    Keypad* _keypad;
    
    // Gamepad reference
    GamepadDevice* _gamepad;
    
  public:
    // Constructor
    MatrixKeyboard(const byte rows, const byte cols, byte* rowPins, byte* colPins, 
                  char** keyMap, GamepadDevice* gamepad);
    
    // Destructor
    ~MatrixKeyboard();
    
    // Initialize the keypad
    void begin();
    
    // Update the keypad state and send gamepad button presses/releases
    void update();
    
    // Map a key character to a gamepad button index
    int mapKeyToButton(char key);
};

#endif // MATRIX_KEYBOARD_H