/*
 * UART0.h
 *
 *  Created on: Jul 21, 2024
 *      Author: mario
 */

#ifndef UART0_H_
#define UART0_H_

#include"std_types.h"

/*******************************************************************************
 *                              Mapped registers                               *
 *******************************************************************************/

#define SYSCTL_RCGCUART (*((volatile uint32*)0x400FE618))
#define SYSCTL_PRUART   (*((volatile uint32*)0x400FEA18))

#define UART0_DATA      (*((volatile uint32*)0x4000C000))
#define UART0_IBRD      (*((volatile uint32*)0x4000C024))
#define UART0_FBRD      (*((volatile uint32*)0x4000C028))
#define UART0_LCRH      (*((volatile uint32*)0x4000C02C))
#define UART0_CTL       (*((volatile uint32*)0x4000C030))
#define UART0_CC        (*((volatile uint32*)0x4000CFC8))
#define UART0_FLAG      (*((volatile uint32*)0x4000C018))



/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern void UART0_Init(void);

extern void UART0_SendByte(uint8 data);

extern uint8 UART0_ReceiveByte(void);

extern void UART0_SendData(const uint8 *pData, uint32 uSize);

extern void UART0_ReceiveData(uint8 *pData, uint32 uSize);

extern void UART0_SendString(const uint8 *pData);

extern void UART0_ReceiveString(uint8 *pData);





#endif /* UART0_H_ */
