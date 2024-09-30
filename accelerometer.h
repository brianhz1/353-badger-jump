/*
 * accelerometer.h
 *
 *  Created on: Apr 30, 2023
 *      Author: alzheng
 */

#include "msp.h"

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

/*
 * Initializes Accelerometer on MKII Boosterpack
 *
 * ACC_XOUT: J3.23 -> P6.1 A14
 * ACC_YOUT: J3.24 -> P4.0 A13
 * ACC_ZOUT: J3.25 -> P4.2 A11
 */

void accel_init(void);

#endif /* ACCELEROMETER_H_ */
