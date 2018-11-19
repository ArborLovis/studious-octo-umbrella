/*
 * driver_general.c
 *
 *  Created on: 22.10.2017
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "driver_general.h"
#include "driver_aktorik.h"
#include "driver_LCD.h"
#include "driver_PC_com.h"
#include "dl_AD5601.h"
#include "mpu9250.h"

#include "hal_gpio.h"
#include "hal_general.h"

void driver_INIT(void)
{
    //set steering to zero
    Driver_setSteering(0);
    //calibrate ESC
    Driver_ESCInit();
    Driver_LCD_Init();
    //InitMPU9250(); // Set MPU9250
    //InitMagno(); // Set Magnetometer
    DRIVER_PC_COM_INIT();
    DRIVER_AD5621_INIT();
}

