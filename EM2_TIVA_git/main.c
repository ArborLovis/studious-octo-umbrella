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

int main(void)
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
        }
    }

    return 0;
}

