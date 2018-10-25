/*
 * hal_ssi2.h
 *
 *  Created on: 22.10.2018
 *      Author: Patrick
 */

#ifndef F_HAL_HAL_SSI2_H_
#define F_HAL_HAL_SSI2_H_

#include "tiva_headers.h"

#define SSI2_DATA_LEN    16              //8
#define SSI2_CLK_SPEED   100000

/* ~~~~~~~~~~~~ PROTOTYP ~~~~~~~~~~~~ */

void halSSI2Init();
void halAD5601Transmit();

/* ~~~~~~~~~~~~ STRUCTS ~~~~~~~~~~~~ */

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
        unsigned char len;              // Länge der Daten in Bytes die übertragen werden
        unsigned char cnt;              // Index auf momentan übertragene Daten
        uint16_t Data[256];    // Tx Daten Array
    }TxData;

    struct
    {
        unsigned char len;              // Länge der empfangenen Daten
        unsigned char is_empty;         // check if buffer has already read
        uint16_t Data[256];    // Rx Daten Array
    }RxData;

}COM_Status_all;

#endif /* F_HAL_HAL_SSI2_H_ */
