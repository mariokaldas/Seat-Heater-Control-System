/*
 * delay.c
 *
 *  Created on: Apr 18, 2024
 *      Author: mario
 */

#include "delay.h"

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 364


void _delay_ms(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}


