/*
 * IO_mappings.h
 *
 * This file contains the mapping of the smartfactory IO ports (relays, optocouplers and direct I/O)
 *
 * Created: 10-8-2021 10:12:56
 *  Author: Sjors Smit
 */ 

#ifndef IO_MAPPINGS_H_
#define IO_MAPPINGS_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr_compiler.h>

typedef enum gpioModes{
	GPIO_MODE_INPUT=0,
	GPIO_MODE_OUTPUT=1
}gpioModes_t;

// Bitmask for the Direct digital I/O, PORTK pins 2:7 and the 3v/5v level shifting pins on PORTK 0:1
#define _3V5VDIO0	PIN0_bm		//PK0
#define _3V5VDIO1	PIN1_bm		//PK1

#define DIO0		PIN2_bm		//PK2
#define DIO1		PIN3_bm		//PK3
#define DIO2		PIN4_bm		//PK4
#define DIO3		PIN5_bm		//PK5
#define DIO4		PIN6_bm		//PK6
#define DIO5		PIN7_bm		//PK7

//Methods for PORTK pins:
/**
 * \brief set the mode of a GPIO pin on the PORTK register to input or output
 * 
 * \param pin the pin to set to (DIO0, DIO2, etc)
 * \param mode The mode to set the pin to
 * 
 * \return int8_t 0 for wrote to input, 1 for wrote to output, -1 for invalid input
 */
void gpioSetMode(uint8_t pin, gpioModes_t mode);


/**
 * \brief write the level of a digital output pin
 * 
 * \param pin pin to read (DIO0, DIO2, etc)
 * \param level 
 * 
 */
void gpioSetLevel(uint8_t pin, bool level);

/**
 * \brief read the level of an input pin
 * 
 * \param pin the pin (DIO0, DIO2, etc)
 * 
 * \return bool true (high) or false (low)
 */
bool gpioGetLevel(uint8_t pin);

//Bitmask for the Logic Level Shifting GPIO pins:

#define _12V5VDIO0		PIN0_bm		//PH0
#define _12V5VDIO1		PIN1_bm		//PH1
#define _12V5VDIO2		PIN6_bm		//PJ6
#define _12V5VDIO3		PIN7_bm		//PJ7

/**
 * \brief set the mode of a 5/12V logic shifting GPIO pin to input or output
 * 
 * \param pin the pin to set to (_12V5VDIO0 etc)
 * \param mode The mode to set the pin to
 * 
 * \return int8_t 0 for wrote to input, 1 for wrote to output, -1 for invalid input
 */
int8_t logicSetMode(uint8_t pin, gpioModes_t mode);

/**
 * \brief write the level of a digital output pin
 * 
 * \param pin - pin to write (_12V5VDIO0 etc)
 * \param level - High or low
 * 
 * \return uint8_t
 */
uint8_t logicSetLevel(uint8_t pin, bool level);

/**
 * \brief read the level of a digital input pin
 * 
 * \param pin pin to write (_12V5VDIO0 etc)
 * 
 * \return uint8_t
 */
bool logicGetLevel(uint8_t pin);

#endif /* IO_MAPPINGS_H_ */