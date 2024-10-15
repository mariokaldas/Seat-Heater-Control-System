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

    if(led_num <= (NUM_OF_PINS_PER_PORT-1)){

        GPIO_setupPinDirection(LED_PORT, led_num, PIN_OUTPUT);
    }
    else{

        GPIO_setupPinDirection(LED_PORT_ADD, led_num % (NUM_OF_PINS_PER_PORT-1), PIN_OUTPUT);
    }

}


void LED_set(uint8 led_num, LED_configType value){

    if(led_num <= (NUM_OF_PINS_PER_PORT-1)){

        GPIO_writePin(LED_PORT, led_num, value);
    }
    else{

        GPIO_writePin(LED_PORT_ADD, led_num % (NUM_OF_PINS_PER_PORT-1), value);
    }
}
