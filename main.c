/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include <main.h>

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    Sem_LCD = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_LCD);

    buzzer_init();
    Crystalfontz128x128_Init();
    character_init();
    accel_init();
    light_sensor_init();
    Queue_Movement = xQueueCreate(5, sizeof(MOVEMENT_TYPE));

    // draw start screen
    lcd_draw_image(LCD_HORIZONTAL_MAX / 2, LCD_VERTICAL_MAX / 2, start_screenWidthPixels, start_screenHeightPixels, start_screenBitmaps, 0xFFFF, 0x000);

    __enable_irq();

    xTaskCreate
    (   Task_button,
        "Checks for button presses",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_character_movement,
        "Handles all character movement inputs",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_character_jump,
        "Tells character to jump",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &start_jumping_handle
    );

    xTaskCreate
    (   Task_obstacle_timer,
        "Spawns obstacles",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_obstacle_handler,
        "Obstacle movement and collision",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_start_game,
        "Manages global game start and restart",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        &Task_start_game_handle
    );

    xTaskCreate
    (   Task_accel_timer,
        "Timer which starts an ADC conversion for accelerometer",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );


    xTaskCreate
    (   Task_accel_bottom_half,
        "Bottom half task for accelerometer",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        &Task_Accel_Handle
    );

    xTaskCreate
    (   Task_light_sensor,
        "Controls dark mode",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_buzzer_sound,
        "Manages all sounds",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};
    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
