/*
 * dl_AD5601.c
 *
 *  Created on: 23.10.2018
 *      Author: Michael
 */

//HAL
#include "hal_ssi2.h"


//DL
#include "dl_AD5601.h"

COM_RADAR Radar_com_;

enum AD5601_states AD5601_state;

void dlAdc56WriteSetpoint(uint16_t value)
{
    //LSB and LSB+1 has to be avoided, these are don't care regions
    value = value << 2;
    value = value & ADC56_CLEAR;    //force power-down mode bits (MSB & MSB-1 to be zero)

    //actual data is cleared and previous power down mode is restored
    uint16_t temp = Radar_com_.TxData.Data[0] & ~ADC56_CLEAR;
    value = temp | value;

    //Check if Transmit ready
    while(!is_AD5601_com_busy());
    //Radar_com_.Status.B.TxSuc = 0;    //FB: not needed here, is set zero where transmission take place

    //Write Transmitdata to struct
    Radar_com_.TxData.Data[0] = value;
    Radar_com_.TxData.cnt = 0;
    Radar_com_.TxData.len = 1;

    //Send Setpoint
    SysCtlDelay(20);
    halAD5601Transmit();

    //Wait until ready
    while(!Radar_com_.Status.B.TxSuc);  //FB: This is always true, because halAD5601Transmit() is a blocking function.
                                        //    The function is returned ater the transmit process succeeded
}

void dlAdc56WriteCommand(enum AD5601_states config)
{
    uint16_t mask = 0;

    //Check if Transmit ready
    while(!is_AD5601_com_busy());
    //Radar_com_.Status.B.TxSuc = 0;    //FB: not needed here, is set zero where transmission take place

    mask = ADC56_CLEAR;
    Radar_com_.TxData.Data[0] = Radar_com_.TxData.Data[0] & mask;

    switch(config)
    {
        case NORMAL:
        {
            mask = ADC56_NORMAL;
            break;
        }
        case R1K:
        {
            mask = ADC56_1K;
            break;
        }
        case R100K:
        {
            mask = ADC56_100K;
            break;
        }
        case TRI_STATE:
        {
            mask = ADC56_THREE_STATE;
            break;
        }
    }

    //Write Transmitdata to struct
    Radar_com_.TxData.Data[0] = Radar_com_.TxData.Data[0] | mask;
    Radar_com_.TxData.cnt = 0;
    Radar_com_.TxData.len = 1;

    //Send Setpoint
    SysCtlDelay(20);
    halAD5601Transmit();

    //Wait until ready
    while(!Radar_com_.Status.B.TxSuc);      //FB: redundant
}


