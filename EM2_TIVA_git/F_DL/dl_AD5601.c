/*
 * dl_AD5601.c
 *
 *  Created on: 23.10.2018
 *      Author: Michael
 */

#include "hal_ssi2.h"
#include "dl_AD5601.h"

extern COM_Status_all Radar_com_;

void dlAdc56WriteSetpoint(uint16_t value)
{
    value = value << 2;
    value = value & ADC56_CLEAR;

    uint16_t temp = Radar_com_.TxData.Data[0] & ~ADC56_CLEAR;
    value = temp | value;

    //Check if Transmit ready
    while(!Radar_com_.Status.B.TxSuc);
    Radar_com_.Status.B.TxSuc = 0;

    //Write Transmitdata to struct
    Radar_com_.TxData.Data[0] = value;

    //Send Setpoint
    SysCtlDelay(20);
    halAD5601Transmit();

    //Wait until ready
    while(!Radar_com_.Status.B.TxSuc);
}

void dlAdc56WriteCommand(int config)
{
    uint16_t mask = 0;

    //Check if Transmit ready
    while(!Radar_com_.Status.B.TxSuc);
    Radar_com_.Status.B.TxSuc = 0;

    mask = ADC56_CLEAR;
    Radar_com_.TxData.Data[0] = Radar_com_.TxData.Data[0] & mask;

    switch(config)
    {
        case 0:
        {
            mask = ADC56_NORMAL;
            break;
        }
        case 1:
        {
            mask = ADC56_1K;
            break;
        }
        case 2:
        {
            mask = ADC56_100K;
            break;
        }
        case 3:
        {
            mask = ADC56_THREE_STATE;
            break;
        }
    }

    //Write Transmitdata to struct
    Radar_com_.TxData.Data[0] = Radar_com_.TxData.Data[0] | mask;

    //Send Setpoint
    SysCtlDelay(20);
    halAD5601Transmit();

    //Wait until ready
    while(!Radar_com_.Status.B.TxSuc);
}


