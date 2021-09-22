/*
 * Solenoid.h
 *
 * Created: 4-6-2020 10:36:55
 *  Author: Nick
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "relays.h"

void Solenoid(uint8_t solenoid, bool InOut)
{
	set_relay(InOut,solenoid);
}

void PulseSolenoid(uint8_t solenoid)
{
	set_relay(1,solenoid);
	_delay_ms(200);
	set_relay(0,solenoid);
}

#endif /* SOLENOID_H_ */