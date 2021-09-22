/*
 * UART.h
 *
 * Created: 5-3-2020 17:48:29
 *  Author: Nick
 */ 


#ifndef UART_H_
#define UART_H_



char HexToASCII(uint8_t i);

bool usart_set_baudrate(uint32_t baud, uint32_t cpu_hz); //__attribute__ ((section(".boot")));
void USART0_Init( uint32_t baud, uint32_t cpu_hz, bool doubleSpeed ); //__attribute__ ((section(".boot")));

void USART0_Transmit( const char data );  //__attribute__ ((section(".boot")));
void USART0_Transmit( const char* buff, uint8_t length); //__attribute__ ((section(".boot")));
void USART0_Transmit_Number(int16_t num);  //__attribute__ ((section(".boot")));
void USART0_Transmit_Hex( const char data ); // __attribute__ ((section(".boot")));
void USART0_TransmitString(const char* str); //__attribute__ ((section(".boot")));

bool USART0_TransmitDone(); //__attribute__ ((section(".boot")));

bool USART0_Available( void ); // __attribute__ ((section(".boot")));

char USART0_Receive( void );  //__attribute__ ((section(".boot")));
char USART0_Receive( uint16_t timeout, bool& isTimedOut ); //__attribute__ ((section(".boot")));


#endif /* UART_H_ */