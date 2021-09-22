/*
 * UART.h
 *
 * Created: 5-3-2020 17:48:29
 *  Author: Nick
 */ 


#ifndef UART_H_
#define UART_H_


#ifndef F_CPU
#define F_CPU 32000000
#endif


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

char HexToASCII(uint8_t i);

bool USART_Set_Baudrate(USART_struct &USART, uint32_t baud, uint32_t cpu_hz); //set baud rate
void USART_Init(USART_struct &USART, uint32_t baud, uint32_t cpu_hz, bool doubleSpeed);	//Initialize UARTC0
void USART_Transmit(USART_struct &USART, const char data );
char USART_Receive(USART_struct &USART);
char USART_Receive(USART_struct &USART, uint16_t timeout, bool& isTimedOut );
bool USART_Available(USART_struct &USART);

void USART_TransmitString(USART_struct &USART, const char* str);
void USART_Transmit(USART_struct &USART, const char* buff, uint8_t length);
void USART_Transmit_Hex(USART_struct &USART, const char data );
void USART_Transmit_Number(USART_struct &USART, int16_t num);
bool USART_TransmitDone(USART_struct &USART);


#endif /* UART_H_ */