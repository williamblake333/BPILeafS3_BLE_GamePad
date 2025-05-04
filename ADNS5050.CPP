/*
 * ADNS5050.cpp
 * Implementation of the ADNS5050 optical mouse sensor class
 */

#include "ADNS5050.h"

// Constructor
ADNS5050::ADNS5050(uint8_t sclk, uint8_t sdio, uint8_t ncs, uint8_t nreset) {
  _sclk = sclk;
  _sdio = sdio;
  _ncs = ncs;
  _nreset = nreset;
}

// Initialize the sensor
void ADNS5050::begin() {
  // Configure pins
  pinMode(_sclk, OUTPUT);
  pinMode(_sdio, OUTPUT);
  pinMode(_ncs, OUTPUT);
  pinMode(_nreset, OUTPUT);
  
  // Set initial pin states
  digitalWrite(_sclk, HIGH);
  digitalWrite(_sdio, HIGH);
  digitalWrite(_ncs, HIGH);
  digitalWrite(_nreset, HIGH);
  
  // Reset and initialize
  reset();
  
  // Configure default settings
  setPerformanceMode(0x80);  // High performance mode
  setSampleRate(0x01);       // Default sample rate
  
  // Clear any initial motion data
  readRegister(ADNS_MOTION);
  readRegister(ADNS_DELTA_X);
  readRegister(ADNS_DELTA_Y);
}

// Reset the sensor
void ADNS5050::reset() {
  // Hardware reset
  digitalWrite(_nreset, LOW);
  delayMicroseconds(1);
  digitalWrite(_nreset, HIGH);
  delay(50);  // Wait for sensor to initialize
  
  // Software reset
  writeRegister(ADNS_RESET, 0x5A);
  delay(50);
}

// Read the Product ID
byte ADNS5050::getProductID() {
  return readRegister(ADNS_PRODUCT_ID);
}

// Check if the sensor is properly connected
bool ADNS5050::checkConnection() {
  byte productID = getProductID();
  // ADNS5050 Product ID should be 0x12
  return (productID == 0x12);
}

// Check if motion has been detected
bool ADNS5050::isMotionDetected() {
  byte motion = readRegister(ADNS_MOTION);
  return (motion & 0x80); // Check if motion bit (bit 7) is set
}

// Get the X and Y motion delta values
void ADNS5050::getMotion(int16_t *deltaX, int16_t *deltaY) {
  // Read the X and Y delta values if motion is detected
  if (isMotionDetected()) {
    *deltaX = (int8_t)readRegister(ADNS_DELTA_X);
    *deltaY = -(int8_t)readRegister(ADNS_DELTA_Y); // Invert Y for screen coordinates
  } else {
    *deltaX = 0;
    *deltaY = 0;
  }
}

// Set the performance mode
void ADNS5050::setPerformanceMode(byte mode) {
  writeRegister(ADNS_PERFORMANCE, mode);
}

// Set the sample rate
void ADNS5050::setSampleRate(byte rate) {
  writeRegister(ADNS_MOUSE_CONTROL, rate);
}

// Read a register value
byte ADNS5050::readRegister(byte addr) {
  byte data = 0;
  
  // Begin SPI transaction
  digitalWrite(_ncs, LOW);
  delayMicroseconds(1);
  
  // Write address
  for (byte i = 0; i < 8; i++) {
    digitalWrite(_sclk, LOW);
    digitalWrite(_sdio, (addr & (1 << (7 - i))) ? HIGH : LOW);
    delayMicroseconds(1);
    digitalWrite(_sclk, HIGH);
    delayMicroseconds(1);
  }
  
  // Switch SDIO to input mode
  pinMode(_sdio, INPUT);
  delayMicroseconds(2);
  
  // Read data
  for (byte i = 0; i < 8; i++) {
    digitalWrite(_sclk, LOW);
    delayMicroseconds(1);
    digitalWrite(_sclk, HIGH);
    delayMicroseconds(1);
    
    // Read bit
    if (digitalRead(_sdio)) {
      data |= (1 << (7 - i));
    }
  }
  
  // End SPI transaction
  digitalWrite(_ncs, HIGH);
  
  // Switch SDIO back to output mode
  pinMode(_sdio, OUTPUT);
  
  return data;
}

// Write a value to a register
void ADNS5050::writeRegister(byte addr, byte data) {
  // Begin SPI transaction
  digitalWrite(_ncs, LOW);
  delayMicroseconds(1);
  
  // Write address with write flag
  addr |= 0x80;  // MSB = 1 for write
  for (byte i = 0; i < 8; i++) {
    digitalWrite(_sclk, LOW);
    digitalWrite(_sdio, (addr & (1 << (7 - i))) ? HIGH : LOW);
    delayMicroseconds(1);
    digitalWrite(_sclk, HIGH);
    delayMicroseconds(1);
  }
  
  // Write data
  for (byte i = 0; i < 8; i++) {
    digitalWrite(_sclk, LOW);
    digitalWrite(_sdio, (data & (1 << (7 - i))) ? HIGH : LOW);
    delayMicroseconds(1);
    digitalWrite(_sclk, HIGH);
    delayMicroseconds(1);
  }
  
  // End SPI transaction
  digitalWrite(_ncs, HIGH);
}