/*
 * hal_pwm.c
 *
 *  Created on: 09.04.2018
 *      Author: mayerflo
 */

/*
* Timer for PWM (Steering and Throttle)
* PWM frequency = 60 Hz
*/
#include "tiva_headers.h"
#include "hal_pwm.h"

#include "driver_aktorik.h"

uint32_t ui32PWMClock;

void HAL_PWM_Aktorik_Init()
{
    // different adjustments ------------------------------------------
    SysCtlPWMClockSet(SYSCTL_PWMDIV_8); // devide the
    // sysclk by 16 --> 16.000.000 / 16 = 1.000.000 Hz

    // activate the peripheral ----------------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)) // ready ?

    ui32PWMClock = SysCtlClockGet() / 8;
    uint32_t ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    // PWM generator = 1, down mode , no sync , stop while debugging
    //( actually it doesn 't matter),
    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, (PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC | PWM_GEN_MODE_DBG_RUN));

    // generator 1, 16.600 cycles are 16,6 ms (60 Hz)
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, 0); // PWM2 , 1000 clock cycles ( only for test )
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, 0); // PWM3 , 500 clock cycles ( only for test )

    PWMGenIntRegister(PWM1_BASE, PWM_GEN_1, &Driver_PWMServo_ISR);
    PWMGenIntTrigEnable(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_ZERO);
    PWMIntEnable(PWM1_BASE, PWM_INT_GEN_1);

    // PWM2 and PWM3 , true
    PWMOutputState(PWM1_BASE, (PWM_OUT_2_BIT | PWM_OUT_3_BIT), true);

    PWMGenEnable(PWM1_BASE, PWM_GEN_1); // generator 1



}


