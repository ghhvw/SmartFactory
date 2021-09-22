/*
 * SorterArm.cpp
 *
 * Created: 10/12/2020 21:28:45
 *  Author: Wout
 */ 

/*
 * TODO SAReady() moet stepper controller uitlezen of deze klaar is met het bereiken van 
 * het aantal stappen. 
 *
 * TODO wanneer een nieuw blockly programma wordt geuploaded en de schakelaar is ingedrukt, 
 * dan start de arm niet totdat de stepper handmatig van de switch af is gedraaid. Dit kan 
 * ongewenst zijn voor de gebruiker. 
 */

#include "SorterArm.h"

/*
 * Onderstaande variabelen geven mogelijkheid tot 8 verschillende sorterarms, met elk een byte 
 * (64/8=8) voor sa_position. MAXPOS en MINPOS moeten dus een waarde van 0 t/m 255 bebben. 
 * De positie van de bits per sorterarm worden bijgehouden met de switch_pin parameter in de structs. 
 */
uint8_t sa_homing_succes = 0;	//op 0 laten, wordt 1 na homing
uint8_t sa_isr_ready = 0;		//op 0 laten, wordt 1 na homing
uint8_t sa_direction = 0;
uint64_t sa_position = 0;		//startwaarde per sorterarm wordt MINPOS na homing

uint64_t sa_timer_time = 0;		//sec, TODO weghalen als stepperdrivers uitgelezen kunnen worden
//TODO weghalen ISR hieronder als stepperdrivers uitgelezen kunnen worden
ISR(TCC1_CCA_vect) {
	//triggered elke seconde
	TCC1.CNT = 0;
	for (uint8_t i=0; i<8; i++) {
		if (SATime(1<<i) > 0) {
			SetSATime(SATime(1<<i)-1, 1<<i);
		}
	}
//	PORTH_OUTTGL |= (1<<4)|(1<<5);
}



/* 
 * Bij meer dan 1 sorterarms zouden de SorterArm blocklys & de functies met "blockly functie" 
 * erboven aangepast moeten worden om een ID te vragen. Of dan kunnen er extra blocklys en 
 * functies toegevoegd worden die met een andere sorterarm struct werken. Pas ook de ISR in 
 * main.cpp aan. 
 */

/* blockly functie */
void MoveSorterArmDistance(bool dir, uint16_t amount) { MoveSADistance(dir, amount, &sa1); }


/* blockly functie */
void MoveSorterArmIndex(uint16_t i) { MoveSAIndex(i, &sa1); }


/* blockly functie */
uint16_t SorterArmPosition() { return SAPosition(sa1.switch_pin); }


/* blockly functie */
bool SorterArmReady() { return SAReady(&sa1); }


void StopSorterArm() { StopSA(&sa1); }


/* beweeg de sorteerarm naar een positie van MINPOS t/m MAXPOS */
void MoveSAIndex(uint16_t i, SorterArm_t *sa)
{
	bool d = (i > SAPosition(sa->switch_pin));
	MoveSADistance(d,abs((int8_t) SAPosition(sa->switch_pin)-(int8_t) i), sa);
}


/* beweeg de sorteerarm "amount" posities naar links of naar rechts */
void MoveSADistance(bool dir, uint16_t amount, SorterArm_t *sa)
{
	//homing is niet afgerond en switch is niet ingedrukt (veiligheid in combinatie met ISR) --> eerste homing
	cli(); //global interrupt disable, voorkom dat stepper verkeerde richting op kan gaan bij interrupt
	if (!(sa_homing_succes & sa->switch_pin) && !SA_SWITCH(sa->switch_pin)) {
		LocatieIsBereikbaarSet(dir, amount, sa);
		HomeSorterArm(sa);
		return; //locatie wordt na homing cycle bereikt
	}
	sei(); //global interrupt enable
	
	if (!SAReady(sa)) { return; }																	//sorter arm niet klaar, niet starten
	if (SAPosition(sa->switch_pin)<sa->minpos || SAPosition(sa->switch_pin)>sa->maxpos) { return; }	//huidige positie ongeldig, programmeerfout
	
	//ga naar juiste positie
	if (LocatieIsBereikbaarSet(dir, amount, sa)) {
		MoveSorterArmFixed(dir, sa->steps_per_position * amount, sa);
	//ga zo dicht mogelijk naar de juiste positie en stop
	} else {
		//direction 1 van switch af, 0 op switch aan
		if (dir) {
			MoveSorterArmFixed(dir, sa->steps_per_position * (sa->maxpos-SAPosition(sa->switch_pin)), sa);
		} else {
			MoveSorterArmFixed(dir, sa->steps_per_position * (SAPosition(sa->switch_pin)-sa->minpos), sa);
		}
	}
}


bool LocatieIsBereikbaar(bool dir, uint16_t amount, SorterArm_t *sa) {
	//direction 1 van switch af, 0 op switch aan
	if (dir) {
		if ((int) (SAPosition(sa->switch_pin) + (int) amount) <= sa->maxpos) { //locatie is bereikbaar
			return 1;
		} else {
			return 0;
		}
	} else {
		if ((int) (SAPosition(sa->switch_pin) - (int) amount) >= sa->minpos) { //locatie is bereikbaar
			return 1;
		} else {
			return 0;
		}
	}
}


/* stelt ook nieuwe locatie in */
bool LocatieIsBereikbaarSet(bool dir, uint16_t amount, SorterArm_t *sa) {
	bool result = LocatieIsBereikbaar(dir, amount, sa);
	if (dir) {
		if (result) {
			SetSAPosition((SAPosition(sa->switch_pin) + amount), sa->switch_pin);
		} else {
			SetSAPosition(sa->maxpos, sa->switch_pin);
		}
	} else {
		if (result) {
			SetSAPosition((SAPosition(sa->switch_pin) - amount), sa->switch_pin);
		} else {
			SetSAPosition(sa->minpos, sa->switch_pin);
		}
	}
	return result;
}


/* 
 * de bitmask van switch_pin wordt gebruikt om te berekenen hoeveel sa_position 
 * geshift moet worden om de waarde voor deze sorteerarm te krijgen 
 */
uint16_t SAPosition(uint8_t switch_pin)
{
	uint8_t i = (uint8_t) (sa_position >> (8*__builtin_ctz(switch_pin)));
	return (uint16_t) i;
}


/* 
 * de bitmask van switch_pin wordt gebruikt om te berekenen hoeveel de inputwaarde 
 * geshift moet worden om naar de locatie van deze sorteerarm te schrijven 
 * http://www.interviewdruid.com/copy-bits-from-one-integer-to-another/ 
 */
void SetSAPosition(uint8_t i, uint8_t switch_pin)
{
	uint64_t ones_mask = ~((uint64_t) 0);			//allemaal 1-en
	ones_mask >>= (64-8);							//...0011111111
	ones_mask <<= (8*__builtin_ctz(switch_pin));
	
	sa_position = (sa_position & ~ones_mask) | (((uint64_t) i << (8*__builtin_ctz(switch_pin))) & ones_mask);
}


bool SAReady(SorterArm_t *sa)
{
	//TODO uitlezen of stepperdriver klaar is met beweging (met motor_id)
	uint8_t stepperdriver_ready = 1; //TODO vervang 1 met leesfunctie
	stepperdriver_ready = (SATime(sa->switch_pin) == 0); //TODO regel weghalen als stepperdriver uitgelezen kan worden
//	_delay_ms(200); //delay zodat stepperdriver niet te veel gerequest wordt
	
	return ((sa_homing_succes & sa->switch_pin) && (sa_isr_ready & sa->switch_pin) && stepperdriver_ready);
}


/* beweeg stepper met vast aantal stappen */
void MoveSorterArmFixed(bool direction, uint16_t steps, SorterArm_t *sa)
{
	if (0 != steps) {
		char directiondata[]={direction};
		stepperWriteRegister(DIRECTION_REG,directiondata,sizeof(directiondata)/sizeof(*directiondata),sa->motor_id, USARTE1);
		char data[]={(uint8_t) (sa->motor_speed >> 8),(uint8_t) sa->motor_speed,(uint8_t) (steps >> 8),(uint8_t) steps,direction,MOTOR_PWR_MIN,MOTOR_ON};
		stepperWriteRegister(STEPS_PS_HREG,data,sizeof(data)/sizeof(*data),sa->motor_id,USARTE1);
	}
	
	/* https://stackoverflow.com/questions/11193800/c-bit-operations-copy-one-bit-from-one-byte-to-another-byte */
	sa_direction = (sa_direction & ~(sa->switch_pin)) | (((uint8_t) direction << __builtin_ctz(sa->switch_pin)) & sa->switch_pin);
	
	if (steps != 0xFFFF) { //TODO weghalen als stepperdrivers uitgelezen kunnen worden
		//de regel hieronder berekend de tijd die de stepperdriver ongeveer nodig is, dit hoeft niet uitgevoerd te worden bij 0xFFFF stappen = oneindig lang draaien
		SetSATime(((float) steps / (float) sa->motor_speed) + ((float) TCC1.CNT / (float) TIMER_COMP_VALUE) + SD_ADD_TIME, sa->switch_pin); //TODO weghalen als stepperdrivers uitgelezen kunnen worden
	}
}


/* stop stepper */
void StopSA(SorterArm_t *sa)
{
	char data[]={MOTOR_OFF};
	stepperWriteRegister(MOTOR_ENABLE_REG, data, sizeof(data)/sizeof(*data),sa->motor_id,USARTE1);

	SetSATime(0, sa->switch_pin); //TODO weghalen als stepperdrivers uitgelezen kunnen worden
}


/* beweeg stepper oneindig */
void MoveSorterArm(bool direction, SorterArm_t *sa)
{
	MoveSorterArmFixed(direction, 0xFFFF, sa);
}


void HomeSorterArm(SorterArm_t *sa)
{
	//switches mogen niet ingedrukt zijn
	SASetPullDown(sa->switch_pin);
	_delay_ms(30);								//storing op pin weg laten gaan
	if (SA_SWITCH(sa->switch_pin)) { return; }	//stepper mag niet starten, er is een schakelaar ingedrukt of kabelbreuk, stop
	
	initSATimer();								//TODO weghalen als stepperdrivers uitgelezen kunnen worden
	SASetInterrupt(sa->switch_pin);				//set interrupts
	MoveSorterArm(0, sa);						//homing cycle starten
}


/* ISR, interrupts moeten aanblijven */
void SorterArmISR(SorterArm_t *sa)
{
	/* interrupt buiten homing procedure om, switch loslaten en opnieuw homing */
	if (sa_homing_succes & sa->switch_pin) {
		if (SA_SWITCH(sa->switch_pin)) {
			//button ingedrukt
			ChangeDirectionStepper(!(sa_direction & sa->switch_pin), sa->motor_id);
			sa_isr_ready &= ~(sa->switch_pin); //voorkom opnieuw starten
		} else {
			//button losgelaten
			sa_homing_succes &= ~(sa->switch_pin);
			MoveSorterArm(0, sa); //start homing procedure
			//TODO misschien aanpassen dat homing alleen gestart wordt als de stepper in beweging was op het moment van de interrupt
		}
		
	/* interrupt van homing process */
	} else {
		if (SA_SWITCH(sa->switch_pin)) {
			//button ingedrukt
			ChangeDirectionStepper(!(sa_direction & sa->switch_pin), sa->motor_id);
		} else {
			//button losgelaten
//			_delay_ms(100); //meer vrije ruimte voor schakelaar
			sa_homing_succes |= sa->switch_pin;
			sa_isr_ready |= sa->switch_pin;
			
			//ga terug naar laatste positie
			uint8_t sa_prev_pos = SAPosition(sa->switch_pin);
			SetSAPosition(sa->minpos, sa->switch_pin);
			if (sa_prev_pos != SAPosition(sa->switch_pin)) {
				MoveSAIndex(sa_prev_pos, sa);
			} else {
				StopSA(sa);
			}
		}
	}
	return;
}


void SASetPullDown(uint8_t switch_pin)
{
	switch(switch_pin)				//pulldown
	{
		case PIN0_bm: PORTJ_PIN0CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN1_bm: PORTJ_PIN1CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN2_bm: PORTJ_PIN2CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN3_bm: PORTJ_PIN3CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN4_bm: PORTJ_PIN4CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN5_bm: PORTJ_PIN5CTRL |= PORT_OPC_WIREDORPULL_gc; break;
		case PIN6_bm: PORTJ_PIN6CTRL |= PORT_OPC_WIREDORPULL_gc; break; //not connected
		case PIN7_bm: PORTJ_PIN7CTRL |= PORT_OPC_WIREDORPULL_gc; break; //not connected
	}
	PORTJ_DIR &= ~(switch_pin);		//pin set as input
}


void SASetInterrupt(uint8_t switch_pin)
{
	PORTJ_INT1MASK |= switch_pin;		//pin listen interrupt
	switch(switch_pin)					//sense both edges
	{
		case PIN0_bm: PORTJ_PIN0CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN1_bm: PORTJ_PIN1CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN2_bm: PORTJ_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN3_bm: PORTJ_PIN3CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN4_bm: PORTJ_PIN4CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN5_bm: PORTJ_PIN5CTRL |= PORT_ISC_BOTHEDGES_gc; break;
		case PIN6_bm: PORTJ_PIN6CTRL |= PORT_ISC_BOTHEDGES_gc; break; //not connected
		case PIN7_bm: PORTJ_PIN7CTRL |= PORT_ISC_BOTHEDGES_gc; break; //not connected
	}
	PORTJ_INTCTRL |= PORT_INT1LVL0_bm;	//enable interrupt at low level
	
	//gebruik vector PORTJ_INT1_vect in main.cpp en roep SorterArmISR() aan
}


//TODO weghalen functie als stepperdrivers uitgelezen kunnen worden
void SetSATime(uint8_t i, uint8_t switch_pin)
{
	uint64_t ones_mask = ~((uint64_t) 0);			//allemaal 1-en
	ones_mask >>= (64-8);							//...0011111111
	ones_mask <<= (8*__builtin_ctz(switch_pin));
	
	sa_timer_time = (sa_timer_time & ~ones_mask) | (((uint64_t) i << (8*__builtin_ctz(switch_pin))) & ones_mask);
}


//TODO weghalen functie als stepperdrivers uitgelezen kunnen worden
uint8_t SATime(uint8_t switch_pin)
{
	uint8_t i = (uint8_t) (sa_timer_time >> (8*__builtin_ctz(switch_pin)));
	return i;
}


//TODO weghalen functie als stepperdrivers uitgelezen kunnen worden
void initSATimer() {
	//FCPU = 24 000 000, 16-bits = 65535, 24MHz/1024/65535 = 0,357687 sec
	TCC1.CTRLB |= TC0_CCAEN_bm;				//enable CTC
	TCC1.INTCTRLB |= TC_CCAINTLVL_LO_gc;	//enable low interrupt level for CTC
	TCC1.CCA = TIMER_COMP_VALUE;			//set compare value
	TCC1.CTRLA |= TC_CLKSEL_DIV1024_gc;		//clock divide
	
	/* gebruik TCC1_CCA_vect */
}
//haal ook "sysclk_enable_peripheral_clock(&TCC1);" weg uit main.cpp