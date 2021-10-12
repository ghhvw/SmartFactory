/*
* SmartFactory.cpp
*
* Created: 2-6-2020 14:15:47
* Author : Nick, Wout, Jon
*/

#define F_CPU 24000000
#define DATA_RECORD 0
#define EOF_RECORD	1

//Uncomment to run in debug mode:
#define DEBUG 1

//Macro for Logging debug info to serial monitor:
#if DEBUG
#define DEBUG_OUT(X) USART_TransmitString(USARTD0, X)
#else
#define DEBUG_OUT(X)
#endif

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
#include "IO_mappings.h"
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


void initLEDs();
void ToggleLED();
void LED(bool i);
void ToggleLED1();
void ToggleLED2();
void passthrough_TWI();
bool DigitalRead(int16_t IO) { return IO_ReadWrite(true, IO); }
uint16_t AnalogRead(int16_t IO) { return (uint16_t)I_AnalogRead(ADCA, (uint8_t)IO); }
bool OptocouplerRead(int16_t IO) { return I_OptocouplerRead((uint8_t)IO); }
void requestStarted() { TWI_Write(TWIC, Started); }
void requestResult() { TWI_Write(TWIC, Result); }


/* ISR INT0, gebruikt voor lift interrupts */
ISR(PORTK_INT0_vect) {
	bool elevatorUpPressed = !(PORTK_IN & EV_SWITCH_PIN_UP); //Pin use pull-ups, invert to give true on pressed
	bool elevatorDownPressed = !(PORTK_IN & EV_SWITCH_PIN_DOWN);

	DEBUG_OUT("Entered INT0 ISR\r\n");


	if(elevatorDownPressed){
		DEBUG_OUT("Elevator Switch DOWN was pressed\n\r");
		ElevatorButtonInISR(false); //Run with parameter false to indicate DOWN

	}
	if(elevatorUpPressed){
		DEBUG_OUT("Elevator Switch UP was pressed\n\r");
		ElevatorButtonInISR(true); //Run with parameter true to indicate UP
	}
}


///* ISR INT1, gebruikt voor sorterarm interrupts */
ISR(PORTK_INT1_vect) {
	
	//Read the PORTK register on the SorterArm pins:
	bool leftIsPressed = !(PORTK_IN & sa1.switch_pin_left); //Pin use pull-ups, invert to give true on pressed
	bool rightIsPressed = !(PORTK_IN & sa1.switch_pin_right);

	DEBUG_OUT("Entered INT1 ISR\r\n");
	if(leftIsPressed){
	 DEBUG_OUT("SorterArm switch LEFT was pressed\n\r");
	 SorterArmISR();
	}
	if(rightIsPressed){
	 DEBUG_OUT("SorterArm switch RIGHT was pressed\n\r");
	 SorterArmISR();
	 }

	//Currently checks the PORTK register for which pin is pressed down
	//The sorterArm should theoretically only be able to press one switch at a time
	//If necessary, code could be added for checking which switch changed state.
	
}


int main(void)
{
	// Setup/init
	irq_initialize_vectors();
	cpu_irq_enable();
	sysclk_init();
	udc_start();
	
	//Set up peripherals
	sysclk_enable_peripheral_clock(&TWIC);		//TWI/I2C line for interfacing with ESP32
	sysclk_enable_peripheral_clock(&USARTD0);	//USB line for debugging
	sysclk_enable_peripheral_clock(&USARTE1);	//RS485
	sysclk_enable_peripheral_clock(&ADCA);		//ADC for reading sensors
	
	TWI_init(TWIC);
	TWI_onRequest(requestStarted, TWIC);

	// Init board
	board_init();
	initLEDs();

	//Init UART for Debug interface and RS485 drivers
	USART_Init(USARTD0, 115200, 24000000, false);	// RX/TX out
	USART_Init(USARTE1,37100,24000000,false);	// RS485 1
	USART_Init(USARTF0,37100,24000000,false);	// RS485 2
	
	PORTE_OUTSET = 0b00110000;
	
	ADC_Init(ADCA);
	
	//Stop all motors on boot:
	for (uint8_t i=1; i<=11; i++) {
		StopBelt(i);
	}
	for (uint8_t i=1; i<=11; i++) {
		StopTurntable(i);
	}
	StopSorterArm();
	StopElevator();
	
	// sysclk_enable_peripheral_clock(&TCC1); //zie SorterArm.cpp, TODO weghalen als stepperdrivers uitgelezen kunnen worden
	
	sei(); //global interrupt enable
	ElevatorInit();
	initOptocouplers();
	//ElevatorInterruptSetup();
	//SaSetInput(sa1.switch_pin_left, sa1.switch_pin_right);
	//SaSetInterrupt(sa1.switch_pin_left, sa1.switch_pin_right);


	USB_TransmitString("TEST\n"); // Test serial working

	
	/* Insert application code here, after the board has been initialized. */
	
	
	USART_TransmitString(USARTD0, "\n\r------------------------------------------------------------\n\rReset\n\n\r");
	USB_TransmitString("\n\r------------------------------------------------------------\n\rReset\n\n\r");
	
	
	getUsbBoot();
	
	for (long i=0;i<500000;i++)
	{
		if(TWI_RecievedAddress(TWIC))
		receiveHexFileI2C(passthrough_TWI); //Check if I2C transmission contains new program or enables Stepper-test mode
		_delay_us(1);
	}
	
	#ifdef DEBUG
	USART_TransmitString(USARTD0, "\r\nRunning in DEBUG mode\r\n");
	#endif
	
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
	JMP(MoveSorterArmTo),
	JMP(MoveSorterArmDistance),
	JMP(SorterarmIsFinnished),
	JMP(StopSorterArm),
	JMP(HomeSorterArm),
	JMP(MoveTurntable),
	JMP(StopTurntable),
	JMP(DemoTestBlock), // Test code
	JMP(StopDemoTestBlock), // Test code
	JMP(SetAddress),
	JMP(MoveElevator),
	JMP(StopElevator),
	JMP(ElevatorIsReady),
	JMP(Solenoid),
	JMP(PulseSolenoid),
	JMP(AnalogRead),
	JMP(ReadSharpSensor),
	JMP(OptocouplerRead),
	JMP(ReadColourSensor),
	JMP(SelectColour),
	JMP(set_relay),
};


void ToggleLED() { PORTH_OUTTGL |= (1<<4)|(1<<5); }
void LED(bool i) {
	if (i) {
		PORTH_OUTCLR |= (1<<4)|(1<<5);
		} else {
		PORTH_OUTSET |= (1<<4)|(1<<5);
	}
}
void initLEDs() {
	PORTH_DIRSET = PIN4_bm | PIN5_bm;
	PORTH_OUTCLR = PIN4_bm | PIN5_bm;
	} //Set the LED pins to output
void ToggleLED1() { PORTH_OUTTGL |= (1 << 4); } // Zet tweede LED aan of uit
void ToggleLED2(){ PORTH_OUTTGL |= (1 << 5); } // Zet tweede LED aan of uit


/* Enter stepper-testing mode. Will exit on Reset */
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
				char data[]={0x01,0x4c,0x00,0x32,buff[2],MOTOR_STEP_HALF,MOTOR_ON};
				stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),buff[1],USARTE1);
				} else if (buff[0] == 1) { //lees analog
				Result = AnalogRead(buff[1]); //bij een interrupt stuurt de ATmega Result via TWI
			}
			
			PORTH_OUTSET |= (1<<4)|(1<<5); //LED off
		}
	}
}