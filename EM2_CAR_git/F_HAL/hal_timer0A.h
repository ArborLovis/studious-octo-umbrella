/*
 * timer0A.h
 *
 *  Created on: 20.10.2017
 *      Author: mayerflo
 */

#ifndef HAL_HAL_TIMER0A_H_
#define HAL_HAL_TIMER0A_H_

void HAL_Timer0A_INIT(void);
void TIMER0A_INT_HANDLER(void);

extern short timer2cnt;
extern unsigned long cnt_for_integral;

#endif /* HAL_HAL_TIMER0A_H_ */
