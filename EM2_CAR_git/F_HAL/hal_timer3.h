/*
 * hal_timer3.h
 *
 *  Created on: 25.10.2018
 *      Author: Patrick
 *
 *  The timer 3 is handled as a general purpose Timer,
 *  also called GPTM.
 *  The aim is to generate a constant timer interval of
 *  64�s resolution. So within this resolution every other
 *  time can be build by counting a variable.
 *  By shifting left 6 times, the right time can be achieved.
 *
 */

//Change in clock frequency: NOW --> 20MHz!!!!!!!!!!

#ifndef F_HAL_HAL_TIMER3_H_
#define F_HAL_HAL_TIMER3_H_

// GPTM_PERIOD = 64us*16MHz (oszi measurement: 1022 is a better value)
#define GPTM_PERIOD 1022            //  64�s (clock frequency 16MHz)

#define RADAR_SWEEP_PERIOD 5858     //9375 -> T = 150ms, 512 steps, 5859,375 = 150ms/512*20MHz
//#define RADAR_SWEEP_PERIOD 11718     //9375 -> T = 150ms, 256 steps, 11718,75 = 150ms/256*20MHz


void hal_GPTM_init();



//the system time can be read after the timer has been enabled.
//otherwise the system time is always zero
uint64_t get_systime_us();

#endif /* F_HAL_HAL_TIMER3_H_ */
