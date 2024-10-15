/* LM35 temperature sensor driver
 * LM35.h
 *
 *  Created on: Oct 12, 2023
 *      Author: mario kaldas
 */

#ifndef LM35_H_
#define LM35_H_

#include "MCAL/ADC.h"


/*****************************************************************************
 *                                 Definitions
 * *************************************************************************/

#define MAX_TEMPERATURE 150
#define MAX_VOLT 1.5
#define CHANNEL 2

/****************************************************************************
 *                             Functions prototypes
 * ************************************************************************/

uint8 LM35_getTemperature(void);


#endif /* LM35_H_ */
