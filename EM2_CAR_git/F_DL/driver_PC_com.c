/*
 * driver_PC_com.c
 *
 *  Created on: 14.11.2018
 *      Author: Patrick
 */

#include "tiva_headers.h"
#include "struct_def.h"
//DL
#include "driver_PC_com.h"
//HAL

void DRIVER_PC_COM_INIT();

extern COM_Status uart_status_;

void DRIVER_PC_COM_INIT()
{
    // init uart status, no data available
    // data and len is zero by default, because of global variable
    //
    uart_status_.RxData.is_empty = 1;
    uart_status_.TxData.in_progress = 0;
}

unsigned short Driver_sendDataPcUart0(unsigned short* data, unsigned short len)
{

    if(!UARTBusy(UART0_BASE))   //check, if uart FIFO is empty
    {
        if((len < 1024) && !uart_status_.TxData.in_progress)
        {
            int cnt = 0;
            for(; cnt < len; cnt++)
                uart_status_.TxData.Data[cnt] = data[cnt];

            uart_status_.TxData.len = len;
            uart_status_.TxData.cnt = 0;
            if(UARTCharPutNonBlocking(UART0_BASE, uart_status_.TxData.Data[uart_status_.TxData.cnt]))
            {
                if(++uart_status_.TxData.cnt == uart_status_.TxData.len)
                    uart_status_.TxData.in_progress = 0;
                else
                    uart_status_.TxData.in_progress = 1;
                return 1;
            }
            else
                return 0;
        }
        return 0;
    }
    return 0;
}

void DRIVER_UART0_ISR()
{
    uint32_t status_int = UARTIntStatus(UART0_BASE, 1); //return interrupt source masked

    if(status_int == UART_INT_TX)
    {
        UARTIntClear(UART0_BASE, UART_INT_TX);

        if(uart_status_.TxData.in_progress)
        {
            if(UARTCharPutNonBlocking(UART0_BASE, uart_status_.TxData.Data[uart_status_.TxData.cnt]))
            {
                if(++uart_status_.TxData.cnt != uart_status_.TxData.len){}
                else
                    uart_status_.TxData.in_progress = 0;
            }
        }
    }
    else if(status_int == UART_INT_RX)
    {
        UARTIntClear(UART0_BASE, UART_INT_RX);

    }
    else
    {
        //source not defined --> DEBUG
    }

}
