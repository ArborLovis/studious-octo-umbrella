/*
 * dl_AD5601.h
 *
 *  Created on: 23.10.2018
 *      Author: Michael
 */

#ifndef F_DL_DL_AD5601_H_
#define F_DL_DL_AD5601_H_

/* ~~~~~~~~~~~~ MAKRO ~~~~~~~~~~~~ */
#define ADC56_CLEAR         0x3FFF
#define ADC56_NORMAL        0x000
#define ADC56_1K            0x4000
#define ADC56_100K          0x8000
#define ADC56_THREE_STATE   0xC000

enum AD5601_states{NORMAL, R1K, R100K, TRI_STATE};

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

/* ~~~~~~~~~~~~ PROTOTYP ~~~~~~~~~~~~ */

void dlAdc56WriteSetpoint(uint16_t value);
void dlAdc56WriteCommand(enum AD5601_states config);   //0 -> normal
                                        //1 -> 1k
                                        //2 -> 100k
                                        //3 -> Three-State
#endif /* F_DL_DL_AD5601_H_ */
