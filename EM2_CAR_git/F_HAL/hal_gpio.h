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
#define AUX_3           GPIO_PIN_5  //US2_DRIVER_EN
#define STEERING        GPIO_PIN_6
#define THROTTLE        GPIO_PIN_7

//++++++++++++++++++++++++
// +++++++ PORT B ++++++++

#define SONIC_FREQ_IN   GPIO_PIN_0  //US1_SIGNAL_OUT
#define MOTION_I2C_INT  GPIO_PIN_1  //US2_SIGNAL_OUT
#define MOTION_I2C_SCL  GPIO_PIN_2
#define MOTION_I2C_SDA  GPIO_PIN_3
#define RADAR_SPI_SCLK  GPIO_PIN_4
#define RADAR_SPI_SYNC  GPIO_PIN_5
#define RADAR_SPI_MISO  GPIO_PIN_6  //NC_1
#define RADAR_SPI_MOSI  GPIO_PIN_7  //NC_0

//++++++++++++++++++++++++
// +++++++ PORT C ++++++++

#define RPM_SENSOR      GPIO_PIN_7
#define RPM_SENSOR_DIR  GPIO_PIN_6
#define UART_TXD_COM    GPIO_PIN_5
#define UART_RXD_COM    GPIO_PIN_4
#define DEBUG_PC3       GPIO_PIN_3
#define DEBUG_PC2       GPIO_PIN_2
#define DEBUG_PC1       GPIO_PIN_1
#define DEBUG_PC0       GPIO_PIN_0

//++++++++++++++++++++++++
// +++++++ PORT D ++++++++

#define TX_ENABLE       GPIO_PIN_0
#define AUX_1           GPIO_PIN_1
#define DISTANCE_LEFT   GPIO_PIN_2
#define DISTANCE_RIGHT  GPIO_PIN_3
#define UART_RXD_AUX    GPIO_PIN_4
#define UART_TXD_AUX    GPIO_PIN_5
#define TRANSPONDER     GPIO_PIN_6
#define STOP_BUTTON     GPIO_PIN_7

//++++++++++++++++++++++++
// +++++++ PORT E ++++++++

#define VBAT_MEASURE    GPIO_PIN_0
#define DISTANCE_FRONT  GPIO_PIN_1
#define RADAR_IF1       GPIO_PIN_2
#define RADAR_IF2       GPIO_PIN_3
#define AUX_2           GPIO_PIN_4
#define SONIC_FREQ_OUT  GPIO_PIN_5

//++++++++++++++++++++++++
// +++++++ PORT F ++++++++

#define LCD_SPI_MISO    GPIO_PIN_0
#define LCD_SPI_MOSI    GPIO_PIN_1
#define LCD_SPI_SCLK    GPIO_PIN_2
#define LCD_SPI_CS      GPIO_PIN_3
#define START_BUTTON    GPIO_PIN_4


#endif /* HAL_HAL_GPIO_H_ */
