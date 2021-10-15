/*
 *  Kleursensor.cpp
 *
 *  @Created: 14/10/2021 09:13:27
 *  @Author: Yannick
 */ 

 #include "Kleursensor.h"

 #define DEBUG_OUT(X) USART_TransmitString(USARTD0, X)


 /**
   * @brief  Initializes the color sensor
   * @param  None
   * @retval None
   */
void initColorSensor(void){
    PORTJ_DIR &= ~(PIN6_bm);	//set pin as input
	PORTH_DIR |= PIN6_bm | PIN7_bm;	//set pins as output	
}

/**
  * @brief  Read color sensor multiple times and return the 'average color' in frequency
  * @param  None
  * @def    DIFFERENTCOLORS = ammount of different colors (3)
  *         AVERAGECOLORS = ammount of samples taken
  * @retval color (#rrggbb) retreived from the color frequency
  */
uint16_t ReadColourSensor(void){
	uint16_t storeOneColor[AVERAGECOLORS];
	uint8_t RedGreenBlue[DIFFERENTCOLORS];

	for (uint8_t desiredColor=0;desiredColor<DIFFERENTCOLORS;desiredColor++){//Read Red Green and Blue apart
        for (uint8_t i=0;i<AVERAGECOLORS;i++){//sample one color 5 times and take the average
            storeOneColor[i] = getColor(desiredColor);
        }
        //map color frequency to RGB and store in array
        /*FrequencyToColourVal(freq, color)
        calcAverageArray(array, size)*/
        RedGreenBlue[desiredColor] = FrequencyToColourVal(calcAverageArray(storeOneColor, AVERAGECOLORS), desiredColor);
    }
    uint8_t redColor     = RedGreenBlue[REDCASE];
    uint8_t greenColor   = RedGreenBlue[GREENCASE];
    uint8_t blueColor    = RedGreenBlue[BLUECASE];
	
	DEBUG_OUT("color = #");
	USART_Transmit_Number(USARTD0, (uint16_t) redColor);
	DEBUG_OUT(" ");
	USART_Transmit_Number(USARTD0, (uint16_t) greenColor);
	DEBUG_OUT(" ");
	USART_Transmit_Number(USARTD0, (uint16_t) blueColor);
	DEBUG_OUT("\n\r");
	
    if (redColor < blueColor && redColor < greenColor && redColor < 20){ //color is red
        DEBUG_OUT("color is ORANGE\n\r");
		return 4; //4 equals orange in blockly
    }else if (blueColor < redColor && blueColor < greenColor && greenColor>190){  //color is blue
        DEBUG_OUT("color is BLUE\n\r");
		return 1; //1 equals blue in blockly
    }else if (greenColor < redColor && greenColor < blueColor){ //color is green
        DEBUG_OUT("color is GREEN\n\r");
		return 2; //2 equals green in blockly
    }else{
		return 0; //0 equals black in blockly
	}
}

/**
  * @brief  map the frequency from sensor to RGB value 0-255 (FF)
  * @param  freq    frequency of the color
  *         color   desired color
  * @retval RGB value 
  */
uint8_t FrequencyToColourVal(uint16_t freq, uint8_t color) {
	if (!freq) { return 0; } //bad frequency, don't return a color
	
    uint8_t RGBValue = 0;
	switch (color) {
        //if the frequency is low there is a high color occurance
		case REDCASE: //red
		    RGBValue = map(freq, MINREDFREQ, MAXREDFREQ, 255, 0);
            break;
		case GREENCASE: //green
		    RGBValue = map(freq, MINGREENFREQ, MAXGREENFREQ, 255, 0);
            break;
		case BLUECASE: //blue
		    RGBValue = map(freq, MINBLUEFREQ, MAXBLUEFREQ, 255, 0);
            break;
	}
	//check on out of bounds
    if (RGBValue<0) { RGBValue = 0; }
	if (RGBValue>255) { RGBValue = 255; }
	
	return RGBValue;
}

/**
  * @brief  reads out raw value of the desired color
  * @param  color you want to read out (0 = red, 1 = green, 2 = blue)
  * @retval Selected color (if color = 0 the raw value of red is returned)
  */
uint16_t getColor(uint8_t color){
/**     Select desired color using this table
  * 
  *     =========================
  *     |Photodiode |S2   |S3   |
  *     |-----------|-----|-----|
  *     |Red        |Low  |Low  |
  *     |Green      |HiGH |High |
  *     |Blue       |Low  |High |
  *     |No filter  |High |Low  |
  *     =========================
  */
   switch (color) {
        case REDCASE: //red
		    PORTH_OUTCLR = (1<<PIN_S2); //S2, to LOW
		    PORTH_OUTCLR = (1<<PIN_S3); //S3, to LOW
		    break;
		
		case GREENCASE: //green
		    PORTH_OUTSET = (1<<PIN_S2); //S2, to HIGH
		    PORTH_OUTSET = (1<<PIN_S3); //S3, to HIGH
    		break;
		
		case BLUECASE: //blue
	    	PORTH_OUTCLR = (1<<PIN_S2); //S2, to LOW
    		PORTH_OUTSET = (1<<PIN_S3); //S3, to HIGH
		    break;
    }
    return (uint16_t) pulseIn(&PORTJ, PIN6_bm, 0, 10000); //pin 10
}

/**
  * @brief  calculate average value in array
  * @param  a       array
  *         size    size of the array
  * @retval sum = average of the array
  */
uint16_t calcAverageArray(uint16_t *a, uint8_t size) {
	unsigned long sum = 0;
	for (uint8_t i=0; i<size; i++) {
		sum += a[i];
	}
	sum /= size;
	return sum;
}

/* blockly functie - functie ter vervanging van werking met char* omdat blockly problemen met kleuren => assembly heeft */
uint16_t SelectColour(uint16_t i) { 
	return i; 
}

/* blockly functie */
bool CompareColours(uint16_t c1, uint16_t c2) {
	return (c1 == c2);
}

/**
  * @brief  map value (arduino function)
  * @reference https://www.arduino.cc/reference/en/language/functions/math/map/ 
  * @retval the mapped value
  */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}