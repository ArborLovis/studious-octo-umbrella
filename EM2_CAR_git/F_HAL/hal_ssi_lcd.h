/*
 * hal_ssi_lcd.h
 *
 *  Created on: 22.03.2018
 *      Author: mayerflo
 */

#ifndef HAL_HAL_SSI_LCD_H_
#define HAL_HAL_SSI_LCD_H_

void HAL_SSI_Init(void);
void HAL_SSI1_Transmit(short);
void SSI1_Handler(void);

#endif /* HAL_HAL_SSI_LCD_H_ */
