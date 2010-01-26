//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_dac.c
//* Object              : Digital To Analog Converter Library.
//*
//* 1.0 25/08/00 LLD    : Creation
//* 2.0 10/12/01 PFi    : Access to Data Pointer/Counter Registers has been removed.
//*                     : The RevA of the M558000 does not features DAC PDC.
//*----------------------------------------------------------------------------

#include    "periph/dac/lib_dac.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_open
//* Object              : Open a DAC Channel
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//*                     : <mode> = resolution, trigger selection
//* Output Parameters   : TRUE
//* Functions called    : at91_clock_open
//*----------------------------------------------------------------------------
void at91_dac_open ( const DacDesc *dac_desc, u_int mode )
//* Begin
{
    //* Enable the DAC clock
    at91_clock_open ( dac_desc->periph_id ) ;

    //* Reset the DAC
    dac_desc->dac_base->DAC_CR = DAC_SWRST ;

    //* Set the mode of the DAC
    dac_desc->dac_base->DAC_MR = mode ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_close
//* Object              : Close DAC Channel
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : at91_clock_close
//*-----------------------------------------------------------------------------
void at91_dac_close ( const DacDesc *dac_desc )
//* Begin
{
    //* Disable the DAC Clock
    at91_clock_close ( dac_desc->periph_id ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_trig_cmd
//* Object              : Set DAC Control Register
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_dac_trig_cmd ( const DacDesc *dac_desc, u_int cmd )
//* Begin
{
    dac_desc->dac_base->DAC_CR = cmd ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_set_mode
//* Object              : Defines a DAC Mode Register
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_dac_set_mode ( const DacDesc *dac_desc, u_int mode )
//* Begin
{
    dac_desc->dac_base->DAC_MR = mode ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_write
//* Object              : Write data to the DAC
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//*                     : <data> = data buffer pointer
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_dac_write ( const DacDesc *dac_desc, u_short *data )
//* Begin
{
    dac_desc->dac_base->DAC_DHR = *data ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_dac_get_status
//* Object              : Return DAC Status Register
//* Input Parameters    : <dac_desc> = DAC Descriptor pointer
//* Output Parameters   : DAC Status Register
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_dac_get_status ( const DacDesc *dac_desc )
//* Begin
{
    return ( dac_desc->dac_base->DAC_SR ) ;
//* End
}
