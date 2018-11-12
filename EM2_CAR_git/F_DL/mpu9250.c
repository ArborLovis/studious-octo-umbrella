/*
 * mpu9250.c
 *
 *  Created on: 11.11.2018
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "mpu9250.h"
#include "motion_reg_addr.h"

#include "hal_i2c.h"

float accel_x,accel_y,accel_z, gyro_x,gyro_y,gyro_z, magno_x,magno_y,magno_z;
int16_t accel_x_16,accel_y_16,accel_z_16,gyro_x_16,gyro_y_16,gyro_z_16, magno_x_16,magno_y_16,magno_z_16;
uint8_t accData[6], gyroData[6], magnetoData[6];
uint8_t magRawASA[3], magRawDest[3];

void getAccelData(void)
{
    int argCnt;
    float resolution = 8.0 / 65536.0;
    for(argCnt = 0; argCnt < sizeof(Accel_reg_addr); argCnt++)
    {
        accData[argCnt] =  I2CReceive(ACCELGYRO_ADDR, Accel_reg_addr[argCnt]);
    }
    accel_x_16 = (accData[0] << 8) | accData[1];
    accel_y_16 = (accData[2] << 8) | accData[3];
    accel_z_16 = (accData[4] << 8) | accData[5];

    //Now we have to recalculate @±4G with
    accel_x = (float)accel_x_16 * resolution;
    accel_y = (float)accel_y_16 * resolution;
    accel_z = (float)accel_z_16 * resolution;
}

void getgyroData(void)
{
    int argCnt;
    float resolution = 1000.0 / 65536.0;
    for(argCnt = 0; argCnt < sizeof(gyro_reg_addr); argCnt++)
    {
        gyroData[argCnt] =  I2CReceive(ACCELGYRO_ADDR, gyro_reg_addr[argCnt]);
    }
    gyro_x_16 = (gyroData[0] << 8) | gyroData[1];
    gyro_y_16 = (gyroData[2] << 8) | gyroData[3];
    gyro_z_16 = (gyroData[4] << 8) | gyroData[5];

    //Now we have to recalculate @+1000dps with
    gyro_x = (float)gyro_x_16 * resolution;
    gyro_y = (float)gyro_y_16 * resolution;
    gyro_z = (float)gyro_z_16 * resolution;
}

void getMagnetoData(void)
{
    int argCnt;
    float resolution = 1;
    for(argCnt = 0; argCnt < sizeof(magn_reg_addr); argCnt++)
    {
        magnetoData[argCnt] =  I2CReceive(MAG_ADDR, magn_reg_addr[argCnt]);
    }
    magno_x_16 = (magnetoData[0] << 8) | magnetoData[1];
    magno_y_16 = (magnetoData[2] << 8) | magnetoData[3];
    magno_z_16 = (magnetoData[4] << 8) | magnetoData[5];

    //
    magno_x = (float)magno_x_16 * resolution;
    magno_y = (float)magno_y_16 * resolution;
    magno_z = (float)magno_z_16 * resolution;
}

void InitMPU9250(void)
{
    //init over I2C
    I2CSend(ACCELGYRO_ADDR, sizeof(MPU_rst), MPU_rst);
    SysCtlDelay(10000); // wait for RESET*/

    // Setting the MPU9250
    int sets = sizeof(Acc_init_reg)/2;
    int cnt;
    char setInit[2];
    // Set ACCL and other MPU settings
    for (cnt = 0; cnt<sets; cnt = cnt + 2)
    {
        setInit[0] = Acc_init_reg[cnt]; setInit[1] = Acc_init_reg[cnt+1];
        I2CSend(ACCELGYRO_ADDR, sizeof(setInit), setInit);
        SysCtlDelay(50);
    }
    // SET GYRO
    sets = sizeof(gyro_init_reg)/2;
    for (cnt = 0; cnt<sets; cnt = cnt + 2)
    {
        setInit[0] = gyro_init_reg[cnt]; setInit[1] = gyro_init_reg[cnt+1];
        I2CSend(ACCELGYRO_ADDR, sizeof(setInit), setInit);
        SysCtlDelay(50);
    }
}

void InitMagno(void)
{
    I2CSend(MAG_ADDR, sizeof(magn_pwrDown), magn_pwrDown);
    SysCtlDelay(100000); // wait for RESET*/

    I2CSend(MAG_ADDR, sizeof(magneto_fuse_rom), magneto_fuse_rom);
    SysCtlDelay(100000); // wait for RESET*/

    int argCnt;
    for(argCnt = 0; argCnt < sizeof(magn_reg_addr); argCnt++)
        {
            magRawASA[argCnt] =  I2CReceive(MAG_ADDR, magno_getASA[argCnt]);
        }
    magRawDest[0] =  (float)(magRawASA[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
    magRawDest[1] =  (float)(magRawASA[1] - 128)/256. + 1.;
    magRawDest[2] =  (float)(magRawASA[2] - 128)/256. + 1.;

    I2CSend(MAG_ADDR, sizeof(magn_pwrDown), magn_pwrDown);
    SysCtlDelay(100000); // wait for RESET*/
    I2CSend(MAG_ADDR, sizeof(magneto_requMeas), magneto_requMeas);
}
