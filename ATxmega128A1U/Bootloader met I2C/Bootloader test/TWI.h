/*
 * TWI.h
 *
 * Created: 19-3-2020 12:02:29
 *  Author: Nick
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdint.h>
#include <avr/io.h>

void TWI_init(TWI_struct &TWI, uint8_t address);
bool TWI_RecievedAddress(TWI_struct &TWI);
bool TWI_ReceivePacket(TWI_struct &TWI, uint8_t* buffer, uint8_t bufferLength);

#endif /* TWI_H_ */