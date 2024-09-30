/*
 * task_accel_timer.h
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_ACCEL_TIMER_H_
#define TASK_ACCEL_TIMER_H_

#include <main.h>

/*****************************************************************************
 * Task which starts the ADC14 for the accelerometer
 ****************************************************************************/
void Task_accel_timer(void *pvParameters);

/*****************************************************************************
 * Initializes the accelerometer and ADC14 to return X, Y, Z values
 ****************************************************************************/
void accel_init(void);

void ADC14_IRQHandler(void);

#endif /* TASK_ACCEL_TIMER_H_ */
