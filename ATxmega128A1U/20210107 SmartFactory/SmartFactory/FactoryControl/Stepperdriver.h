/*
 * Stepperdriver.h
 *
 * Created: 4-6-2020 10:37:17
 *  Author: Nick
 */ 


#ifndef STEPPERDRIVER_H_
#define STEPPERDRIVER_H_

#ifndef F_CPU
#define F_CPU 24000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr_compiler.h>

#define STEPS_PS_HREG 70	//steps per second high byte register
#define STEPS_PS_LREG 71	//steps per second low byte register
#define STEPS_HREG 72		//number of steps high register
#define STEPS_LREG 73		//number of steps low register
#define DIRECTION_REG 74	//motor direction register
#define MOTORPOWER_REG 75	//motor power register
#define MOTOR_ENABLE_REG 76 //motor enable register 0=off 1=on
#define LED1_REG 77			//LED 1 0=off 1=on
#define LED2_REG 78			//LED 2 0=off 1=on

#define MOTOR_FORWARD 1		//write to DIRECTION_REG
#define MOTOR_REVERSE 0		//write to DIRECTION_REG
#define MOTOR_ON 1			//write to MOTOR_ENABLE_REG
#define MOTOR_OFF 0			//write to MOTOR_ENABLE_REG
#define MOTOR_PWR_MIN 0		//write to MOTORPOWER_REG
#define MOTOR_PWR_MEDIUM 1	//write to MOTORPOWER_REG
#define MOTOR_PWR_MAX 2		//write to MOTORPOWER_REG

#define BELT_1_MOTOR_ID 0x01
#define BELT_2_MOTOR_ID 0x02
#define BELT_3_MOTOR_ID 0x03
#define BELT_4_MOTOR_ID 0x04
#define SORTER_MOTOR_ID 0x05
#define TURNTABLE_1_MOTOR_ID 0x06
#define TURNTABLE_2_MOTOR_ID 0x07
#define ELEVATOR_MOTOR_ID 0x08
#define KABELBAAN_MOTOR_ID 0x09


void stepperWriteRegister(uint8_t address, const char* data, uint8_t length, uint8_t motorID, USART_struct &USART);
void ChangeDirectionStepper(bool direction, uint8_t motor_id);
void MoveBelt(bool direction, uint16_t i);
void StopBelt(uint16_t i);
void MoveTurntable(bool direction, uint16_t i);
void StopTurntable(uint16_t i);


#endif /* STEPPERDRIVER_H_ */