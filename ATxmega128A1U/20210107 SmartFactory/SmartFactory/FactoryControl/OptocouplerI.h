/*
 * OptocouplerI.h
 *
 * Created: 2-12-2020 15:29:21
 *  Author: Wout & Sjors
 */ 


#ifndef OPTOCOUPLERI_H_
#define OPTOCOUPLERI_H_


//Optocoupler pin bitmasks:
#define OPTO0 PIN0_bm
#define OPTO1 PIN1_bm
#define OPTO2 PIN2_bm
#define OPTO3 PIN3_bm
#define OPTO4 PIN4_bm
#define OPTO5 PIN5_bm

#define OPTOS_bm OPTO0 | OPTO1 | OPTO2 | OPTO3 | OPTO4| OPTO5 

#define OPTO_DIRCLR PORTJ_DIRCLR
#define OPTO_IN		PORTJ_IN

/**
 * \brief - Set all optocouplers to input
 */
void initOptocouplers(){
	OPTO_DIRCLR = OPTOS_bm;
}

/**
 * \brief - Read the level of an optocoupler
 */
bool I_OptocouplerRead(uint8_t io_port)
{
	switch(io_port)
	{
		case 0: return OPTO_IN & OPTO0;
		case 1: return OPTO_IN & OPTO1;
		case 2: return OPTO_IN & OPTO2;
		case 3: return OPTO_IN & OPTO3;
		case 4: return OPTO_IN & OPTO4;
		case 5: return OPTO_IN & OPTO5;
		default: return 0;
	}
}


#endif /* OPTOCOUPLERI_H_ */