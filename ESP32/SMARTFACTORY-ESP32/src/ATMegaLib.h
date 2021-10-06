// Global libraries
#include <stdint.h>
#include <stddef.h>
#include <Wire.h>
#include <HardwareSerial.h>

// Project libraries

// Custom files

// Methods
void resetATmega();
void programATmega(uint8_t *data, size_t length);
uint8_t getATmegaStatus();
void setATmegaStatus(uint8_t i);
bool getTransmissionRunning();
void setTransmissionRunning(bool i);
void testStepperDrivers();
bool writeATmegaIfAvailable(uint8_t* buffer, uint8_t bufferLength);
void writeATmega(uint8_t* buffer, uint8_t bufferLength);
void requestATmegaStatus();
uint8_t readATmegaReply();