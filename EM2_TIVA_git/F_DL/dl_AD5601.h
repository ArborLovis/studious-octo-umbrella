/*
 * dl_AD5601.h
 *
 *  Created on: 23.10.2018
 *      Author: Michael
 */

#ifndef F_DL_DL_AD5601_H_
#define F_DL_DL_AD5601_H_

/* ~~~~~~~~~~~~ MAKRO ~~~~~~~~~~~~ */
#define ADC56_CLEAR 0x3FFF
#define ADC56_NORMAL 0x000
#define ADC56_1K 0x4000
#define ADC56_100K 0x8000
#define ADC56_THREE_STATE 0xC000

/* ~~~~~~~~~~~~ PROTOTYP ~~~~~~~~~~~~ */

void dlAdc56WriteSetpoint(uint16_t value);
void dlAdc56WriteCommand(int config);     //0 -> normal
                                        //1 -> 1k
                                        //2 -> 100k
                                        //3 -> Three-State
#endif /* F_DL_DL_AD5601_H_ */
