/*
 * Convert.h
 *
 * Created: 6-12-2017 13:43:33
 *  Author: TD1
 */ 


#ifndef CONVERT_H_
#define CONVERT_H_

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



uint8_t hexToByte(char h, char l)
{
	return (hexToNibble(h) << 4) | hexToNibble(l);
}


#endif /* CONVERT_H_ */