/*
 * LED.c
 *
 *  Created on: Jul 3, 2024
 *      Author: mario
 */

#include"LED.h"

/***************************************************************************
 *                          Functions definition
 *************************************************************************** */

void LED_init(uint8 led_num){

    GPIO_setupPinDirection(LED_PORT, led_num, PIN_OUTPUT);
}


void LED_set(uint8 led_num, LED_configType value){

    GPIO_writePin(LED_PORT, led_num, value);

}
