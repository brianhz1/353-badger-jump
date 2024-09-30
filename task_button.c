/*
 * button_task.c
 *
 *  Created on: Apr 28, 2023
 *      Author: Brian Zhang
 */

#include <task_button.h>

/*****************************************************************************
 * Debounce s1 on MKII and returns if pressed
 ****************************************************************************/
bool debounce_s1(void)
{
    static uint8_t debounce_state = 0x00;
    // shifts debounce_state to the left by 1
    debounce_state = debounce_state << 1;
    // if button is pressed set LSB to 1
    if ((P5->IN & BIT1) == 0)
    {
        debounce_state |= 0x01;
    }

    return debounce_state == 0x7F;
}

/*****************************************************************************
 * Checks for when s1 is pressed
 ****************************************************************************/
void Task_button(void *pvParameters)
{
    MOVEMENT_TYPE msg;

    while(1)
    {
        while(game_running)
        {
            // tell character to jump if s1 is pressed or duck if s2 is pressed
            if(debounce_s1())
            {
                msg = JUMP;
                xQueueSendToBack(Queue_Movement, &msg, portMAX_DELAY);
            }

            // block for 10 ms
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}
