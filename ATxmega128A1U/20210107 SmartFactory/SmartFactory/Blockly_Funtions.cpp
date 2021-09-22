/*
 * Blockly_Funtions.cpp
 *
 * Created: 3-6-2020 16:26:07
 *  Author: Nick
 */ 

#include "Blockly_Functions.h"

void delay1sec()
{
	_delay_ms(1000);
	return;
}


void delay_ms(uint16_t ms)
{
	for(uint16_t i = 0; i < ms; i++)
	_delay_ms(1);
	return;
}



void printNumber(uint16_t num)
{
	USART_Transmit_Number(USARTD0, num);
	USART_TransmitString(USARTD0, "\n\r");
}


uint16_t invert(uint16_t num)
{
	return -num;
}



int16_t add(int16_t A, int16_t B)
{
	long res = (long)A + B;

	if(res > 32767)
	return 32767;
	if(res < -32768)
	return -32767;

	return (int16_t)res;
}


int16_t subtract(int16_t A, int16_t B)
{
	long res = (long)A - B;

	if(res > 32767)
	return 32767;
	if(res < -32768)
	return -32767;

	return (int16_t)res;
}


int16_t multiply(int16_t A, int16_t B)
{
	long res = (long)A * B;

	if(res > 32767)
	return 32767;
	if(res < -32768)
	return -32767;

	return (int16_t)res;
}


int16_t divide(int16_t A, int16_t B)
{
	return A / B;
}


bool isEqual(int16_t A, int16_t B)			{return A == B; }
bool isBigger(int16_t A, int16_t B)			{return A > B;	}
bool isSmaller(int16_t A, int16_t B)		{return A < B;	}
bool isBiggerOrEqual(int16_t A, int16_t B)	{return A >= B;	}
bool isSmallerOrEqual(int16_t A, int16_t B)	{return A <= B; }

bool logic_or(bool A, bool B)	{return A || B; }
bool logic_and(bool A, bool B)	{return A && B; }
bool logic_xor(bool A, bool B)	{return A ^ B;  }