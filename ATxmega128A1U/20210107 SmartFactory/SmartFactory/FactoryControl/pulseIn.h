/*
 * pulseIn.h
 *
 * Created: 05/12/2020 21:49:59
 *  Author: Wout
 */ 


#ifndef PULSEIN_H_
#define PULSEIN_H_

#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU 24000000 //Hz, 24MHz
#endif



#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )
unsigned long pulseIn(PORT_struct *port, uint8_t pin_bm, uint8_t state, unsigned long timeout);


#ifdef __cplusplus
}
#endif

#endif /* PULSEIN_H_ */