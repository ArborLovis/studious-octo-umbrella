/*
 * dl_general.h
 *
 *  Created on: 22.03.2018
 *      Author: Patrick
 */

#ifndef F_DL_DL_GENERAL_H_
#define F_DL_DL_GENERAL_H_

#include "../tiva_headers.h"

//left and right out of the view of the front
#define STEERING_MIDDLE         1539
#define STEERING_MAX_RIGHT      1899
#define STEERING_MAX_LEFT       1199

#define MIN_RPW_ESC      2500
#define MAX_RPW_ESC      5000
#define MIN_FPW_ESC      1560
#define MAX_FPW_ESC      2470
#define MAX_BRAKE_ESC    1400

#define MAX_RPM_BUFFER 11
#define NUM_CHANNEL     8

#define FFT_LENGTH_512  512
#define FFT_LENGTH_16   16

typedef enum speed_mode {FORWARD, BACKWARD, BRAKE} SpeedMode;

typedef struct
{
    struct
    {
        unsigned long cnt_rpm_fwd;          //all over count forward
        unsigned long cnt_rpm_bwd;          //all over count backward
        unsigned char direction;            //forwards or backwards
        int speed;                          //mm per sec
        unsigned long rpm_data_buffer_[MAX_RPM_BUFFER];            //RPM data buffer
        unsigned short capture_of;            //Overflow capture flag

    }RPM;

    union
    {
       unsigned char R;
       struct
       {
           unsigned char ADCrdy:1;      //if adc data is ready, this bit will be set
           unsigned char AdcDummy:7;
       }B;
    }Status;

    uint32_t adc_values[NUM_CHANNEL];

    unsigned int adc_mean_values[NUM_CHANNEL];

    struct
    {
        bool us1_data_ready;
        bool us2_data_ready;
        unsigned int timer_cnt_us1;
        unsigned int timer_cnt_us2;
        unsigned int distance_us1;
        unsigned int distance_us2;
    }Sonic;

    struct
    {
        float I_signal[FFT_LENGTH_16];
        float Q_signal[FFT_LENGTH_16];
        uint8_t fft_data_ready;
    }Radix2_FFT;


}Sensor;


/*  Name:           dlSetSteering
 *  Parameter:      int16_t ctr_val
 *  Description:    The steering (servo) can be controlled.
 *                  By setting the ctr_val between -100 and 100
 *                  the angle of the servo can be cotrolled.        */
void dlSetSteering(int16_t ctr_val);

/*  Name:           dlSetThrottle
 *  Parameter:      SpeedMode dir, int16_t speed
 *  Description:    The ESC (dc-motor) of the car can be controlled.
 *                  By setting a value for "dir" the direction can be selected.
 *                  With "speed", the speed of the car can be controlled by setting
 *                  it from 0 to 100.                         */
void dlSetThrottle(SpeedMode dir, int16_t speed);

#endif /* F_DL_DL_GENERAL_H_ */
