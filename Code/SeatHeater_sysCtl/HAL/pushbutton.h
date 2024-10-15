/* pushbutton driver
 * pushbutton.h
 *
 *  Created on: Nov 30, 2023
 *      Author: mario kaldas
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "MCAL/std_types.h"

/***************************************************************************
 *                                Definitions
 *************************************************************************** */
#define PULLUP

#ifdef PULLUP
#define PB_PRESSED    0
#define PB_RELEASED   1
#endif


#ifdef PULLDOWN
#define PB_PRESSED    1
#define PB_RELEASED   0
#endif


/***************************************************************************
 *                              PB's definition
 *************************************************************************** */

/*
 * NOTE:
 *
 * If you want to use more than one port, add port definition with extension _ADD to it
 * and begin pin numbers with 8
 *
 *  */

#define PB_PORT                 PORTF_ID
#define PB_PORT_ADD             PORTB_ID

#define PB_DRIVER_CONTROL       0   /* PF0 */
#define PB_DRIVER_MULTI_FN      11   /* PB4 */

#define PB_PASSENGER_CONTROL    4  /* PF4 */

/***************************************************************************
 *                           Functions declaration
 *************************************************************************** */

void PB_init(uint8 PB_num);
void PB_initEdgeTriggered(uint8 PB_num,uint8 priority);

uint8 PB_getReading(uint8 PB_num);


#endif /* PUSHBUTTON_H_ */
