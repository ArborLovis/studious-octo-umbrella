/*
 * hal_ssi2.c
 *
 *  Created on: 22.10.2018
 *      Author: Patrick
 */

//HAL
#include "tiva_headers.h"
#include "hal_ssi2.h"
#include "hal_gpio.h"

//DL
#include "dl_AD5601.h"


extern COM_RADAR Radar_com_;

void halSSI2Init()
{
    //enable peripherals and wait until peripherals are ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI2));

    GPIOPinConfigure(GPIO_PB4_SSI2CLK); //enable SSI clk for the module
    GPIOPinConfigure(GPIO_PB7_SSI2TX);  //enable MOSI for the ssi module
    GPIOPinConfigure(GPIO_PB5_SSI2FSS); //enable chip select
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, RADAR_SPI_SYNC);     //conf Chip select as output
    GPIOPinWrite(GPIO_PORTB_BASE, RADAR_SPI_SYNC, ~RADAR_SPI_SYNC);   //drive pin low, enable DAC communication

    //connect pins to the ssi module 2
    GPIOPinTypeSSI(GPIO_PORTB_BASE, RADAR_SPI_MISO | RADAR_SPI_MOSI | RADAR_SPI_SCLK | RADAR_SPI_SYNC);

    //Moto fmt, polarity 0, phase 1 --> Mode
    //use clk from system, also SysCtlClockGet() possible
    //Master-mode, 100kHz, 8 Bit, phase 0, polarity 1
    //SysCtlClockGet() returns the clock speed of the system
    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_1, SSI_MODE_MASTER, SSI2_CLK_SPEED, SSI2_DATA_LEN);
    SSIEnable(SSI2_BASE);   //enable SSI1 module

    Radar_com_.Status.B.TxSuc = 1;

}


void halAD5601Transmit()
{
    uint8_t len = 1;

    Radar_com_.Status.B.TxSuc = 0;        //SPI is loaded with data, not ready anymore

    for(Radar_com_.TxData.cnt = 0; Radar_com_.TxData.cnt < len; Radar_com_.TxData.cnt++)
    {
        SSIDataPut(SSI2_BASE, Radar_com_.TxData.Data[Radar_com_.TxData.cnt]);
        while(SSIBusy(SSI2_BASE));      //wait until byte has been send --> blocking function
    }

    Radar_com_.Status.B.TxSuc = 1;
}

uint8_t is_AD5601_com_busy()
{
    return Radar_com_.Status.B.TxSuc;
}
