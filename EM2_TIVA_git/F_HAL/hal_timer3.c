/*
 * hal_timer3.c
 *
 *  Created on: 25.10.2018
 *      Author: Patrick
 */

//TIVA
#include "tiva_headers.h"

//HAL
#include "hal_timer3.h"
#include "hal_gpio.h"

//#define DEBUG_GPTM  1

void timer3ISR();

volatile uint64_t gptm_systime_64us_steps = 0;

void hal_GPTM_init()
{
#ifdef DEBUG_GPTM
    GPIOPinWrite(GPIO_PORTD_BASE, PORTD_PIN1, ~PORTD_PIN1);    //drive low for idle
#endif

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)); //wait until timer 3 module is ready

    TimerDisable(TIMER3_BASE, TIMER_A); //safety measure, to be sure
    TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER3_BASE, TIMER_CFG_A_PERIODIC);  //timer count down
    TimerLoadSet(TIMER3_BASE, TIMER_A, GPTM_PERIOD);  //precision is 8us
    TimerEnable(TIMER3_BASE, TIMER_A);

    //configuration for the interrupt handling
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_A, timer3ISR);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

}

void timer3ISR()
{
#ifdef  DEBUG_GPTM
    static volatile uint8_t toggle = 0;
    toggle = !toggle;
    if(toggle)
        GPIOPinWrite(GPIO_PORTD_BASE, PORTD_PIN1, PORTD_PIN1); //toggle pin -> period of 16µs
    else
        GPIOPinWrite(GPIO_PORTD_BASE, PORTD_PIN1, ~PORTD_PIN1);
#endif

    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    gptm_systime_64us_steps++;
}

uint64_t get_systime_us()
{
    return (gptm_systime_64us_steps << 6);
}
