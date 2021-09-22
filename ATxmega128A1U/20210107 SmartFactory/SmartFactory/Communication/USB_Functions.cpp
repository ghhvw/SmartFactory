/*
 * USB_Functions.cpp
 *
 * Created: 2-6-2020 14:32:49
 *  Author: Nick
 */ 

#include "USB_Functions.h"
#include <asf.h>


void USB_Transmit(const char data )
{
	//while(!udi_cdc_is_tx_ready())
	//{
	udi_cdc_putc(data);
	//}
}

char USB_Receive()
{
	// 	/* Wait for data to be received */
	while (!udi_cdc_is_rx_ready());
	// 	/* Get and return received data from buffer */
	return udi_cdc_getc();
}

char USB_Receive(uint16_t timeout, bool& isTimedOut )
{
	/* Wait for data to be received */
	for(uint16_t i = 0; i < timeout; i++)
	{
		if(udi_cdc_is_rx_ready())
		{
			/* Get and return received data from buffer */
			return udi_cdc_getc();
		}

		_delay_us(1);
	}
	
	isTimedOut = true;
	return 0;
}

bool USB_Available()
{
	return (udi_cdc_is_tx_ready());
}


void USB_TransmitString(const char* str)
{
	for(uint8_t i = 0; str[i]; i++)
	USB_Transmit(str[i]);
}


void USB_Transmit(const char* buff, uint8_t length)
{
	for(uint8_t i = 0; i < length; i++)
	USB_Transmit(buff[i]);
}


void USB_Transmit_Hex(const char data )
{
	USB_TransmitString("0x");
	USB_Transmit(HexToASCII(data>>4));
	USB_Transmit(HexToASCII(data));
}


void USB_Transmit_Number(int16_t num)
{
	if(num < 0)
	{
		num = -num;
		USB_Transmit('-');
	}

	bool started = false;
	uint8_t ten_thousands	= (num/10000);
	if(ten_thousands > 0)
	{
		USB_Transmit('0'+ten_thousands);
		started = true;
	}

	uint8_t thousands	= (num/1000)%10;
	if(thousands > 0)
	{
		USB_Transmit('0'+thousands);
		started = true;
	}

	uint8_t hundreds	= (num/100)%10;
	if(hundreds > 0 || started)
	{
		USB_Transmit('0'+hundreds);
		started = true;
	}

	uint8_t tens		= (num/10)%10;
	if(tens > 0 || started)
	{
		USB_Transmit('0'+tens);
		started = true;
	}
	
	USB_Transmit('0' + (num%10));
}
