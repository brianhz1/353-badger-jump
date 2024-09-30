/*
 * interrupts.h
 *
 *  Created on: May 3, 2023
 *      Author: alzheng
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"
#include "ece353.h"

extern volatile uint32_t INT_ACCEL_X_DIR;
extern volatile uint32_t INT_ACCEL_Y_DIR;
extern volatile uint32_t INT_ACCEL_Z_DIR;

void T32_INT1_IRQHandler(void);



#endif /* INTERRUPTS_H_ */
