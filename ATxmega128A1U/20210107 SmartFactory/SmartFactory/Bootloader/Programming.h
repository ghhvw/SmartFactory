/*
 * Programming.h
 *
 * Created: 2-6-2020 15:15:09
 *  Author: Nick
 */ 


#ifndef PROGRAMMING_H_
#define PROGRAMMING_H_

#include <stdint.h>
#include <avr/io.h>
#include "sp_driver.h"
#include "USB_Functions.h"
#include "UART.h"
#include "TWI.h"
#include "Convert.h"

#define DATA_RECORD 0
#define EOF_RECORD	1

#define LOWER_ADDRESS_LIMIT	0x8000
#define UPPER_ADDRESS_LIMIT	0xFFFE

void resetDevice();
void getUsbBoot();
void receiveHexFileUSB();
void receiveHexFileI2C(void (*cb)());
void programHexLine(char* line);
void programFlash(uint8_t byteCount, uint16_t address, uint8_t recordType, uint8_t* data);


#endif /* PROGRAMMING_H_ */