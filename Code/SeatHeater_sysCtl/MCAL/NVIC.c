/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: Source file for the ARM Cortex M4 NVIC driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/


#include"NVIC.h"


/*******************************************************************************
 *                           Functions definition                               *
 *******************************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){

    /*
     * - Divide IRQ_Num by 32 to determine which enable register by offset
     * - Remainder IRQ_Num with 32 to determine which bit to be set
     *
     * */

    NVIC_IRQ_EN_BASE[IRQ_Num/32] = NVIC_IRQ_EN_BASE[IRQ_Num/32] | (1<<(IRQ_Num % 32));

}

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){

    /*
     * - Divide IRQ_Num by 32 to determine which enable register by offset
     * - Remainder IRQ_Num with 32 to determine which bit to be set
     *
     * */
    NVIC_IRQ_DIS_BASE[IRQ_Num/32] = NVIC_IRQ_DIS_BASE[IRQ_Num/32] | (1<<(IRQ_Num % 32));

}

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){



    /*
     * -  To determine which register required : consider the IRQ number (0-138) is the offset of
     * the base register IRQ's priority registers
     *
     * -  note that the offset applied by one byte not four bytes
     * -  (<<5) to jump over with reserved bits
     *
     * */
    NVIC_IRQ_PRI_BASE[IRQ_Num] = (NVIC_IRQ_PRI_BASE[IRQ_Num] & 0x1F) | ((IRQ_Priority & 0x07)<<5);


}

void NVIC_EnableException(NVIC_ExceptionType Exception_Num){

    Enable_Faults();

    switch(Exception_Num){

    case EXCEPTION_MEM_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R |= (1<<16);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R |= (1<<17);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R |= (1<<18);
        break;



    }

}

void NVIC_DisableException(NVIC_ExceptionType Exception_Num){

    switch(Exception_Num){

    case EXCEPTION_MEM_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R &= ~(1<<16);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R &= ~(1<<17);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:

        NVIC_SYSHNDCTRL_R &= ~(1<<18);
        break;

    }

}


void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){

    switch(Exception_Num){

    case EXCEPTION_MEM_FAULT_TYPE:

        NVIC_SYSPRI1_R = (NVIC_SYSPRI1_R & 0xFFFFFF1F) | ((Exception_Priority & 0x07)<<5);
        break;

    case EXCEPTION_BUS_FAULT_TYPE:

        NVIC_SYSPRI1_R = (NVIC_SYSPRI1_R & 0xFFFF1FFF) | ((Exception_Priority & 0x07)<<13);
        break;

    case EXCEPTION_USAGE_FAULT_TYPE:

        NVIC_SYSPRI1_R = (NVIC_SYSPRI1_R & 0xFF1FFFFF) | ((Exception_Priority & 0x07)<<21);
        break;

    case EXCEPTION_SVC_TYPE :

        NVIC_SYSPRI2_R = (NVIC_SYSPRI2_R & 0x1FFFFFFF) | ((Exception_Priority & 0x07)<<29);
        break;

    case EXCEPTION_DEBUG_MONITOR_TYPE :

        NVIC_SYSPRI3_R = (NVIC_SYSPRI3_R & 0xFFFFFF1F) | ((Exception_Priority & 0x07)<<5);
        break;

    case EXCEPTION_PEND_SV_TYPE :

        NVIC_SYSPRI3_R = (NVIC_SYSPRI3_R & 0xFF1FFFFF) | ((Exception_Priority & 0x07)<<21);
        break;

    case EXCEPTION_SYSTICK_TYPE :

        NVIC_SYSPRI3_R = (NVIC_SYSPRI3_R & 0x1FFFFFFF) | ((Exception_Priority & 0x07)<<29);
        break;
    }

}



