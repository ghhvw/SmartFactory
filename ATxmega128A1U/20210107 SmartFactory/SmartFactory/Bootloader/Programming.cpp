/*
 * Programming.cpp
 *
 * Created: 3-6-2020 13:35:25
 *  Author: Nick
 */

 #include "Programming.h"

void resetDevice()
{
	//disable interrupts
	asm("cli");
	// enable watchdog timer
	CCP = 0xD8;
	WDT.CTRL = (1<< WDT_ENABLE_bp)| (1<<WDT_CEN_bp);
	// let the watchdog time out
	while(true);
}

void getUsbBoot()
{
	bool timeout = true;
	char* check = "ABCD";

	for(uint16_t t = 0; t < 10000; t++)
	{
		if(USART_Available(USARTD0))
		{
			timeout = false;
			break;
		}
		if(TWI_RecievedAddress(TWIC))
		{
			return;
		}
		
		_delay_us(100);
	}

	if(timeout)
	return;

	for(uint8_t i = 0; i < 4; i++)
	{
		char c = USART_Receive(USARTD0);
		//USART0_Transmit(c);
		if(c != check[i])
		return;
	}


	switch(USART_Receive(USARTD0))
	{
		case 'U':
		// upload hex file via usb
		USART_TransmitString(USARTD0,"Receiving program via UART\n\r");
		//USB_TransmitString("Receiving program via UART\n\r");
		receiveHexFileUSB();
		break;
		default:
		break;
	}
}

void receiveHexFileUSB()
{
	char buff[50];

	while(true)
	{
		// receive a line of the hex file
		for(uint8_t i = 0; i < 50; i++)
		{
			char c = USART_Receive(USARTD0);
			buff[i] = c;
			if(c == '\n')
			{
				buff[i+1] = '\0';
				break;
			}
		}
		programHexLine(buff);
	}
}

void receiveHexFileI2C(void (*cb)())
{
	char buff[50];

	while(true)
	{
		USART_TransmitString(USARTD0, "\n\rtest4\n\r");
		// receive a line of the hex file
		TWI_ReceivePacket(TWIC,(uint8_t*)buff, 50);
		
		if(buff[0] == 's') { cb(); } //voer callback uit: stepper-test modus
			
		if(buff[0] != ':')
		{
			USART_TransmitString(USARTD0,"Error while receiving program");
			return;
		}
		USART_TransmitString(USARTD0,"test");
		programHexLine(buff);
	}
}

void programHexLine(char* line)
{
	cli();
	// parse the line
	uint8_t byteCount	= hexToByte(line[1], line[2]);
	uint8_t address_H	= hexToByte(line[3], line[4]);
	uint8_t address_L	= hexToByte(line[5], line[6]);
	uint8_t recordType	= hexToByte(line[7], line[8]);

	uint8_t checksum = byteCount + address_H + address_L + recordType;
	uint8_t data[16];

	// loop through data bytes
	for(uint8_t i = 0; i < byteCount; i++)
	{
		uint8_t charOffset = 9+2*i;
		uint8_t byte = hexToByte(line[charOffset], line[charOffset+1]);
		checksum += byte;
		data[i] = byte;
	}

	checksum += hexToByte(line[9+2*byteCount],line[10+2*byteCount]);
	
	if(checksum != 0)
	{
		USART_TransmitString(USARTD0, "\n\rChecksum error while receiving program\n\rResetting");
		//USB_TransmitString("\n\rChecksum error while receiving program\n\rResetting");
		resetDevice();
		return;
	}
	
	USART_TransmitString(USARTD0, "\r\nReceived: ");
	USART_Transmit(USARTD0, line, 11+2*byteCount);
	
	//USB_TransmitString("\r\nReceived: ");
	//USB_Transmit(line, 11+2*byteCount);
		
	programFlash(byteCount, ((uint16_t)(address_H << 8)) | address_L, recordType, data);
}


void programFlash(uint8_t byteCount, uint16_t address, uint8_t recordType, uint8_t* data)
{
	static uint16_t previousAddress = 0xFFFF;
	static bool firstByte = true;

	if(recordType == EOF_RECORD)
	{
		// if the first byte has already been sent
		if(!firstByte)
		{
			// check if the address is within the blockly range
			if(previousAddress < LOWER_ADDRESS_LIMIT || previousAddress > UPPER_ADDRESS_LIMIT)
			{
				USART_TransmitString(USARTD0, "\n\rFlash address:");
				USART_Transmit_Number(USARTD0, previousAddress);
				USART_TransmitString(USARTD0, " out of range\n\rResetting");
				
				//USB_TransmitString("\n\rFlash address:");
				//USB_Transmit_Number(previousAddress);
				//USB_TransmitString(" out of range\n\rResetting");
				resetDevice();
			}
			
			SP_WaitForSPM();	//wait for nvm module if busy
			SP_EraseWriteApplicationPage(previousAddress); //program page to flash
		}
		// reset device
		resetDevice();
	}
	else if(recordType == DATA_RECORD)
	{
		// loop through bytes
		for(uint8_t i = 0; i < byteCount; i+=2)
		{
			// if address is in the another page than the last
			if(previousAddress/SPM_PAGESIZE != address/SPM_PAGESIZE)
			{
				// if this isn't the first byte
				if(!firstByte)
				{
					if(previousAddress < LOWER_ADDRESS_LIMIT || previousAddress > UPPER_ADDRESS_LIMIT)
					{
						USART_TransmitString(USARTD0, "\n\rFlash address:");
						USART_Transmit_Number(USARTD0, previousAddress);
						USART_TransmitString(USARTD0, " out of range\n\rResetting");
						
						//USB_TransmitString("\n\rFlash address:");
						//USB_Transmit_Number(previousAddress);
						//USB_TransmitString(" out of range\n\rResetting");
						
						resetDevice();
					}
					
					SP_WaitForSPM();
					SP_EraseWriteApplicationPage(previousAddress);
				}
			}
			
			//load byte into temporary page buffer
			SP_WaitForSPM();
			SP_LoadFlashWord(address%SPM_PAGESIZE, ((uint16_t)data[i+1] << 8 | data[i]));
				
			// track the programming state
			firstByte = false;
			previousAddress = address;
			address+=2;
		}
	}

}