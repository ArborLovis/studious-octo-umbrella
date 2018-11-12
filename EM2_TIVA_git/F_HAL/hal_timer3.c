/*
 * hal_timer3.c
 *
 *  Created on: 25.10.2018
 *      Author: Patrick
 */

//TIVA
#include "tiva_headers.h"
#include "dl_AD5601.h"

//HAL
#include "hal_timer3.h"
#include "hal_gpio.h"
#include "hal_adc.h"

//#define DEBUG_GPTM  1
void timer3AIsr();
void timer3BIsr();


volatile uint64_t gptm_systime_64us_steps = 0;

void hal_GPTM_init()
{
#ifdef DEBUG_GPTM
    GPIOPinWrite(GPIO_PORTD_BASE, PORTD_PIN1, ~PORTD_PIN1);    //drive low for idle
#endif

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)); //wait until timer 3 module is ready


    TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC | TIMER_CFG_B_PERIODIC);  //timer count down

    //Timer A Configuration
    TimerDisable(TIMER3_BASE, TIMER_A); //safety measure, to be sure
    TimerLoadSet(TIMER3_BASE, TIMER_A, GPTM_PERIOD);  //precision is 8us
    TimerEnable(TIMER3_BASE, TIMER_A);

    //configuration for the interrupt handling of Timer A
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_A, timer3AIsr);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);


    //Timer B Configuration
    TimerDisable(TIMER3_BASE, TIMER_B);
    TimerLoadSet(TIMER3_BASE, TIMER_B, RADAR_SWEEP_PERIOD);  //precision is 8us
    TimerEnable(TIMER3_BASE, TIMER_B);

    //configuration for the interrupt handling of Timer A
    TimerIntClear(TIMER3_BASE, TIMER_TIMB_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_B, timer3BIsr);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMB_TIMEOUT);

}

void timer3AIsr()
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

void timer3BIsr()
{
    TimerIntClear(TIMER3_BASE, TIMER_TIMB_TIMEOUT);

    // Send new SPI-Value
    static int value = 0;
    //static char updown = 1;
    uint16_t signal = 0;

    //if(value == 0)
    //    updown = 1;
    //else if(value >= 128)
    //    updown = 0;

    signal = 14*value;      //Steps with 14 is signal up to 3584
    dlAdc56WriteSetpoint(signal);

    if(value < 255)
        value++;
    else
        value = 0;

    //if(updown)
    //     value++;
    //else
    //    value--;

    halRadarSamplesIQ();

}



uint64_t get_systime_us()
{
    return (gptm_systime_64us_steps << 6);
}
