/*
 * task_buzzer.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Brian Zhang
 */

#include <task_buzzer.h>

QueueHandle_t Queue_buzzer_sounds;

/*****************************************************************************
 * Initializes buzzer and TIMER_A0 to produce sound
 ****************************************************************************/
void buzzer_init() {
    // set as output
    P2->DIR |= BIT7;

    // set output to TIMER_A0 PWM
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // reset TIMER_A0
    TIMER_A0->CTL = 0;

    // sets SMCLK as source and TIMER_A0 to up mode
    TIMER_A0->CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR;

    // sets to reset/set mode
    TIMER_A0->CCTL[4] |= TIMER_A_CCTLN_OUTMOD_7;

    Queue_buzzer_sounds = xQueueCreate(10, sizeof(SOUND_TYPE));
}

/*****************************************************************************
 * Sets TIMER_A0 to generate a PWM signal with a given period
 ****************************************************************************/
void play_sound(int period)
{
    // clears and starts timer
    TIMER_A0->CTL |= (TIMER_A_CTL_MC__UP | BIT2);

    // sets period
    TIMER_A0->CCR[0] = period - 1;
    // duty cycle 50%
    TIMER_A0->CCR[4] = (period / 2) - 1;
}

/*****************************************************************************
 * Handles all sounds that should be produced using a queue
 ****************************************************************************/
void Task_buzzer_sound(void *pvParameters)
{
    SOUND_TYPE msg;

    while (1)
    {
        xQueueReceive(Queue_buzzer_sounds, &msg, portMAX_DELAY);

        switch (msg)
        {

            // play the jumping sound
            case JUMP_SOUND:
            {
                play_sound(22945); // sets pitch
                vTaskDelay(pdMS_TO_TICKS(500));
                TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; // stops TIMER_A0
                break;
            }

            // play the duck sound
            case DUCK_SOUND:
            {
                play_sound(18196);
                vTaskDelay(pdMS_TO_TICKS(500));
                TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; // stops TIMER_A0
                break;
            }

            // play the start sound
            case START_SOUND:
            {
                play_sound(15306);
                vTaskDelay(pdMS_TO_TICKS(500));
                TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; // stops TIMER_A0
                break;
            }

            // play the death sound
            case DEATH_SOUND:
            {
                play_sound(12146);
                vTaskDelay(pdMS_TO_TICKS(500));
                TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; // stops TIMER_A0
                break;
            }
            default:
            {
                break;
            }
        }
    }
}
