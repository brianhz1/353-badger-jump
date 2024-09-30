/*
 * character_task.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#include <task_character.h>

TaskHandle_t start_jumping_handle;
QueueHandle_t Queue_Movement;
MOVEMENT_TYPE current_movement;
const int floor_y = (LCD_VERTICAL_MAX - 35);
const int bucky_x = ((45 / 2) + 2); // center position
const int jump_height = 75;

int x_pos; // offset from center position (bucky_x)
int y_pos; // offset from floor_y
int bucky_color;

/*****************************************************************************
 * Initializes Queue_Movement and other variables
 ****************************************************************************/
void character_init(void)
{
    x_pos = 0;
    y_pos = 0;
    current_movement = NEUTRAL;
}

/*****************************************************************************
 * Handles all character movement by utilizing a queue
 ****************************************************************************/
void Task_character_movement(void *pvParameters)
{
    MOVEMENT_TYPE msg;
    SOUND_TYPE sound_msg;

    while (1)
    {
        while (game_running)
        {
            // wait until a movement is recieved
            xQueueReceive(Queue_Movement, &msg, portMAX_DELAY);
            switch (msg)
            {
                // update character to jumping position
                case JUMP:
                {
                    if (current_movement == NEUTRAL)
                    {
                        // update character status
                        current_movement = JUMP;

                        // play jump sound
                        sound_msg = JUMP_SOUND;
                        xQueueSendToBack(Queue_buzzer_sounds, &sound_msg, portMAX_DELAY);

                        // start jump task
                        xTaskNotifyGive(start_jumping_handle);
                    }

                    break;
                }

                // update character to ducking position
                case DUCK:
                {
                    if (current_movement != JUMP)
                    {
                        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                        // updates image
                        clear_character();
                        draw_character_ducking();

                        // updates character status
                        current_movement = DUCK;

                        // play duck sound
                        sound_msg = DUCK_SOUND;
                        xQueueSendToBack(Queue_buzzer_sounds, &sound_msg, portMAX_DELAY);
                        xSemaphoreGive(Sem_LCD);
                    }

                    break;
                }

                // update character to neutral position
                case NEUTRAL:
                {

                    if (current_movement == DUCK)
                    {
                        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                        // updates image
                        clear_character_ducking();
                        draw_character();

                        // updates character status
                        current_movement = NEUTRAL;
                        xSemaphoreGive(Sem_LCD);
                    }

                    break;
                }

                // move character left two pixels
                case MOVE_LEFT:
                {
                    // current position is less than left boundary
                    if (x_pos > -bucky_x && current_movement != DUCK)
                    {
                        // update and draw character
                        if (current_movement == JUMP)
                        {
                            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                            clear_character();
                            x_pos -= 2;
                            xSemaphoreGive(Sem_LCD);
                        }
                        else
                        {
                            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                            clear_character();
                            x_pos -= 2;
                            draw_character();
                            xSemaphoreGive(Sem_LCD);
                        }
                    }

                    break;
                }

                // move character right two pixels
                case MOVE_RIGHT:
                {
                    // current position is less than right boundary
                    if (x_pos < bucky_x && current_movement != DUCK)
                    {
                        // update and draw character
                        if (current_movement == JUMP)
                        {
                            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                            clear_character();
                            x_pos += 3;
                            xSemaphoreGive(Sem_LCD);
                        }
                        else
                        {
                            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                            clear_character();
                            x_pos += 3;
                            draw_character();
                            xSemaphoreGive(Sem_LCD);
                        }
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }
}

/*****************************************************************************
 * Draws the character based on location data
 ****************************************************************************/
void draw_character(void)
{
    lcd_draw_image(bucky_x + x_pos, floor_y - 2 - (buckyBadger_pixHeightPixels / 2) - y_pos, buckyBadger_pixWidthPixels, buckyBadger_pixHeightPixels, buckyBadger_pixBitmaps, bucky_color, background_color);
}

/*****************************************************************************
 * Clears character from LCD by drawing a black rectangle
 ****************************************************************************/
void clear_character(void)
{
    lcd_draw_rectangle(bucky_x + x_pos, floor_y - 2 - (buckyBadger_pixHeightPixels / 2) - y_pos, buckyBadger_pixWidthPixels, buckyBadger_pixHeightPixels, background_color);
}

/*****************************************************************************
 * Draws the character ducking based on location data
 ****************************************************************************/
void draw_character_ducking(void)
{
    lcd_draw_image(bucky_x + x_pos, floor_y - 2 - (bucky_duck_pixHeightPixels / 2) - y_pos, bucky_duck_pixWidthPixels, bucky_duck_pixHeightPixels, bucky_duck_pixBitmaps, bucky_color, background_color);
}

/*****************************************************************************
 * Clears character ducking from LCD by drawing a black rectangle
 ****************************************************************************/
void clear_character_ducking(void)
{
    lcd_draw_rectangle(bucky_x + x_pos, floor_y - 2 - (bucky_duck_pixHeightPixels / 2) - y_pos, bucky_duck_pixWidthPixels, bucky_duck_pixHeightPixels, background_color);
}

/*****************************************************************************
 * Draws the level line
 ****************************************************************************/
void draw_level(void)
{
    xSemaphoreTake(Sem_LCD, portMAX_DELAY);
    // draw a line across the center
    lcd_draw_rectangle(LCD_HORIZONTAL_MAX / 2, floor_y, LCD_HORIZONTAL_MAX, 2, 0x03E0);
    xSemaphoreGive(Sem_LCD);
}

