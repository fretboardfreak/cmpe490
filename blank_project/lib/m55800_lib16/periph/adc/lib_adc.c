//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_adc.c
//* Object              : Analog to Digital Converter Library File
//*
//* 1.0 25/08/00  PF    : Creation
//*----------------------------------------------------------------------------

#include "periph/adc/lib_adc.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_open
//* Object              : Open an ADC Channel
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//*                     : <mode> = resolution, trigger selection
//* Output Parameters   : none
//* Functions called    : at91_clock_open
//*----------------------------------------------------------------------------
void at91_adc_open ( const AdcDesc *adc_desc, u_int mode )
//* Begin
{
    //* Enable the ADC clock
    at91_clock_open ( adc_desc->periph_id ) ;

    //* Reset the ADC
    adc_desc->adc_base->ADC_CR = ADC_SWRST ;

    //* Set the mode of the ADC
    adc_desc->adc_base->ADC_MR = mode ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_close
//* Object              : Close an ADC Channel
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : at91_clock_close
//*----------------------------------------------------------------------------
void at91_adc_close ( const AdcDesc *adc_desc )
//* Begin
{
    //* Disable the ADC Clock
    at91_clock_close ( adc_desc->periph_id ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_trig_cmd
//* Object              : Defines an ADC Control Register
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_adc_trig_cmd ( const AdcDesc *adc_desc, u_int cmd )
//* Begin
{
    adc_desc->adc_base->ADC_CR = cmd ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_get_status
//* Object              : Return ADC Status Register
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_adc_get_status ( const AdcDesc *adc_desc )
//* Begin
{
    return ( adc_desc->adc_base->ADC_SR ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_channel_open
//* Object              : Enable the analog input channels
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//*                       <channel> = channels to be enabled
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_adc_channel_open ( const AdcDesc *adc_desc, u_int channel )
//* Begin
{
    //* Write the Channel Enable Register
    adc_desc->adc_base->ADC_CHER = channel ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_channel_close
//* Object              : Disable the analog input channels
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//*                       <channel> = channels to be enabled
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_adc_channel_close ( const AdcDesc *adc_desc, u_int channel )
//* Begin
{
    //* Write the Channel Disable Register
    adc_desc->adc_base->ADC_CHDR = channel ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_channel_get_status
//* Object              : Return the Channel status
//* Input Parameters    : <adc_desc> = ADC Descriptor pointer
//* Output Parameters   : Channel status
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_adc_channel_get_status ( const AdcDesc *adc_desc )
//* Begin
{
    //* Return the Channel Status Register
    return ( adc_desc->adc_base->ADC_CHSR ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_adc_read
//* Object              : Read all ADC Convert Data Registers
//* Input Parameters    : <adc_desc> = ADC Descriptor Pointer
//*                     : <channel> = Destination Register Value Table Pointer
//* Output Parameters   : <channel> = Register Value
//* Functions called    : None
//*----------------------------------------------------------------------------
void at91_adc_read ( const AdcDesc *adc_desc, u_int channel[] )
//* Begin
{
    channel[0] = adc_desc->adc_base->ADC_CDR[0] ;
    channel[1] = adc_desc->adc_base->ADC_CDR[1] ;
    channel[2] = adc_desc->adc_base->ADC_CDR[2] ;
    channel[3] = adc_desc->adc_base->ADC_CDR[3] ;
//* End
}
//* End of file
