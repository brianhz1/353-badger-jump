    /*
 * obstacle_task.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#include <task_obstacle.h>

//TaskHandle_t Task_obstacle_handle;
struct obstacle_t obstacles[MAX_OBSTACLES];

/*****************************************************************************
 * Helper method which removes an obstacle from lcd
 ****************************************************************************/
void clear_obstacle(int index, int x, int y)
{
    if(obstacles[index].type == FOOTBALL)
    {
        lcd_draw_rectangle(x, y, football_pixWidthPixels, football_pixHeightPixels, background_color);
    }
    else
    {
        lcd_draw_rectangle(x, y, cheese_pixWidthPixels, cheese_pixHeightPixels, background_color);
    }
}

/*****************************************************************************
 * Helper method which updates an obstacles position given an index
 ****************************************************************************/
void draw_obstacle(int i)
{
    int y;
    if (obstacles[i].in_queue) // lower track
    {
        y = 115;
    }
    else // upper track
    {
        if (obstacles[i].type == FOOTBALL)
        {
            y = FOOTBALL_HEIGHT;
        }
        else
        {
            y = floor_y - cheese_pixHeightPixels / 2 - 3;
        }
    }

    int x = LCD_HORIZONTAL_MAX - obstacles[i].x_pos;

    if ((obstacles[i].type == FOOTBALL) && (x > 132 - football_pixWidthPixels / 2) ||
        (obstacles[i].type == CHEESE) && (x > 132 - cheese_pixWidthPixels / 2)) // avoid drawing over max lcd horizontal size
    {
        obstacles[i].x_pos += obstacles[i].movespeed;
    }
    else if ((obstacles[i].type == FOOTBALL) && (x < obstacles[i].movespeed - football_pixWidthPixels / 2) ||
             (obstacles[i].type == CHEESE) && (x < obstacles[i].movespeed - cheese_pixWidthPixels / 2)) // wrap movement
    {
        obstacles[i].x_pos = 0;

        if (obstacles[i].in_queue) // move obstacle to upper track
        {
            obstacles[i].in_queue = false;

        }
        else // delete the obstacle
        {
            obstacles[i].generated = false;
        }

        // clear obstacle from lcd
        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
        clear_obstacle(i, x + obstacles[i].movespeed, y);
        xSemaphoreGive(Sem_LCD);
    }
    else // moving normally
    {
        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
        clear_obstacle(i, x + obstacles[i].movespeed, y);
        obstacles[i].x_pos += obstacles[i].movespeed;
        // draws obstacle
        if (obstacles[i].type == FOOTBALL)
        {
            lcd_draw_image(x, y, football_pixWidthPixels, football_pixHeightPixels, football_pixBitmaps, FOOTBALL_COLOR, background_color);
        }
        else
        {
            lcd_draw_image(x, y, cheese_pixWidthPixels, cheese_pixHeightPixels, cheese_pixBitmaps, CHEESE_COLOR, background_color);
        }
        xSemaphoreGive(Sem_LCD);
    }
}

/*****************************************************************************
 * Method which deletes all obstacles
 ****************************************************************************/
void reset_obstacles(void)
{
    int i;
    for(i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacles[i].generated = false;
    }
}

/*****************************************************************************
 * Helper method which detects collisions of a given obstacle
 ****************************************************************************/
void detect_collision(int i)
{
    if(!obstacles[i].in_queue) // check if obstacle is in upper track
    {
        int bucky_right_bound;
        int bucky_left_bound;
        int bucky_upper_bound;
        int bucky_lower_bound;

        if(current_movement == DUCK)
        {
            // set hitbox bounds for ducking
            bucky_right_bound = bucky_x + x_pos + bucky_duck_pixWidthPixels / 2;
            bucky_left_bound = bucky_x + x_pos - bucky_duck_pixWidthPixels / 2;
            int bucky_corrected_y = floor_y - y_pos - bucky_duck_pixHeightPixels / 2;
            bucky_upper_bound = bucky_corrected_y - bucky_duck_pixHeightPixels / 2;
            bucky_lower_bound = bucky_corrected_y + bucky_duck_pixHeightPixels / 2;
        }
        else
        {
            // set hitbox bounds for standing
            bucky_right_bound = bucky_x + x_pos + buckyBadger_pixWidthPixels / 2;
            bucky_left_bound = bucky_x + x_pos - buckyBadger_pixWidthPixels / 2;
            int bucky_corrected_y = floor_y - y_pos - buckyBadger_pixHeightPixels / 2;
            bucky_upper_bound = bucky_corrected_y - buckyBadger_pixHeightPixels / 2;
            bucky_lower_bound = bucky_corrected_y + buckyBadger_pixHeightPixels / 2;
        }



        if (obstacles[i].type == FOOTBALL)
        {
            // define football horizontal hitbox
            int upper_hitbox_bound = FOOTBALL_HEIGHT - football_pixWidthPixels / 2;
            int lower_hitbox_bound = FOOTBALL_HEIGHT + football_pixWidthPixels / 2;

            // checks if character is in y range
            if(bucky_upper_bound < lower_hitbox_bound && bucky_upper_bound > upper_hitbox_bound ||
                    bucky_lower_bound < lower_hitbox_bound && bucky_lower_bound > upper_hitbox_bound)
            {
                // define football horizontal hitbox bounds
                int left_hitbox_bound = LCD_HORIZONTAL_MAX - obstacles[i].x_pos - football_pixWidthPixels / 2 + 8;
                int right_hitbox_bound = LCD_HORIZONTAL_MAX - obstacles[i].x_pos + football_pixWidthPixels / 2 - 8;

                // checks if character is in x range
                if (bucky_right_bound > left_hitbox_bound && bucky_right_bound < right_hitbox_bound ||
                    bucky_left_bound > left_hitbox_bound && bucky_left_bound < right_hitbox_bound)
                {
                    xTaskNotifyGive(Task_start_game_handle);
                }
            }
        }
        else
        {
            // checks if character is in y range
            if(bucky_lower_bound > (floor_y - cheese_pixHeightPixels + 4))
            {
                // define cheese horizontal hitbox bounds
                int left_hitbox_bound = LCD_HORIZONTAL_MAX - obstacles[i].x_pos  - cheese_pixWidthPixels / 2 + 2;
                int right_hitbox_bound = LCD_HORIZONTAL_MAX - obstacles[i].x_pos + cheese_pixWidthPixels / 2 - 2;

                // checks if character is in x range
                if (bucky_right_bound > left_hitbox_bound && bucky_right_bound < right_hitbox_bound ||
                    bucky_left_bound > left_hitbox_bound && bucky_left_bound < right_hitbox_bound)
                {
                    xTaskNotifyGive(Task_start_game_handle);
                }
            }
        }
    }
}

/*****************************************************************************
 * Controls updating obstacle position and collisions
 ****************************************************************************/
void Task_obstacle_handler(void *pvParameters)
{
    while(1)
    {
        while(game_running)
        {
            int i;
            for(i = 0; i < MAX_OBSTACLES; i++)
            {
                if(obstacles[i].generated) // check if an obstacles exists
                {
                    draw_obstacle(i); // update movement
                    detect_collision(i); // detect collision
                }
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}
