/*
 * SorterArm.cpp
 *
 *  Created: 29-3-2021 11:35:52
 *  Author: Jon, basis Wout
 */


 /*
  * TODO SAReady() moet stepper controller uitlezen of deze klaar is met het bereiken van
  * het aantal stappen.
  *
  * TODO wanneer een nieuw blockly programma wordt geuploaded en de schakelaar is ingedrukt,
  * dan start de arm niet totdat de stepper handmatig van de switch af is gedraaid. Dit kan
  * ongewenst zijn voor de gebruiker.
  */

 #include "SorteerArm.h"

  /*
   * Onderstaande variabelen geven mogelijkheid tot 8 verschillende sorterarms, met elk een byte
   * (64/8=8) voor sa_position. MAXPOS en MINPOS moeten dus een waarde van 0 t/m 255 hebben.
   * De positie van de bits per sorterarm worden bijgehouden met de switch_pin parameter in de structs.
   */

volatile bool saIsLeft, saIsRight;

/* stop stepper */
//void StopSA()
//{
	//char data[] = { MOTOR_OFF };
	//uint16_t motor_id = 0x0A;
	//stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);
//
//}


/* beweeg stepper oneindig */
void MoveSorterArm(bool direction)
{
		uint16_t motor_id = 0x0A;
		uint16_t motor_speed = 500;
		uint16_t steps = 5000;

		char directiondata[] = { direction };
		stepperWriteRegister(DIRECTION_REG, directiondata, sizeof(directiondata) / sizeof(*directiondata), motor_id, USARTE1);
		char data[] = { (uint8_t)(motor_speed >> 8),(uint8_t)motor_speed,(uint8_t)(steps >> 8),(uint8_t)steps,direction,MOTOR_PWR_MIN,MOTOR_ON };
		stepperWriteRegister(STEPS_PS_HREG, data, sizeof(data) / sizeof(*data), motor_id, USARTE1);

	/* https://stackoverflow.com/questions/11193800/c-bit-operations-copy-one-bit-from-one-byte-to-another-byte */
	// sa_direction = (sa_direction & ~(sa->switch_pin)) | (((uint8_t)direction << __builtin_ctz(sa->switch_pin)) & sa->switch_pin);
}


//void HomeSorterArm()
//{
//}

void SorteerarmLinksISR() {
	saIsLeft = true;
	saIsRight = false;
	StopSA();
}

void SorteerArmRechtsISR() {
	saIsLeft = false;
	saIsRight = true;
	StopSA();
}


// Zet pinnen van de sorterarm als input-pullup
void SASetPullDown(uint8_t switch_pin_left, uint8_t switch_pin_right)
{
	switch (switch_pin_left)				//pulldown
	{
	case PIN0_bm: PORTJ_PIN0CTRL |= PORT_OPC_WIREDORPULL_gc;  PORTJ_PIN1CTRL |= PORT_OPC_WIREDORPULL_gc; break;
	case PIN1_bm: PORTJ_PIN1CTRL |= PORT_OPC_WIREDORPULL_gc;  PORTJ_PIN2CTRL |= PORT_OPC_WIREDORPULL_gc; break;
	case PIN2_bm: PORTJ_PIN2CTRL |= PORT_OPC_WIREDORPULL_gc;  PORTJ_PIN3CTRL |= PORT_OPC_WIREDORPULL_gc; break;
	case PIN3_bm: PORTJ_PIN3CTRL |= PORT_OPC_WIREDORPULL_gc;  PORTJ_PIN4CTRL |= PORT_OPC_WIREDORPULL_gc; break;
	case PIN4_bm: PORTJ_PIN4CTRL |= PORT_OPC_WIREDORPULL_gc;  PORTJ_PIN5CTRL |= PORT_OPC_WIREDORPULL_gc; break;
	}

	PORTJ_DIR &= ~(switch_pin_left);		//pin set left as input
	PORTJ_DIR &= ~(switch_pin_right);		//pin set right as input
}


// Zet interrupts aan op de sorterarm pinnen
void SASetInterrupt(uint8_t switch_pin_left, uint8_t switch_pin_right)
{
	PORTJ_INT1MASK |= switch_pin_left;		//pin listen interrupt left
	PORTJ_INT1MASK |= switch_pin_right;		//pin listen interrupt right

	switch (switch_pin_left)					//sense both edges
	{
	case PIN0_bm: PORTJ_PIN0CTRL |= PORT_ISC_BOTHEDGES_gc, PORTJ_PIN1CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	case PIN1_bm: PORTJ_PIN1CTRL |= PORT_ISC_BOTHEDGES_gc, PORTJ_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	case PIN2_bm: PORTJ_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc, PORTJ_PIN3CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	case PIN3_bm: PORTJ_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc, PORTJ_PIN4CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	case PIN4_bm: PORTJ_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc, PORTJ_PIN5CTRL |= PORT_ISC_BOTHEDGES_gc; break;
	}

	PORTJ_INTCTRL |= PORT_INT1LVL0_bm;	//enable interrupt at low level

	//gebruik vector PORTJ_INT1_vect in main.cpp en roep SorterArmISR() aan
}