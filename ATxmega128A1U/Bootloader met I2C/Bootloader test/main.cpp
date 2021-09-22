/*
 * Bootloader test.cpp
 *
 * Created: 5-3-2020 17:24:50
 * Author : Nick
 */ 

#define F_CPU 32000000

#include "sp_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include <limits.h>
#include "UART.h"
#include <inttypes.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "Convert.h"
#include "TWI.h"


void ToggleLED();
void resetDevice();

#define DATA_RECORD 0
#define EOF_RECORD	1

#define LOWER_ADDRESS_LIMIT	0x4000
#define UPPER_ADDRESS_LIMIT	0x7FFF

void getUsbBoot();
void receiveHexFileUSB();
void receiveHexFileI2C();
void programHexLine(char* line);
void programFlash(uint8_t byteCount, uint16_t address, uint8_t recordType, uint8_t* data);

// functions that are accessible to blockly
void delay_ms(uint16_t ms);
void delay1sec();
void printNumber(uint16_t num);
uint16_t invert(uint16_t num);

int16_t add(int16_t A, int16_t B);
int16_t subtract(int16_t A, int16_t B);
int16_t multiply(int16_t A, int16_t B);
int16_t divide(int16_t A, int16_t B);

bool isEqual(int16_t A, int16_t B);
bool isBigger(int16_t A, int16_t B);
bool isSmaller(int16_t A, int16_t B);
bool isBiggerOrEqual(int16_t A, int16_t B);
bool isSmallerOrEqual(int16_t A, int16_t B);

bool logic_or(bool A, bool B);
bool logic_and(bool A, bool B);
bool logic_xor(bool A, bool B);


int main(void)
{
	TWI_init(TWIC,0x20);
	
	OSC_CTRL |= OSC_RC32MEN_bm; //Setup 32Mhz crystal
	
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));
	
	CCP = CCP_IOREG_gc; //Trigger protection mechanism
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc; //Enable internal  32Mhz crystal
	
	PORTA_PIN0CTRL = (1<<PORT_OPC0_bp )|(1<<PORT_OPC1_bp);
	//PORTA_INTCTRL = 0b00000011;
	//PORTA_INT0MASK |= (1<<0);
	
	PORTD_DIRSET = 0b00001000;
	
	PORTH_DIR |= (1 << 4)|(1<<5);
	PORTH_OUTSET |= (1 << 4)|(1<<5);
	//PORTQ_PIN3CTRL |= (1<<PORT_ISC1_bp);
	
	
	USART_Init(USARTD0, 115200, 32000000, false);
	USART_TransmitString(USARTD0, "\n\r------------------------------------------------------------\n\rReset\n\n\r");
   
	
	getUsbBoot();
	
	if(TWI_RecievedAddress(TWIC))
	receiveHexFileI2C();
	
	
	// check if the blockly code area is empty
	USART_TransmitString(USARTD0, "Checking for program\n\r");
	
	if(pgm_read_byte(0x4000) == 0xFF)
	{
		USART_TransmitString(USARTD0, "No program found\n\r");
		
		while(true)
		{
			//USART0_TransmitString("test");
			if (!PORTA_IN &(1<<0))
			{
				resetDevice();
			}
		}
	}

	// run the blockly
	USART_TransmitString(USARTD0, "Starting your program\n\r");
	asm("jmp 0x4000");

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
		USART_TransmitString(USARTD0, "Receiving program via USB\n\r");
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

		USART_TransmitString(USARTD0, buff);
		programHexLine(buff);
	}
}

void receiveHexFileI2C()
{
	char buff[50];

	while(true)
	{
		USART_TransmitString(USARTD0, "\n\rtest4\n\r");
		// receive a line of the hex file
		TWI_ReceivePacket(TWIC,(uint8_t*)buff, 50);
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
	
	USART_Transmit_Number(USARTD0,byteCount);
	USART_Transmit_Number(USARTD0,address_H);
	USART_Transmit_Number(USARTD0,address_L);
	USART_Transmit_Number(USARTD0,recordType);

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

	USART_TransmitString(USARTD0, "\n\rtest2\n\r");
	
	checksum += hexToByte(line[9+2*byteCount],line[10+2*byteCount]);
	
	if(checksum != 0)
	{
		USART_TransmitString(USARTD0, "\n\rChecksum error while receiving program\n\rResetting");
		resetDevice();
		return;
	}
	
	USART_TransmitString(USARTD0, "\r\nReceived: ");
	USART_Transmit(USARTD0, line, 11+2*byteCount);
	USART_TransmitString(USARTD0, "\r\n");
	USART_Transmit_Hex(USARTD0, address_H);
	USART_Transmit_Hex(USARTD0, address_L);
	USART_TransmitString(USARTD0, "\r\n");
	//USART0_Transmit(data);
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
				resetDevice();
			}
			
			SP_WaitForSPM();
			SP_EraseWriteApplicationPage(previousAddress);
		
			// erase the last page
			//boot_page_erase_safe(previousAddress);
			// write the last page to flash
			//boot_page_write_safe(previousAddress);
			
			USART_Transmit_Hex(USARTD0, pgm_read_byte(0x4000));
			//for (uint8_t i = 0;i<10;i++)
			//{
			//	USART0_Transmit_Number(pgm_read_byte(previousAddress-i));
			//}
		}
		// reset device
		resetDevice();
	}
	else if(recordType == DATA_RECORD)
	{
		USART_TransmitString(USARTD0, "\n\rtest3\n\r");
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
						resetDevice();
					}
					
					SP_WaitForSPM();
					SP_EraseWriteApplicationPage(previousAddress);
					
					
					
					// erase the previous page
					//boot_page_erase_safe(previousAddress);
					// write the previous page to flash
					//boot_page_write_safe(previousAddress);
				}
			}
			
			
			SP_WaitForSPM();
			SP_LoadFlashWord(address%SPM_PAGESIZE, ((uint16_t)data[i+1] << 8 | data[i]));
						
			// put byte in temporary buffer
			//boot_page_fill_safe(address%SPM_PAGESIZE, ((uint16_t)data[i+1] << 8 | data[i]));
			
			// track the programming state
			firstByte = false;
			previousAddress = address;
			address+=2;
		}
	}

}

void Solanoid();

#define JMP(F) (uint16_t)0x940C, (uint16_t)&F

volatile uint16_t jump_table[] __attribute__ ((section(".jmp_table"))) =  {
	JMP(delay_ms),
	JMP(delay1sec),
	JMP(printNumber),
	JMP(invert),
	JMP(add),
	JMP(subtract),
	JMP(multiply),
	JMP(divide),
	JMP(isEqual),
	JMP(isBigger),
	JMP(isSmaller),
	JMP(isBiggerOrEqual),
	JMP(isSmallerOrEqual),
	JMP(logic_or),
	JMP(logic_and),
	JMP(logic_xor),
	//JMP(Solanoid),
	JMP(ToggleLED)
};

//


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


void ToggleLED()
{
	PORTH_OUTTGL |= (1 << 4)|(1<<5);
}