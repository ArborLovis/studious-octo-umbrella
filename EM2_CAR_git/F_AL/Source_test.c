/*
 * Source_test.c
 *
 *  Created on: 23.10.2018
 *      Author: Michael
 */


#include "tiva_headers.h"
#include "Source_test.h"
#include "radix2_fft.h"
#include "test_sig128.h"
#include "dl_AD5601.h"
#include "struct_def.h"

#include "hal_timer3.h"

#define WAIT_10MS 10000
#define WAIT_1MS  1000
#define WAIT_500us  500

//static float test_i_sig[128] = { 0.0 };
//static float test_q_sig[128] = { 0.0 };

extern Sensor sensor_data_;


void clear_test_vect(float* vect)
{
    vect[0] = 0;
    vect[1] = 2.0137;
    vect[2] = 2.4142;
    vect[3] = 1.2483;
    vect[4] = 0;
    vect[5] = -0.1659;
    vect[6] = 0.4142;
    vect[7] = 0.5995;
    vect[8] = 0;
    vect[9] = -0.5995;
    vect[10] = -0.4142;
    vect[11] = 0.1659;
    vect[12] = 0;
    vect[13] = -1.2483;
    vect[14] = -2.4142;
    vect[15] = -2.0137;
}


void test_fft()
{
    uint16_t i = 0;

    for(i = 0; i < 256; i++)
   {
        if(i < 128)
        {
            sensor_data_.Radar_FFT.I_signal[i] = test_sig128[i];
           SysCtlDelay(100);
           sensor_data_.Radar_FFT.Q_signal[i] = 0;
        }
        else
        {
            sensor_data_.Radar_FFT.Q_signal[i] = 0;
            sensor_data_.Radar_FFT.I_signal[i] = 0;
        }

   }
   //do_fft_radix2(test_sample, zero_vect, 16, freq_bins);

   //refresh data vales
   /*

   clear_test_vect(test_sample);
   for(index = 0; index < 16; index++)
   {
       zero_vect[index] = 0;
       freq_bins[index] = 0;
   }
   */
   // ++++++++++++++++++++++++++++

   fft_radix2_var(sensor_data_.Radar_FFT.I_signal, sensor_data_.Radar_FFT.Q_signal, 256);
}

void test_rampe_ADC56()
{
    static char value = 0;
    uint16_t signal = 0;
    static uint64_t delta_time = 0;

    if(value > 100)
        value = 0;

    signal = (3700.0/100.0)*(float)value;
/*
    dlAdc56WriteSetpoint(signal);
    SysCtlDelay(1000000);
    value++;
*/

    if((get_systime_us() - delta_time) > 1500)
    {
        delta_time = get_systime_us();
        dlAdc56WriteSetpoint(signal);
        value++;
    }

}
