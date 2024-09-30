/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Console(void *pvParameters)
{
    //JOYSTICK_DIR_t dir;
    ACCEL_DIR_t accel_x_dir;
    ACCEL_DIR_t accel_y_dir;
    ACCEL_DIR_t accel_z_dir;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        //xQueueReceive(Queue_Console, &dir, portMAX_DELAY);

        /* ADD CODE
         * based on the message that was received, print out one of the following
         * message to the UART.
         *
         *  "Task_Console: Joystick position - CENTER\n\r"
         *  "Task_Console: Joystick position - LEFT\n\r"
         *  "Task_Console: Joystick position - RIGHT\n\r"
         *  "Task_Console: Joystick position - UP\n\r"
         *  "Task_Console: Joystick position - DOWN\n\r"
         *
         * NOTE, the UART is only accessed in this task, so
         * there is no need to use a semaphore for mutual exclusion of the UART.
         */
        /*
         if(dir == JOYSTICK_DIR_CENTER){ //center
             printf("Task_Console: Joystick position - Center\n\r");
         }
         else if(dir == JOYSTICK_DIR_LEFT){ //left
             printf("Task_Console: Joystick position - Left\n\r");
         }
         else if(dir == JOYSTICK_DIR_RIGHT){ //right
             printf("Task_Console: Joystick position - Right\n\r");
         }
         else if(dir == JOYSTICK_DIR_UP){ //up
             printf("Task_Console: Joystick position - Up\n\r");
         }
         else if(dir == JOYSTICK_DIR_DOWN){ //down
             printf("Task_Console: Joystick position - Down\n\r");
         }
         */

        xQueueReceive(Queue_Console, &accel_x_dir, portMAX_DELAY);
        xQueueReceive(Queue_Console, &accel_y_dir, portMAX_DELAY);
        xQueueReceive(Queue_Console, &accel_z_dir, portMAX_DELAY);
/*
        if(accel_dir == ACCEL_DIR_CENTER){ //center
            printf("Task_Console: Accelerometer direction - Center\n\r");
        }
*/
        if(accel_x_dir == ACCEL_DIR_POS_X){ //+x
            printf("Task_Console: Accelerometer X direction: +X\n\r");
        }
        else if(accel_x_dir == ACCEL_DIR_NEG_X){ //-x
            printf("Task_Console: Accelerometer X direction: -X\n\r");
        }
        else {
            printf("Task_Console: Accelerometer X direction: 0\n\r");
        }

        if(accel_y_dir == ACCEL_DIR_POS_Y){ //+y
            printf("Task_Console: Accelerometer Y directionn: +Y\n\r");
        }
        else if(accel_y_dir == ACCEL_DIR_NEG_Y){ //-y
            printf("Task_Console: Accelerometer Y direction: -Y\n\r");
        }
        else {
            printf("Task_Console: Accelerometer Y direction: 0\n\r");
        }

        if(accel_z_dir == ACCEL_DIR_POS_Z){ //+z
            printf("Task_Console: Accelerometer Z directionn: +Z\n\r");
        }
        else if(accel_z_dir == ACCEL_DIR_NEG_Z){ //-z
            printf("Task_Console: Accelerometer Z direction: -Z\n\r");
        }
        else {
            printf("Task_Console: Accelerometer Z direction: 0\n\r");
        }


    }
}


