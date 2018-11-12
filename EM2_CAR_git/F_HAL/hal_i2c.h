/*
 * hal_i2c.h
 *
 *  Created on: 11.11.2018
 *      Author: mayerflo
 */

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_

void InitI2C0(void);
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, char vars[]);
uint8_t I2CReceive(uint8_t slave_addr, uint8_t reg);
void I2CSendString(uint8_t slave_addr, char array[]);

#endif /* HAL_HAL_I2C_H_ */
