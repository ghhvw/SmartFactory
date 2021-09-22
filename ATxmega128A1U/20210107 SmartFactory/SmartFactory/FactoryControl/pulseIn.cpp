/*
 * pulseIn.cpp
 *
 * Created: 05/12/2020 21:49:21
 *  Author: Wout
 */ 

#include "pulseIn.h"


unsigned long pulseIn(PORT_struct *port, uint8_t pin_bm, uint8_t state, unsigned long timeout)
{
	uint8_t stateMask = (state ? pin_bm : 0); // The stateMask is a variable to check if the bit coresponds to the pin is 0 or 1. When the state is 0, it is set to 0 to measure the time of LOW state. If the state i not 0, it is set to bitmask of the pin. 
	unsigned long width = 0; // keep initialization out of time critical area
	
	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes 16 clock cycles per iteration.
	unsigned long numloops = 0;
	unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;
	
	// wait for any previous pulse to end
	while ((port->IN & pin_bm) == stateMask) {
		if (numloops++ == maxloops) { return 0; }
	}
	
	// wait for the pulse to start
	while ((port->IN & pin_bm) != stateMask) {
		if (numloops++ == maxloops) { return 0; }
	}
	
	// wait for the pulse to stop
	while ((port->IN & pin_bm) == stateMask) {
		if (numloops++ == maxloops) { return 0; }
		width++;
	}

	// convert the reading to microseconds. The loop has been determined
	// to be 20 clock cycles long and have about 16 clocks between the edge
	// and the start of the loop. There will be some error introduced by
	// the interrupt handlers.
	return clockCyclesToMicroseconds(width * 21 + 16);
}