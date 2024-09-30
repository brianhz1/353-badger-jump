/*
 * obstacle.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#ifndef TASK_OBSTACLE_H_
#define TASK_OBSTACLE_H_

#include <main.h>

#define FOOTBALL_COLOR 0xB282
#define CHEESE_COLOR 0xFE60
#define MAX_OBSTACLES 3
#define FOOTBALL_HEIGHT 40

typedef enum {CHEESE, FOOTBALL} OBSTACLE_TYPE;
typedef struct obstacle_t
{
    OBSTACLE_TYPE type;
    int x_pos; // number of pixels from right edge
    int movespeed; // number of pixels to move each time
    bool in_queue; // true if in lower track
    bool generated; // true if obstacle has been set by the Task_obstacle_timer task
} obstacle;

extern struct obstacle_t obstacles[MAX_OBSTACLES];
//extern TaskHandle_t Task_obstacle_handle;

void clear_obstacle(int index, int x, int y);

/*****************************************************************************
 * Helper method which draws the obstacle of a given index
 ****************************************************************************/
void draw_obstacle(int i);

/*****************************************************************************
 * Method which deletes all obstacles
 ****************************************************************************/
void reset_obstacles(void);

/*****************************************************************************
 * Controls updating obstacle position and collisions
 ****************************************************************************/
void Task_obstacle_handler(void *pvParameters);

#endif /* TASK_OBSTACLE_H_ */
