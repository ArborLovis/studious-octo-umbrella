/*
 * radix2_fft.c
 *
 *  Created on: 11.10.2018
 *      Author: Patrick
 */

#include "radix2_fft.h"
#include "Scramble_data.h"
#include "twiddle_16.h"
#include "twiddle_1024.h"
#include "tiva_headers.h"

#include "dl_general.h"

uint8_t get_num_stage(uint16_t fft_length);

extern Sensor sensor_data_;

void do_fft_radix2(float* i_sig, float* q_sig, uint16_t length, float* freq_bin)
{
    //indicate radar data are not available at the moment
    sensor_data_.Radar_FFT.fft_data_ready = 0;

    short p = FFT_STAGE_FACTOR_4;     //length of stage: 2^p
    short half = 1;
    short stage = 1;
    short index = 0;
    short n = 0;
    short pos = 0;
    short k = 0;

    float i_sig_temp = 0.0f;
    float q_sig_temp = 0.0f;

    Scramble_data(i_sig, q_sig, length);    //change bit order

    for (stage = 1; stage <= p; stage++)
    {
        for (index = 0; index < length; index += (0x01<<stage))
        {
            for (n = 0; n < half; n++)
            {
                pos = n + index;
                k = (1<<(p-stage))*n;   //pow(2, p-stage)*n //(2^(O-stage))*n;

                //w_real = cos((2*pi)*k/nSamples);%real(w);
                //w_imag = -sin((2*pi)*k/nSamples);%imag(w);

                i_sig_temp = i_sig[pos+half]*twiddle_array[k][0] - q_sig[pos+half]*twiddle_array[k][1];
                q_sig_temp = q_sig[pos+half]*twiddle_array[k][0] + i_sig[pos+half]*twiddle_array[k][1];

                i_sig[pos+half] = i_sig[pos] - i_sig_temp;
                q_sig[pos+half] = q_sig[pos] - q_sig_temp;

                i_sig[pos] = i_sig[pos] + i_sig_temp;
                q_sig[pos] = q_sig[pos] + q_sig_temp;

            }
        }
        half = 2 * half;
    }

    for(stage = 0; stage < length; stage++)
    {
        freq_bin[stage] = i_sig[stage];
        q_sig[stage] = q_sig[stage];
    }

    sensor_data_.Radar_FFT.fft_data_ready = 1;
}

void fft_radix2_var(float* i_sig, float* q_sig, uint16_t fft_len)
{
    //indicate radar data are not available at the moment
    sensor_data_.Radar_FFT.fft_data_ready = 0;

    uint8_t p = get_num_stage(fft_len);     //length of stage: 2^p
    uint16_t half = 1;
    uint8_t stage = 0;
    uint16_t index = 0;
    uint16_t n = 0;
    uint16_t pos = 0;
    uint16_t k = 0;

    float i_sig_temp = 0.0f;
    float q_sig_temp = 0.0f;

    Scramble_data(i_sig, q_sig, fft_len);    //change bit order

    for (stage = 1; stage <= p; stage++)
    {
        for (index = 0; index < fft_len; index += (0x01<<stage))
        {
            for (n = 0; n < half; n++)
            {
                pos = n + index;
                k = (1<<(p-stage))*n;
                k = (0x01 << (P_MAX-p))*k;

                i_sig_temp = i_sig[pos+half]*twiddle1024[k][0] - q_sig[pos+half]*twiddle1024[k][1];
                q_sig_temp = q_sig[pos+half]*twiddle1024[k][0] + i_sig[pos+half]*twiddle1024[k][1];

                i_sig[pos+half] = i_sig[pos] - i_sig_temp;
                q_sig[pos+half] = q_sig[pos] - q_sig_temp;

                i_sig[pos] = i_sig[pos] + i_sig_temp;
                q_sig[pos] = q_sig[pos] + q_sig_temp;

            }
        }
        half = 2 * half;
    }

    sensor_data_.Radar_FFT.fft_data_ready = 1;
}

uint8_t get_num_stage(uint16_t fft_length)
{
    unsigned short index = 0;

    while(fft_length)
    {
        index++;
        fft_length = fft_length >> 0x01;
    }

    if(!index)
        return 0;
    else
        return (index-1);
}
