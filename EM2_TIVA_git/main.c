//TIVA
#include "tiva_headers.h"

//AL
#include "Source_test.h"
#include "radix2_fft.h"

//HAL
#include "hal_init.h"
#include "hal_timer3.h"
#include "hal_adc.h"

//DL
#include "dl_AD5601.h"

extern uint8_t adc_finished_;
extern RADAR_BUFFER_ADC radar_data_;

void main(void)
{
    //Initialization HAL System
    hal_init();

    //Set config to normal
    dlAdc56WriteCommand(NORMAL);
    SysCtlDelay(2000);

    while(1)
    {
        //FFT Test function
        //test_fft();
/*
        if(adc_finished_)
        {
            adc_finished_ = 0;
            startADC1();
        }
*/
        //test ramp_function
        //halRadarSamplesIQ();
        //test_rampe_ADC56();

        //SysCtlDelay(100);

        if(radar_data_.data_release_)
        {
            fft_radix2_var(radar_data_.radar_buffer_i_, radar_data_.radar_buffer_q_, 256);

            radar_data_.data_release_ = 0;

            int i = 0;
            for(i = 0; i<RADAR_BUFFER_SIZE; i++)
            {
                if(i > 0)
                    radar_data_.radar_pwr_[i] = radar_data_.radar_buffer_i_[i]*radar_data_.radar_buffer_i_[i] + radar_data_.radar_buffer_q_[i]*radar_data_.radar_buffer_q_[i];
                else
                    radar_data_.radar_pwr_[i] = 0;
            }

            i = 0;
            SysCtlDelay(100000);
        }

    }
}

