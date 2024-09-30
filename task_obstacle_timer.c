/*
 * task_obstacle_timer.c
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#include <task_obstacle_timer.h>

/*****************************************************************************
 * Timer controlling the spawning of obstacles. Chosen obstacle is random
 ****************************************************************************/
void Task_obstacle_timer(void *pvParameters)
{
    struct obstacle_t new_obstacle;

    while(1)
    {
        // reset speed
        int speed = INITIAL_OBSTACLE_SPEED * 3;

        while (game_running)
        {
            // spawns an obstacle if there is space
            int i;
            for (i = 0; i < MAX_OBSTACLES; i++)
            {
                if (obstacles[i].generated == false)
                {
                    int random = rand();

                    if (1) //random % 2 == 0) // runs 50% of the time
                    {
                        // sets initial object information
                        new_obstacle.x_pos = 0;
                        new_obstacle.movespeed = (int) (speed++ / 3); // increases by 1 for every 3 obstacles
                        if (random > 16383)
                        {
                            new_obstacle.type = FOOTBALL;
                        }
                        else
                        {
                            new_obstacle.type = CHEESE;
                        }
                        new_obstacle.in_queue = true;
                        new_obstacle.generated = true;
                        obstacles[i] = new_obstacle;
                        break;
                    }
                }
            }

            // block for 4 seconds
            vTaskDelay(pdMS_TO_TICKS(4000));
        }
    }
}
