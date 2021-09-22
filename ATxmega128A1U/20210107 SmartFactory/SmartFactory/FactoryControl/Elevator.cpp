/*
 * Elevator.cpp
 *
 * Created: 10/12/2020 21:28:24
 *  Author: Wout
 */ 

/*
 * TODO wanneer een nieuw blockly programma wordt geuploaded en de schakelaar is ingedrukt, 
 * dan start de lift niet totdat de stepper handmatig van de switch af is gedraaid. Dit kan 
 * ongewenst zijn voor de gebruiker. 
 */

#include "Elevator.h"

uint8_t elevator_ready = 0xFF, ev_direction = 0;



/* 
 * Bij meer dan 1 elevators zouden de Elevator blocklys & de functies met "blockly functie" 
 * erboven aangepast moeten worden om een ID te vragen. Of dan kunnen er extra blocklys en 
 * functies toegevoegd worden die met een ander motor ID en switch pin werken, zoals de 
 * kabelbaan functies. Pas ook de ISR in main.cpp aan. 
 */

/* blockly functie */
void MoveElevator(bool direction) { MoveLift(direction, ELEVATOR_MOTOR_ID, EV_SWITCH_PIN); }


/* blockly functie */
void StopElevator() { StopLift(ELEVATOR_MOTOR_ID, EV_SWITCH_PIN); }


/* blockly functie */
bool ElevatorReady() { return LiftReady(EV_SWITCH_PIN); }
	

/* blockly functie */											//block nog niet geïmplementeerd in blockly 
void MoveKabelbaan(bool direction) { MoveLift(direction, KABELBAAN_MOTOR_ID, KB_SWITCH_PIN); }


/* blockly functie */											//block nog niet geïmplementeerd in blockly 
void StopKabelbaan() { StopLift(KABELBAAN_MOTOR_ID, KB_SWITCH_PIN); }


/* blockly functie */											//block nog niet geïmplementeerd in blockly 
bool KabelbaanReady() { return LiftReady(KB_SWITCH_PIN); }


void MoveLift(bool direction, uint8_t motor_id, uint8_t switch_pin)
{
	if (ConfLift(direction, switch_pin)) {
		//TODO wanneer de INT0 interrupt hier optreedt kan de stepper de verkeerde richting opgaan
		
		char directiondata[]={direction};
		stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),motor_id, USARTE1);
		char data[]={0x03,0x66,0xFF,0xFF,direction,MOTOR_PWR_MIN,MOTOR_ON};
		stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),motor_id,USARTE1);
	}
}


void StopLift(uint8_t motor_id, uint8_t switch_pin)
{
	char data[]={MOTOR_OFF};
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data)/sizeof(*data),motor_id,USARTE1);
	ResetLift(switch_pin);
}


bool LiftReady(uint8_t switch_pin)
{
	return (elevator_ready & switch_pin);
}


/* set variables & interrupts, return 1 als de stepper mag starten */
bool ConfLift(bool direction, uint8_t switch_pin)
{
	//switches mogen niet ingedrukt zijn (NC switches, ingedruk wanneer signaal hoog)
	EVSetPullUp(switch_pin);
	_delay_ms(30);									//storing op pin weg laten gaan
	if (PORTK_IN & switch_pin) { return 0; }		//stepper mag niet starten, er is een schakelaar ingedrukt of kabelbreuk, stop
	/* 
	 * TODO wanneer de schakelaar nog niet is losgelaten en de lift 
	 * al naar de andere positie mag gaan (en dit wordt 1x aangeroepen 
	 * in blockly), dan wordt dit niet uitgevoerd
	 */
	
	//richting opslaan voor ISR
	if (direction) {
		ev_direction |= switch_pin; //set bit
	} else {
		ev_direction &= ~(switch_pin); //clear bit
	}
	elevator_ready &= ~(switch_pin); //clear ready bit
	
	//set interrupts
	EVSetInterrupt(switch_pin);

	return 1; //stepper mag starten
}


/* set variables & clear interrupts */
void ResetLift(uint8_t switch_pin)
{
	elevator_ready |= switch_pin; //set ready bit

	//disable listen interrupt on pin
	PORTK_INT0MASK &= ~(switch_pin);
}


/* ISR */
void LiftISR(uint8_t motor_id, uint8_t switch_pin)
{
//	if (elevator_ready & switch_pin) { return; }						//lift was niet actief, ISR stopt
	
	/* switch is ingedrukt (NC, hoog wanneer ingedrukt) */
	if (PORTK_IN & switch_pin) {
		ChangeDirectionStepper(!(ev_direction & switch_pin), motor_id);	//teruggaan totdat switch weer is losgelaten
		
	/* switch is losgelaten (closed circuit) */
	} else {
		StopLift(motor_id, switch_pin);								//lift stopzetten en interrupts uitzetten
	}
	return;
}


void EVSetPullUp(uint8_t switch_pin)
{
	switch(switch_pin)				//pullup
	{
		case PIN0_bm: PORTK_PIN0CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN1_bm: PORTK_PIN1CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN2_bm: PORTK_PIN2CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN3_bm: PORTK_PIN3CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN4_bm: PORTK_PIN4CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN5_bm: PORTK_PIN5CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN6_bm: PORTK_PIN6CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN7_bm: PORTK_PIN7CTRL |= PORT_OPC_PULLUP_gc; break;
	}
//	PORTK_OUT |= switch_pin;		//totem-pole set pin high
	PORTK_DIR &= ~(switch_pin);		//pin set as input
}


void EVSetInterrupt(uint8_t switch_pin)
{
	PORTK_INT0MASK |= switch_pin;		//pin listen interrupt
	switch(switch_pin)					//sense both edges
	{
		case PIN0_bm: PORTK_PIN0CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN1_bm: PORTK_PIN1CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN2_bm: PORTK_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN3_bm: PORTK_PIN3CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN4_bm: PORTK_PIN4CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN5_bm: PORTK_PIN5CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN6_bm: PORTK_PIN6CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN7_bm: PORTK_PIN7CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	}
	PORTK_INTCTRL |= PORT_INT0LVL0_bm;	//enable interrupt at low level
	
	//gebruik vector PORTK_INT0_vect in main.cpp en roep ElevatorISR() aan
}