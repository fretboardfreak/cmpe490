//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : analog_adc_irq.c
//* Object              : ADC driver irq management
//*
//* 1.0 31/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "analog.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_c_handler_adc
//* Object              : C handler interrup function called by the interrups
//*                       assembling routine
//*                       This function can be redefined in the user project
//* Input Parameters    : <Irq Descriptor> Analog ADC Interrupt descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_c_handler_adc(AnalogAdcIrqDesc *desc)
//* Begin
{
     u_short   adc_val;

    //* Read Channel
    adc_val = desc->adc->adc_base->ADC_CDR[desc->adc_channel];

    //* Software PDC
    //* Write the current value in the Memory
    *(desc->pdc.cur_add) =adc_val ;
    //* Update the pointer
    if (desc->pdc.cur_cmpt !=0)
    {
       desc->pdc.cur_add++;
       desc->pdc.cur_cmpt--;
    }
    else
    {
       desc->pdc.cur_add = desc->pdc.base_add ;
       desc->pdc.cur_cmpt= desc->pdc.base_cmpt;
    } //* End Update

    //* check if loop mode
    if (desc->loop_mode == LOOP_DAC)
            at91_dac_write(desc->dac_loop, &adc_val );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_open_adc_irq
//* Object              : Open ADC whith IRQ
//* Input Parameters    : <Irq Descriptor> Analog ADC Interrupt descriptor
//*                       <adc_mode> for resolution and Presacler
//*                       <tioc> Timer Comparator value for sampling
//*                       <tc_div> Timer MCKI value divisor for sampling
//*                       <data>  Input table pointer for software PDC
//*                       <nb_point>  Input table size for software PDC
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_open_adc_irq( AnalogAdcIrqDesc *ADC_pt,u_int adc_mode, int tioc,
                                int tc_div ,u_short * data,u_int nb_point)
//* Begin
{

    //* Set the Software PDC value
    ADC_pt->pdc.base_add = (u_short *)data;
    ADC_pt->pdc.cur_add =  (u_short *)data;
    ADC_pt->pdc.base_cmpt = nb_point-1;
    ADC_pt->pdc.cur_cmpt  = nb_point-1;

    //* -- Configure ADC
    at91_adc_open ( ADC_pt->adc, (adc_mode | ADC_TRGEN_EN)) ;

    at91_adc_channel_open (ADC_pt->adc,(1<<ADC_pt->adc_channel)) ;

    //* Open Irq
    at91_irq_open ( ADC_pt->adc->periph_id, 7, AIC_SRCTYPE_INT_EDGE_TRIGGERED, ADC_pt->AsmADCHandler ) ;
    ADC_pt->adc->adc_base->ADC_IER = (1<<ADC_pt->adc_channel);

    //* if DAC in loop mode
    if (ADC_pt->loop_mode == LOOP_DAC)
            at91_dac_open(ADC_pt->dac_loop,(DAC_10_BIT_RES |DAC_TTRGEN_DIS ));

    // init  timer
    at91_analog_open_timer(ADC_pt->timer,tioc,tc_div);

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_close_adc_irq
//* Object              : Stop the adc irq function
//* Input Parameters    : <Irq Descriptor> Analog ADC Interrupt descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_close_adc_irq( AnalogAdcIrqDesc *ADC_pt)
//* Begin
{
    //* stop the adc
    at91_adc_close( ADC_pt->adc);

    //* deselect the channel
    at91_adc_channel_close ( ADC_pt->adc, (1<<ADC_pt->adc_channel) );

    // Close interrupt
    at91_irq_close ( ADC_pt->adc->periph_id);

    // disable all interrup
    ADC_pt->adc->adc_base->ADC_IDR = -1;

    // Chek loop mode
    if (ADC_pt->loop_mode == LOOP_DAC)
            at91_dac_close(ADC_pt->dac_loop);

    //* -- close Timer
    at91_analog_close_timer(ADC_pt->timer);

//* End
}
//* End of file
