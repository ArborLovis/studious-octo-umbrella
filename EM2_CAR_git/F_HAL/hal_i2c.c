/*
 * hal_i2c.c
 *
 *  Created on: 11.11.2018
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "hal_i2c.h"

//initialize I2C module 0
//Slightly modified version of TI's example code
void InitI2C0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);                         // enable I2C module 0
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0)){};

    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);                          // reset the module

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){};

    GPIOPinConfigure(GPIO_PB2_I2C0SCL);                                 // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);                     // Select the I2C function for these pins.
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);             // 400kbps

    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;                        //clear I2C FIFOs
}

// I2CSend
// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ sends an I2C command to the specified slave +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, char vars[])
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, vars[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);  //Initiate send of data from the MCU
        while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
        while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        int i = 1;
        while(i < (num_of_args - 1))
        {
            I2CMasterDataPut(I2C0_BASE, vars[i]); //put next piece of data into I2C FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); //send next data that was just placed into FIFO
            while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.
            i++;
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, vars[i]); //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Wait until MCU is done transferring.

        while(I2CMasterBusy(I2C0_BASE));

    }
}


// I2CSendString
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ sends an array of data via I2C to the specified slave +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void I2CSendString(uint8_t slave_addr, char array[])
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
    I2CMasterDataPut(I2C0_BASE, array[0]); //put data to be sent into FIFO

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == '\0')
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND); //Initiate send of data from the MCU
        while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START); //Initiate send of data from the MCU
        while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.

        uint8_t i = 1; //initialize index into array

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != '\0')
        {
            I2CMasterDataPut(I2C0_BASE, array[i++]); //put next piece of data into I2C FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); //send next data that was just placed into FIFO
            while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.
        }

        I2CMasterDataPut(I2C0_BASE, array[i]); //put last piece of data into I2C FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); //send next data that was just placed into FIFO
        while(I2CMasterBusy(I2C0_BASE)); // Wait until MCU is done transferring.
    }
}

uint8_t I2CReceive(uint8_t slave_addr, uint8_t reg)
{
    while(I2CMasterBusy(I2C0_BASE));
    //specify that we are writing (a register address) to the
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false); //slave device
    I2CMasterDataPut(I2C0_BASE, reg); //specify register to be read

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START); //send control byte and register address byte to slave device
    while(I2CMasterBusy(I2C0_BASE)); //wait for MCU to finish transaction

    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, true); //specify that we are going to read from slave device

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(I2C0_BASE)); //wait for MCU to finish transaction

    return I2CMasterDataGet(I2C0_BASE); //return data pulled from the specified register
}
