/*
 * hal_uart0.c
 *
 *  Created on: 14.11.2018
 *      Author: Patrick
 */

#include "tiva_headers.h"
//DL
#include "driver_general.h"
#include "driver_PC_com.h"
//HAL
#include "hal_uart0.h"
#include "hal_gpio.h"

extern COM_Status uart_status_;

void halUart0Init()
{
    // Enable Peripheral of the UART module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    // Configure Clock for UART
    //115200 baud, 8 data bits, one stop bit, no parity check
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    // Configure the GPIO Pin Mux for PA1
    // for U0TX
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, UART0_TX);

    // Configure the GPIO Pin Mux for PC5
    // for U0RX
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, UART0_RX);

    // enable UART for interrupt handling
    // Level-set: Inform about when interrupt should be triggered. After which buffer size?
    UARTIntRegister(UART0_BASE, &DRIVER_UART0_ISR);
    UARTFIFOEnable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTTxIntModeSet(UART0_BASE, UART_TXINT_MODE_EOT); //generate interrupt by reaching empty FIFO level
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_TX);

    UARTEnable(UART0_BASE);
}

uint8_t halSendDataToPcUart0(uint8_t *data, uint8_t len)
{
    uint8_t cnt_send = 0;
    uint8_t sending_failure = 0;

    if(len < 200)
    {
        for(cnt_send = 0; cnt_send < len; cnt_send++)
        {
            if(UARTCharPutNonBlocking(UART0_BASE, data[cnt_send]))
            {
                sending_failure = 0;
            }
            else
            {
                sending_failure = 1;
                break;
            }
        }
    }
    else
    {
        return 0;
    }

    if(!sending_failure)
        return 1;
    else
        return 0;
}

void halGetPcDataUart0()
{
    uint32_t uart_status = 0;
    static uint8_t cnt_rx = 0;
    uint16_t cnt_delete = 0;//, wait_next = 0;

    if(uart_status_.RxData.is_empty)
    {
        for(cnt_delete = 0;  cnt_delete < 256; cnt_delete++)    //delete received buffer
            uart_status_.RxData.Data[cnt_delete] = 0;

        cnt_rx = 0;
    }
    else
    {
        if(uart_status_.RxData.len < 201)       // start where buffer has end, because buffer has
            cnt_rx = uart_status_.RxData.len;   // not been read yet
    }

    // get uart flags, so interrupt source can be determined
    //
    uart_status = UARTIntStatus(UART0_BASE, UART_INT_RX);

    // clear interrupt flag, so after exiting the function,
    // function do not get called again
    //
    UARTIntClear(UART0_BASE, UART_INT_RX);

    if(uart_status & UART_INT_RX)   //Received an Interrupt?
    {
        while(UARTCharsAvail(UART0_BASE))
        {
            uart_status_.RxData.Data[cnt_rx++] = UARTCharGet(UART0_BASE);
            SysCtlDelay(100);
        }
        uart_status_.RxData.len = cnt_rx;
        uart_status_.Status.R = 1;
        uart_status_.RxData.is_empty = 0;
    }

}

/*
             if(((cnt_rx != 1) && (uart_status_.RxData.Data[cnt_rx-1] == 0x02)) || wait_next)    //new transmission
            {
                wait_next = 1;

                if((uart_status_.RxData.Data[cnt_rx-1] == CMD_GET_CHANNEL)  ||
                   (uart_status_.RxData.Data[cnt_rx-1] == CMD_GET_NODE)     ||
                   (uart_status_.RxData.Data[cnt_rx-1] == CMD_GET_FIRMWARE) ||
                   (uart_status_.RxData.Data[cnt_rx-1] == CMD_SEND_DATA)       )
                {
                    uart_status_.RxData.Data[0] = uart_status_.RxData.Data[cnt_rx-2];
                    uart_status_.RxData.Data[1] = uart_status_.RxData.Data[cnt_rx-1];

                    for(cnt_delete = cnt_rx-3; cnt_delete > 0; cnt_delete--)
                        uart_status_.RxData.Data[cnt_delete] = 0;
                    cnt_rx = 2;
                    wait_next = 0;
                }
            }
 */

