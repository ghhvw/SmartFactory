/*
 * Convert.cpp
 *
 * Created: 3-6-2020 14:33:01
 *  Author: Nick
 */ 

#include "Convert.h"

uint8_t hexToByte(char h, char l)
{
	return (hexToNibble(h) << 4) | hexToNibble(l);
}

uint8_t hexToNibble(char hex)
{
	if(hex >= '0' && hex <= '9')
	{
		return hex-'0';
	}
	else if(hex >= 'A' && hex <= 'F')
	{
		return hex-'A'+10;
	}
	else if(hex >= 'a' && hex <= 'f')
	{
		return hex-'a'+10;
	}
	return 0xff;
}


