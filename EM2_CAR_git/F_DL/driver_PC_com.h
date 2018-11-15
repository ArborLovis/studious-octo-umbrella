/*
 * driver_PC_com.h
 *
 *  Created on: 14.11.2018
 *      Author: Patrick
 */

#ifndef F_DL_DRIVER_PC_COM_H_
#define F_DL_DRIVER_PC_COM_H_

void DRIVER_UART0_ISR();
unsigned short Driver_sendDataPcUart0(unsigned short* data, unsigned short len);

#endif /* F_DL_DRIVER_PC_COM_H_ */
