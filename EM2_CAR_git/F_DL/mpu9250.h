/*
 * mpu9250.h
 *
 *  Created on: 11.11.2018
 *      Author: mayerflo
 */

#ifndef DL_MPU9250_H_
#define DL_MPU9250_H_

void InitMPU9250(void);
void InitMagno(void);
short ReadAccel(uint8_t reg);

void getAccelData(void);
void getgyroData(void);
void getMagnetoData(void);

#endif /* DL_MPU9250_H_ */
