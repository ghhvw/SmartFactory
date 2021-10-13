/*
* Relays.h
*
* Created: 4-6-2020 10:35:02
*  Author: Nick & Sjors
*/


#ifndef RELAYS_H_
#define RELAYS_H_

#if DEBUG
#include "UART.h"
#define DEBUG_OUT(x) USART_TransmitString(USARTD0, x)
#else
#define DEBUG_OUT(x)
#endif

//Bitmask for all relays on their corresponding ports
#define RELAY0_bm	PIN1_bm
#define RELAY1_bm	PIN0_bm
#define RELAY2_bm	PIN3_bm
#define RELAY3_bm	PIN2_bm
#define RELAY4_bm	PIN1_bm
#define RELAY5_bm	PIN0_bm


//These are used since the relays are not on the same ports (see Smartfactory helpguide chapter IO)
#define RELAY0_OUTSET	PORTR_OUTSET
#define RELAY1_OUTSET	PORTR_OUTSET
#define RELAY2_OUTSET	PORTQ_OUTSET
#define RELAY3_OUTSET	PORTQ_OUTSET
#define RELAY4_OUTSET	PORTQ_OUTSET
#define RELAY5_OUTSET	PORTQ_OUTSET

#define RELAY0_OUTCLR	PORTR_OUTCLR
#define RELAY1_OUTCLR	PORTR_OUTCLR
#define RELAY2_OUTCLR	PORTQ_OUTCLR
#define RELAY3_OUTCLR	PORTQ_OUTCLR
#define RELAY4_OUTCLR	PORTQ_OUTCLR
#define RELAY5_OUTCLR	PORTQ_OUTCLR


void set_relay(bool value, uint8_t relay)
{
//	DEBUG_OUT("Setting a relay!");
	switch (relay)
	{	
		//Use conditional operator to check for SET or CLR for relay:
		//IMPORTANT: In the ULN2803, signal traces get inverted (Relay0 on Atmega pin label is Relay output marked K6, see schematic sheet 5: "Relays_Optocoupers")
		case 6: value ? RELAY0_OUTSET = RELAY0_bm : RELAY0_OUTCLR = RELAY0_bm; break;
		case 5: value ? RELAY1_OUTSET = RELAY1_bm : RELAY1_OUTCLR = RELAY1_bm; break;
		case 4: value ? RELAY2_OUTSET = RELAY2_bm : RELAY2_OUTCLR = RELAY2_bm; break;
		case 3: value ? RELAY3_OUTSET = RELAY3_bm : RELAY3_OUTCLR = RELAY3_bm; break;
		case 2: value ? RELAY4_OUTSET = RELAY4_bm : RELAY4_OUTCLR = RELAY4_bm; break;
		case 1: value ? RELAY5_OUTSET = RELAY5_bm : RELAY5_OUTCLR = RELAY5_bm; break;
		default: break;
	}
}


#endif /* RELAYS_H_ */