
#include "tiva_headers.h"
//#include "al_general.h"
#include "hal_gpio.h"

#include "struct_def.h"
#include "driver_general.h"
#include "driver_LCD.h"
#include "mpu9250.h"
#include "driver_aktorik.h"
#include "driver_PC_com.h"
#include "radix2_fft.h"
#include "hal_general.h"
#include "hal_uart0.h"
#include "hal_adc.h"


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

extern RADAR_BUFFER_ADC radar_data_;
extern COM_Status uart_status_;

void main()
{

    HAL_INIT();
    driver_INIT();
    ButtonSwitch.RPM_ticks = 0;
    ButtonSwitch.Speed = 0;

    uint32_t current_clock = SysCtlClockGet(); //check the system clock
    short steer = 0;
    short ESCspeed = 0;

    uint8_t IQ_TX_State = 0;

    while(1)
    {
        //Driver_setSteering(steer);
        //Driver_setThrottle(ESCspeed);
        //Driver_LCD_WriteUInt(ButtonSwitch.Speed, 2, 50);
        //getAccelData();
        //getgyroData();
        //getMagnetoData();

        if(radar_data_.data_release_)
        {
            fft_radix2_var(radar_data_.radar_buffer_i_, radar_data_.radar_buffer_q_, 512);

            radar_data_.data_release_ = 0;

            int i = 0;
            for(i = 0; i<RADAR_BUFFER_SIZE; i++)
            {
                if(i > 0)   //filter dc value
                    radar_data_.radar_pwr_[i] = radar_data_.radar_buffer_i_[i]*radar_data_.radar_buffer_i_[i] + radar_data_.radar_buffer_q_[i]*radar_data_.radar_buffer_q_[i];
                else
                    radar_data_.radar_pwr_[i] = 0;
            }

            i = 0;
            SysCtlDelay(100000);
        }
    }

}

