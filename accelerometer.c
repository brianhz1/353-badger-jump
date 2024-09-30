/*
 * accelerometer.c
 *
 *  Created on: Apr 30, 2023
 *      Author: alzheng
 */

/*
 * Initializes Accelerometer on MKII Boosterpack
 *
 * ACC_XOUT: J3.23 -> P6.1 A14
 * ACC_YOUT: J3.24 -> P4.0 A13
 * ACC_ZOUT: J3.25 -> P4.2 A11
 */
#include "accelerometer.h"
void accel_init(void){
    // Configure the X direction as an analog input pin.
    //P6.1 A14
    P6 -> SEL0 |= BIT1;
    P6 -> SEL1 |= BIT1;

    // Configure the Y direction as an analog input pin.
    //P4.0 A13
    P4 -> SEL0 |= BIT0;
    P4 -> SEL1 |= BIT0;

    // Configure the Z direction as an analog input pin.
    //P4.2 A11
    P4 -> SEL0 |= BIT2;
    P4 -> SEL1 |= BIT2;


    // Configure CTL0 to sample 16-times in pulsed sample mode.
    ADC14 -> CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_SHT12 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14 -> CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0]
    ADC14 -> MCTL[0] = ADC14_MCTLN_INCH_9;

    // Associate the Y direction analog signal with MEM[1]
    ADC14 -> MCTL[1] = ADC14_MCTLN_INCH_10;

    // Associate the Z direction analog signal with MEM[2]
    ADC14 -> MCTL[2] = ADC14_MCTLN_INCH_15 | ADC14_MCTLN_EOS;;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    ADC14 -> IER0 = ADC14_IER0_IE1;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);

    // Turn ADC ON
    ADC14 -> CTL0 |= ADC14_CTL0_ON;

}



