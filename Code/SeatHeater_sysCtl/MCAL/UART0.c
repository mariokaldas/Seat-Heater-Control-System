/******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.c
 *
 * Description: Source file for the ARM Cortex M4 TM4C123GH6PM UART driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#include"UART0.h"
#include"GPIO.h"


/*******************************************************************************
 *                            Functions definition                             *
 *******************************************************************************/

void GPIO_SetupUART0Pins(void){


    /* Enable clock for PORTA for GPIO module */
    SYSCTL_RCGCGPIO_R |= 1;

    /* Make sure that clock is enabled and registers are accessible */
    while(!(SYSCTL_PRGPIO_R & 1));

    /* Receiver pin as input */
    GPIO_PORTA_DIR_R &= ~(1<<0);

    /* Transmitter pin as output */
    GPIO_PORTA_DIR_R |= (1<<1);

    /* Use first 2 pins as alternative function (not GPIO) */
    GPIO_PORTA_AFSEL_R |= 0x3;

    /* Use first 2 pins as UART pins */
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | (0x00000011);

    /* Digital enable for transmitter and receiver pins */
    GPIO_PORTA_DEN_R |= 0x3;
}

void UART0_Init(void){

    GPIO_SetupUART0Pins();

    /* Open clock for UART0 */
    SYSCTL_RCGCUART |= (1<<0);

    /*  Make sure clock open successfully and registers are accessible*/
    while(!(SYSCTL_PRUART & 1));

    /* Disable the UART */
    UART0_CTL &= ~(1<<0);

    /* Use internal oscillator as clock source */
    UART0_CC = 0x5;

    /* Integer part of the equation : 16MHZ / (16 * 9600) */
    UART0_IBRD = 104;

    /* Fractional part of the equation * 64 + 0.5 */
    UART0_FBRD = 11;

    /* No stick parity */
    UART0_LCRH &= ~(1<<7);

    /* UART word length is 8 bits */
    UART0_LCRH |= (3<<5);

    /* FIFO is disabled */
    UART0_LCRH &= ~(1<<4);

    /* Use one stop bit */
    UART0_LCRH &= ~(1<<3);

    /* Parity is disabled */
    UART0_LCRH &= ~(1<<1);

    /* Normal use of break */
    UART0_LCRH &= ~(1<<0);

    /* UART transmit and receive enable */
    UART0_CTL = UART0_CTL | (1<<8) | (1<<9);

    /* High speed enable (system clock is divided by 16 ) */
    UART0_CTL &= ~(1<<5);

    /* Enable the UART */
    UART0_CTL |= (1<<0);

}

void UART0_SendByte(uint8 data){

    UART0_DATA = data;
    while(!(UART0_FLAG & (1<<7)));
}

uint8 UART0_ReceiveByte(void){

    while(!(UART0_FLAG & (1<<6)));
    return UART0_DATA;
}


void UART0_SendString(const uint8 *pData){

    uint32 i;

    for(i=0; pData[i] != '\0';i++){

        UART0_SendByte(pData[i]);
    }
}

void UART0_ReceiveString(uint8 *pData){

    uint32 i,data;

    for(i=0;;i++){

        data = UART0_ReceiveByte();

        if(data == '#')
            break;
        else
            pData[i] = data;
    }
}

void UART0_SendData(const uint8 *pData, uint32 uSize){

    uint32 i;

    for(i=0; i<uSize ;i++){

        UART0_SendByte(pData[i]);
    }
}

void UART0_ReceiveData(uint8 *pData, uint32 uSize){

    uint32 i;

    for(i=0;i<uSize;i++){

        pData[i] = UART0_ReceiveByte();
    }
}

void UART0_SendInteger(sint64 sNumber)
{

    uint8 uDigits[20];
    sint8 uCounter = 0;

    /* Send the negative sign in case of negative numbers */
    if (sNumber < 0)
    {
        UART0_SendByte('-');
        sNumber *= -1;
    }

    /* Convert the number to an array of characters */
    do
    {
        uDigits[uCounter++] = sNumber % 10 + '0'; /* Convert each digit to its corresponding ASCI character */
        sNumber /= 10; /* Remove the already converted digit */
    }
    while (sNumber != 0);

    /* Send the array of characters in a reverse order as the digits were converted from right to left */
    for( uCounter--; uCounter>= 0; uCounter--)
    {
        UART0_SendByte(uDigits[uCounter]);
    }
}
