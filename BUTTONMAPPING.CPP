/*
 * ButtonMapping.cpp
 * Implementation of button mapping functions
 */

#include "ButtonMapping.h"
#include "config.h"

// Maps a row and column to a button ID
uint8_t mapPositionToButton(uint8_t row, uint8_t col) {
  // Use a switch statement to map each position in the matrix
  // to the corresponding gamepad button
  
  if (row == 0) {
    switch (col) {
      case 0: return KEY_00_BUTTON;
      case 1: return KEY_01_BUTTON;
      case 2: return KEY_02_BUTTON;
      case 3: return KEY_03_BUTTON;
      case 4: return KEY_04_BUTTON;
    }
  }
  else if (row == 1) {
    switch (col) {
      case 0: return KEY_10_BUTTON;
      case 1: return KEY_11_BUTTON;
      case 2: return KEY_12_BUTTON;
      case 3: return KEY_13_BUTTON;
      case 4: return KEY_14_BUTTON;
    }
  }
  else if (row == 2) {
    switch (col) {
      case 0: return KEY_20_BUTTON;
      case 1: return KEY_21_BUTTON;
      case 2: return KEY_22_BUTTON;
      case 3: return KEY_23_BUTTON;
      case 4: return KEY_24_BUTTON;
    }
  }
  else if (row == 3) {
    switch (col) {
      case 0: return KEY_30_BUTTON;
      case 1: return KEY_31_BUTTON;
      case 2: return KEY_32_BUTTON;
      case 3: return KEY_33_BUTTON;
      case 4: return KEY_34_BUTTON;
    }
  }
  else if (row == 4) {
    switch (col) {
      case 0: return KEY_40_BUTTON;
      case 1: return KEY_41_BUTTON;
      case 2: return KEY_42_BUTTON;
      case 3: return KEY_43_BUTTON;
      case 4: return KEY_44_BUTTON;
    }
  }
  
  // Default return value if position is invalid
  return 0;
}

// Maps a key character to a button ID
uint8_t mapKeyCharToButton(char keyChar) {
  // Map the key to a button index (1-21)
  switch (keyChar) {
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