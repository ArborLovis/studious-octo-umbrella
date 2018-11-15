
#include "tiva_headers.h"
//#include "al_general.h"
#include "hal_gpio.h"

#include "driver_general.h"
#include "driver_LCD.h"
#include "mpu9250.h"
#include "driver_aktorik.h"
#include "driver_PC_com.h"
#include "hal_general.h"
#include "hal_uart0.h"

#include <math.h>
#include <complex.h>

#define M_PI 3.14159265358979323846

/**
 * main.c
 */
extern ButtonCom ButtonSwitch;

extern float accel_x,accel_y,accel_z, gyro_x,gyro_y,gyro_z, magno_x,magno_y,magno_z;
extern int16_t accel_x_16,accel_y_16,accel_z_16,gyro_x_16,gyro_y_16,gyro_z_16, magno_x_16,magno_y_16,magno_z_16;
extern uint8_t accData[6], gyroData[6], magnetoData[6];
extern uint8_t magRawASA[3], magRawDest[3];

void main()
{

    HAL_INIT();
    driver_INIT();
    ButtonSwitch.RPM_ticks = 0;
    ButtonSwitch.Speed = 0;

    uint32_t current_clock = SysCtlClockGet(); //check the system clock
    short steer = 0;
    short ESCspeed = 0;
    static uint16_t send_buffer[128] = {0};
    uint32_t delay = 0;
    uint8_t check_transmit = 0;

    int i = 0;
    for(; i < 128; i++)
        send_buffer[i] = i;

    i = 0;
    while(1)
    {
        //Driver_setSteering(steer);
        //Driver_setThrottle(ESCspeed);
        //Driver_LCD_WriteUInt(ButtonSwitch.Speed, 2, 50);
        //getAccelData();
        //getgyroData();
        //getMagnetoData();

        if(++delay >= 2000)
        {
            delay = 0;
            /*
            UARTCharPutNonBlocking(UART0_BASE, send_buffer[i++]);
            UARTCharPutNonBlocking(UART0_BASE, send_buffer[i++]);
            UARTCharPutNonBlocking(UART0_BASE, send_buffer[i++]);
            UARTCharPutNonBlocking(UART0_BASE, send_buffer[i++]);

            if(i >= 124)
                i = 0;
            */

            if(Driver_sendDataPcUart0(send_buffer, 128))
            {
                check_transmit = 5;
            }

        }

    }

}

