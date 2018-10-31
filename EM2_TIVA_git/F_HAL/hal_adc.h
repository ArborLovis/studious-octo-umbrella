/*
 * hal_adc.h
 *
 *  Created on: 06.06.2018
 *      Author: Patrick
 */

#ifndef F_HAL_HAL_ADC_H_
#define F_HAL_HAL_ADC_H_

#include "../tiva_headers.h"

#define ADC_SS0                   0     //8 samples per sequence
#define ADC_SS1                   1     //4 samples per sequence
#define ADC_SS2                   2
#define ADC_SS3                   3     //1 sample per sequence
#define ADC_SAMPLE_ORDER_0        0
#define ADC_SAMPLE_ORDER_1        1
#define ADC_SAMPLE_ORDER_2        2
#define ADC_SAMPLE_ORDER_3        3
#define ADC_SAMPLE_ORDER_4        4
#define ADC_SAMPLE_ORDER_5        5

void halAdc0Init(bool enable_hw_avg);
void halAdc1Init(bool enable_hw_avg);
void halGetAdcSamples();
void halRadarSamplesIQ();

void startADC1();

#endif /* F_HAL_HAL_ADC_H_ */
