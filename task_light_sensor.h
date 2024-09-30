/*
 * task_light_sensor.h
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_LIGHT_SENSOR_H_
#define TASK_LIGHT_SENSOR_H_

#include <main.h>
#include "math.h"

#define OPT3001_ADDRESS 0x44

#define OPT_INTERRUPT_PIN 11
#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define MANUFACTUREID_REG 0x7E
#define DEVICEID_REG 0x7F

#define DARK_MODE_LUX_THRESHOLD 40
#define LIGHT_BACKGROUND_COLOR 0xFFFF
#define DARK_BACKGROUND_COLOR 0x0000

extern bool dark_mode;
int background_color;

/******************************************************************************
 * Task which toggles dark mode based on light sensor
 ******************************************************************************/
void Task_light_sensor(void);

#endif /* TASK_LIGHT_SENSOR_H_ */
