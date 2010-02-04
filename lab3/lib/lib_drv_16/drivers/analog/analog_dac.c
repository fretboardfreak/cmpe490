//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : analog_dac.c
//* Object              : DAC driver wave generation for the AT91EB55
//*
//* 1.0 25/08/00 JPP    : Creation
//* 2.0 10/12/01 PFi    : The "at91_analog_open_dac_loop" function has been removed.
//*                     : The RevA of the M558000 does not feature DAC PDC.
//*----------------------------------------------------------------------------

#include "analog.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_close_dac
//* Object              : Close the DAC and timer
//* Input Parameters    : <Descriptor> DAC descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_close_dac( AnalogDescDac *DAC_pt)
//* Begin
{
    //* stop the dac
    at91_dac_close( DAC_pt->dac);

    //* -- close Timer
    if ( DAC_pt->timer != 0)
        at91_analog_close_timer(DAC_pt->timer);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_open_dac
//* Object              : Init the DAC
//* Input Parameters    : <Descriptor> DAC descriptor
//*                       <dac_mode> for resolution and Trig
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_open_dac( AnalogDescDac *DAC_pt,u_int dac_mode)
//* Begin
{
    //* Open the dac
    at91_dac_open( DAC_pt->dac,dac_mode);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_write_dac
//* Object              : Write in the dac
//* Input Parameters    : <Descriptor> DAC descriptor
//*                       <data> pointer of date to write
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_write_dac( AnalogDescDac *DAC_pt,u_short * data)
//* Begin
{
    //* stop the dac
    at91_dac_write(DAC_pt->dac, data);

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_open_dac_loop_soft
//* Object              : Open the DAC in loop mode with software PDC
//* Input Parameters    : <Descriptor> DAC descriptor
//*                       <dac_mode> for resolution and trig
//*                       <tioc> Timer Comparator value for sampling
//*                       <tc_div> Timer MCKI value divisor for sampling
//*                       <data>  Input table pointer for software PDC
//*                       <nb_point>  Input table size for software PDC
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_open_dac_loop_soft(AnalogDACTimerIrqDesc *DAC_pt,u_int dac_mode, int tioc,int tc_div ,const u_short * data,u_int nb_point)
//* Begin
{
    //* -- Configure DAC
    at91_dac_open ( DAC_pt->dac, (dac_mode | DAC_TTRGEN_EN)) ;

    // init timer in interrupt for software PDC
    at91_analog_open_timer_irq(DAC_pt,tioc,tc_div,data,nb_point);

//* End
}

//* End of file
