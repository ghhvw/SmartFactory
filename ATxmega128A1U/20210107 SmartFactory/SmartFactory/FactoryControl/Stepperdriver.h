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
#define STEP_REG 75			// Motor microstep register
#define MOTOR_ENABLE_REG 76 //motor enable register 0=off 1=on
#define LED1_REG 77			//LED 1 0=off 1=on
#define LED2_REG 78			//LED 2 0=off 1=on
#define BUS_ADDRESS_REG 5   // Het eigen rs-485 bus adres, verander adres op afstand

#define MOTOR_FORWARD 1		//write to DIRECTION_REG
#define MOTOR_REVERSE 0		//write to DIRECTION_REG
#define MOTOR_ON 1			//write to MOTOR_ENABLE_REG
#define MOTOR_OFF 0			//write to MOTOR_ENABLE_REG
#define MOTOR_STEP_FULL 0			// Write to STEP_REG fullstep
#define MOTOR_STEP_HALF 1			// Write to STEP_REG halfstep
#define MOTOR_STEP_QUARTER 2		// Write to STEP_REG 1/4 step
#define MOTOR_STEP_EIGHTH 3			// Write to STEP_REG 1/8 step
#define MOTOR_STEP_SIXTEENTH 4		// Write to STEP_REG 1/16 step
#define MOTOR_STEP_THIRTYSECOND 5	// Write to STEP_REG 1/32 step

// Motor addresses
#define BELT_1_MOTOR_ID 0x01
#define BELT_2_MOTOR_ID 0x02
#define BELT_3_MOTOR_ID 0x03
#define BELT_4_MOTOR_ID 0x04
#define TURNTABLE_1_MOTOR_ID 0x05
#define TURNTABLE_2_MOTOR_ID 0x06
#define SORTER_MOTOR_ID 0x07
#define ELEVATOR_MOTOR_ID 0x08
#define TEST_DEMO_MOTOR_ID 0x0A // Address of test motor


void stepperWriteRegister(uint8_t address, const char* data, uint8_t length, uint8_t motorID, USART_struct &USART);
void ChangeDirectionStepper(bool direction, uint8_t motor_id);
void MoveBelt(bool direction, uint16_t i, int16_t speed);
void StopBelt(uint16_t i);
void MoveTurntable(bool direction, uint16_t i, int16_t speed);
void StopTurntable(uint16_t i);
void DemoTestBlock(); // Test code
void StopDemoTestBlock(); // Test code
void SetAddress(uint8_t from, uint8_t to); // Change the address of a stepper motor


#endif /* STEPPERDRIVER_H_ */