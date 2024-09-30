/*
 * task_obstacle_timer.h
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_OBSTACLE_TIMER_H_
#define TASK_OBSTACLE_TIMER_H_

#include <main.h>

#define INITIAL_OBSTACLE_SPEED 5

/*****************************************************************************
 * Timer controlling the spawning of obstacles. Chosen obstacle is random
 ****************************************************************************/
void Task_obstacle_timer(void *pvParameters);

#endif /* TASK_OBSTACLE_TIMER_H_ */
