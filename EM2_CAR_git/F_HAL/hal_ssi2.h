/*
 * hal_ssi2.h
 *
 *  Created on: 22.10.2018
 *      Author: Patrick
 */

#ifndef F_HAL_HAL_SSI2_H_
#define F_HAL_HAL_SSI2_H_

#include "tiva_headers.h"

#define SSI2_DATA_LEN    16              //8
#define SSI2_CLK_SPEED   8000000         //1MHz

/* ~~~~~~~~~~~~ PROTOTYP ~~~~~~~~~~~~ */

void halSSI2Init();
void halAD5601Transmit();

/*
 *  This function gives information about the communication bus
 *  with the AD5601 (DAC), if the bus is available or not.
 *  1:  Communication is allowed
 *  0:  Bus already busy, try again later
 */
uint8_t is_AD5601_com_busy();

#endif /* F_HAL_HAL_SSI2_H_ */
