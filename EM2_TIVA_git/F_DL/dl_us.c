/*
 * dl_us.c
 *
 *  Created on: 13.06.2018
 *      Author: Patrick
 */

#include "dl_us.h"
#include "dl_general.h"
#include "hal_timer2.h"
#include "hal_us.h"

extern volatile Sensor sensor_data_;

unsigned int calc_distance_us(unsigned int sonic_time_us);

unsigned int dlGetDistance_US1()
{
    if(sensor_data_.Sonic.us1_data_ready)
    {
        sensor_data_.Sonic.distance_us1 = calc_distance_us(sensor_data_.Sonic.timer_cnt_us1);
        sensor_data_.Sonic.timer_cnt_us1 = 0;
        sensor_data_.Sonic.us1_data_ready = false;
        return sensor_data_.Sonic.distance_us1;
    }
    else
        return 0;
}

unsigned int dlGetDistance_US2()
{
    if(sensor_data_.Sonic.us2_data_ready)
    {
        sensor_data_.Sonic.distance_us2 = calc_distance_us(sensor_data_.Sonic.timer_cnt_us2);
        sensor_data_.Sonic.timer_cnt_us2 = 0;
        sensor_data_.Sonic.us2_data_ready = false;
        return sensor_data_.Sonic.distance_us2;
    }
    else
        return 0;
}

unsigned int calc_distance_us(unsigned int sonic_time_us)
{
    return (unsigned int)((double)HALF_VEL_SONIC * ((double)sonic_time_us / 1000000.0));
}
