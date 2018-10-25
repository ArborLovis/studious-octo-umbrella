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

extern Sensor sensor_data_;

//Note: ADC0 and ADC1 share the same AIN - Pins!

void halAdcInit(bool enable_hw_avg)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(10);    //program get stuck in while, so a little delay is applied (for now - just a try)
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)); //wait for ADC0 to be ready

    //enable Pins for ADC-module
    //
    GPIOPinTypeADC(GPIO_PORTE_BASE, VBAT_MEASURE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, RADAR_IF1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, RADAR_IF2);
    GPIOPinTypeADC(GPIO_PORTE_BASE, IR1_SENSE_OUT);
    GPIOPinTypeADC(GPIO_PORTD_BASE, IR2_SENSE_OUT);
    GPIOPinTypeADC(GPIO_PORTD_BASE, IR3_SENSE_OUT);

    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);    //internal ref. voltage - 3V

    //ADC Setup
    //ADC0 module; Sequence 1: 4 Samples; Software triggered; highest priority
    //
    ADCSequenceDisable(ADC0_BASE, ADC_SS1);
    ADCSequenceConfigure(ADC0_BASE, ADC_SS1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_0, ADC_CTL_CH2);         //Sensors 0-2
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_1, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_2, ADC_CTL_CH5);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SS1, ADC_SAMPLE_ORDER_3, ADC_CTL_CH3 | ADC_CTL_END);   //Battery

    if(enable_hw_avg)
    {
        ADCHardwareOversampleConfigure(ADC0_BASE, 8);   //average 8 samples automatical; slow down throughput
    }

    ADCSequenceEnable(ADC0_BASE, ADC_SS1);
    ADCIntClear(ADC0_BASE, ADC_SS1);
}

void halGetAdcSamples()
{
    ADCProcessorTrigger(ADC0_BASE, ADC_SS1);
    //while(ADC0_ACTSS_R & ADC_ACTSS_BUSY); //wait until adc has finished;
    while(ADCBusy(ADC0_BASE));  //wait until conversion finished
    ADCIntClear(ADC0_BASE, ADC_SS1);
    ADCSequenceDataGet(ADC0_BASE, ADC_SS1, sensor_data_.adc_values);
}
