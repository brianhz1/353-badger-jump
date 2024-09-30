/*
 * task_manage_game.h
 *
 *  Created on: May 3, 2023
 *      Author: bzhan
 */

#ifndef TASK_MANAGE_GAME_H_
#define TASK_MANAGE_GAME_H_

#include <main.h>

extern TaskHandle_t Task_start_game_handle;
extern bool game_running; // global variable which controls if game is running

/*****************************************************************************
 * Checks for when s2 is pressed to start the game
 ****************************************************************************/
void Task_start_game(void *pvParameters);

#endif /* TASK_MANAGE_GAME_H_ */
