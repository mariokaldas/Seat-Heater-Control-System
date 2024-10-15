/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.C
 *
 * Description: source file for the ARM Cortex M4 TM4C123GH6PM GPIO driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/
#include"GPIO.h"
#include"NVIC.h"

void GPIO_setupPinDirection(GPIO_ports port_num, uint8 pin_num, GPIO_PinDirectionType direction){

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        /* Setup the pin direction as required */

        SYSCTL_RCGCGPIO_R |= (1<<port_num); // enable clock for PORT

        while((SYSCTL_PRGPIO_R&(1<<port_num)) == 0){}; // make sure that the clock enabled for PORT




        switch(port_num)
        {
        case PORTA_ID:

            GPIO_PORTA_DEN_R   |=  (1<<pin_num); // Digital enable
            GPIO_PORTA_AMSEL_R &= ~(1<<pin_num); // Analog disable
            GPIO_PORTA_AFSEL_R &= ~(1<<pin_num); // Alternative function disable

            if(direction == PIN_INPUT){

                GPIO_PORTA_DIR_R &= ~(1<<pin_num);// set up direction
                GPIO_PORTA_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTA_DIR_R |= (1<<pin_num);// set up direction

            }
            break;

        case PORTB_ID:

            GPIO_PORTB_DEN_R   |=  (1<<pin_num); // digital enable
            GPIO_PORTB_AMSEL_R &= ~(1<<pin_num); // Analog disable
            GPIO_PORTB_AFSEL_R &= ~(1<<pin_num); // Alternative function disable


            if(direction == PIN_INPUT){

                GPIO_PORTB_DIR_R &= ~(1<<pin_num);// set up direction
                GPIO_PORTB_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTB_DIR_R |= (1<<pin_num);// set up direction

            }
            break;

        case PORTC_ID:

            /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
            if(pin_num <= 3){
                break;
            }

            GPIO_PORTC_DEN_R   |=  (1<<pin_num); // digital enable
            GPIO_PORTC_AMSEL_R &= ~(1<<pin_num); // Analog disable
            GPIO_PORTC_AFSEL_R &= ~(1<<pin_num); // Alternative function disable


            if(direction == PIN_INPUT){

                GPIO_PORTC_DIR_R &= ~(1<<pin_num);// set up direction
                GPIO_PORTC_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTC_DIR_R |= (1<<pin_num);// set up direction

            }
            break;

        case PORTD_ID:

            /* This is NMI pin so we need to unlock and commit it first */
            if(pin_num == 7){

                GPIO_PORTD_LOCK_R = 0x4C4F434B;
                GPIO_PORTD_CR_R |= (1<<7);
            }

            GPIO_PORTD_DEN_R   |=  (1<<pin_num);  // digital enable
            GPIO_PORTD_AMSEL_R &= ~(1<<pin_num);  // Analog disable
            GPIO_PORTD_AFSEL_R &= ~(1<<pin_num);  // Alternative function disable


            if(direction == PIN_INPUT){

                GPIO_PORTD_DIR_R &= ~(1<<pin_num); // set up direction
                GPIO_PORTD_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTD_DIR_R |= (1<<pin_num); // set up direction

            }
            break;

        case PORTE_ID:

            GPIO_PORTE_DEN_R   |=  (1<<pin_num);  // digital enable
            GPIO_PORTE_AMSEL_R &= ~(1<<pin_num);  // Analog disable
            GPIO_PORTE_AFSEL_R &= ~(1<<pin_num);  // Alternative function disable


            if(direction == PIN_INPUT){

                GPIO_PORTE_DIR_R &= ~(1<<pin_num);// set up direction
                GPIO_PORTE_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTE_DIR_R |= (1<<pin_num);// set up direction

            }
            break;

        case PORTF_ID:

            /* This is NMI pin so we need to unlock and commit it first */
            if(pin_num == 0){

                GPIO_PORTF_LOCK_R = 0x4C4F434B;
                GPIO_PORTF_CR_R |= 1;
            }

            GPIO_PORTF_DEN_R   |=  (1<<pin_num);  // digital enable
            GPIO_PORTF_AMSEL_R &= ~(1<<pin_num);  // Analog disable
            GPIO_PORTF_AFSEL_R &= ~(1<<pin_num);  // Alternative function disable


            if(direction == PIN_INPUT){

                GPIO_PORTF_DIR_R &= ~(1<<pin_num);// set up direction
                GPIO_PORTF_PUR_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTF_DIR_R |= (1<<pin_num);// set up direction

            }
            break;

        }
    }
}


void GPIO_writePin(GPIO_ports port_num, uint8 pin_num, uint8 value){

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else{
        switch(port_num)
        {
        case PORTA_ID:

            if(value == HIGH){
                GPIO_PORTA_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTA_DATA_R &= ~(1<<pin_num);
            }
            break;

        case PORTB_ID:

            if(value == HIGH){
                GPIO_PORTB_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTB_DATA_R &= ~(1<<pin_num);
            }
            break;

        case PORTC_ID:

            /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
            if(pin_num <= 3){
                break;
            }

            if(value == HIGH){
                GPIO_PORTC_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTC_DATA_R &= ~(1<<pin_num);
            }
            break;

        case PORTD_ID:

            if(value == HIGH){
                GPIO_PORTD_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTD_DATA_R &= ~(1<<pin_num);
            }
            break;

        case PORTE_ID:

            if(value == HIGH){
                GPIO_PORTE_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTE_DATA_R &= ~(1<<pin_num);
            }
            break;

        case PORTF_ID:

            if(value == HIGH){
                GPIO_PORTF_DATA_R |= (1<<pin_num);
            }
            else{
                GPIO_PORTF_DATA_R &= ~(1<<pin_num);
            }
            break;

        }
    }
}

uint8 GPIO_readPin(GPIO_ports port_num, uint8 pin_num){


    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        return 0;
    }
    switch(port_num){

    case PORTA_ID:
        return (GPIO_PORTA_DATA_R & (1<<pin_num))>>pin_num;

    case PORTB_ID:
        return (GPIO_PORTB_DATA_R & (1<<pin_num))>>pin_num;

    case PORTC_ID:

        /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
        if(pin_num <= 3){
            break;
        }

        return (GPIO_PORTC_DATA_R & (1<<pin_num))>>pin_num;

    case PORTD_ID:
        return (GPIO_PORTD_DATA_R & (1<<pin_num))>>pin_num;

    case PORTE_ID:
        return (GPIO_PORTE_DATA_R & (1<<pin_num))>>pin_num;

    case PORTF_ID:
        return (GPIO_PORTF_DATA_R & (1<<pin_num))>>pin_num;
    }

    return 0;
}


void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction){

    if(port_num >= NUM_OF_PORTS){

        /* DO NOTHING */
    }
    else{

        SYSCTL_RCGCGPIO_R |= (1<<port_num); // enable clock for PORT
        while((SYSCTL_PRGPIO_R&(1<<port_num)) == 0){}; // make sure that the clock enabled for PORT

        switch(port_num){

        case PORTA_ID:

            GPIO_PORTA_DEN_R = 0xFF;
            GPIO_PORTA_AMSEL_R = 0; // Analog disable
            GPIO_PORTA_AFSEL_R = 0; // Alternative function disable
            GPIO_PORTA_DIR_R = direction;
            GPIO_PORTA_PUR_R = ~direction;
            break;

        case PORTB_ID:

            GPIO_PORTB_DEN_R = 0xFF;
            GPIO_PORTB_AMSEL_R = 0; // Analog disable
            GPIO_PORTB_AFSEL_R = 0; // Alternative function disable
            GPIO_PORTB_DIR_R = direction;
            GPIO_PORTB_PUR_R = ~direction;

            break;

        case PORTC_ID:

            if(direction == PORT_INPUT){

                GPIO_PORTC_DEN_R   |= 0xF0;
                GPIO_PORTC_AMSEL_R &= 0x0F; // Analog disable
                GPIO_PORTC_AFSEL_R &= 0x0F; // Alternative function disable
                GPIO_PORTC_DIR_R   &= 0x0F;
                GPIO_PORTC_PUR_R   |= 0xF0;

            }
            else{

                GPIO_PORTC_DEN_R   |= 0xF0;
                GPIO_PORTC_AMSEL_R &= 0x0F; // Analog disable
                GPIO_PORTC_AFSEL_R &= 0x0F; // Alternative function disable
                GPIO_PORTC_DIR_R   |= 0xF0;
            }


            break;

        case PORTD_ID:

            GPIO_PORTD_DEN_R = 0xFF;
            GPIO_PORTD_AMSEL_R = 0; // Analog disable
            GPIO_PORTD_AFSEL_R = 0; // Alternative function disable
            GPIO_PORTD_DIR_R = direction;
            GPIO_PORTD_PUR_R = ~direction;

            break;

        case PORTE_ID:

            GPIO_PORTE_DEN_R = 0xFF;
            GPIO_PORTE_AMSEL_R = 0; // Analog disable
            GPIO_PORTE_AFSEL_R = 0; // Alternative function disable
            GPIO_PORTE_DIR_R = direction;
            GPIO_PORTE_PUR_R = ~direction;

            break;

        case PORTF_ID:

            GPIO_PORTF_DEN_R = 0xFF;
            GPIO_PORTF_AMSEL_R = 0; // Analog disable
            GPIO_PORTF_AFSEL_R = 0; // Alternative function disable
            GPIO_PORTF_DIR_R = direction;
            GPIO_PORTF_PUR_R = ~direction;

            break;
        }
    }
}


void GPIO_writePort(uint8 port_num, uint8 value){

    if(port_num >= NUM_OF_PORTS)
    {
        /* Do Nothing */
    }
    else{

        switch(port_num){

        case PORTA_ID:
            GPIO_PORTA_DATA_R = value;
            break;

        case PORTB_ID:
            GPIO_PORTB_DATA_R = value;
            break;

        case PORTC_ID:
            GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & 0x0F) | (value & 0xF0);
            break;

        case PORTD_ID:
            GPIO_PORTD_DATA_R = value;
            break;

        case PORTE_ID:
            GPIO_PORTE_DATA_R = value;
            break;

        case PORTF_ID:
            GPIO_PORTF_DATA_R = value;
            break;
        }
    }
}


uint8 GPIO_readPort(uint8 port_num){

    if(port_num >= NUM_OF_PORTS)
    {
        return 0;
    }
    else{

        switch(port_num){

        case PORTA_ID:
            return GPIO_PORTA_DATA_R;

        case PORTB_ID:
            return GPIO_PORTB_DATA_R;

        case PORTC_ID:
            return (GPIO_PORTC_DATA_R & 0xF0);

        case PORTD_ID:
            return GPIO_PORTD_DATA_R;

        case PORTE_ID:
            return GPIO_PORTE_DATA_R;

        case PORTF_ID:
            return GPIO_PORTF_DATA_R;
        }
    }
    return 0;
}


void GPIO_edgeTriggeredInterruptInit(uint8 port_num,uint8 pin_num, GPIO_EdgeTriggerType edge, uint8 priority){

    if(port_num >= NUM_OF_PORTS)
    {
        return ;
    }
    else{

        switch(port_num){

        case PORTA_ID:

            GPIO_PORTA_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
            GPIO_PORTA_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

            if(edge == RISING_EDGE){

                GPIO_PORTA_GPIOIEV_R |= (1<<pin_num); /* rising edge */
            }
            else if(edge == FALLING_EDGE){

                GPIO_PORTA_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
            }

            GPIO_PORTA_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
            GPIO_PORTA_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

            NVIC_EnableIRQ(GPIO_PORTA_IRQ);                     /* Enable interrupt for port from NVIC controller */
            NVIC_SetPriorityIRQ(GPIO_PORTA_IRQ,priority);       /* Set priority */

            return;

        case PORTB_ID:

            GPIO_PORTB_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
            GPIO_PORTB_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

            if(edge == RISING_EDGE){

                GPIO_PORTB_GPIOIEV_R |= (1<<pin_num); /* rising edge */
            }
            else if(edge == FALLING_EDGE){

                GPIO_PORTB_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
            }

            GPIO_PORTB_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
            GPIO_PORTB_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

            NVIC_EnableIRQ(GPIO_PORTB_IRQ);                     /* Enable interrupt for port from NVIC controller */
            NVIC_SetPriorityIRQ(GPIO_PORTB_IRQ,priority);       /* Set priority */

            return;
        case PORTC_ID:

            /* From pin 0 to pin 3 in port c : JTAG pins please don't use them */
            if(pin_num <= 3){
                return;
            }
            else{
                GPIO_PORTC_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
                GPIO_PORTC_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

                if(edge == RISING_EDGE){

                    GPIO_PORTC_GPIOIEV_R |= (1<<pin_num); /* rising edge */
                }
                else if(edge == FALLING_EDGE){

                    GPIO_PORTC_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
                }

                GPIO_PORTC_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
                GPIO_PORTC_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

                NVIC_EnableIRQ(GPIO_PORTC_IRQ);                     /* Enable interrupt for port from NVIC controller */
                NVIC_SetPriorityIRQ(GPIO_PORTC_IRQ,priority);       /* Set priority */

                return;
            }

        case PORTD_ID:

            GPIO_PORTD_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
            GPIO_PORTD_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

            if(edge == RISING_EDGE){

                GPIO_PORTD_GPIOIEV_R |= (1<<pin_num); /* rising edge */
            }
            else if(edge == FALLING_EDGE){

                GPIO_PORTD_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
            }

            GPIO_PORTD_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
            GPIO_PORTD_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

            NVIC_EnableIRQ(GPIO_PORTD_IRQ);                     /* Enable interrupt for port from NVIC controller */
            NVIC_SetPriorityIRQ(GPIO_PORTD_IRQ,priority);       /* Set priority */

            return;

        case PORTE_ID:

            GPIO_PORTE_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
            GPIO_PORTE_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

            if(edge == RISING_EDGE){

                GPIO_PORTE_GPIOIEV_R |= (1<<pin_num); /* rising edge */
            }
            else if(edge == FALLING_EDGE){

                GPIO_PORTE_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
            }

            GPIO_PORTE_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
            GPIO_PORTE_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

            NVIC_EnableIRQ(GPIO_PORTE_IRQ);                     /* Enable interrupt for port from NVIC controller */
            NVIC_SetPriorityIRQ(GPIO_PORTE_IRQ,priority);       /* Set priority */

            return;

        case PORTF_ID:

            GPIO_PORTF_GPIOIS_R &= ~(1<<pin_num);  /* Edge level enabled */
            GPIO_PORTF_GPIOIBE_R &= ~(1<<pin_num); /* Certain edge is used */

            if(edge == RISING_EDGE){

                GPIO_PORTF_GPIOIEV_R |= (1<<pin_num); /* rising edge */
            }
            else if(edge == FALLING_EDGE){

                GPIO_PORTF_GPIOIEV_R &= ~(1<<pin_num);  /* falling edge */
            }

            GPIO_PORTF_GPIOIM_R |= (1<<pin_num);   /* This pin is enabled */
            GPIO_PORTF_GPIOICR_R &= ~(1<<pin_num); /* Clear interrupt flag */

            NVIC_EnableIRQ(GPIO_PORTF_IRQ);                     /* Enable interrupt for port from NVIC controller */
            NVIC_SetPriorityIRQ(GPIO_PORTF_IRQ,priority);       /* Set priority */

            return;

        }
    }

}

