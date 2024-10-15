/*
 * LED.h
 *
 *  Created on: Jul 3, 2024
 *      Author: mario
 */

#ifndef LED_H_
#define LED_H_

/* Please configure pins and positive or negative logic before use */

#include"MCAL/std_types.h"
#include"MCAL/GPIO.h"



/***************************************************************************
 *                              LED's definition
 *************************************************************************** */

#define LED_PORT PORTF_ID

#define RED 1
#define BLUE 2
#define GREEN 3


/***************************************************************************
 *                              User-defined types
 *************************************************************************** */

#define POSITIVE_LOGIC


#ifdef POSITIVE_LOGIC

typedef enum{

    LED_OFF,LED_ON
}LED_configType;

#endif

#ifdef NEGATIVE_LOGIC

typedef enum{

    LED_ON,LED_OFF
}LED_configType;

#endif

/***************************************************************************
 *                           Functions declaration
 *************************************************************************** */

void LED_init(uint8 led_num);
void LED_set(uint8 led_num, LED_configType value);


#endif /* LED_H_ */
