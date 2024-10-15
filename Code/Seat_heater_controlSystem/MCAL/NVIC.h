/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: Header file for the ARM Cortex M4 NVIC driver
 *
 * Author: Mario kaldas
 *
 *******************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"


/********************************************************************************
 *                             Mapped registers
 *******************************************************************************/

#define NVIC_SYSHNDCTRL_R   (*((volatile uint32*) 0xE000ED24))

#define NVIC_SYSPRI1_R      (*((volatile uint32*) 0xE000ED18))
#define NVIC_SYSPRI2_R      (*((volatile uint32*) 0xE000ED1C))
#define NVIC_SYSPRI3_R      (*((volatile uint32*) 0xE000ED20))

#define NVIC_IRQ_EN_BASE    (((volatile uint32*) 0xE000E100))
#define NVIC_IRQ_EN0_R      (*((volatile uint32*) 0xE000E100))
#define NVIC_IRQ_EN1_R      (*((volatile uint32*) 0xE000E104))
#define NVIC_IRQ_EN2_R      (*((volatile uint32*) 0xE000E108))
#define NVIC_IRQ_EN3_R      (*((volatile uint32*) 0xE000E10C))
#define NVIC_IRQ_EN4_R      (*((volatile uint32*) 0xE000E110))

#define NVIC_IRQ_DIS_BASE   (((volatile uint32*) 0xE000E180))
#define NVIC_IRQ_DIS0_R     (*((volatile uint32*) 0xE000E180))
#define NVIC_IRQ_DIS1_R     (*((volatile uint32*) 0xE000E184))
#define NVIC_IRQ_DIS2_R     (*((volatile uint32*) 0xE000E188))
#define NVIC_IRQ_DIS3_R     (*((volatile uint32*) 0xE000E18C))
#define NVIC_IRQ_DIS4_R     (*((volatile uint32*) 0xE000E190))


#define NVIC_IRQ_PRI_BASE   (((volatile uint8*) 0xE000E400))
#define NVIC_IRQ_PRI0_R     (*((volatile uint32*) 0xE000E400))
#define NVIC_IRQ_PRI1_R     (*((volatile uint32*) 0xE000E404))
#define NVIC_IRQ_PRI2_R     (*((volatile uint32*) 0xE000E408))
#define NVIC_IRQ_PRI3_R     (*((volatile uint32*) 0xE000E40C))
#define NVIC_IRQ_PRI4_R     (*((volatile uint32*) 0xE000E410))
#define NVIC_IRQ_PRI5_R     (*((volatile uint32*) 0xE000E414))
#define NVIC_IRQ_PRI6_R     (*((volatile uint32*) 0xE000E418))
#define NVIC_IRQ_PRI7_R     (*((volatile uint32*) 0xE000E41C))
#define NVIC_IRQ_PRI8_R     (*((volatile uint32*) 0xE000E420))
#define NVIC_IRQ_PRI9_R     (*((volatile uint32*) 0xE000E424))
#define NVIC_IRQ_PRI10_R    (*((volatile uint32*) 0xE000E428))
#define NVIC_IRQ_PRI11_R    (*((volatile uint32*) 0xE000E42C))
#define NVIC_IRQ_PRI12_R    (*((volatile uint32*) 0xE000E430))
#define NVIC_IRQ_PRI13_R    (*((volatile uint32*) 0xE000E434))
#define NVIC_IRQ_PRI14_R    (*((volatile uint32*) 0xE000E438))
#define NVIC_IRQ_PRI15_R    (*((volatile uint32*) 0xE000E43C))
#define NVIC_IRQ_PRI16_R    (*((volatile uint32*) 0xE000E440))
#define NVIC_IRQ_PRI17_R    (*((volatile uint32*) 0xE000E444))
#define NVIC_IRQ_PRI18_R    (*((volatile uint32*) 0xE000E448))
#define NVIC_IRQ_PRI19_R    (*((volatile uint32*) 0xE000E44C))
#define NVIC_IRQ_PRI20_R    (*((volatile uint32*) 0xE000E450))
#define NVIC_IRQ_PRI21_R    (*((volatile uint32*) 0xE000E454))
#define NVIC_IRQ_PRI22_R    (*((volatile uint32*) 0xE000E458))
#define NVIC_IRQ_PRI23_R    (*((volatile uint32*) 0xE000E45C))
#define NVIC_IRQ_PRI24_R    (*((volatile uint32*) 0xE000E460))
#define NVIC_IRQ_PRI25_R    (*((volatile uint32*) 0xE000E464))
#define NVIC_IRQ_PRI26_R    (*((volatile uint32*) 0xE000E468))
#define NVIC_IRQ_PRI27_R    (*((volatile uint32*) 0xE000E46C))
#define NVIC_IRQ_PRI28_R    (*((volatile uint32*) 0xE000E470))
#define NVIC_IRQ_PRI29_R    (*((volatile uint32*) 0xE000E474))
#define NVIC_IRQ_PRI30_R    (*((volatile uint32*) 0xE000E478))
#define NVIC_IRQ_PRI31_R    (*((volatile uint32*) 0xE000E47C))
#define NVIC_IRQ_PRI32_R    (*((volatile uint32*) 0xE000E480))
#define NVIC_IRQ_PRI33_R    (*((volatile uint32*) 0xE000E484))
#define NVIC_IRQ_PRI34_R    (*((volatile uint32*) 0xE000E488))



/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;


/*******************************************************************************
 *                           Functions prototype                               *
 *******************************************************************************/


/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);


/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);


/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num, IRQ_Priority
 * Return value: None
 * Description: Function to set priority for Interrupt request for specific IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);


/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the exception from the target vector table
 * Return value: None
 * Description: Function to enable Interrupt request for specific exception
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);


/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the exception from the target vector table
 * Return value: None
 * Description: Function to disable Interrupt request for specific exception
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);


/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num, Exception_Priority - Number of the exception from the target vector table
 * Return value: None
 * Description: Function to set priority for Interrupt request for specific exception
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);

#endif /* NVIC_H_ */
