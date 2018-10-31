/*
 * hal_adc.c
 *
 *  Created on: 06.06.2018
 *      Author: Patrick
 *  ADC - Tutorial: https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials/tiva-adc/internal-temperature-sensor (Stand: 10.06.2018)
 */

#include "hal_adc.h"
#include "tiva_headers.h"
#include "hal_gpio.h"
#include "dl_general.h"



void ADC1ISR();

#pragma DATA_ALIGN(DMAcontroltable, 1024)
uint8_t DMAcontroltable[1024];

//uint8_t DMAcontroltable[1024] __attribute__ ((aligned(1024)));


extern Sensor sensor_data_;
uint8_t adc_finished_ = 1;

uint16_t buffer[16] = {0};

RADAR_BUFFER_ADC radar_data_;

//Note: ADC0 and ADC1 share the same AIN - Pins!

void halAdc0Init(bool enable_hw_avg)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(10);    //program get stuck in while, so a little delay is applied (for now - just a try)
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)); //wait for ADC0 to be ready

    //enable Pins for ADC-module
    //
    GPIOPinTypeADC(GPIO_PORTE_BASE, VBAT_MEASURE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, IR1_SENSE_OUT);
    GPIOPinTypeADC(GPIO_PORTD_BASE, IR2_SENSE_OUT);
    GPIOPinTypeADC(GPIO_PORTD_BASE, IR3_SENSE_OUT);

    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);    //internal ref. voltage - 3V

    //ADC Setup
    //ADC0 module; Sequence 1: 4 Samples; Software triggered; highest priority
    //
    ADCSequenceDisable(ADC0_BASE, ADC_SS1);
    ADCSequenceConfigure(ADC0_BASE, ADC_SS1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_0, ADC_CTL_CH2);         //IR - sensors 0-2
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_1, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_2, ADC_CTL_CH5);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_3, ADC_CTL_CH3 | ADC_CTL_END);   //Battery

    if(enable_hw_avg)
    {
        ADCHardwareOversampleConfigure(ADC0_BASE, 8);   //average 8 samples automatically; slow down throughput
    }

    ADCSequenceEnable(ADC0_BASE, ADC_SS1);
    ADCIntClear(ADC0_BASE, ADC_SS1);
}

//for radar module
void halAdc1Init(bool enable_hw_avg)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1));

    //enable Pins for ADC-module
    //
    GPIOPinTypeADC(GPIO_PORTE_BASE, RADAR_IF1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, RADAR_IF2);

    ADCReferenceSet(ADC1_BASE, ADC_REF_INT);    //internal ref. voltage - 3V

    //ADC Setup
    //ADC1 module; Sequence 1: 4 Samples per sequence; Software triggered; highest priority
    //
    ADCSequenceDisable(ADC1_BASE, ADC_SS1);
    ADCSequenceConfigure(ADC1_BASE, ADC_SS1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, ADC_SS1, ADC_SAMPLE_ORDER_0, ADC_CTL_CH1);                  //PE2 --> IF1    radar
    ADCSequenceStepConfigure(ADC1_BASE, ADC_SS1, ADC_SAMPLE_ORDER_1, ADC_CTL_CH0 | ADC_CTL_END);    //PE3 --> IF2    radar

/*
    //DMA configuration
    ADCSequenceDMAEnable(ADC1_BASE, ADC_SS1);   //DMA FIFO length: 4

    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    SysCtlDelay(10);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA));

    uDMAControlBaseSet(DMAcontroltable);
    uDMAChannelAssign(UDMA_CH24_ADC1_1);       //select channel, which is connected to the uDMA
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC1, UDMA_ATTR_USEBURST | UDMA_ATTR_HIGH_PRIORITY);
    uDMAChannelControlSet(UDMA_CHANNEL_ADC1 | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 |
                           UDMA_DST_INC_16 | UDMA_ARB_16);

    uDMAChannelTransferSet(UDMA_CHANNEL_ADC1 | UDMA_PRI_SELECT, UDMA_MODE_BASIC, (void*)(ADC1_BASE | ADC_SSFIFO0_DATA_M),
                           buffer, 2);

    uDMAChannelEnable(UDMA_CHANNEL_ADC1);       //will be disabled after data transfer has finished
    uDMAEnable();
*/

    if(enable_hw_avg)
    {
        ADCHardwareOversampleConfigure(ADC1_BASE, 8);   //average 8 samples automatically; slow down throughput
    }

    ADCSequenceEnable(ADC1_BASE, ADC_SS1);
    ADCIntClear(ADC1_BASE, ADC_SS1);
    //ADCIntRegister(ADC1_BASE, ADC_SS1, ADC1ISR);
    //ADCIntEnable(ADC1_BASE, ADC_SS1);

    radar_data_.data_release_ = 0;
    radar_data_.fft_done_ = 0;
    radar_data_.dead_samples_ = 20;

    int i = 0;
    for(i=0; i<256; i++)
    {
        radar_data_.radar_buffer_i_[i] = 0;
        radar_data_.radar_buffer_i_[i] = 0;
    }

}

void ADC1ISR()
{
    adc_finished_ = 0;

    ADCIntClear(ADC1_BASE, ADC_SS1);
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC1 | UDMA_PRI_SELECT, UDMA_MODE_BASIC, (void*)(ADC1_BASE | ADC_SSFIFO0_DATA_M),
                           buffer, 2);

    uDMAChannelEnable(UDMA_CHANNEL_ADC1);       //will be disabled after data transfer has finished
    adc_finished_ = 1;
}

void halGetAdcSamples()
{
    ADCProcessorTrigger(ADC0_BASE, ADC_SS1);
    //while(ADC0_ACTSS_R & ADC_ACTSS_BUSY); //wait until adc has finished;
    while(ADCBusy(ADC0_BASE));  //wait until conversion finished
    ADCIntClear(ADC0_BASE, ADC_SS1);
    ADCSequenceDataGet(ADC0_BASE, ADC_SS1, sensor_data_.adc_values);
}

void halRadarSamplesIQ()
{
    static int cnt = 0;
    uint32_t radar_adc[2] = {0};
    static uint32_t radar_buffer[2][256] = {{0}, {0}};

    ADCProcessorTrigger(ADC1_BASE, ADC_SS1);
    while(ADCBusy(ADC1_BASE));  //wait until conversion finished

    ADCIntClear(ADC1_BASE, ADC_SS1);
    ADCSequenceDataGet(ADC1_BASE, ADC_SS1, radar_adc);

    if(cnt < 255)
    {
        radar_buffer[0][cnt] = radar_adc[0];
        radar_buffer[1][cnt] = radar_adc[1];
        cnt++;
    }
    else
        cnt = 0;

    if(cnt == 0)
    {
        int i = 0;
        for(i=0; i<256; i++)
        {
            if(i <= radar_data_.dead_samples_)
            {
                radar_data_.radar_buffer_i_[i] = 0;
                radar_data_.radar_buffer_q_[i] = 0;
            }
            else
            {
                radar_data_.radar_buffer_i_[i] = (float)radar_buffer[0][i];
                radar_data_.radar_buffer_q_[i] = (float)radar_buffer[1][i];
            }
        }
        radar_data_.data_release_ = 1;
    }
}

void startADC1()
{
    ADCProcessorTrigger(ADC1_BASE, ADC_SS1);
}
