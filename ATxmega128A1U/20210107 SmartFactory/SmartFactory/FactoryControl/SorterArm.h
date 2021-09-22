/*
 * Elevator.h
 *
 * Created: 27-11-2020 12:37:02
 *  Author: Wout
 */ 


#ifndef SORTERARM_H_
#define SORTERARM_H_

#include "Stepperdriver.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SD_ADD_TIME ((float) 1.4)	//sec, TODO regel weghalen als stepperdriver uitgelezen kan worden
#define TIMER_COMP_VALUE 23438		//TODO regel weghalen als stepperdriver uitgelezen kan worden
#define SA_SWITCH(pin_bm) (!(PORTJ_IN&pin_bm))
//kijk voor MOTOR_ID defines in Stepperdriver.h

typedef const struct SorterArm {
	uint8_t switch_pin;		//_bm
	uint8_t minpos;			//niet < 0 maken
	uint8_t maxpos;			//niet < minpos maken
	int steps_per_position;	//let erop dat de waarde uit (maxpos-minpos)*steps_per_position in een uint16_t moet passen
	uint8_t motor_id;
	uint16_t motor_speed;
} SorterArm_t;

/*
 * Voor het aanmaken van een nieuwe sorterarm kan je onderstaande struct dupliceren met aangepaste parameters die 
 * het beste bij de hardware passen. Alleen de "blockly functie"s in SorterArm.cpp en de blocks in de website 
 * moeten wel aangepast of toegevoegd worden. Pas ook de ISR in main.cpp aan. 
 * Alle sorterarms gebruiken standaard PORTJ (optocouplers). 
 */
SorterArm_t sa1 = {
	PIN0_bm,
	0,
	2,
	2000,
	SORTER_MOTOR_ID,
	0x02FF
};


void MoveSorterArmDistance(bool dir, uint16_t amount);
void MoveSorterArmIndex(uint16_t i);
uint16_t SorterArmPosition();
bool SorterArmReady();
void StopSorterArm();
void MoveSADistance(bool dir, uint16_t amount, SorterArm_t *sa);
bool LocatieIsBereikbaar(bool dir, uint16_t amount, SorterArm_t *sa);
bool LocatieIsBereikbaarSet(bool dir, uint16_t amount, SorterArm_t *sa);
void MoveSAIndex(uint16_t i, SorterArm_t *sa);
uint16_t SAPosition(uint8_t switch_pin);
void SetSAPosition(uint8_t i, uint8_t switch_pin);
bool SAReady(SorterArm_t *sa);
void MoveSorterArmFixed(bool direction, uint16_t steps, SorterArm_t *sa);
void StopSA(SorterArm_t *sa);
void MoveSorterArm(bool direction, SorterArm_t *sa);
void HomeSorterArm(SorterArm_t *sa);
void SorterArmISR(SorterArm_t *sa);
void SASetPullDown(uint8_t switch_pin);
void SASetInterrupt(uint8_t switch_pin);

void SetSATime(uint8_t i, uint8_t switch_pin); //TODO weghalen als stepperdrivers uitgelezen kunnen worden
uint8_t SATime(uint8_t switch_pin); //TODO weghalen als stepperdrivers uitgelezen kunnen worden
void initSATimer(); //TODO weghalen als stepperdrivers uitgelezen kunnen worden


#ifdef __cplusplus
}
#endif

#endif /* ELEVATOR_H_ */