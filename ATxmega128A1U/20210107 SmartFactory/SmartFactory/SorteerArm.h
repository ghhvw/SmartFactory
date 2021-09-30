/*
 * SorteerArm.h
 *
 * Created: 29-3-2021 11:35:52
 *  Author: Jon_n
 */ 


#ifndef SORTEERARM_H_
#define SORTEERARM_H_


#include "Stepperdriver.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define SA_SWITCH_PIN_LEFT PIN0_bm
// #define SA_SWITCH_PIN_RIGHT PIN1_bm

//kijk voor MOTOR_ID defines in Stepperdriver.h

typedef const struct SorterArm {
    uint8_t switch_pin_left;  // Pin links
    uint8_t switch_pin_right; // Pin rechts
    uint8_t minpos;			//niet < 0 maken
    uint8_t maxpos;			//niet < minpos maken
    int steps_per_position;	//let erop dat de waarde uit (maxpos-minpos)*steps_per_position in een uint16_t moet passen
    uint8_t motor_id;
    uint16_t motor_speed;
} SorterArm_t;

// * Voor het aanmaken van een nieuwe sorterarm kan je onderstaande struct dupliceren met aangepaste parameters die
// * het beste bij de hardware passen. Alleen de "blockly functie"s in SorterArm.cpp en de blocks in de website
// * moeten wel aangepast of toegevoegd worden. Pas ook de ISR in main.cpp aan.
// * Alle sorterarms gebruiken standaard PORTJ (optocouplers).
// */

SorterArm_t sa1 = {
        PIN0_bm,
        PIN1_bm,
        0,
        2,
        2000,
        SORTER_MOTOR_ID,
        0x02FF
};

void MoveSorterArmTo();
bool SorterarmIsFinnished();
void StopSA();
void MoveSorterArm(bool direction);
void HomeSorterArm();
void SorteerarmLinksISR();
void SorteerArmLinksISR();
void SorteerArmRechtsISR();
void SASetPullDown(uint8_t switch_pin_left);
void SASetInterrupt(uint8_t switch_pin_left);

#ifdef __cplusplus
}
#endif

#endif /* SORTEERARM_H_ */