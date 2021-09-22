/*
 * SPI.h
 *
 * Created: 19-3-2020 10:06:24
 *  Author: Nick
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <avr/io.h>

void SPI_Init(SPI_struct &SPI);

uint8_t SPI_Tranciever(SPI_struct &SPI, uint8_t data);

void SS_set_high(PORT_struct &PORT, uint8_t pin);
void SS_set_low(PORT_struct &PORT, uint8_t pin);

uint8_t SPI_CAN_Read(SPI_struct &SPI, uint8_t address, uint8_t read_cmd);
void SPI_CAN_write(SPI_struct &SPI, uint8_t address, uint8_t data, uint8_t write_cmd);



#endif /* SPI_H_ */