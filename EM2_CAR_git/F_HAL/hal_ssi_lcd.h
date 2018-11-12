/*
 * hal_ssi_lcd.h
 *
 *  Created on: 22.03.2018
 *      Author: mayerflo
 */

#ifndef HAL_HAL_SSI_LCD_H_
#define HAL_HAL_SSI_LCD_H_

void HAL_SSI_Init(void);
void HAL_SSI1_Transmit(short);
void SSI1_Handler(void);

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

}SSI_Com ;

#endif /* HAL_HAL_SSI_LCD_H_ */
