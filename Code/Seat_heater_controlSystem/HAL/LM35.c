/* LM35 temperature sensor driver
 * LM35.c
 *
 *  Created on: Oct 12, 2023
 *      Author: mario magdy
 */

#include"LM35.h"

/****************************************************************************
 *                             Functions definition
 * ************************************************************************/

uint8 LM35_getTemperature(void){

uint8 temp;
uint16 adc_value;


#ifdef POLLING
adc_value = ADC_readChannel(CHANNEL);
#endif

#ifdef INTERRUPT
ADC_readChannel(CHANNEL);
adc_value = g_channelReading;
#endif

temp = (uint8)(((uint32)adc_value*MAX_TEMPERATURE*ADC_V_REF)/(MAX_VOLT*ADC_MAX_VALUE));

return temp;
}//end LM35_getTemperature

