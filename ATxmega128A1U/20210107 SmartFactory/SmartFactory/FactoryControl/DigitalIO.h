/*
 * DigitalIO.h
 *
 * Created: 4-6-2020 10:30:41
 *  Author: Nick
 */ 


#ifndef DIGITALIO_H_
#define DIGITALIO_H_

bool IO_ReadWrite(bool value, uint8_t io_port)
{
	switch(io_port)
	{
		case 1:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN7_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN7_bp);
		}
		return (PORTK_IN &(1<<PIN7_bp));
		break;
		
		case 2:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN6_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN6_bp);
		}
		return (PORTK_IN &(1<<PIN6_bp));
		break;
		
		case 3:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN5_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN5_bp);
		}
		return (PORTK_IN &(1<<PIN5_bp));
		break;
		
		case 4: //Lift limit switches
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN4_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN4_bp);
		}
		return (PORTK_IN &(1<<PIN4_bp));
		break;
		
		case 5:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN3_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN3_bp);
		}
		return (PORTK_IN &(1<<PIN3_bp));
		break;
		
		case 6:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN2_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN2_bp);
		}
		return (PORTK_IN &(1<<PIN2_bp));
		break;
		
		case 7:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN1_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN1_bp);
		}
		return (PORTK_IN &(1<<PIN1_bp));
		break;
		
		case 8:
		if (value == true)
		{
			PORTK_OUTSET = (1<<PIN0_bp);
		}
		else
		{
			PORTK_OUTCLR = (1<<PIN0_bp);
		}
		return (PORTK_IN &(1<<PIN0_bp));
		break;
		
		case 9:
		if (value == true)
		{
			PORTJ_OUTSET = (1<<PIN7_bp);
		}
		else
		{
			PORTJ_OUTCLR = (1<<PIN7_bp);
		}
		return (PORTJ_IN &(1<<PIN7_bp));
		break;
		
		case 10:
		if (value == true)
		{
			PORTJ_OUTSET = (1<<PIN6_bp);
		}
		else
		{
			PORTJ_OUTCLR = (1<<PIN6_bp);
		}
		return (PORTJ_IN &(1<<PIN6_bp));
		break;
		
		case 11:
		if (value == true)
		{
			PORTH_OUTSET = (1<<PIN7_bp);
		}
		else
		{
			PORTH_OUTCLR = (1<<PIN7_bp);
		}
		return (PORTH_IN &(1<<PIN7_bp));
		break;
		
		case 12:
		if (value == true)
		{
			PORTH_OUTSET = (1<<PIN6_bp);
		}
		else
		{
			PORTH_OUTCLR = (1<<PIN6_bp);
		}
		return (PORTH_IN &(1<<PIN6_bp));
		break;
		
	}
	return 0;
}


#endif /* DIGITALIO_H_ */