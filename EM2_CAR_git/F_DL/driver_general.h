/*
 * driver_general.h
 *
 *  Created on: 22.10.2017
 *      Author: mayerflo
 */

#ifndef DL_DRIVER_GENERAL_H_
#define DL_DRIVER_GENERAL_H_

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
        uint8_t in_progress;    //indicate if TX is still ongoing
        unsigned char Data[256]; // Tx Daten Array
    }TxData;

    struct
    {
        unsigned char len;          // Länge der empfangenen Daten
        unsigned char is_empty;   // check if buffer has already read
        unsigned char Data[256];    // Rx Daten Array
    }RxData;

}COM_Status;


void driver_INIT(void);


#endif /* DL_DRIVER_GENERAL_H_ */
