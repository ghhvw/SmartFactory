/*
 * UART.cpp
 *
 * Created: 5-3-2020 17:48:48
 *  Author: Nick
 */ 
#define F_CPU 32000000

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

char HexToASCII(uint8_t i)
  {
	  i &= 0x0f;
	  if(i > 9)
	  return i+'A'-10;
	  else
	  return i+'0';
  }
 
 void USART0_Init(uint32_t baud, uint32_t cpu_hz, bool doubleSpeed)
 {	
	 //set TX pin to output
	 PORTC_DIR |= (1 << 3);
	 /* Set baud rate */
	 //UBRR1H = (unsigned char)(ubrr>>8);
	 //UBRR1L = (unsigned char)ubrr;
	 //USARTC0_BAUDCTRLB |= (unsigned char)(ubrr>>8);
	 //USARTC0_BAUDCTRLA = (unsigned char)ubrr;
	 usart_set_baudrate(baud,cpu_hz);
	 _delay_ms(10); // wait for stable clock
	 //if(doubleSpeed)
	 //UCSR1A |= 1 << U2X1;
	 /* Enable receiver and transmitter */
	 //UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	 /* Set frame format: 8data, 2stop bit */
	 //UCSR1C = (1<<USBS1)|(3<<UCSZ10);
	 USARTC0_CTRLA = (1 << USART_RXCINTLVL1_bp)|(1 << USART_TXCINTLVL1_bp)|(1 << USART_DREINTLVL1_bp);
	 USARTC0_CTRLB = (1 << USART_RXEN_bp)|(1 << USART_TXEN_bp);
	 //USARTC0_CTRLC = (1 << USART_SBMODE_bp);
	 
 }


 bool USART0_Available()
 {
	 return (USARTC0_STATUS & (1<<USART_RXCIF_bp));
 }

void USART0_Transmit( const char data )
 {
	 /* Wait for empty transmit buffer */
	 while ( !( USARTC0_STATUS & (1<<USART_DREIF_bp)) );
	 /* Put data into buffer, sends the data */
	 USARTC0_DATA = data;
 }


 char USART0_Receive( void )
 {
	 /* Wait for data to be received */
	 while ( !(USARTC0_STATUS & (1<<USART_RXCIF_bp)));
	 /* Get and return received data from buffer */
	 //USART0_Transmit_Hex(USARTC0_STATUS);
	 return USARTC0_DATA;
 }

 char USART0_Receive( uint16_t timeout, bool& isTimedOut )
 {
	 /* Wait for data to be received */
	 for(uint16_t i = 0; i < timeout; i++)
	 {
		 if(USARTC0_STATUS & (1<<USART_RXCIF_bp))
		 {
			 /* Get and return received data from buffer */
			 return USARTC0_DATA;
		 }

		 _delay_us(1);
	 }
	 
	 isTimedOut = true;
	 return 0;
 }


 void USART0_TransmitString(const char* str)
 {
	 for(uint8_t i = 0; str[i]; i++)
	 USART0_Transmit(str[i]);
 }



 void USART0_Transmit( const char* buff, uint8_t length)
 {
	 for(uint8_t i = 0; i < length; i++)
	 USART0_Transmit(buff[i]);
 }

 bool USART0_TransmitDone()
 {
	 return USARTC0_STATUS & (1<<USART_DREIF_bp);
 }
 
 void USART0_Transmit_Hex( const char data )
 {
	 USART0_TransmitString("0x");
	 USART0_Transmit(HexToASCII(data>>4));
	 USART0_Transmit(HexToASCII(data));
 }


 void USART0_Transmit_Number(int16_t num)
 {
	 if(num < 0)
	 {
		 num = -num;
		 USART0_Transmit('-');
	 }

	 bool started = false;
	 uint8_t ten_thousands	= (num/10000);
	 if(ten_thousands > 0)
	 {
		 USART0_Transmit('0'+ten_thousands);
		 started = true;
	 }

	 uint8_t thousands	= (num/1000)%10;
	 if(thousands > 0)
	 {
		 USART0_Transmit('0'+thousands);
		 started = true;
	 }

	 uint8_t hundreds	= (num/100)%10;
	 if(hundreds > 0 || started)
	 {
		 USART0_Transmit('0'+hundreds);
		 started = true;
	 }

	 uint8_t tens		= (num/10)%10;
	 if(tens > 0 || started)
	 {
		 USART0_Transmit('0'+tens);
		 started = true;
	 }
	 
	 USART0_Transmit('0' + (num%10));
 }
 
 
 
 bool usart_set_baudrate(uint32_t baud, uint32_t cpu_hz)
{
	int8_t exp;
	uint32_t div;
	uint32_t limit;
	uint32_t ratio;
	uint32_t min_rate;
	uint32_t max_rate;

	/*
	 * Check if the hardware supports the given baud rate
	 */
	/* 8 = (2^0) * 8 * (2^0) = (2^BSCALE_MIN) * 8 * (BSEL_MIN) */
	max_rate = cpu_hz / 8;
	/* 4194304 = (2^7) * 8 * (2^12) = (2^BSCALE_MAX) * 8 * (BSEL_MAX+1) */
	min_rate = cpu_hz / 4194304;

	if (!(USARTC0_CTRLB & USART_CLK2X_bm)) {
		max_rate /= 2;
		min_rate /= 2;
	}

	if ((baud > max_rate) || (baud < min_rate)) {
		return false;
	}

	/* Check if double speed is enabled. */
	if (!(USARTC0_CTRLB & USART_CLK2X_bm)) {
		baud *= 2;
	}

	/* Find the lowest possible exponent. */
	limit = 0xfffU >> 4;
	ratio = cpu_hz / baud;

	for (exp = -7; exp < 7; exp++) {
		if (ratio < limit) {
			break;
		}

		limit <<= 1;

		if (exp < -3) {
			limit |= 1;
		}
	}

	/*
	 * Depending on the value of exp, scale either the input frequency or
	 * the target baud rate. By always scaling upwards, we never introduce
	 * any additional inaccuracy.
	 *
	 * We are including the final divide-by-8 (aka. right-shift-by-3) in
	 * this operation as it ensures that we never exceeed 2**32 at any
	 * point.
	 *
	 * The formula for calculating BSEL is slightly different when exp is
	 * negative than it is when exp is positive.
	 */
	if (exp < 0) {
		/* We are supposed to subtract 1, then apply BSCALE. We want to
		 * apply BSCALE first, so we need to turn everything inside the
		 * parenthesis into a single fractional expression.
		 */
		cpu_hz -= 8 * baud;

		/* If we end up with a left-shift after taking the final
		 * divide-by-8 into account, do the shift before the divide.
		 * Otherwise, left-shift the denominator instead (effectively
		 * resulting in an overall right shift.)
		 */
		if (exp <= -3) {
			div = ((cpu_hz << (-exp - 3)) + baud / 2) / baud;
		} else {
			baud <<= exp + 3;
			div = (cpu_hz + baud / 2) / baud;
		}
	} else {
		/* We will always do a right shift in this case, but we need to
		 * shift three extra positions because of the divide-by-8.
		 */
		baud <<= exp + 3;
		div = (cpu_hz + baud / 2) / baud - 1;
	}

	USARTC0_BAUDCTRLB = (uint8_t)(((div >> 8) & 0X0F) | (exp << 4));
	USARTC0_BAUDCTRLA = (uint8_t)div;

	return true;
}