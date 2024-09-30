/*
 * button_task.h
 *
 *  Created on: Apr 28, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_

#include <main.h>

/*****************************************************************************
 * Checks which buttons are pressed and sends a message to the character
 * movement queue
 ****************************************************************************/
void Task_button(void *pvParameters);

#endif /* TASK_BUTTON_H_ */
