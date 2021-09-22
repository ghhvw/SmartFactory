/*
 * SPI.cpp
 *
 * Created: 19-3-2020 10:06:39
 *  Author: Nick
 */
#define F_CPU 32000000

#include "SPI.h"
#include <util/delay.h>

void SPI_Init(SPI_struct &SPI)
{
	//enable SPI, Set master mode, 8MHz default Clock
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER0_bm;
}

uint8_t SPI_Tranciever(SPI_struct &SPI, uint8_t data)
{
	//load data into data buffer
	SPI.DATA = data;
	//wait for transmit complete
	while (!(SPI.STATUS & (1<<SPI_IF_bp)));
	
	//return received data
	return(SPI.DATA);		
}

void SS_set_high(PORT_struct &PORT, uint8_t pin)
{
	PORT.OUTSET = (1<<pin);
	_delay_us(1);
}

void SS_set_low(PORT_struct &PORT, uint8_t pin)
{
	PORT.OUTCLR = (1<<pin);
	_delay_us(1);
}

uint8_t SPI_CAN_Read(SPI_struct &SPI, uint8_t address, uint8_t read_cmd)
{
	SPI_Tranciever(SPI, read_cmd);
	SPI_Tranciever(SPI, address);
	uint8_t data = SPI_Tranciever(SPI, 0x00);
	return data;
}

void SPI_CAN_write(SPI_struct &SPI, uint8_t address, uint8_t data, uint8_t write_cmd)
{
	SPI_Tranciever(SPI, write_cmd);
	SPI_Tranciever(SPI, address);
	SPI_Tranciever(SPI, data);
}
