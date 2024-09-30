/*
 * task_buzzer.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_BUZZER_H_
#define TASK_BUZZER_H_

#include <main.h>

typedef enum {JUMP_SOUND, DUCK_SOUND, START_SOUND, DEATH_SOUND} SOUND_TYPE;

extern QueueHandle_t Queue_buzzer_sounds;

/*****************************************************************************
 * Initializes buzzer and TIMER_A0 to produce sound
 ****************************************************************************/
void buzzer_init (void);

/*****************************************************************************
 * Handles all sounds that should be produced using a queue
 ****************************************************************************/
void Task_buzzer_sound(void *pvParameters);

#endif /* TASK_BUZZER_H_ */
