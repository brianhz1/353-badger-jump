/*
 * task_accel_timer.c
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#include <task_accel_timer.h>

/*****************************************************************************
 * Task which starts the ADC14 for the accelerometer
 ****************************************************************************/
void Task_accel_timer(void *pvParameters)
{
    while (1)
    {
        while (game_running)
        {
            // starts conversion
            ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

            // blocks task for
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

/*****************************************************************************
 * Initializes the accelerometer and ADC14 to return X, Y, Z values
 ****************************************************************************/
void accel_init(void)
{
    // Configure the X direction as an analog input pin.
    //P6.1 A14
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;

    // Configure the Y direction as an analog input pin.
    //P4.0 A13
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;

    // Configure the Z direction as an analog input pin.
    //P4.2 A11
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_SHT12
            | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14;

    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13;

    // Associate the Z direction analog signal with MEM[2]
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[2].
    ADC14->IER0 = ADC14_IER0_IE2;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    NVIC_SetPriority(ADC14_IRQn, 2);

    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}

void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Read the X value
    INT_ACCEL_X_DIR = ADC14->MEM[0];
    // Read the Y value
    INT_ACCEL_Y_DIR = ADC14->MEM[1];
    // Read the Z value
    INT_ACCEL_Z_DIR = ADC14->MEM[2];

    // Notify bottom half task
    vTaskNotifyGiveFromISR(Task_Accel_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
