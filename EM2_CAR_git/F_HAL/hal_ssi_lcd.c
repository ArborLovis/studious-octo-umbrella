/*
 * hal_ssi_lcd.c
 *
 *  Created on: 22.03.2018
 *      Author: mayerflo
 */

#include "hal_ssi_LCD.h"
#include "hal_gpio.h"
#include "tiva_headers.h"
#include  "struct_def.h"

extern COM_Status LCD_Data;

void HAL_SSI_Init(void)
{
/*
 * This function should configure our SPI module as followed :
 * * SPI Master Mode
 * * 100 kHz
 * * 8 bit MSB first
 * * clk phase 0
 * * clk polarity 1*/

     // Enable the SSI1 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    // Wait for the SSI0 module to be ready .
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI1));

    // Configure the clock of the SSI for the display
    SSIConfigSetExpClk(SSI1_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_3,SSI_MODE_MASTER,100000,8);
    // Enable the SSI module
    SSIEnable(SSI1_BASE);

    LCD_Data.Status.B.TxSuc=1;
}

void HAL_SSI1_Transmit(short data_len)
{
    LCD_Data.TxData.cnt=0;
    LCD_Data.Status.B.TxSuc = 0;

    while(data_len > LCD_Data.TxData.cnt)
    {
        SSIDataPut(SSI1_BASE, LCD_Data.TxData.Data[LCD_Data.TxData.cnt]);
        LCD_Data.TxData.cnt++;
        while(SSIBusy(SSI1_BASE)); // wait for display
    }

    LCD_Data.Status.B.TxSuc = 1;
}
