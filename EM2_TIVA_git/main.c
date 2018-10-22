

/**
 * main.c
 */

#include "tiva_headers.h"
#include "radix2_fft.h"
#include "test_sig128.h"

void clear_test_vect(float*);

int main(void)
{

    static float test_i_sig[128] = { 0.0 };
    static float test_q_sig[128] = { 0.0 };

    uint16_t i = 0;
    // new test var
    uint16_t test = 7;

    while(1)
    {
        for(i = 0; i < 128; i++)
        {
            test_i_sig[i] = test_sig128[i];
            SysCtlDelay(100);
            test_q_sig[i] = 0;
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

        fft_radix2_var(test_i_sig, test_q_sig, 128);

    }

	return 0;
}

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
