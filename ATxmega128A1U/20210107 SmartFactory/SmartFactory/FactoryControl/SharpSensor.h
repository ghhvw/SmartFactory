/*
 * AnalogI.h
 *
 * Created: 25-11-2020 13:49:11
 *  Author: Wout
 */ 


#ifndef SHARPSENSOR_H_
#define SHARPSENSOR_H_

uint8_t ReadSharpSensor(uint8_t sensor)
{
	uint8_t val = I_AnalogRead(ADCA, sensor);
	
	switch(val)
	{
		case 250 ... 255:
		return 4; //centimeter
		break;
		
		case 245 ... 249:
		return 5; //centimeter
		break;
		
		case 240 ... 244:
		return 7; //centimeter
		break;
		
		case 235 ... 239:
		return 8; //centimeter
		break;
		
		case 230 ... 234:
		return 9; //centimeter
		break;
		
		case 200 ... 229:
		return 10; //centimeter
		break;
		
		case 190 ... 199:
		return 11; //centimeter
		break;
		
		case 170 ... 189:
		return 12; //centimeter
		break;
		
		case 155 ... 169:
		return 13; //centimeter
		break;
		
		case 140 ... 154:
		return 14; //centimeter
		break;
		
		case 110 ... 119:
		return 16; //centimeter
		break;
		
		case 80 ... 99:
		return 20; //centimeter
		break;
		
		case 60 ... 79:
		return 25; //centimeter
		break;
		
		default:
		return 30;
		break;
	}
}

#endif /* SHARPSENSOR_H_ */