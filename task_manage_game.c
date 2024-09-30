/*
 * task_manage_game.c
 *
 *  Created on: May 3, 2023
 *      Author: Brian Zhang
 */

#include <task_manage_game.h>

TaskHandle_t Task_start_game_handle;
bool game_running;

/*****************************************************************************
 * Debounce s2 on MKII and returns if pressed
 ****************************************************************************/
bool debounce_s2()
{
    static uint8_t debounce_state = 0x00;
    // shifts debounce_state to the left by 1
    debounce_state = debounce_state << 1;
    // if button is pressed set LSB to 1
    if((P3->IN & BIT5) == 0)
    {
        debounce_state |= 0x01;
    }

    return debounce_state == 0x7F;
}

/*****************************************************************************
 * Checks for when s2 is pressed to start the game
 ****************************************************************************/
void Task_start_game(void *pvParameters)
{
    SOUND_TYPE sound_msg;

    while(1)
    {
        // starts game on s2 press
        if(debounce_s2())
        {
            // clears screen
            lcd_clear_screen();

            // reset initial character information
            character_init();
            draw_level();
            draw_character();

            // reset obstacle initial information
            reset_obstacles();

            sound_msg = START_SOUND;
            xQueueSendToBack(Queue_buzzer_sounds, &sound_msg, portMAX_DELAY);

            game_running = true;
            int background = background_color;

            // wait until collision is detected
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            // end game
            game_running = false;
            sound_msg = DEATH_SOUND;
            xQueueSendToBack(Queue_buzzer_sounds, &sound_msg, portMAX_DELAY);
            vTaskDelay(pdMS_TO_TICKS(10));
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            // draw end screen
            lcd_draw_image(LCD_HORIZONTAL_MAX / 2, LCD_VERTICAL_MAX / 2, end_screenWidthPixels, end_screenHeightPixels, end_screenBitmaps, 0xF800, background);
            xSemaphoreGive(Sem_LCD);
        }

        // block for 10 ms
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
