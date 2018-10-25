/*
 * hal_init.c
 *
 *  Created on: 15.03.2018
 *      Author: Patrick
 */

#include "../tiva_headers.h"
#include "hal_gpio.h"
#include "hal_pwm.h"
#include "hal_usc.h"
#include "hal_us.h"
#include "hal_ssi1.h"
#include "hal_ssi2.h"
#include "hal_uart1.h"
#include "hal_timer2.h"
#include "hal_adc.h"

#define HW_AVG_ON   0

void hal_init()
{
   // IntMasterDisable();
    halSysClkInit();
    halGpioInit();
    //halPWMInit();
    //halUsInit();
    //halSsi1Int();
    halSSI2Init();
    //halUart1Init();
    //halTimer2Init();
    //halAdcInit(HW_AVG_ON);
    //while(!IntMasterEnable());  //wait until interrupts are enabled, global bit
}
