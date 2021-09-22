/*
 * OptocouplerI.h
 *
 * Created: 2-12-2020 15:29:21
 *  Author: Wout
 */ 


#ifndef OPTOCOUPLERI_H_
#define OPTOCOUPLERI_H_

#define OPTO_PD //defined --> pulldown on pins

bool I_OptocouplerRead(uint8_t io_port)
{
	switch(io_port)
	{
		case 0: //sorterarm interrupt schakelaars
		PORTJ_DIR &= ~(PIN0_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN0CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN0_bp));
		break;
		
		case 1:
		PORTJ_DIR &= ~(PIN1_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN1CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN1_bp));
		break;
		
		case 2:
		PORTJ_DIR &= ~(PIN2_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN2CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN2_bp));
		break;
		
		case 3:
		PORTJ_DIR &= ~(PIN3_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN3CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN3_bp));
		break;
		
		case 4:
		PORTJ_DIR &= ~(PIN4_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN4CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN4_bp));
		break;
		
		case 5:
		PORTJ_DIR &= ~(PIN5_bm);	//set pin as input
		#ifdef OPTO_PD
		PORTJ_PIN5CTRL |= PORT_OPC_PULLDOWN_gc;
		#endif
		return (PORTJ_IN &(1<<PIN5_bp));
		break;
		
		//pin 6 & 7 niet verbonden met optocouplers
	}
	return 0;
}


#endif /* OPTOCOUPLERI_H_ */