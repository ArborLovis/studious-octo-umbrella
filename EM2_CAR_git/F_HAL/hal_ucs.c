/*
 * hal_ucs.c
 *
 *  Created on: 14.10.2017
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "hal_gpio.h"
#include "hal_ucs.h"

void HAL_UCS_INIT()
{
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}


