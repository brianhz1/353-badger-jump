/*
 * character_task.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_CHARACTER_H_
#define TASK_CHARACTER_H_

#include <main.h>
#include <project_image.h>

#define BUCKY_LIGHT_COLOR 0xF862
#define BUCKY_DARK_COLOR 0xFFFF

typedef enum {JUMP, DUCK, NEUTRAL, MOVE_LEFT, MOVE_RIGHT} MOVEMENT_TYPE;

extern TaskHandle_t start_jumping_handle;
extern QueueHandle_t Queue_Movement;
extern MOVEMENT_TYPE current_movement;
extern const int floor_y;
extern const int bucky_x;
extern const int jump_height;
extern int x_pos;
extern int y_pos;
extern int bucky_color;

/*****************************************************************************
 * Initializes Queue_Movement and other variables
 ****************************************************************************/
void character_init(void);

/*****************************************************************************
 * Handles all character movement by utilizing a queue
 ****************************************************************************/
void Task_character_movement(void *pvParameters);

/*****************************************************************************
 * Draws the character based on location data
 ****************************************************************************/
void draw_character(void);

/*****************************************************************************
 * Clears character from LCD by drawing a black rectangle
 ****************************************************************************/
void clear_character(void);

/*****************************************************************************
 * Draws the character ducking based on location data
 ****************************************************************************/
void draw_character_ducking(void);

/*****************************************************************************
 * Clears character ducking from LCD by drawing a black rectangle
 ****************************************************************************/
void clear_character_ducking(void);

/*****************************************************************************
 * Draws the level line
 ****************************************************************************/
void draw_level(void);

#endif /* TASK_CHARACTER_H_ */
