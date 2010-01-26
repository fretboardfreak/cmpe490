//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : analog_timer.c
//* Object              : Analog timer functions Library.
//*
//* 1.0 31/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include    "periph/stdc/std_c.h"
#include    "periph/timer_counter/lib_tc.h"
#include    "drivers/analog/analog.h"
#include    "drivers/com/com.h"
#include    <stdio.h>

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_c_handler_timer
//* Object              : C handler interrup function called by the interrups
//*                       assembling routine
//* Input Parameters    : <Irq Descriptor> Analog DAC Interrupt descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_c_handler_timer(AnalogDACTimerIrqDesc *desc)
//* Begin
{
    u_int tmp;

    //* Write the current value in the DAC
    desc->dac->dac_base->DAC_DHR = *(desc->pdc.cur_add);

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

    //* -- Deasert timer interrupt by read Status register (TC_SR)
    tmp =desc->timer->tc_base->TC_SR ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_init_timer
//* Object              : Timer initialisation for analog trigger without irq
//*                       use TIOA for DAC/ADC sampling
//*                       use TIOB for external trig (for test)
//*           _____         ____________
//*                |_______|            |_________
//*                 RA val      RC val               TIOA
//*                 RB val      RC val
//*
//* Input Parameters    : <TC_pt> timer descriptor
//*                       <tioc>  timer comparator value
//*                       <tc_div> timer MCKI divisor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_init_timer(const TCDesc *TC_pt, int tioc, int tc_div)
//* Begin
{

    u_int   mode_tc;
    u_int   regtc[3] ;

    // Initialize the mode of the timer
    mode_tc =
        TC_WAVE                 |   // WAVE   : Waveform mode
        TC_ENETRG               |   // ENETRG : Enable Trigger on External Event
        TC_CPCTRG               |   // CPCTRG : Register C compare trigger enable
        TC_AEEVT_CLEAR_OUTPUT   |   // External Event Effect on TIOA
        TC_BEEVT_CLEAR_OUTPUT   |   // External Event Effect on TIOB
        TC_BCPC_SET_OUTPUT      |   // RC Compare Effect on TIOB
        TC_BCPB_CLEAR_OUTPUT    |   // RB Compare Effect on TIOB
        TC_EEVT_XC0             |   // External Event Selection
        TC_EEVTEDG_FALLING_EDGE |   // External Event Edge Selection
        TC_ACPA_SET_OUTPUT      |   // RA Compare Effect on TIOA
        TC_ACPC_CLEAR_OUTPUT    |   // RC Compare Effect on TIOA
        TC_ASWTRG_CLEAR_OUTPUT  |   // ASWTRG   : software trigger clears TIOA
        TC_BSWTRG_CLEAR_OUTPUT ;    // BSWTRG   : software trigger clear  TIOB

    // set the clock divisor CLKS_MCK
    // tc_div = TC_CLKS_MCK2 or TC_CLKS_MCK4 or TC_CLKS_MCK8 ...
    mode_tc |= tc_div;

    //* -- Initialize the compare registers of the timer
    regtc[0] = 0x0002;       //* First Value  -> Register A  TIOA
    regtc[1] = 0x0002;       //* Second Value -> Register B TIOB
    regtc[2] = tioc;         //* Third Value  -> Register C  Comparator
    //* -- Configure Timer TIOA and TIOB as output
    at91_tc_open ( TC_pt, mode_tc, TRUE, TRUE ) ;

    //* Write Timer Counter Register
    at91_tc_write ( TC_pt, regtc ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_open_timer_irq
//* Object              : Timer initialisation for analog trigger with irq
//* Input Parameters    : <TC_pt> timer descriptor
//*                       <tioc>  timer comparator value
//*                       <tc_div> timer MCKI divisor
//*                       <data>  Input table pointer for software PDC
//*                       <nb_point>  Input table size for software PDC
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_open_timer_irq(AnalogDACTimerIrqDesc *DAC_pt, int tioc, int tc_div,const u_short * data,u_int nb_point)
//* Begin
{
    //* Set the timer value
    at91_analog_init_timer(DAC_pt->timer,tioc,tc_div);

    //* set Software PDC param
    DAC_pt->pdc.base_add = (u_short *) data;
    DAC_pt->pdc.cur_add = (u_short *)data;
    DAC_pt->pdc.base_cmpt = nb_point-1;
    DAC_pt->pdc.cur_cmpt = nb_point-1;

    //* Open the interrupt on the AIC
    at91_irq_open ( DAC_pt->timer->periph_id, 7, AIC_SRCTYPE_INT_EDGE_TRIGGERED,  DAC_pt->AsmDacHandler ) ;
    //* Enable the RC Compare interrupt
    DAC_pt->timer->tc_base->TC_IER = TC_CPCS ;

    //* -- Software Trigger on Timer
    //* -- generates a software trigger simultaneously for each of the channels.
    at91_tc_trig_cmd ( DAC_pt->timer, TC_TRIG_CHANNEL ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_init_timer
//* Object              : Timer initialisation for analog trigger without irq
//* Input Parameters    : <TC_pt> timer descriptor
//*                     : <tioc>  timer comparator value
//*                     : <tc_div> timer MCKI divisor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_open_timer(const TCDesc *TC_pt, int tioc, int tc_div)
//* Begin
{

    //* Set the timer value
    at91_analog_init_timer(TC_pt,tioc,tc_div);

    //* Enable the RC Compare interrupt
    TC_pt->tc_base->TC_IER = TC_CPCS ;

    //* -- Software Trigger on Timer
    //* -- generates a software trigger simultaneously for each of the channels.
    at91_tc_trig_cmd ( TC_pt, TC_TRIG_CHANNEL ) ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_analog_close_timer
//* Object              : Timer close  for analog trigger
//* Input Parameters    : <TC_pt> timer descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_analog_close_timer(const TCDesc *TC_pt)
//* Begin
{
    //* Close the interrupt on the AIC
     at91_irq_close ( TC_pt->periph_id ) ;

    //* -- close Timer
    at91_tc_close( TC_pt) ;


//* End
}
//* End of file
