/*
 * task_light_sensor.c
 *
 *  Created on: May 4, 2023
 *      Author: Brian Zhang
 */

#include <task_light_sensor.h>

bool dark_mode;

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII and the i2c
 ******************************************************************************/
void light_sensor_init(void)
{
    i2c_init();
    i2c_write_16(OPT3001_ADDRESS, CONFIG_REG, 0xC610);
}

/******************************************************************************
 * Returns the current ambient light in lux
 ******************************************************************************/
float light_sensor_read_lux(void)
{
    uint16_t result = i2c_read_16(OPT3001_ADDRESS, RESULT_REG);
    float LSB_Size = 0.01 * pow(2, result >> 12);
    float lux = LSB_Size * (result & 0x0FFF);
    return lux;

}

/******************************************************************************
 * Task which toggles dark mode based on light sensor
 ******************************************************************************/
void Task_light_sensor(void)
{
    while (1)
    {
        while (!game_running)
        {
            float lux = light_sensor_read_lux();

            if (lux < DARK_MODE_LUX_THRESHOLD)
            {
                dark_mode = true;
                background_color = DARK_BACKGROUND_COLOR;
                bucky_color = BUCKY_DARK_COLOR;
            }
            else
            {
                dark_mode = false;
                background_color = LIGHT_BACKGROUND_COLOR;
                bucky_color = BUCKY_LIGHT_COLOR;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
