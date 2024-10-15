/******************************************************************************
 *
 * Module: Complex driver
 *
 * File Name: Temperature_sensor.c
 *
 * Description: Source file for any Temperature sensor driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#include"Temperature_sensor.h"

/****************************************************************************
 *                             Functions definition
 * ************************************************************************/

void TEMPSENSOR_init(void){

    ADC_init(&configs);
}

uint8 TEMPSENSOR_getTemperature(uint8 channel){

    /*
     * The following mathematical equation represents the conversion from any range to any range
     *
     *  value: The input number you want to map.
     *  in_min: The lower bound of the input value’s current range.   (value from ADC)
     *  in_max: The upper bound of the input value’s current range.   (value from ADC that represents the maximum volt from sensor)
     *  out_min: The lower bound of the desired output range.         (minimum range of the sensor (degree celsius))
     *  out_max: The upper bound of the desired output range          (maximum range of the sensor (degree celsius))
     *
     *
     *  Temperature = ( (value - in_min) * (out_max - out_min) / (in_max - in_min) ) + out_min;
     *
     * */


    uint8 Temperature;
    uint32 adc_value;

    /* This variable represents the max value from ADC that sensor inputs */
    uint32 maxADC_sensor;


#ifdef POLLING
    adc_value = ADC_readChannel(channel);
#endif

#ifdef INTERRUPT
    ADC_readChannel(channel);
    adc_value = g_channelReading;
#endif

    maxADC_sensor = (uint32)(((float32)ADC_MAX_VALUE * TEMPERATURE_MAX_VOLT)/ADC_V_REF) ;

    Temperature =
            (uint8)( ( ((float32)(adc_value - ADC_MIN_VALUE) * (TEMPERATURE_MAX - TEMPERATURE_MIN))
                    / (maxADC_sensor - ADC_MIN_VALUE) ) + TEMPERATURE_MIN ) ;

    return Temperature;
}

