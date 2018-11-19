/*
 * hal_gpio.c
 *
 *  Created on: 13.03.2018
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "hal_gpio.h"

extern ButtonCom ButtonSwitch;

void HAL_GPIO_INIT(void)
{
    HAL_GPIO_PORTS(); //activate PORTS

    //Set all Pins on each Ports as Output
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0xFF); //PORT A
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF); //PORT B
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, 0xFF); //PORT C
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0xFF); //PORT D
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, 0xFF); //PORT E
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0xFF); //PORT F

    // PORT A
    //+++++++++++++++++++++++++++++
    // Hardware
    GPIOPinConfigure(GPIO_PA6_M1PWM2);
    GPIOPinConfigure(GPIO_PA7_M1PWM3);
    // PWM Mode
    GPIOPinTypePWM(GPIO_PORTA_BASE,THROTTLE);
    GPIOPinTypePWM(GPIO_PORTA_BASE,STEERING);
    // SSI or SPI (for LCD Display)
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_BACKLIGHT);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_A0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_RST);
    //UART0
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, UART0_TX);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, UART0_RX);

    // PORT B
    //+++++++++++++++++++++++++++++
    // Outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, RADAR_SPI_MOSI | RADAR_SPI_SCLK | RADAR_SPI_SYNC);
    GPIOPinWrite(GPIO_PORTB_BASE, RADAR_SPI_MOSI | RADAR_SPI_SCLK | RADAR_SPI_SYNC, 0);

    // Inputs
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, RADAR_SPI_MISO);


    // PORT C
    //+++++++++++++++++++++++++++++
    // Inputs
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, RPM_SENSOR | RPM_SENSOR_DIR);
    // Hardware
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPadConfigSet(GPIO_PORTC_BASE, RPM_SENSOR,
                    GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //UART
    GPIOPinTypeUART(GPIO_PORTC_BASE, UART_RXD_COM | UART_TXD_COM);

    //Interrupt Port C
    GPIOIntDisable(GPIO_PORTC_BASE, RPM_SENSOR);
    GPIOIntClear(GPIO_PORTC_BASE, RPM_SENSOR);
    GPIOIntRegister(GPIO_PORTC_BASE, GPIOCIntHandler);
    GPIOIntTypeSet(GPIO_PORTC_BASE, RPM_SENSOR, GPIO_RISING_EDGE);
    GPIOIntEnable(GPIO_PORTC_BASE, RPM_SENSOR);

    // PORT D
    //+++++++++++++++++++++++++++++
    // Inputs
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, DISTANCE_LEFT | DISTANCE_RIGHT | STOP_BUTTON);
    GPIOPadConfigSet(GPIO_PORTD_BASE, STOP_BUTTON,
                GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //Interrupt PORT D
    GPIOIntDisable(GPIO_PORTD_BASE, STOP_BUTTON);
    GPIOIntClear(GPIO_PORTD_BASE, STOP_BUTTON);
    GPIOIntRegister(GPIO_PORTD_BASE, GPIODIntHandler);
    GPIOIntTypeSet(GPIO_PORTD_BASE, STOP_BUTTON, GPIO_RISING_EDGE);
    GPIOIntEnable(GPIO_PORTD_BASE, STOP_BUTTON);

    // PORT E
    //+++++++++++++++++++++++++++++
    // Inputs
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, DISTANCE_FRONT | VBAT_MEASURE | RADAR_IF1 | RADAR_IF2);
    // Hardware
    GPIOPinConfigure(GPIO_PE4_M0PWM4);
    GPIOPinConfigure(GPIO_PE5_M0PWM5);
    // PWM Mode
    //GPIOPinTypePWM(GPIO_PORTE_BASE,US2_SIGNAL_IN);
    GPIOPinTypePWM(GPIO_PORTE_BASE, SONIC_FREQ_IN);

    // PORT F
    //+++++++++++++++++++++++++++++
    // Inputs
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, START_BUTTON);
    GPIOPadConfigSet(GPIO_PORTF_BASE, START_BUTTON,
                GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //Interrupt PORT F
    GPIOIntDisable(GPIO_PORTF_BASE, START_BUTTON);
    GPIOIntClear(GPIO_PORTF_BASE, START_BUTTON);
    GPIOIntRegister(GPIO_PORTF_BASE, GPIOFIntHandler);
    GPIOIntTypeSet(GPIO_PORTF_BASE, START_BUTTON, GPIO_RISING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, START_BUTTON);

    //Outputs
    // Hardware
    GPIOPinConfigure(GPIO_PF0_SSI1RX);
    GPIOPinConfigure(GPIO_PF1_SSI1TX);
    GPIOPinConfigure(GPIO_PF2_SSI1CLK);
    GPIOPinConfigure(GPIO_PF3_SSI1FSS);

    GPIOPinTypeSSI(GPIO_PORTF_BASE, (LCD_SPI_MISO | LCD_SPI_MOSI | LCD_SPI_SCLK | LCD_SPI_CS));

}

void HAL_GPIO_PORTS(void)
{
    // FIRST WE ENABLE ALL PORTS AND WAIT FOR THEIR INITIALIZATION
    // +++++++++++++++++++++++++++++
    // PORTA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)); // Wait for Port to be ready

    // +++++++++++++++++++++++++++++
    // PORTB
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)); // Wait for Port to be ready

    // +++++++++++++++++++++++++++++
    // PORTC

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)); // Wait for Port to be ready

    // +++++++++++++++++++++++++++++
    // PORTD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)); // Wait for Port to be ready

    // +++++++++++++++++++++++++++++
    // PORTE
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)); // Wait for Port to be ready

    // +++++++++++++++++++++++++++++
    // PORTF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Wait for Port to be ready
}

void GPIOFIntHandler(void)
{
    switch(GPIOIntStatus(GPIO_PORTF_BASE,true))
    {
        case START_BUTTON:  // Start button
           ButtonSwitch.active = 1;
           ButtonSwitch.button = START_BUTTON;
           GPIOIntClear(GPIO_PORTF_BASE, START_BUTTON);
        break;

        default:
            GPIOIntClear(GPIO_PORTF_BASE, 0xFF);
        break;
    }
}

void GPIODIntHandler(void)
{
    switch(GPIOIntStatus(GPIO_PORTD_BASE,true))
    {
        case STOP_BUTTON:  // Start button
           ButtonSwitch.active = 2;
           ButtonSwitch.button = STOP_BUTTON;
           GPIOIntClear(GPIO_PORTD_BASE, STOP_BUTTON);
        break;

        default:
            GPIOIntClear(GPIO_PORTD_BASE, 0xFF);
        break;
    }

}

void GPIOCIntHandler(void)
{
    switch(GPIOIntStatus(GPIO_PORTC_BASE,true))
    {
        case RPM_SENSOR:  // Start button
           ButtonSwitch.RPM_ticks++;
           GPIOIntClear(GPIO_PORTC_BASE, STOP_BUTTON);
        break;

        default:
            GPIOIntClear(GPIO_PORTC_BASE, 0xFF);
        break;
    }

}
