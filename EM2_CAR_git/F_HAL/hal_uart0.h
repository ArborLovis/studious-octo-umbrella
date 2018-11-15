/*
 * hal_uart0.h
 *
 *  Created on: 14.11.2018
 *      Author: Patrick
 */

#ifndef F_HAL_HAL_UART0_H_
#define F_HAL_HAL_UART0_H_

void halUart0Init();
void halGetPcDataUart0();
uint8_t halSendDataToPcUart0(uint8_t *data, uint8_t len);


#endif /* F_HAL_HAL_UART0_H_ */
