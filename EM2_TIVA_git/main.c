//TIVA
#include "tiva_headers.h"

//AL
#include "Source_test.h"

//HAL
#include "hal_init.h"
#include "hal_timer3.h"
#include "hal_adc.h"

//DL
#include "dl_AD5601.h"

extern uint8_t adc_finished_;

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
        halRadarSamplesIQ();
        test_rampe_ADC56();
    }

    return 0;
}

