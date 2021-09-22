/*
 * TWI.h
 *
 * Created: 19-3-2020 12:02:29
 *  Author: Nick & Wout
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void TWI_HandleISR(void (*TxCallback)(), void (*RxCallback)(uint8_t), TWI_struct &TWI);
void TWI_init(TWI_struct &TWI);
bool TWI_RecievedAddress(TWI_struct &TWI);
bool TWI_ReceivePacket(TWI_struct &TWI, uint8_t* buffer, uint8_t bufferLength);
bool TWI_Write(TWI_struct &TWI, uint8_t byte);
void TWI_onRequest(void (*f)(), TWI_struct &twi);
void TWI_onReceive(void (*f)(uint8_t), TWI_struct &twi);

#endif /* TWI_H_ */