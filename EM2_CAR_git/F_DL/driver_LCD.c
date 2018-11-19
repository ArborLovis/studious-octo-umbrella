/*
 * driver_LCD.c
 *
 *  Created on: 07.11.2017
 *      Author: mayerflo
 */

#include "tiva_headers.h"
#include "struct_def.h"
#include "driver_LCD.h"
#include "driver_fonttable.h"
#include "hal_gpio.h"
#include "hal_ssi_lcd.h"

extern COM_Status LCD_Data;
unsigned char LCD_Pos_Array[];

void Driver_LCD_Init(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_BACKLIGHT, LCD_BACKLIGHT); //LCD Backlight ON
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_RST, ~LCD_RST); //Reset Line LOW
    SysCtlDelay(500000); //Wait for Display
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_RST, LCD_RST); //Reset Line HIGH
    SysCtlDelay(10000);
    unsigned char LCD_Init_Array[9] = {
              LCD_RESET,
              LCD_BIAS,
              ADC_SEL_NORMAL,
              COMMON_REVERSE,
              RES_RATIO,
              ELEC_VOL_MODE,
              ELEC_VOL_VALUE,
              POWER_CONT,
              DISPLAY_ON
    };

    //data_length //Wait for Display
    Driver_LCD_WriteCommand(LCD_Init_Array , sizeof(LCD_Init_Array));
    while(!LCD_Data.Status.B.TxSuc);
    SysCtlDelay(200000);


    Driver_LCD_Clear(); //lcd alle pixel löschen
    Driver_LCD_WriteText("Energy Mobility", 15, 1, 1);
    Driver_LCD_WriteUInt(2018, 2, 1);

}

void Driver_LCD_WriteCommand(unsigned char *data , unsigned char data_length)
{
    int i;
    while(LCD_Data.Status.B.TxSuc == 0);
    // switch to command mode
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_A0 ,0);

    LCD_Data.TxData.len = 0;

    for (i=0; i < data_length ;i++)
    {
        LCD_Data.TxData.Data[i] = *(data+i);
        LCD_Data.TxData.len ++;
    }

    HAL_SSI1_Transmit(LCD_Data.TxData.len); // send data
}

void Driver_LCD_SetPosition(unsigned char page_sel , unsigned char col_sel)
{
    unsigned char msb_col = (col_sel >> 4); //0001 xxxx
    unsigned char lsb_col = col_sel & 0x0F; // 0000 xxxx

    LCD_Pos_Array[0] = SET_PAGE + page_sel;
    LCD_Pos_Array[1] = MSB_COL_ADDR + msb_col;
    LCD_Pos_Array[2] = LSB_COL_ADDR + lsb_col;
    Driver_LCD_WriteCommand(LCD_Pos_Array , 3); //check

    while(LCD_Data.Status.B.TxSuc == 0);
}

void Driver_LCD_Clear(void)
{
    LCD_Pos_Array[0] = SET_PAGE;
    LCD_Pos_Array[1] = MSB_COL_ADDR;
    LCD_Pos_Array[2] = LSB_COL_ADDR;

    unsigned char i;
    unsigned char j;
    while(LCD_Data.Status.B.TxSuc == 0);

    for(j=0x00; (SET_PAGE+j) <= LAST_PAGE; j++ )
    {
        LCD_Pos_Array[0] = SET_PAGE+j;
        Driver_LCD_WriteCommand(LCD_Pos_Array , 3); //check
        while(LCD_Data.Status.B.TxSuc == 0);//Wait for Display
        GPIOPinWrite(GPIO_PORTA_BASE, LCD_A0 , LCD_A0);

        for(i=0; i< LCD_MAX_COLM; i++)
        {
            LCD_Data.TxData.Data[i] = 0x00;
        }

        LCD_Data.TxData.len = LCD_MAX_COLM;
        HAL_SSI1_Transmit(LCD_Data.TxData.len);
        while(LCD_Data.Status.B.TxSuc == 0);
    }
        Driver_LCD_SetPosition(3,100);
}

void Driver_LCD_WriteText(char *text , unsigned char text_length , unsigned char page , unsigned char col)
{
    unsigned char i;
    unsigned char text_length_cnt, col_pos = col;

    Driver_LCD_SetPosition(page ,col);
    while(LCD_Data.Status.B.TxSuc == 0);//Wait for Display
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_A0 , LCD_A0);
    for(text_length_cnt=0;text_length_cnt < text_length; text_length_cnt++) //for string
    {
        for(i=0; i < fonts_width_max; i++) //for character
        {
            LCD_Data.TxData.Data[i] = font_table[*text][i];
            col_pos++;
        }
        LCD_Data.TxData.len = fonts_width_max;
        HAL_SSI1_Transmit(LCD_Data.TxData.len);
        while(LCD_Data.Status.B.TxSuc == 0);
        if((col_pos+fonts_width_max) >= LCD_MAX_COLM)
        {
            Driver_LCD_SetPosition(++page ,0);
            while(LCD_Data.Status.B.TxSuc == 0);//Wait for Display
            GPIOPinWrite(GPIO_PORTA_BASE, LCD_A0 , LCD_A0);
            col_pos=0;
        }
        text++;
    }
}

// Writes an unsigned integer to the display
// number: the number which gets displayed
// row: the page number (row) in where the text should be displayed
// col: the column where the text starts
void Driver_LCD_WriteUInt(unsigned int number, int page, int col)
{
    int stringSpace = 7;
    char text[7] = {0};
    int d[7] = {0};              //array to store the string (uint32_t max. 10 chars + end of string)
    //int len = UIntToString(number, text);             //convert number to string

    int i,m;

    i = 0;
    while(number > 0)
    {
        d[i] = number % 10 + '0';
        number = number / 10;
        i++;
    }
    // Reverse Result
    for(m = 0; m < stringSpace; m++)
    {
        text[stringSpace-1-m] = d[m];
    }

    //text[i] = '\0';

    Driver_LCD_WriteText(text, stringSpace, page, col); //write converted number as string to display
}

int UIntToString(int n, char s[])
{
    int i,m;

    i = 0;
    while(n > 0)
    {
        s[i] = n % 10 + '0';
        n = n / 10;
        i++;
    }
    char d[i];
    // Reverse Result
    for(m = i; m < 0; m--)
    {
        d[i-m] = s[m];
    }
    s = d;
    s[i] = '\0';

    return i;
}
