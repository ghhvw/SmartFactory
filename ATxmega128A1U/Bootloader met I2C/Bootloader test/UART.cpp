/*
 * UART.cpp
 *
 * Created: 5-3-2020 17:48:48
 *  Author: Nick
 */ 

#include "UART.h"

char HexToASCII(uint8_t i)
  {
	  i &= 0x0f;
	  if(i > 9)
	  return i+'A'-10;
	  else
	  return i+'0';
  }
 
 bool USART_Set_Baudrate(USART_struct &USART, uint32_t baud, uint32_t cpu_hz)
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

	if (!(USART.CTRLB & USART_CLK2X_bm)) {
		max_rate /= 2;
		min_rate /= 2;
	}

	if ((baud > max_rate) || (baud < min_rate)) {
		return false;
	}

	/* Check if double speed is enabled. */
	if (!(USART.CTRLB & USART_CLK2X_bm)) {
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

	USART.BAUDCTRLB = (uint8_t)(((div >> 8) & 0X0F) | (exp << 4));
	USART.BAUDCTRLA = (uint8_t)div;

	return true;
}
 
 
 void USART_Init(USART_struct &USART, uint32_t baud, uint32_t cpu_hz, bool doubleSpeed)
 {	
	 //set TX pin to output
	// PORTC_DIR |= (1 << 3);
	 //PORTF_DIR |= (1 << 3);
	 /* Set baud rate */
	 USART_Set_Baudrate(USART, baud,cpu_hz);
	 _delay_ms(10); // wait for stable clock
	 USART.CTRLA = (1 << USART_RXCINTLVL1_bp)|(1 << USART_TXCINTLVL1_bp)|(1 << USART_DREINTLVL1_bp);
	 USART.CTRLB = (1 << USART_RXEN_bp)|(1 << USART_TXEN_bp); 
 }

void USART_Transmit(USART_struct &USART, const char data )
{
	/* Wait for empty transmit buffer */
	while ( !( USART.STATUS & (1<<USART_DREIF_bp)) );
	/* Put data into buffer, sends the data */
	USART.DATA = data;
}

char USART_Receive(USART_struct &USART)
{
	/* Wait for data to be received */
	while ( !(USART.STATUS & (1<<USART_RXCIF_bp)));
	/* Get and return received data from buffer */
	return USART.DATA;
}

char USART_Receive(USART_struct &USART, uint16_t timeout, bool& isTimedOut )
{
	/* Wait for data to be received */
	for(uint16_t i = 0; i < timeout; i++)
	{
		if(USART.STATUS & (1<<USART_RXCIF_bp))
		{
			/* Get and return received data from buffer */
			return USART.DATA;
		}

		_delay_us(1);
	}
	 
	isTimedOut = true;
	return 0;
}

 bool USART_Available(USART_struct &USART)
 {
	 return (USART.STATUS & (1<<USART_RXCIF_bp));
 }


 void USART_TransmitString(USART_struct &USART, const char* str)
 {
	 for(uint8_t i = 0; str[i]; i++)
	 USART_Transmit(USART, str[i]);
 }


 void USART_Transmit(USART_struct &USART, const char* buff, uint8_t length)
 {
	 for(uint8_t i = 0; i < length; i++)
	 USART_Transmit(USART, buff[i]);
 }

 
 void USART_Transmit_Hex(USART_struct &USART, const char data )
 {
	 USART_TransmitString(USART, "0x");
	 USART_Transmit(USART, HexToASCII(data>>4));
	 USART_Transmit(USART, HexToASCII(data));
 }


 void USART_Transmit_Number(USART_struct &USART, int16_t num)
 {
	 if(num < 0)
	 {
		 num = -num;
		 USART_Transmit(USART, '-');
	 }

	 bool started = false;
	 uint8_t ten_thousands	= (num/10000);
	 if(ten_thousands > 0)
	 {
		 USART_Transmit(USART, '0'+ten_thousands);
		 started = true;
	 }

	 uint8_t thousands	= (num/1000)%10;
	 if(thousands > 0)
	 {
		 USART_Transmit(USART, '0'+thousands);
		 started = true;
	 }

	 uint8_t hundreds	= (num/100)%10;
	 if(hundreds > 0 || started)
	 {
		 USART_Transmit(USART, '0'+hundreds);
		 started = true;
	 }

	 uint8_t tens		= (num/10)%10;
	 if(tens > 0 || started)
	 {
		 USART_Transmit(USART, '0'+tens);
		 started = true;
	 }
	 
	 USART_Transmit(USART, '0' + (num%10));
 }
 


bool USART_TransmitDone(USART_struct &USART)
{
	return USART.STATUS & (1<<USART_DREIF_bp);
}