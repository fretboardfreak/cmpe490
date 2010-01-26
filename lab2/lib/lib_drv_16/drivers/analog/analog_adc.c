//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : analog_adc.c
//* Object              : ADC driver in polling management
//*
//* 1.0 31/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "analog.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_open_adc
//* Object              : Open the adc
//* Input Parameters    : <Descriptor> Analog descriptor ,ADC mode
//*                       <adc_mode> for resolution and Presacler
//* Output Parameters   : none
//*----------------------------------------------------------------------------
 void at91_analog_open_adc( AnalogDescAdc *Analog_pt,u_int adc_mode)
//* Begin
{
    //* -- Open ADC
    at91_adc_open(Analog_pt->adc_desc,adc_mode);
    //* -- Configure Channel
    at91_adc_channel_open(Analog_pt->adc_desc, Analog_pt->channel);

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_close_adc
//* Object              : Close the adc
//* Input Parameters    : <Descriptor> Analog descriptor
//*                     : Timer descriptor , compter value , mcki divisor
//* Output Parameters   : True
//*----------------------------------------------------------------------------
void at91_analog_close_adc( AnalogDescAdc *Analog_pt)
//* Begin
{
    //* -- Close ADC
        at91_adc_close(Analog_pt->adc_desc);

    //* -- close analog Channel
       at91_adc_channel_close(Analog_pt->adc_desc, Analog_pt->channel);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_read_adc
//* Object              : Read adc value
//* Input Parameters    : <Descriptor> Analog descriptor
//*                       <channel>  adc channel number 0 to 3
//* Output Parameters   : read value
//*----------------------------------------------------------------------------
u_short at91_analog_read_adc(AnalogDescAdc *Analog_pt,u_int channel)
//* Begin
{
    //* Start the convertion by software trigger
    at91_adc_trig_cmd (Analog_pt->adc_desc,ADC_START);

    //* wait the end of convertion
    while ( (at91_adc_get_status(Analog_pt->adc_desc) << channel) == 0) {}

    //* read one value
    return Analog_pt->adc_desc->adc_base->ADC_CDR[channel];
//* End
}
//* End of file
