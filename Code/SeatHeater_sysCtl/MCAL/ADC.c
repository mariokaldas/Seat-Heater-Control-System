/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Source file for the ARM Cortex M4 ADC driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#include"ADC.h"
#include"NVIC.h"

/***************************************************************************
 *                              Configurations
 * *************************************************************************/

/* Please just change the boolean variable ONLY */

ADC_configType configs = {
                          {
                           {GPIO_PORTE_BASE_ADDRESS,3,TRUE},    /* channel AIN0  PE3  */
                           {GPIO_PORTE_BASE_ADDRESS,2,TRUE},    /* channel AIN1  PE2  */
                           {GPIO_PORTE_BASE_ADDRESS,1,FALSE},    /* channel AIN2  PE1  */
                           {GPIO_PORTE_BASE_ADDRESS,0,FALSE},    /* channel AIN3  PE0  */
                           {GPIO_PORTD_BASE_ADDRESS,3,FALSE},    /* channel AIN4  PD3  */
                           {GPIO_PORTD_BASE_ADDRESS,2,FALSE},    /* channel AIN5  PD2  */
                           {GPIO_PORTD_BASE_ADDRESS,1,FALSE},    /* channel AIN6  PD1  */
                           {GPIO_PORTD_BASE_ADDRESS,0,FALSE},    /* channel AIN7  PD0  */
                           {GPIO_PORTE_BASE_ADDRESS,5,FALSE},    /* channel AIN8  PE5  */
                           {GPIO_PORTE_BASE_ADDRESS,4,FALSE},    /* channel AIN9  PE4  */
                           {GPIO_PORTB_BASE_ADDRESS,4,FALSE},    /* channel AIN10 PB4  */
                           {GPIO_PORTB_BASE_ADDRESS,5,FALSE}     /* channel AIN11 PB5  */
                          }
};

/***************************************************************************
                          Global variables
 ****************************************************************************/

#ifdef INTERRUPT

/* Used in case of interrupt */
volatile uint16 g_channelReading;

#endif

/**************************************************************************
 *                    Interrupt service routine
 * ***********************************************************************/

#ifdef INTERRUPT

void ADC0_handler(void){

    /* Copy result into the global variable */
    g_channelReading = ADC0_ADCSSFIFO3;

    /* Clear interrupt bit */
    ADC0_ADCISC |= (1<<3);

}

#endif
/*************************************************************************
 *                           Functions definition
 * **********************************************************************/

void ADC_init(const ADC_configType* ptr){

    /* Channel index is counter variable to loop into channels array */
    uint8 ch_i;
    uint32 *ch_ptr;

    /* enable clock for ADC0 module */
    ADC_RCGCADC |= (1<<0);

    /* make sure ADC0 is ready */
    while((ADC_PRADC & (1<<0)) == 0);

    /* Enable clock for port B,D and E */
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | (1<<4) | (1<<3) | (1<<1);

    /* Make sure that clock enabled for these ports */
    while((SYSCTL_PRGPIO_R & (1<<1)) == 0){};
    while((SYSCTL_PRGPIO_R & (1<<3)) == 0){};
    while((SYSCTL_PRGPIO_R & (1<<4)) == 0){};


    /* Disable sample sequencer 3 (which will be used) during configuration of SS3 */
    ADC0_ADCACTSS &= ~(1<<3);

    /* Trigger source of SS3 is GPIO external pin */
    ADC0_ADCEMUX = (ADC0_ADCEMUX & 0xFFFF0FFF) |(0x0<<12);

    /* Control bits of SS3 :
     *
     * bit3 (TS0)  = 0 >>> no temperature sensor used
     * bit2 (IE0)  = 1 >>> use interrupt
     * bit1 (END0) = 1 >>> end of sequence (necessary thing for this MCU)
     * bit0 (D0)   = 0 >>> no differential input
     *
     *  */
    ADC0_ADCSSCTL3 |= 0x6;

    /* Enable interrupts for SS3 */
    ADC0_ADCIM |= (1<<3);

    for(ch_i=0;ch_i<ADC_NUMBER_OF_CHANNELS;ch_i++){

        if(ptr->channels[ch_i].active == FALSE){

            continue;
        }
        else{

            ch_ptr = (uint32*)(ptr->channels[ch_i].port);


            /* Configure the direction register according to the channel port and pin */
            *((uint32*)((uint8*)ch_ptr + PORT_DIR_REG_OFFSET)) &= ~(1<<ptr->channels[ch_i].pin);

            /* Configure the alternative function select register according to the channel port and pin */
            *((uint32*)((uint8*)ch_ptr + PORT_ALT_FUNC_REG_OFFSET)) |= (1<<ptr->channels[ch_i].pin);

            /* Configure the digital enable register according to the channel port and pin */
            *((uint32*)((uint8*)ch_ptr + PORT_DIGITAL_ENABLE_REG_OFFSET)) &= ~(1<<ptr->channels[ch_i].pin);

            /* Configure the analog enable register according to the channel port and pin */
            *((uint32*)((uint8*)ch_ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET)) |= (1<<ptr->channels[ch_i].pin);

            /* Enable SS3 */
            ADC0_ADCACTSS |= (1<<3);

        }
    }

#ifdef INTERRUPT

    NVIC_EnableIRQ(ADC0_SS3_IRQ);
    NVIC_SetPriorityIRQ(ADC0_SS3_IRQ,6);

#endif
}

#ifdef POLLING
uint16 ADC_readChannel(uint8 ch_num){

    /* Configure channel number in SS3 to the required channel to be read */
    ADC0_ADCSSMUX3 = (ADC0_ADCSSMUX3 & 0X0) | (ch_num);

    /* Start conversion */
    ADC0_ADCPSSI |= (1<<3);

    /* Check on RIS bit in SS3 statues to make sure conversion is completed */
    while((ADC0_ADCRIS & (1<<3)) != (1<<3));

    /* Clear interrupt bit */
    ADC0_ADCISC |= (1<<3);

    /* Return the result */
    return ADC0_ADCSSFIFO3;
}
#endif

#ifdef INTERRUPT
void ADC_readChannel(uint8 ch_num){

    /* Configure channel number in SS3 to the required channel to be read */
    ADC0_ADCSSMUX3 = (ADC0_ADCSSMUX3 & 0) | (ch_num);

    /* Start conversion */
    ADC0_ADCPSSI |= (1<<3);

}
#endif
