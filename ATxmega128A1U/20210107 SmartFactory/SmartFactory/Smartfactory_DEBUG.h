/*
 * Smartfactory_DEBUG.h
 *
 * Created: 23-8-2021 13:48:15
 *  Author: TD1
 */ 


#ifndef SMARTFACTORY_DEBUG_H_
#define SMARTFACTORY_DEBUG_H_

#include "UART.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_OUT(x) USART_TransmitString(USARTD0, x)
#else
#define DEBUG_OUT(x)
#endif


#endif /* SMARTFACTORY_DEBUG_H_ */