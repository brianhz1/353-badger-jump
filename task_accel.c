/*
 * task_accel.c
 *
 *  Created on: May 2, 2023
 *      Author: alzheng
 */
#include <task_accel.h>

TaskHandle_t Task_Accel_Handle;

// Add a global variable that holds the most recent value of the X direction
uint32_t INT_ACCEL_X_DIR = 0;
// Add a global variable that holds the most recent value of the Y direction
uint32_t INT_ACCEL_Y_DIR = 0;
// Add a global variable that holds the most recent value of the Z direction
uint32_t INT_ACCEL_Z_DIR = 0;

/*****************************************************************************
 * Bottom half task which handles accelerometer data
 ****************************************************************************/
void Task_accel_bottom_half(void *pvParameters){
    uint32_t prev_y = 0;

    while(1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from ISR

        if(game_running)
        {
            MOVEMENT_TYPE msg;

            if (INT_ACCEL_X_DIR > 2200) // right tilt
            {
                msg = MOVE_RIGHT;
                xQueueSend(Queue_Movement, &msg, portMAX_DELAY);
            }
            else if (INT_ACCEL_X_DIR < 1800) // left tilt
            {
                msg = MOVE_LEFT;
                xQueueSend(Queue_Movement, &msg, portMAX_DELAY);
            }

            if (prev_y > DUCKING_THRESHOLD && INT_ACCEL_Y_DIR <= DUCKING_THRESHOLD) // duck
            {
                msg = DUCK;
                xQueueSend(Queue_Movement, &msg, portMAX_DELAY);
            }
            else if (prev_y <= DUCKING_THRESHOLD && INT_ACCEL_Y_DIR > DUCKING_THRESHOLD) // unduck
            {
                msg = NEUTRAL;
                xQueueSend(Queue_Movement, &msg, portMAX_DELAY);
            }

            prev_y = INT_ACCEL_Y_DIR;
        }
    }
}
