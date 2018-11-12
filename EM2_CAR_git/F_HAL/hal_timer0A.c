/*
 * timerA1.c
 *
 *  Created on: 20.10.2017
 *      Author: mayerflo
 */
#include "stdint.h"

#include "tiva_headers.h"
#include "hal_timer0A.h"
#include "hal_gpio.h"

uint32_t timer0A_load;
extern ButtonCom ButtonSwitch;

void HAL_Timer0A_INIT()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)); // Wait for peripheral to be ready

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    timer0A_load = (SysCtlClockGet() / 10);
    TimerLoadSet(TIMER0_BASE, TIMER_A, timer0A_load);

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);         // Disable interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);          // Clear pending interrupts
    TimerIntRegister(TIMER0_BASE, TIMER_A, TIMER0A_INT_HANDLER);       // Register our handler function

    TimerEnable(TIMER0_BASE, TIMER_A);
}

void TIMER0A_INT_HANDLER() //Test a Timer !
{
    ButtonSwitch.Speed = (ButtonSwitch.RPM_ticks*10*10 + ButtonSwitch.Speed)>>1; // mm per second
    ButtonSwitch.RPM_ticks = 0;
    TimerIntClear(TIMER0_BASE, TIMER_A);
}

