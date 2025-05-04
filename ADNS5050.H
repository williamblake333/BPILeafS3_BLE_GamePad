/*
 * ADNS5050.h
 * Header file for the ADNS5050 optical mouse sensor
 */

#ifndef ADNS5050_H
#define ADNS5050_H

#include <Arduino.h>

// ADNS5050 Register Definitions
#define ADNS_PRODUCT_ID            0x00
#define ADNS_REVISION_ID           0x01
#define ADNS_MOTION                0x02
#define ADNS_DELTA_X               0x03
#define ADNS_DELTA_Y               0x04
#define ADNS_SQUAL                 0x05
#define ADNS_SHUTTER_UPPER         0x06
#define ADNS_SHUTTER_LOWER         0x07
#define ADNS_MAXIMUM_PIXEL         0x08
#define ADNS_PIXEL_SUM             0x09
#define ADNS_MINIMUM_PIXEL         0x0A
#define ADNS_PIXEL_GRAB            0x0B
#define ADNS_MOUSE_CONTROL         0x0D
#define ADNS_RUN_DOWNSHIFT         0x0E
#define ADNS_REST1_PERIOD          0x0F
#define ADNS_REST1_DOWNSHIFT       0x10
#define ADNS_REST2_PERIOD          0x11
#define ADNS_REST2_DOWNSHIFT       0x12
#define ADNS_REST3_PERIOD          0x13
#define ADNS_PERFORMANCE           0x22
#define ADNS_RESET                 0x3A
#define ADNS_INVERSE_PRODUCT_ID    0x3F
#define ADNS_SERIAL_COM_MODE       0x41

class ADNS5050 {
  private:
    // Pin configurations
    uint8_t _sclk;
    uint8_t _sdio;
    uint8_t _ncs;
    uint8_t _nreset;
    
    // SPI communication methods
    byte readRegister(byte addr);
    void writeRegister(byte addr, byte data);
    
  public:
    // Constructor
    ADNS5050(uint8_t sclk, uint8_t sdio, uint8_t ncs, uint8_t nreset);
    
    // Initialization
    void begin();
    void reset();
    
    // Status methods
    byte getProductID();
    bool checkConnection();
    
    // Motion tracking
    bool isMotionDetected();
    void getMotion(int16_t *deltaX, int16_t *deltaY);
    
    // Configuration
    void setPerformanceMode(byte mode);
    void setSampleRate(byte rate);
};

#endif // ADNS5050_H