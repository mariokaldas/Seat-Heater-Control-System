/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for the ARM Cortex M4 ADC driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"

/* DON'T forget to modify the configuration (boolean variable only) */

/**************************************************************************
                                     Registers
****************************************************************************/
/* Required GPIO registers */

#define SYSCTL_RCGCGPIO_R           (*((volatile uint32*)0x400FE608))
#define SYSCTL_PRGPIO_R             (*((volatile uint32*)0x400FEA08))

/* ADC Registers address */

#define ADC_RCGCADC                       (*((volatile uint32*)0x400FE638))
#define ADC_PRADC                         (*((volatile uint32*)0x400FEA38))

#define ADC0_ADCACTSS                     (*((volatile uint32*)0x40038000))
#define ADC0_ADCEMUX                      (*((volatile uint32*)0x40038014))
#define ADC0_ADCSSMUX0                    (*((volatile uint32*)0x40038040))
#define ADC0_ADCSSMUX1                    (*((volatile uint32*)0x40038060))
#define ADC0_ADCSSMUX2                    (*((volatile uint32*)0x40038080))
#define ADC0_ADCSSMUX3                    (*((volatile uint32*)0x400380A0))
#define ADC0_ADCSSCTL0                    (*((volatile uint32*)0x40038044))
#define ADC0_ADCSSCTL1                    (*((volatile uint32*)0x40038064))
#define ADC0_ADCSSCTL2                    (*((volatile uint32*)0x40038084))
#define ADC0_ADCSSCTL3                    (*((volatile uint32*)0x400380A4))
#define ADC0_ADCIM                        (*((volatile uint32*)0x40038008))
#define ADC0_ADCSSPRI                     (*((volatile uint32*)0x40038020))
#define ADC0_ADCSSFIFO0                   (*((volatile uint32*)0x40038048))
#define ADC0_ADCSSFIFO1                   (*((volatile uint32*)0x40038068))
#define ADC0_ADCSSFIFO2                   (*((volatile uint32*)0x40038088))
#define ADC0_ADCSSFIFO3                   (*((volatile uint32*)0x400380A8))
#define ADC0_ADCSSFSTAT0                  (*((volatile uint32*)0x4003804C))
#define ADC0_ADCSSFSTAT1                  (*((volatile uint32*)0x4003806C))
#define ADC0_ADCSSFSTAT2                  (*((volatile uint32*)0x4003808C))
#define ADC0_ADCSSFSTAT3                  (*((volatile uint32*)0x400380AC))
#define ADC0_ADCPSSI                      (*((volatile uint32*)0x40038028))
#define ADC0_ADCRIS                       (*((volatile uint32*)0x40038004))
#define ADC0_ADCISC                       (*((volatile uint32*)0x4003800C))
#define ADC0_ADCCC                        (*((volatile uint32*)0x40038FC8))



/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/**************************************************************************
                                     Definitions
****************************************************************************/

#define ADC_V_REF               3.3
#define ADC_MAX_VALUE           4095
#define ADC_MIN_VALUE           0
#define ADC_NUMBER_OF_CHANNELS  12

#define POLLING
#define ADC0_SS3_IRQ            17

/**************************************************************************
                                   Types declaration
****************************************************************************/

typedef struct{

    uint32 port;
    uint8 pin;
    uint8 active;

}ADC_channelSpecs;

typedef struct{

    /* Every element is boolean variable indicates the channel is used or not */
    ADC_channelSpecs channels[12];

}ADC_configType;

/* Use these names as channel number */
typedef enum{

    AIN0,   /* channel AIN0  PE3  */
    AIN1,   /* channel AIN1  PE2  */
    AIN2,   /* channel AIN2  PE1  */
    AIN3,   /* channel AIN3  PE0  */
    AIN4,   /* channel AIN4  PD3  */
    AIN5,   /* channel AIN5  PD2  */
    AIN6,   /* channel AIN5  PD1  */
    AIN7,   /* channel AIN6  PD0  */
    AIN8,   /* channel AIN7  PE5  */
    AIN9,   /* channel AIN8  PE4  */
    AIN10,  /* channel AIN9  PB4  */
    AIN11   /* channel AIN10 PB5  */

}ADC_channelNummberType;


/***************************************************************************
 *                                 Global variables
 * *************************************************************************/

extern ADC_configType configs;
extern volatile uint16 g_channelReading;

/***************************************************************************
 *                               Function prototypes
 * *************************************************************************/

void ADC_init(const  ADC_configType* ptr);

#ifdef POLLING
uint16 ADC_readChannel(uint8 ch_num);
#endif

#ifdef INTERRUPT
void ADC_readChannel(uint8 ch_num);
#endif

#endif /* ADC_H_ */
