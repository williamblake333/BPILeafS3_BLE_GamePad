/*
 * ButtonMapping.h
 * Header file for button mapping functions
 */

#ifndef BUTTON_MAPPING_H
#define BUTTON_MAPPING_H

#include <Arduino.h>

// Function to map a row and column position to a button ID
uint8_t mapPositionToButton(uint8_t row, uint8_t col);

// Function to map a key character to a button ID
uint8_t mapKeyCharToButton(char keyChar);

#endif // BUTTON_MAPPING_H