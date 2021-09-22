/*
 * SmartFactory.cpp
 *
 * Created: 2-6-2020 14:15:47
 * Author : Nick
 */ 

#define F_CPU 24000000
#define DATA_RECORD 0
#define EOF_RECORD	1

#include <asf.h>
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
#include "Blockly_Functions.h"
#include "Programming.h"
#include "DigitalIO.h"
#include "AnalogI.h"
#include "OptocouplerI.h"
#include "Relays.h"
#include "Solenoid.h"
#include "Stepperdriver.h"
#include "Elevator.h"
#include "SorterArm.h"
#include "SharpSensor.h"
#include "USB_Functions.h"
#include "Kleursensor.h"

uint8_t Started = 0; //wordt 1 bij start van blockly code
uint8_t Result = 0; //voor teruggeven waardes in stepper-test modus

void ToggleLED();
void LED(bool i);
void passthrough_TWI();
bool DigitalRead(int16_t IO){ return IO_ReadWrite(true, IO); }
uint16_t AnalogRead(int16_t IO) { return (uint16_t) I_AnalogRead(ADCA, (uint8_t) IO); }
bool OptocouplerRead(int16_t IO) { return I_OptocouplerRead((uint8_t) IO); }
void requestStarted() { TWI_Write(TWIC, Started); }
void requestResult() {TWI_Write(TWIC, Result); }

/* ISR vars */
uint8_t portk_in_prev, portk_in_cur = PORTK_IN;
uint8_t portj_in_prev, portj_in_cur = PORTJ_IN;

/* ISR INT0 */
ISR(PORTK_INT0_vect) {
	portk_in_prev = portk_in_cur;
	portk_in_cur = PORTK_IN;
	
	//welke pin is veranderd?
	if ((portk_in_prev & EV_SWITCH_PIN)  ^  (portk_in_cur & EV_SWITCH_PIN)) {
		LiftISR(ELEVATOR_MOTOR_ID, EV_SWITCH_PIN);
	}
	if ((portk_in_prev & KB_SWITCH_PIN)  ^  (portk_in_cur & KB_SWITCH_PIN)) {
		LiftISR(KABELBAAN_MOTOR_ID, KB_SWITCH_PIN);
	}
//	if (PORTK_IN&(1<<PIN4_bp)) { LED(1); } else { LED(0); }
}

/* ISR INT1 */
ISR(PORTJ_INT1_vect) {
	portj_in_prev = portj_in_cur;
	portj_in_cur = PORTJ_IN;
	
	//welke pin is veranderd?
	if ((portj_in_prev & sa1.switch_pin)  ^  (portj_in_cur & sa1.switch_pin)) {
		SorterArmISR(&sa1);
	}
//	if (PORTJ_IN&(1<<PIN0_bp)) { LED(1); } else { LED(0); }
}


int main(void)
{
	irq_initialize_vectors();
	cpu_irq_enable();
	
	/* Insert system clock initialization code here (sysclk_init()). */
	
	sysclk_init();
	
	udc_start();
	
	sysclk_enable_peripheral_clock(&TWIC);
	sysclk_enable_peripheral_clock(&USARTD0);
	sysclk_enable_peripheral_clock(&USARTE1); //RS485 voor aansturen steppermotoren
	sysclk_enable_peripheral_clock(&ADCA);
	
	TWI_init(TWIC);
	TWI_onRequest(requestStarted, TWIC);

	board_init();
	
	PORTH_OUTSET |= (1 << 4)|(1<<5);
	
	USART_Init(USARTD0, 115200, 24000000, false);
	USART_Init(USARTE1,37100,24000000,false);
	USART_Init(USARTF0,37100,24000000,false);
	
	PORTE_OUTSET = 0b00110000;
	
	ADC_Init(ADCA);
	
	for (uint8_t i=1; i<=4; i++) {
		StopBelt(i);
	}
	for (uint8_t i=1; i<=2; i++) {
		StopTurntable(i);
	}
	StopSorterArm();
	StopElevator();
	
	sysclk_enable_peripheral_clock(&TCC1); //zie SorterArm.cpp, TODO weghalen als stepperdrivers uitgelezen kunnen worden
	
	sei(); //global interrupt enable
	
	/*while(1) {
		USB_Transmit(ReadColourSensor(), 7);
		USB_TransmitString("	");
		USB_Transmit_Number(ReadOneColour(0));
		USB_TransmitString("	");
		USB_Transmit_Number(ReadOneColour(1));
		USB_TransmitString("	");
		USB_Transmit_Number(ReadOneColour(2));
		
		USB_TransmitString("\n\r");
		_delay_ms(300);
	}*/
//	ToggleLED();
//	_delay_ms(100);
//	ToggleLED();
	
	/* Insert application code here, after the board has been initialized. */
	
	
	USART_TransmitString(USARTD0, "\n\r------------------------------------------------------------\n\rReset\n\n\r");
	USB_TransmitString("\n\r------------------------------------------------------------\n\rReset\n\n\r");
   
	
	getUsbBoot();
	
	for (long i=0;i<500000;i++)
	{
		if(TWI_RecievedAddress(TWIC))
		receiveHexFileI2C(passthrough_TWI); //dit bepaalt of flash wordt geprogrammeerd of dat stepperdrivers worden getest
		_delay_us(1);
	}
	
	
	
	// check if the blockly code area is empty
	USART_TransmitString(USARTD0, "Checking for program\n\r");
	USB_TransmitString("Checking for program\n\r");
	
	if(pgm_read_byte(0x8000) == 0xFF)
	{
		USART_TransmitString(USARTD0, "No program found\n\r");
		USB_TransmitString("No program found\n\r");
		
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
	Started = 1;
	USART_TransmitString(USARTD0, "Starting your program\n\r");
	USB_TransmitString("Starting your program\n\r");
	asm("jmp 0x8000");

}

////////////////////////////////////JUMPTABLE//////////////////////////////////

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
	JMP(ToggleLED),
	JMP(LED),
	JMP(DigitalRead),
	JMP(MoveBelt),
	JMP(StopBelt),
	JMP(MoveSorterArmDistance),
	JMP(MoveSorterArmIndex),
	JMP(SorterArmPosition),
	JMP(SorterArmReady),
	JMP(MoveTurntable),
	JMP(StopTurntable),
	JMP(MoveElevator),
	JMP(StopElevator),
	JMP(ElevatorReady),
	JMP(Solenoid),
	JMP(PulseSolenoid),
	JMP(AnalogRead),
	JMP(ReadSharpSensor),
	JMP(OptocouplerRead),
	JMP(ReadColourSensor),
	JMP(SelectColour)
};


void ToggleLED() { PORTH_OUTTGL |= (1<<4)|(1<<5); }
void LED(bool i) {
	if (i) {
		PORTH_OUTCLR |= (1<<4)|(1<<5);
	} else {
		PORTH_OUTSET |= (1<<4)|(1<<5);
	}
}


/* test stepperdrivers totdat ATmega gereset wordt */
void passthrough_TWI() {
	char buff[3];
	TWI_onRequest(requestResult, TWIC);
	
	while (1) {
		if (TWI_RecievedAddress(TWIC)) {
			PORTH_OUTCLR |= (1<<4)|(1<<5); //LED on
			
			TWI_ReceivePacket(TWIC,(uint8_t*)buff, 3);
			_delay_ms(1);
			TWIC.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp); //clear interrupts
			
			if (buff[0] == 0) { //test steppers
				//buff[1] motorid, buff[2] direction
				char directiondata[]={buff[2]};
				stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),buff[1], USARTE1);
				char data[]={0x01,0x4c,0x00,0x32,buff[2],MOTOR_PWR_MEDIUM,MOTOR_ON};
				stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),buff[1],USARTE1);
			} else if (buff[0] == 1) { //lees analog
				Result = AnalogRead(buff[1]); //bij een interrupt stuurt de ATmega Result via TWI
			}
			
			PORTH_OUTSET |= (1<<4)|(1<<5); //LED off
		}
	}
}