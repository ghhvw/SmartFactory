/*
 * UART.h
 *
 * Created: 18-3-2020 10:18:32
 *  Author: Nick
 */ 


#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
#define F_CPU 24000000
#endif


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

char HexToASCII(uint8_t i);

bool USART_Set_Baudrate(USART_struct &USART, uint32_t baud, uint32_t cpu_hz); //set baud rate
void USART_Init(USART_struct &USART, uint32_t baud, uint32_t cpu_hz, bool doubleSpeed);	//Initialize UART
void USART_Transmit(USART_struct &USART, const char data ); //Transmit single char
char USART_Receive(USART_struct &USART); //Receive single char
char USART_Receive(USART_struct &USART, uint16_t timeout, bool& isTimedOut ); //Receive single char with receive timeout
bool USART_Available(USART_struct &USART); //Check for received data
void USART_TransmitString(USART_struct &USART, const char* str); //Transmit String
void USART_Transmit(USART_struct &USART, const char* buff, uint8_t length); //Transmit array
void USART_Transmit_Hex(USART_struct &USART, const char data ); //Transmit number in HEX format: 0x[HEX NUMBER]
void USART_Transmit_Number(USART_struct &USART, int16_t num); //Transmit number
bool USART_TransmitDone(USART_struct &USART); //Check if transmit completed

//void USART_Transmit(USART_struct &USART, const unsigned char data );
//inline unsigned char USART_Receive(USART_struct &USART);




#endif /* UART_H_ */