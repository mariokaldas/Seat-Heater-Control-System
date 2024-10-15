/******************************************************************************
 *
 * Module: Complex driver
 *
 * File Name: Temperature_sensor.h
 *
 * Description: Header file for any Temperature sensor driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#ifndef HAL_TEMPERATURE_SENSOR_H_
#define HAL_TEMPERATURE_SENSOR_H_

#include "MCAL/ADC.h"


/*****************************************************************************
 *                                 Definitions
 * *************************************************************************/
#define TEMPERATURE_MIN             0
#define TEMPERATURE_MAX             45

#define TEMPERATURE_MAX_VOLT        3.3

/* Make sure that channels are configured from ADC driver */

#define TEMPERATURE_DRIVER    AIN0  /* channel AIN0  PE3  */
#define TEMPERATURE_PASSENGER AIN1  /* channel AIN1  PE2  */

/****************************************************************************
 *                             Functions prototypes
 * ************************************************************************/

/* Configure channel in ADC.c configuration */
void TEMPSENSOR_init(void);

/* Pass the channel that connected to the required sensor */
uint8 TEMPSENSOR_getTemperature(uint8 channel);


#endif /* HAL_TEMPERATURE_SENSOR_H_ */
