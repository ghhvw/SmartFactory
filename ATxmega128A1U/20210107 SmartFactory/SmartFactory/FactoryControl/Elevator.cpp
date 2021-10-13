//
// Elevator.cpp
//
// Created by Jon_n on 17-3-2021.
//	Edited by Sjors
//

#include "Elevator.h"

bool elevatorDirection;							// Richting van de lift
volatile bool elevatorIsUp, elevatorIsDown;	// Boleans om de stand van de lift bij te houden

/* blockly functie */
void MoveElevator(bool direction) {
	elevatorDirection = direction;
	if (ConfigElevator(direction)) {
		DEBUG_OUT("-----MOVING ELEVATOR------ \n\r");
		
		uint16_t motor_id = ELEVATOR_MOTOR_ID; // Motor ID van lift
		bool Direction = !direction;

		char directiondata[] = { Direction };
		stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
		char data[] = { 0x03,0x66,0xFF,0xFF,Direction,MOTOR_STEP_HALF,MOTOR_ON };
		stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
	}
}


/* blockly functie */
void StopElevator() {
	DEBUG_OUT("-----STOPPING ELEVATOR------ \n\r");
	uint16_t motor_id = ELEVATOR_MOTOR_ID;
	char data[] = { MOTOR_OFF };
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1); // Stopt lift motor
}


/* blockly functie */
bool ElevatorIsReady() {
	
	if ((elevatorDirection == 1) && (elevatorIsUp == true)) {
		StopElevator();
		return 1; // Lift is boven aangekomen
	}
	else if ((elevatorDirection == 0) && (elevatorIsDown == true)) {
		StopElevator();
		return 1; // Lift is beneden aangekomen
	}
	else {
		return 0; // Lift is nog bezig
	}
}



bool ConfigElevator(bool direction) {

	bool start = 0;

	if (!(PORTK_IN & EV_SWITCH_PIN_UP) && (direction == 1)) {
		elevatorIsUp = true;
		start = 0; // Lift mag niet starten, want wil naar boven en is al boven
	}
	else if (!(PORTK_IN & EV_SWITCH_PIN_DOWN) && (direction == 0)) {
		elevatorIsDown = true;
		start = 0; // Lift mag niet starten, want wil naar beneden en is al beneden
	}
	else if ((elevatorIsUp == true) && (elevatorIsDown == true)) {
		start = 0; // Lift mag niet starten, want is boven en beneden, ERROR!!!
	}
	else if (!(PORTK_IN & EV_SWITCH_PIN_UP) && (direction == 0)) {
		elevatorIsUp = true;
		start = 1; // Lift mag starten, want is boven en wil naar beneden
	}
	else if (!(PORTK_IN & EV_SWITCH_PIN_DOWN) && (direction == 1)) {
		elevatorIsDown = true;
		start = 1; // Lift mag starten, want wil naar boven en is beneden
	}
	else if ((PORTK_IN & EV_SWITCH_PIN_UP) && (PORTK_IN & EV_SWITCH_PIN_DOWN)) {
		elevatorIsUp = false;
		elevatorIsDown = false;
		start = 1; // Lift mag starten want is niet boven of beneden
	}

	

	if (start == 1) {
		ElevatorInterruptSetup(); // Pinnen worden ingesteld om interrupts te kunnen genereren 
		return 1; // Lift mag starten
	}
	else {
		return 0; // Lift mag niet starten
	}
}


// ISR, switch is ingedrukt
void ElevatorButtonInISR(bool ElevatorIsUp) {
	if (ElevatorIsUp == elevatorDirection){ //Elevator stops moving if it reaches switch opposite to moving direction
		if(elevatorDirection == true){ //(ev_richting 1 = up, 0 = down)
			elevatorIsUp = true;
			elevatorIsDown = false;
		}else { //(ev_richting 1 = up, 0 = down)
			elevatorIsUp = false;
			elevatorIsDown = true;
		}
		StopElevator();
	}
}

// Inputs voor de lift worden op Input-Pullup gezet
void ElevatorInit() {
	PORTK_DIR &= ~(EV_SWITCH_PIN_UP); // Set pin as input
	PORTK_DIR &= ~(EV_SWITCH_PIN_DOWN);



	//Set the PINnCTRL of the down switch to PULLUP and falling edge
	//This is to print the Pinout for the elevator
	switch (EV_SWITCH_PIN_DOWN)
	{
		case PIN0_bm: PORTK_PIN0CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN0CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN0CTRL for DOWN\n\r"); break;
		case PIN1_bm: PORTK_PIN1CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN1CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN1CTRL for DOWN\n\r"); break;
		case PIN2_bm: PORTK_PIN2CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN2CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN2CTRL for DOWN\n\r"); break;
		case PIN3_bm: PORTK_PIN3CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN3CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN3CTRL for DOWN\n\r"); break;
		case PIN4_bm: PORTK_PIN4CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN4CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN4CTRL for DOWN\n\r"); break;
		case PIN5_bm: PORTK_PIN5CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN5CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN5CTRL for DOWN\n\r"); break;
		case PIN6_bm: PORTK_PIN6CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN6CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN6CTRL for DOWN\n\r"); break;
		case PIN7_bm: PORTK_PIN7CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN7CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN7CTRL for DOWN\n\r"); break;
		default: break;
	}

	//Set the PINnCTRL of the UP switch to PULLUP and falling edge
	switch(EV_SWITCH_PIN_UP){
		case PIN0_bm: PORTK_PIN0CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN0CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN0CTRL for UP\n\r"); break;
		case PIN1_bm: PORTK_PIN1CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN1CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN1CTRL for UP\n\r"); break;
		case PIN2_bm: PORTK_PIN2CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN2CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN2CTRL for UP\n\r"); break;
		case PIN3_bm: PORTK_PIN3CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN3CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN3CTRL for UP\n\r"); break;
		case PIN4_bm: PORTK_PIN4CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN4CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN4CTRL for UP\n\r"); break;
		case PIN5_bm: PORTK_PIN5CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN5CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN5CTRL for UP\n\r"); break;
		case PIN6_bm: PORTK_PIN6CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN6CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN6CTRL for UP\n\r"); break;
		case PIN7_bm: PORTK_PIN7CTRL = PORT_OPC_PULLUP_gc; PORTK_PIN7CTRL = PORT_ISC_FALLING_gc; USART_TransmitString(USARTD0, "Set PIN7CTRL for UP\n\r"); break;
		default: break;
	}

	PORTK_INT0MASK |= EV_SWITCH_PIN_UP; // Stel pin in interrupt opwekkende pin, in het K register
	PORTK_INT0MASK |= EV_SWITCH_PIN_DOWN;


	PORTK_INTCTRL |= PORT_INT0LVL0_bm; // Enable PORTK INT0 as a Low-Level interrupt
}


// Deprecated. Functionality moved to ElevatorInit()
void ElevatorInterruptSetup() {
	PORTK_INT0MASK |= EV_SWITCH_PIN_UP; // Stel pin in interreupt opwekkende pin, in het K register
	PORTK_INT0MASK |= EV_SWITCH_PIN_DOWN;

	PORTK_PIN4CTRL |= PORT_ISC_FALLING_gc; // Interupts op beide flanken
	PORTK_PIN5CTRL |= PORT_ISC_FALLING_gc;
	// 31-03-2021, Falling edges om gedrag daarvan te bestuderen


	PORTK_INTCTRL |= PORT_INT0LVL0_bm; // Enable PORTK INT0 as a Low-Level interrupt
}
