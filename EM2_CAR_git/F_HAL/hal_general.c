/*
 * hal_general.c
 *
 *  Created on: 20.09.2017
 *      Author: mayerflo
 */

#include "tiva_headers.h"

#include "hal_general.h"
#include "hal_gpio.h"
#include "hal_ssi_lcd.h"
#include "hal_pwm.h"
#include "hal_timer0A.h"
#include "hal_ucs.h"
#include "hal_i2c.h"
#include "hal_uart0.h"
#include "hal_adc.h"
#include "hal_ssi2.h"
#include "hal_timer3.h"


ButtonCom ButtonSwitch;
short timer2cnt;
unsigned long dist_USl_in_cm;
char help_US;

void HAL_INIT(void)
{
    HAL_GPIO_INIT();
    HAL_UCS_INIT();
    HAL_PWM_Aktorik_Init();
    HAL_Timer0A_INIT();
    HAL_SSI_Init();
    halUart0Init();
    halAdc0Init(0);     //Infrared Sensors & VBAT
    halAdc1Init(0);     //RADAR
    //InitI2C0();
}
