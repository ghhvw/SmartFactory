/*
 * SorterArm.cpp
 *
 *  Created: 29-3-2021 11:35:52
 *  Author: Jon, basis Wout
 */

 #include "SorterArm.h"
 #include "Stepperdriver.h"

//Macro for Logging debug info to serial monitor:
#if DEBUG
#define DEBUG_OUT(X) USART_TransmitString(USARTD0, X)
#else
#define DEBUG_OUT(X)
#endif

uint16_t sorterarmPosition = 0;

// Variabellen voor sorterarm interupts
bool saDirection; // Richting die de arm op moet gaan, links of rechts
volatile bool saIsLeft, saIsRight; // Sorterarm is links of rechts van zijn uiterste rijkweidte

// Interrupt ISR
void SorterArmISR(){
	if (!(PORTK_IN & sa1.switch_pin_left)){
		DEBUG_OUT("----------------Stop sorter arm----------------\n");
		StopSorterArm();
		saIsLeft = true;
		saIsRight = false;
	}
	else if (!(PORTK_IN & sa1.switch_pin_right)){
		DEBUG_OUT("----------------Stop sorter arm----------------\n");
		StopSorterArm();
		saIsLeft = false;
		saIsRight = true;
	}
	else {
		DEBUG_OUT("----------------Don't stop sorter arm----------------\n");
		saIsLeft = false;
		saIsRight = false;
	}
}

//TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool SorterarmIsFinnished(){
	return 0;
}
//TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool ConfigSorterArm(){
	SaSetInput(sa1.switch_pin_left, sa1.switch_pin_right);
	_delay_ms(30); // Debounce tijd
	
	bool Start = 0; // Sorterarm mag starten of niet
	
	if (!(PORTK_IN & sa1.switch_pin_left) && (saDirection == 1)){ // Sorterarm is links en wil naar links, niet mogelijk
		saIsLeft = true;
		Start = 0;
	}
	else if (!(PORTK_IN & sa1.switch_pin_left) && (saDirection == 0)){ // Sorterarm is links en wil naar rechts, mogelijk
		Start = 1;
	}
	else if ((saIsLeft == true) && (saIsRight == true)){
		Start = 0; // Bijde zijn waar, is niet mogelijk
	}
	else if (!(PORTK_IN & sa1.switch_pin_right) && (saDirection == 1)){ // Sorterarm is rechts en wil naar links, mogelijk
		Start = 1;
	}
	else if (!(PORTK_IN & sa1.switch_pin_right) && (saDirection == 0)){ // Sorterarm is rechts en wil naar rechts, niet mogelijk
		saIsRight = true;
		Start = 0;
	}
	else if ((PORTK_IN & sa1.switch_pin_left) && (PORTK_IN & sa1.switch_pin_right)){ // Sorterarm is niet links of rechts, mogelijk
		saIsLeft = false;
		saIsRight = false;
		Start = 1;
	}
		
	if (Start == 1){
		SaSetInterrupt(sa1.switch_pin_left, sa1.switch_pin_right); // Stel Sorterarm in om interrupts te genereren 
		return 1; // Sorteram mag starten
	}
	else {
		return 0; // Sorterarm mag niet starten
	}
}

/* stop stepper */
void StopSorterArm()
{
	char data[] = { MOTOR_OFF };
	uint16_t motor_id = SORTER_MOTOR_ID;
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
}


/* beweeg stepper oneindig */
void MoveSorterArm(bool direction)
{
	if (ConfigSorterArm() == 1){
		saDirection = direction;
		uint16_t motor_id = SORTER_MOTOR_ID;
		uint16_t motor_speed = 300;
		uint16_t steps = 5000;

		char directiondata[] = { direction };
		stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
		char data[] = { (uint8_t)(motor_speed >> 8),(uint8_t)motor_speed,(uint8_t)(steps >> 8),(uint8_t)steps,direction,MOTOR_STEP_FULL,MOTOR_ON };
		stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
		}

	/* https://stackoverflow.com/questions/11193800/c-bit-operations-copy-one-bit-from-one-byte-to-another-byte */
	// sa_direction = (sa_direction & ~(sa->switch_pin)) | (((uint8_t)direction << __builtin_ctz(sa->switch_pin)) & sa->switch_pin);
}

void MoveSorterArmTo(uint16_t toPosition){
	bool direction = 0;
	uint16_t steps = 0;
		
	if (ConfigSorterArm() == 1){
		if(toPosition >= sa1.minpos || toPosition <= sa1.maxpos){
			if (toPosition < sorterarmPosition){
				direction = 1;
				steps = toPosition * 200;
				//steps = toPosition - sa1.position;
			}
			else if (toPosition > sorterarmPosition){
				direction = 0;
				steps = toPosition * 200;
				//steps = sa1.position - toPosition;
			}else{
				steps = 0;
			}
		
			MoveSorterArmDistance(direction, steps);
			sorterarmPosition = toPosition;
		}
	}
}

void MoveSorterArmDistance(bool direction, uint16_t steps){
	
	if (ConfigSorterArm() == 1){
	uint16_t motor_id = SORTER_MOTOR_ID;
	uint16_t motor_speed = 300;

	char directiondata[] = { direction };
	stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
	char data[] = { (uint8_t)(motor_speed >> 8),(uint8_t)motor_speed,(uint8_t)(steps >> 8),(uint8_t)steps,direction,MOTOR_STEP_FULL,MOTOR_ON };
	stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
	}
}


void HomeSorterArm()
{
	while (saIsLeft == false) {
		MoveSorterArm(0);
	}
	


	while (saIsRight == false) {
		MoveSorterArm(1);
	}


}

void SorterarmLinksISR() {
	saIsLeft = true;
	saIsRight = false;
	StopSorterArm();
}

void SorterArmRechtsISR() {
	saIsLeft = false;
	saIsRight = true;
	StopSorterArm();
}


// Zet pinnen van de sorterarm als input-pullup
void SaSetInput(uint8_t switch_pin_left, uint8_t switch_pin_right)
{
	PORTK_DIR &= ~(switch_pin_left);		//pin set left as input
	PORTK_DIR &= ~(switch_pin_right);		//pin set right as input
	
	//Set the PINnCTRL of the left switch to PULLUP
	switch (switch_pin_left)				//pull-up
	{
		case PIN0_bm: PORTK_PIN0CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN1_bm: PORTK_PIN1CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN2_bm: PORTK_PIN2CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN3_bm: PORTK_PIN3CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN4_bm: PORTK_PIN4CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN5_bm: PORTK_PIN5CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN6_bm: PORTK_PIN6CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN7_bm: PORTK_PIN7CTRL |= PORT_OPC_PULLUP_gc; break;
		default: break;
	}

	//Set the PINnCTRL of the right switch to PULLUP
	switch(switch_pin_right){
		case PIN0_bm: PORTK_PIN0CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN1_bm: PORTK_PIN1CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN2_bm: PORTK_PIN2CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN3_bm: PORTK_PIN3CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN4_bm: PORTK_PIN4CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN5_bm: PORTK_PIN5CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN6_bm: PORTK_PIN6CTRL |= PORT_OPC_PULLUP_gc; break;
		case PIN7_bm: PORTK_PIN7CTRL |= PORT_OPC_PULLUP_gc; break;
		default: break;
	}

	
}


// Zet interrupts aan op de sorterarm pinnen
void SaSetInterrupt(uint8_t switch_pin_left, uint8_t switch_pin_right)
{
	PORTK_INT1MASK |= switch_pin_left;		//pin listen interrupt left
	PORTK_INT1MASK |= switch_pin_right;		//pin listen interrupt right

	switch (switch_pin_left)					//sense both edges
	{
	case PIN0_bm: PORTK_PIN0CTRL |= PORT_ISC_FALLING_gc, PORTK_PIN1CTRL |= PORT_ISC_FALLING_gc; break;
	case PIN1_bm: PORTK_PIN1CTRL |= PORT_ISC_FALLING_gc, PORTK_PIN2CTRL |= PORT_ISC_FALLING_gc; break;
	case PIN2_bm: PORTK_PIN2CTRL |= PORT_ISC_FALLING_gc, PORTK_PIN3CTRL |= PORT_ISC_FALLING_gc; break;
	case PIN3_bm: PORTK_PIN2CTRL |= PORT_ISC_FALLING_gc, PORTK_PIN4CTRL |= PORT_ISC_FALLING_gc; break;
	case PIN4_bm: PORTK_PIN2CTRL |= PORT_ISC_FALLING_gc, PORTK_PIN5CTRL |= PORT_ISC_FALLING_gc; break;
	}

	PORTK_INTCTRL |= PORT_INT1LVL0_bm;	//enable interrupt on PORTK

	//Use vector PORTK_INT1_vect in main.cpp and call SorterArmISR()
}