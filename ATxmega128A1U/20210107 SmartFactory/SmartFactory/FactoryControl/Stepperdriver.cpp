/*
 * Stepperdriver.cpp
 *
 * Created: 13/12/2020 14:51:37
 *  Author: Nick (& Wout)
 */ 

#include "Stepperdriver.h"



void stepperWriteRegister(uint8_t address, const char* data, uint8_t length, uint8_t motorID, USART_struct &USART)
{
	cli(); //global interrupt disable, this function is not re-entrant and should not be interrupted
	uint8_t checksum = 0xFF-motorID-(length+3)-address;
	for(uint8_t i = 0; i < length; i++)
	{
		checksum = checksum - data[i];
	}
	
	USART_Transmit(USART, 0xFF); //send 0xFFFF
	USART_Transmit(USART, 0xFF);
	USART_Transmit(USART, motorID); //send motorID
	USART_Transmit(USART, length+3); //transmit message length (register instruction+address+data+checksum)
	USART_Transmit(USART, 0x00); // instruction (not yet implemented)
	USART_Transmit(USART, address); // send address to start writing
	USART_Transmit(USART, data, length); //send data to write to registers
	USART_Transmit(USART, checksum);

	_delay_ms(30);
	sei(); //global interrupt enable
}


void ChangeDirectionStepper(bool direction, uint8_t motor_id)
{
	char directiondata[]={direction};
	stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
}


void MoveBelt(bool direction, uint16_t i, int16_t speed)
{
	uint8_t motor_id;
	//Only move when 'i' has a number that is a Belt motor ID
	switch(i) {
		case 1: motor_id = BELT_1_MOTOR_ID; break;
		case 2: motor_id = BELT_2_MOTOR_ID; break;
		case 3: motor_id = BELT_3_MOTOR_ID; break;
		case 4: motor_id = BELT_4_MOTOR_ID; break;
		default: return;
	}
	//Convert speed from uint16_t to byte array:
	char speedData[2]={(char)((speed>>8)&0xff), (char)(speed&0xff)};
	//Convert bool to byte array, could this be a typecast instead (and would that make a difference)
	char directiondata[]={direction};
	//Write direction data to the direction register
	stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
	//Write the remaining data:
	char data[]={speedData[0], speedData[1],0xFF,0xFF,direction,MOTOR_STEP_FULL,MOTOR_ON};
	stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),motor_id,USARTE1); //This write operation also contains direction data? Why is the other one still needed?
}


void StopBelt(uint16_t i)
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = BELT_1_MOTOR_ID; break;
		case 2: motor_id = BELT_2_MOTOR_ID; break;
		case 3: motor_id = BELT_3_MOTOR_ID; break;
		case 4: motor_id = BELT_4_MOTOR_ID; break;
		default: return;
	}
	char data[]={MOTOR_OFF};
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data)/sizeof(*data),motor_id,USARTE1);
}


void MoveTurntable(bool direction, uint16_t i, int16_t speed )
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = TURNTABLE_1_MOTOR_ID; break;
		case 2: motor_id = TURNTABLE_2_MOTOR_ID; break;
		default: return;
	}

	char speedData[2] = { (char)((speed >> 8) & 0xff), (char)(speed & 0xff) };
	char directiondata[] = { direction };
	stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
	char data[] = { speedData[0], speedData[1],0xFF,0xFF,direction,MOTOR_STEP_QUARTER,MOTOR_ON }; // Turntable's draaien op 1/4 step mode, hierdoor kunnen de motoreren soepeler draaien
	stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
}


void StopTurntable(uint16_t i)
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = TURNTABLE_1_MOTOR_ID; break;
		case 2: motor_id = TURNTABLE_2_MOTOR_ID; break;
		default: return;
	}

	char data[] = { MOTOR_OFF };
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
}


// Test Code om uit te zoeken hoe een motor gestart moet worden op adres 0x0A
void DemoTestBlock() {
	uint8_t motor_id = TEST_DEMO_MOTOR_ID; // Dit zou 0x0A moeten zijn
	int16_t speed = 1000;
	bool direction = 0;
	
	char speedData[2] = { (char)((speed >> 8) & 0xff), (char)(speed & 0xff) };
	char directiondata[] = { direction };
	stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
	char data[] = { speedData[0], speedData[1],0xFF,0xFF,direction,MOTOR_STEP_FULL,MOTOR_ON };
	stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
}


// Test code om de motor op TEST_DEMO_MOTOR_ID weer te stoppen
void StopDemoTestBlock() {
	uint8_t motor_id = TEST_DEMO_MOTOR_ID;
	char data[] = { MOTOR_OFF };
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
}


// Change the address of a motor
void SetAddress(uint8_t from, uint8_t to) {
	uint16_t motor_id = from; // Old address
	char regdata = to; // New address

	stepperWriteRegister(BUS_ADDRESS_REG, 
						 &regdata, 
						 1, // Size of message
						 motor_id, 
						 USARTE1
						 ); //Write new address to motor
}