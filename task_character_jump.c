/*
 * task_character_jump.c
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#include <task_character_jump.h>

/*****************************************************************************
 * Task which manages character y position when jumping
 ****************************************************************************/
void Task_character_jump(void *pvParameters)
{
    while(1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        int count = 12;// used to create parabolic movement
        while (game_running && y_pos < jump_height) // moving up
        {
            // updates image and increments character position
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            if(game_running)
            {
                clear_character();
                y_pos += (count--) ^ 2 / 5;
                draw_character();
            }
            xSemaphoreGive(Sem_LCD);

            vTaskDelay(pdMS_TO_TICKS((int) (5000/(jump_height))));
        }

        count = 0;
        while (game_running && y_pos > 0 + (count++) ^ 2 / 5) // moving down
        {
            // updates image and increments character position
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            if(game_running)
            {
                clear_character();
                y_pos -= (count++) ^ 2 / 5;
                draw_character();
            }
            xSemaphoreGive(Sem_LCD);

            vTaskDelay(pdMS_TO_TICKS((int) (10000/(jump_height))));
        }

        if (y_pos > 0) // set position to zero
        {
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            if(game_running)
            {
                clear_character();
                y_pos = 0;
                draw_character();
            }
            xSemaphoreGive(Sem_LCD);
        }

        current_movement = NEUTRAL;
    }
}
