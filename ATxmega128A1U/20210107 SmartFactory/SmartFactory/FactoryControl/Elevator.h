/*
 * Elevator.h
 *
 * Created: 27-11-2020 12:37:02
 *  Author: Wout
 */ 


#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "Stepperdriver.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EV_SWITCH_PIN PIN4_bm //uit PORTK, elevator switches
#define KB_SWITCH_PIN PIN0_bm //uit PORTK, sorterarm switches
//kijk voor MOTOR_ID defines in Stepperdriver.h


void MoveElevator(bool direction);
void StopElevator();
bool ElevatorReady();
void MoveKabelbaan(bool direction);
void StopKabelbaan();
bool KabelbaanReady();
void MoveLift(bool direction, uint8_t motor_id, uint8_t switch_pin);
void StopLift(uint8_t motor_id, uint8_t switch_pin);
bool LiftReady(uint8_t switch_pin);
bool ConfLift(bool direction, uint8_t switch_pin);
void ResetLift(uint8_t switch_pin);
void LiftISR(uint8_t motor_id, uint8_t switch_pin);
void EVSetPullUp(uint8_t switch_pin);
void EVSetInterrupt(uint8_t switch_pin);


#ifdef __cplusplus
}
#endif

#endif /* ELEVATOR_H_ */