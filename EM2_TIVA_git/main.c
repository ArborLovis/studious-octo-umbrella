

/**
 * main.c
 */

#include "tiva_headers.h"
#include "Source_test.h"
#include "hal_init.h"



int main(void)
{
    //Initialization HAL System
    void hal_init();

    while(1)
    {
        //FFT Test function
        test_fft();


    }
}

