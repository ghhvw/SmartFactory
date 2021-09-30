/*
 * IO_mappings.cpp
 *
 * This file contains the mapping of the smartfactory IO ports (relays, optocouplers and direct I/O)
 *
 * Created: 10-8-2021 10:12:56
 *  Author: Sjors Smit
 */ 
#include "IO_mappings.h"



void gpioSetMode(uint8_t pin, gpioModes_t mode)
{
	//Set the PORTK Direction register using the DIRSET and DIRCLR register
	if(mode == GPIO_MODE_INPUT){
		//Write PORTK_DIR bit 'pin' to 0
		PORTK_DIRCLR = pin;
	}
	else if(mode == GPIO_MODE_OUTPUT){
		PORTK_DIRSET = pin;
	}
}

void gpioSetLevel(uint8_t pin, bool level)
{
	//Set the output level of PORTK using the OUTSET and OUTCLR register
	if(level){
		PORTK_OUTSET = pin;
	}
	else{
		PORTK_OUTCLR = pin;
	}
}

bool gpioGetLevel(uint8_t pin)
{
	
	return ((PORTK_IN & pin) ? 1 : 0);
}
