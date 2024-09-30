/*
 * main.h
 *
 *  Created on: Apr 28, 2023
 *      Author: Brian Zhang
 */

#ifndef MAIN_H_
#define MAIN_H_


#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* Includes */
#include <task_character.h>
#include <task_obstacle.h>
#include <task_button.h>
#include <task_buzzer.h>
#include <task_manage_game.h>
#include <task_accel.h>
#include <task_accel_timer.h>
#include <task_character_jump.h>
#include <task_obstacle_timer.h>
#include <task_light_sensor.h>
#include <lcd.h>
#include <i2c.h>

extern SemaphoreHandle_t Sem_LCD;

#endif /* MAIN_H_ */
