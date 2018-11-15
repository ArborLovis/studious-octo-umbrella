/*
 * hal_gpio.h
 *
 *  Created on: 13.03.2018
 *      Author: mayerflo
 */

#ifndef HAL_HAL_GPIO_H_
#define HAL_HAL_GPIO_H_

void HAL_GPIO_INIT(void);
void HAL_GPIO_PORTS(void);
void GPIOFIntHandler(void);
void GPIODIntHandler(void);
void GPIOCIntHandler(void);

extern short timer2cnt;

typedef struct {
    unsigned char active; //True 1 / False 0
    unsigned char button; //Button number
    unsigned int  RPM_ticks;
    unsigned int  Speed;
}ButtonCom;

// +++++++ PORT A ++++++++
#define UART0_RX        GPIO_PIN_0
#define UART0_TX        GPIO_PIN_1
#define LCD_BACKLIGHT   GPIO_PIN_2
#define LCD_A0          GPIO_PIN_3
#define LCD_RST         GPIO_PIN_4
#define US2_DRIVER_EN   GPIO_PIN_5
#define STEERING        GPIO_PIN_6
#define THROTTLE        GPIO_PIN_7

//++++++++++++++++++++++++
// +++++++ PORT B ++++++++

#define US1_SIGNAL_OUT  GPIO_PIN_0
#define US2_SIGNAL_OUT  GPIO_PIN_1
#define MOTION_I2C_SCL  GPIO_PIN_2
#define MOTION_I2C_SDA  GPIO_PIN_3
#define RADAR_SPI_SCLK  GPIO_PIN_4
#define RADAR_SPI_SYNC  GPIO_PIN_5
#define NC_1            GPIO_PIN_6
#define NC_0            GPIO_PIN_7

//++++++++++++++++++++++++
// +++++++ PORT C ++++++++

#define RPM_SENSOR      GPIO_PIN_7
#define RPM_SENSOR_DIR  GPIO_PIN_6
#define RF_TXD          GPIO_PIN_4
#define RF_RXD          GPIO_PIN_5

//++++++++++++++++++++++++
// +++++++ PORT D ++++++++

#define US1_DRIVER_EN   GPIO_PIN_0
#define RADAR_SPI_MOSI  GPIO_PIN_1
#define IR3_SENSE_OUT   GPIO_PIN_2
#define IR2_SENSE_OUT   GPIO_PIN_3

#define TRANSPONDER      GPIO_PIN_6
#define STOP_BUTTON      GPIO_PIN_7
//++++++++++++++++++++++++
// +++++++ PORT E ++++++++

#define VBAT_MEASURE    GPIO_PIN_0
#define IR1_SENSE_OUT   GPIO_PIN_1
#define RADAR_IF1       GPIO_PIN_2
#define RADAR_IF2       GPIO_PIN_3
#define US2_SIGNAL_IN   GPIO_PIN_4
#define US1_SIGNAL_IN   GPIO_PIN_5
#define REMOTE_CH1      GPIO_PIN_6
#define REMOTE_CH2      GPIO_PIN_7

//++++++++++++++++++++++++
// +++++++ PORT F ++++++++

#define LCD_SPI_MISO    GPIO_PIN_0
#define LCD_SPI_MOSI    GPIO_PIN_1
#define LCD_SPI_SCLK    GPIO_PIN_2
#define LCD_SPI_CS      GPIO_PIN_3
#define START_BUTTON    GPIO_PIN_4


#endif /* HAL_HAL_GPIO_H_ */
