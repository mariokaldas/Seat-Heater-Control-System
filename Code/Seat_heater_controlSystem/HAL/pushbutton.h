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
#define PULLDOWN

#ifdef PULLUP
#define PB_PRESSED    0
#define PB_RELEASED   1
#endif


#ifdef PULLDOWN
#define PB_PRESSED    1
#define PB_RELEASED   0
#endif


#define PB_PORT PORTA_ID


/***************************************************************************
 *                              IR's definition
 *************************************************************************** */

#define PB1 0
#define PB2 1


/***************************************************************************
 *                           Functions declaration
 *************************************************************************** */

void PB_init(uint8 PB_num);
uint8 PB_getReading(uint8 PB_num);


#endif /* PUSHBUTTON_H_ */
