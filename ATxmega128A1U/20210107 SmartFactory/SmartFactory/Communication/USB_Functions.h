/*
 * USB_Functions.h
 *
 * Created: 2-6-2020 14:28:17
 *  Author: Nick
 */ 


#ifndef USB_FUNCTIONS_H_
#define USB_FUNCTIONS_H_

#ifndef F_CPU
#define  F_CPU 24000000
#endif


#include <stdint.h>
#include <util/delay.h>

char HexToASCII(uint8_t i);

void USB_Transmit(const char data );
char USB_Receive();
char USB_Receive(uint16_t timeout, bool& isTimedOut );
bool USB_Available();
void USB_TransmitString(const char* str);
void USB_Transmit(const char* buff, uint8_t length);
void USB_Transmit_Hex(const char data );
void USB_Transmit_Number(int16_t num);

#endif /* USB_FUNCTIONS_H_ */