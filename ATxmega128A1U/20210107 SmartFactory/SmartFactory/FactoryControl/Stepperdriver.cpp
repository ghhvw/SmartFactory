/*
 * Stepperdriver.cpp
 *
 * Created: 13/12/2020 14:51:37
 *  Author: Nick (& Wout)
 */ 

#include "Stepperdriver.h"



void stepperWriteRegister(uint8_t address, const char* data, uint8_t length, uint8_t motorID, USART_struct &USART)
{
	cli(); //global interrupt disable, deze functie is niet re-entrant
	uint8_t checksum = 0xFF-motorID-(length+3)-address;
	for(uint8_t i = 0; i < length; i++)
	{
		checksum = checksum - data[i];
	}
	
	USART_Transmit(USART, 0xFF); //send 0xFFFF
	USART_Transmit(USART, 0xFF);
	USART_Transmit(USART, motorID); //send motorID
	USART_Transmit(USART, length+3); //transmit message length (register instruction+address+data+checksum)
	USART_Transmit(USART, 0x00); // instructie (not yet implemented)
	USART_Transmit(USART, address); // send address to start writing
	USART_Transmit(USART, data, length); //send data to write to registers
	USART_Transmit(USART, checksum);
	_delay_ms(30);
	sei(); //global interrupt enable, ga ISR uitvoeren als er een flag was gezet
}


void ChangeDirectionStepper(bool direction, uint8_t motor_id)
{
	char directiondata[]={direction};
	stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
}


void MoveBelt(bool direction, uint16_t i)
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = BELT_1_MOTOR_ID; break;
		case 2: motor_id = BELT_2_MOTOR_ID; break;
		case 3: motor_id = BELT_3_MOTOR_ID; break;
		case 4: motor_id = BELT_4_MOTOR_ID; break;
		default: return;
	}
	char directiondata[]={direction};
	stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
	char data[]={0x01,0x4c,0xFF,0xFF,direction,MOTOR_PWR_MEDIUM,MOTOR_ON};
	stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),motor_id,USARTE1);
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


void MoveTurntable(bool direction, uint16_t i)
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = TURNTABLE_1_MOTOR_ID; break;
		case 2: motor_id = TURNTABLE_2_MOTOR_ID; break;
		default: return;
	}
	char directiondata[]={direction};
	stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
	char data[]={0x00,0x40,0xFF,0xFF,direction,MOTOR_PWR_MIN,MOTOR_ON};
	stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),motor_id,USARTE1);
}


void StopTurntable(uint16_t i)
{
	uint8_t motor_id;
	switch(i) {
		case 1: motor_id = TURNTABLE_1_MOTOR_ID; break;
		case 2: motor_id = TURNTABLE_2_MOTOR_ID; break;
		default: return;
	}
	char data[]={MOTOR_OFF};
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data)/sizeof(*data),motor_id,USARTE1);
}