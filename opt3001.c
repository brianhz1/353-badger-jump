/*
 * opt3001.c
 *
 *  Created on: Mar 14, 2021
 *      Author: younghyunkim
 */

#include "opt3001.h"
#include "math.h"

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/

void opt3001_init(void)
{
    // Initialize OPT3001
    /*
     * conversion time: 100ms
     * continuous conversion
     */
    /* ADD CODE */

    //1100 0110 0000 1000
    //0xc608

    //j1.10 -> sda
    //j1.9 -> scl
    //j1.8 -> light_int


    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xcc08);
    //i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xc410);

}


/******************************************************************************
 * Returns the current ambient light in lux
 *  ******************************************************************************/
float opt3001_read_lux(void)
{
    // Read the Result register of OPT3001 and convert into Lux, then return.
    /* ADD CODE */
    uint16_t result = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);
    float LSB_Size = 0.01 * pow(2, result >> 12);
    float lux = LSB_Size * ((result << 4) >> 4);
    return lux; // Need to modify

}

void display_lux(float light)
{
    if(light < 200.0)
    {
        ece353_MKII_RGB_LED(false, false, true); // turn on BLUE
    }
    else if (light < 500.0)
    {
        ece353_MKII_RGB_LED(false, true, false); // turn on GREEN
    }
    else
    {
        ece353_MKII_RGB_LED(true, false, false); // turn on RED
    }
}
