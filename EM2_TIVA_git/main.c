

/**
 * main.c
 */

#include "tiva_headers.h"
#include "Source_test.h"
#include "hal_init.h"
#include "dl_AD5601.h"



int main(void)
{
    //Initialization HAL System
    hal_init();

    //Set config to normal
    dlAdc56WriteCommand(0);
    SysCtlDelay(2000);

    while(1)
    {
        //FFT Test function
        //test_fft();


        //test ramp_function
        test_rampe_ADC56();
    }
}

