/*
 * radix2_fft.h
 *
 *  Created on: 11.10.2018
 *      Author: Patrick
 */

#ifndef F_AL_RADIX2_FFT_H_
#define F_AL_RADIX2_FFT_H_

#include "tiva_headers.h"

#define FFT_STAGE_FACTOR_4  4
#define FFT_STAGE_FACTOR_6  6   //64 bit
#define FFT_STAGE_FACTOR_7  7   //128 bit
#define FFT_STAGE_FACTOR_8  8   //256 bit
#define FFT_STAGE_FACTOR_9  9   //512 bit

#define N_MAX   1024
#define P_MAX   10

void do_fft_radix2(float* i_sig, float* q_sig, uint16_t length, float*);

void fft_radix2_var(float* i_sig, float* q_sig, uint16_t fft_len);

#endif /* F_AL_RADIX2_FFT_H_ */
