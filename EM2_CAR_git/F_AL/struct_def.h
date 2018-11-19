/*
 * struct_def.h
 *
 *  Created on: 19.11.2018
 *      Author: Patrick
 */

#ifndef F_AL_STRUCT_DEF_H_
#define F_AL_STRUCT_DEF_H_

#define NUM_CHANNEL         8
#define MAX_RPM_BUFFER      11
#define FFT_LENGTH_512      512

#include "tiva_headers.h"
// ****************** RADAR ****************** //
//

typedef struct
{
    union
    {
        unsigned char R;
        struct
        {
            unsigned char TxSuc:1;      //set Bit, if data transmitted
            unsigned char dummy:7;
        }B;

    }Status;

    struct
    {
        unsigned char len; // Länge der Daten in Bytes die übertragen werden
        unsigned char cnt; // Index auf momentan übertragene Daten
        uint16_t Data[16]; // Tx Daten Array
    }TxData;

    struct
    {
        unsigned char len;          // Länge der empfangenen Daten
        unsigned char is_empty;     // check if buffer has already read
        uint16_t Data[16];              // Rx Daten Array
    }RxData;

}COM_RADAR;

// ****************** COMMUNICATION ****************** //
//
typedef struct
{
    union
    {
        unsigned char R;
        struct
        {
            unsigned char TxSuc:1;      //set Bit, if data transmitted
            unsigned char dummy:7;
        }B;

    }Status;

    struct
    {
        unsigned char len; // Länge der Daten in Bytes die übertragen werden
        unsigned char cnt; // Index auf momentan übertragene Daten
        unsigned char in_progress;
        unsigned char Data[256]; // Tx Daten Array
    }TxData;

    struct
    {
        unsigned char len;          // Länge der empfangenen Daten
        unsigned char is_empty;   // check if buffer has already read
        unsigned char Data[256];    // Rx Daten Array
    }RxData;

}COM_Status;

typedef struct
{
    union
    {
        unsigned char R;
        struct
        {
            unsigned char TxSuc :1; // Bit =1, if data were sent
            unsigned char dummy :7;
        }B;
    }Status;

   struct
   {
        unsigned char len;
        unsigned char cnt;
        unsigned char Data [256];
   }TxData;

   struct
   {
       unsigned char len;
       unsigned char Data [256];
   }RxData;

}SSI_Com;

// ****************** SENSORS & ACTUATORS ****************** //
//
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
        float I_signal[FFT_LENGTH_512];
        float Q_signal[FFT_LENGTH_512];
        uint8_t fft_data_ready;
    }Radar_FFT;

}Sensor;

#endif /* F_AL_STRUCT_DEF_H_ */
