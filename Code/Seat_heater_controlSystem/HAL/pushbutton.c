/* pushbutton driver
 * pushbutton.c
 *
 *  Created on: Nov 30, 2023
 *      Author: mario kaldas
 */
#include"pushbutton.h"

#include "MCAL/gpio.h"

/***************************************************************************
 *                          Functions definition
 *************************************************************************** */
void PB_init(uint8 PB_num){

	GPIO_setupPinDirection(PB_PORT,PB_num,PIN_INPUT);
}


uint8 PB_getReading(uint8 PB_num){

	return GPIO_readPin(PB_PORT,PB_num);
}


