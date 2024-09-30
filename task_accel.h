/*
 * task_accel.h
 *
 *  Created on: May 2, 2023
 *      Author: alzheng
 */

#ifndef TASK_ACCEL_H_
#define TASK_ACCEL_H_

#include "main.h"

#define DUCKING_THRESHOLD 1500

extern TaskHandle_t Task_Accel_Handle;
extern uint32_t INT_ACCEL_X_DIR;
extern uint32_t INT_ACCEL_Y_DIR;
extern uint32_t INT_ACCEL_Z_DIR;

/*****************************************************************************
 * Bottom half task which handles accelerometer data
 ****************************************************************************/
void Task_accel_bottom_half(void *pvParameters);

#endif /* TASK_ACCEL_H_ */
