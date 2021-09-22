/*
 * Relays.h
 *
 * Created: 4-6-2020 10:35:02
 *  Author: Nick
 */ 


#ifndef RELAYS_H_
#define RELAYS_H_

void set_relay(bool value, uint8_t relay)
{
	switch (relay)
	{
		case 1:
		if (value == true)
		{
			PORTR_OUTSET = (1<<PIN1_bp);
		}
		else
		{
			PORTR_OUTCLR = (1<<PIN1_bp);
		}
		break;
		
		case 2:
		if (value == true)
		{
			PORTR_OUTSET = (1<<PIN0_bp);
		}
		else
		{
			PORTR_OUTCLR = (1<<PIN0_bp);
		}
		break;
		
		case 3:
		if (value == true)
		{
			PORTQ_OUTSET = (1<<PIN3_bp);
		}
		else
		{
			PORTQ_OUTCLR = (1<<PIN3_bp);
		}
		break;
		
		case 4:
		if (value == true)
		{
			PORTQ_OUTSET = (1<<PIN2_bp);
		}
		else
		{
			PORTQ_OUTCLR = (1<<PIN2_bp);
		}
		break;
		
		case 5:
		if (value == true)
		{
			PORTQ_OUTSET = (1<<PIN1_bp);
		}
		else
		{
			PORTQ_OUTCLR = (1<<PIN1_bp);
		}
		break;
		
		case 6:
		if (value == true)
		{
			PORTQ_OUTSET = (1<<PIN0_bp);
		}
		else
		{
			PORTQ_OUTCLR = (1<<PIN0_bp);
		}
		break;
	}
}


#endif /* RELAYS_H_ */