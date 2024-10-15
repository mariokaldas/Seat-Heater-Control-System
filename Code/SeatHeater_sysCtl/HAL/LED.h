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

/*
 * NOTE:
 *
 * If you want to use more than one port, add port definition with extension _ADD to it
 * and begin pin numbers with 8
 *
 *  */

#define LED_PORT        PORTF_ID
#define LED_PORT_ADD    PORTB_ID

#define LED_DRIVER_RED         1    /* PF1 */
#define LED_DRIVER_BLUE        2    /* PF2 */
#define LED_DRIVER_GREEN       3    /* PF3 */

#define LED_PASSENGER_RED      8    /* PB1 */
#define LED_PASSENGER_BLUE     9    /* PB2 */
#define LED_PASSENGER_GREEN    10   /* PB3 */

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
