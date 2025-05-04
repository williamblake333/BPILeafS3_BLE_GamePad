/*
 * AnalogJoystick.h
 * Header file for the analog joystick
 */

#ifndef ANALOG_JOYSTICK_H
#define ANALOG_JOYSTICK_H

#include <Arduino.h>
#include <GamepadDevice.h>

class AnalogJoystick {
  private:
    // Pin configurations
    uint8_t _xPin;
    uint8_t _yPin;
    
    // Calibration values
    int _xCenter;
    int _yCenter;
    int _deadzone;
    
    // Gamepad reference
    GamepadDevice* _gamepad;
    
    // Last read values
    int16_t _lastX;
    int16_t _lastY;
    
  public:
    // Constructor
    AnalogJoystick(uint8_t xPin, uint8_t yPin, int deadzone, GamepadDevice* gamepad);
    
    // Initialize the joystick
    void begin();
    
    // Calibrate the joystick (center position)
    void calibrate();
    
    // Update the joystick state and send axis values to the gamepad
    void update();
    
    // Get the raw joystick values
    void getRawValues(int* x, int* y);
    
    // Get the mapped joystick values (-127 to 127)
    void getMappedValues(int16_t* x, int16_t* y);
};

#endif // ANALOG_JOYSTICK_H