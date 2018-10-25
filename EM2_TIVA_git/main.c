//TIVA
#include "tiva_headers.h"

//AL
#include "Source_test.h"

//HAL
#include "hal_init.h"
#include "hal_timer3.h"

//DL
#include "dl_AD5601.h"

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


        //test ramp_function
        test_rampe_ADC56();
    }

    return 0;
}

