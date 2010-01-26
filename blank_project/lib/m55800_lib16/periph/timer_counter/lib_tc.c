//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_tc.c
//* Object              : Timer Counter Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//* 1.1 12/10/00 JPP    : cutting the lib_tc in two files
//*----------------------------------------------------------------------------

#include    "periph/timer_counter/tc.h"
#include    "periph/timer_counter/lib_tc.h"
#include    "periph/power_saving/lib_power_save.h"
#include    "periph/stdc/lib_err.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_open
//* Object              : Initialize Timer Counter Channel and enable is clock
//* Input Parameters    : <tc_pt> = TC Channel Descriptor Pointer
//*                       <mode> = Timer Counter Mode
//*                     : <tioa> = TIOA enabled as peripheral if non null
//*                     : <tiob> = TIOB enabled as peripheral if non null
//* Output Parameters   : None
//* Functions called    : at91_clock_open, at91_pio_close
//*----------------------------------------------------------------------------
void at91_tc_open ( const TCDesc *tc_pt, u_int mode, u_int tioa, u_int tiob )
//* Begin
{
    u_int pio = 0 ;
    //* Start the Clock of the Timer
    at91_clock_open ( tc_pt->periph_id ) ;

    pio = 1<<tc_pt->pin_tclk ;
    //* Enable TIOA pin if requested
    if ( tioa == TRUE )
    {
        pio |= 1<<tc_pt->pin_tioa ;
    }
    //* Enable TIOB pin if requested
    if ( tiob == TRUE )
    {
        pio |= 1<<tc_pt->pin_tiob ;
    }
    at91_pio_close ( tc_pt->pio_ctrl, pio ) ;

    //* Disable the clock and the interrupts
    tc_pt->tc_base->TC_CCR = TC_CLKDIS ;
    tc_pt->tc_base->TC_IDR = 0xFFFFFFFF ;
    pio = tc_pt->tc_base->TC_SR ;

    //* Set the Mode of the Timer Counter
    tc_pt->tc_base->TC_CMR = mode ;

    //* Enable the clock
    tc_pt->tc_base->TC_CCR = TC_CLKEN ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_close
//* Object              : Stop a Timer Counter Channel and disable is clock
//* Input Parameters    : <tc_pt> = the channel number
//* Output Parameters   : None
//* Functions called    : at91_clock_close
//*----------------------------------------------------------------------------
void at91_tc_close ( const TCDesc *tc_pt )
//* Begin
{
    //* Disable the clock and interrupts
    tc_pt->tc_base->TC_CCR = TC_CLKDIS ;
    tc_pt->tc_base->TC_IDR = 0xFFFFFFFF ;

    //* Stop the Clock of the Timer
    at91_clock_close ( tc_pt->periph_id ) ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_get_status
//* Object              : Read the Status of a Timer Counter Channel
//* Input Parameters    : <tc_pt> = the channel number
//* Output Parameters   : the status value
//* Functions called    : None
//*----------------------------------------------------------------------------
u_int at91_tc_get_status ( const TCDesc *tc_pt )
//* Begin
{
    //* Return the value of the Status Register
    return ( tc_pt->tc_base->TC_SR ) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_trig_cmd
//* Object              : Generate a software trigger on a TC channel
//* Input Parameters    : <tc_pt> = the channel number to trig
//* Output Parameters   : None
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
void at91_tc_trig_cmd ( const TCDesc *tc_pt, u_int cmd )
//* Begin
{
    //* Depending on the command
    switch (cmd)
    {
        //* Case Channel Trigger
        case TC_TRIG_CHANNEL:
            //* Perform a Software trigger on the corresponding channel
            tc_pt->tc_base->TC_CCR = TC_SWTRG ;
            break ;

        //* Case Synchronization Trigger
        case TC_TRIG_BLOCK:
            //* Perform a synchronization trigger
            ((StructTCBlock *) ((u_int)tc_pt->tc_base & 0xF0))->TC_BCR = TC_SYNC ;
            break ;

        //* Unkonwn
      //  default :
            //* Run the AT91 Library Error Macro
       //$$$$     at91_error ("__FILE__","__LINE__") ;
    //* End Switch
    }
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_set_mode
//* Object              : Update Timer Counter Mode Register with mask
//* Input Parameters    : <tc_pt> = the channel number
//*                     : <mask> = bit to modify in the mode register
//*                     : <data> = set/clear bits in the mode register
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_tc_set_mode ( const TCDesc *tc_pt, u_int mask, u_int data )
//* Begin
{
    //* If data is not null
    if (data != 0)
        //* Set bits in the Mode Register corresponding to the mask
        tc_pt->tc_base->TC_CMR |= mask ;
    //* Else
    else
        //* Clear bits in the Mode Register corresponding to the mask
        tc_pt->tc_base->TC_CMR &= ~mask ;
    //* EndIf
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_read
//* Object              : Read all Timer Counter Register
//* Input Parameters    : <tc_pt> = Channel Descriptor Pointer
//*                     : <reg> = Destination Register Value Table Pointer
//* Output Parameters   : None
//* Functions called    : None
//*----------------------------------------------------------------------------
void at91_tc_read ( const TCDesc *tc_pt, u_int reg[] )
//* Begin
{
    reg[RA] = tc_pt->tc_base->TC_RA ;
    reg[RB] = tc_pt->tc_base->TC_RB ;
    reg[RC] = tc_pt->tc_base->TC_RC ;
    reg[CV] = tc_pt->tc_base->TC_CV ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_write
//* Object              : Write Timer Counter Register
//* Input Parameters    : <tc_pt> = Timer Counter Channel Descriptor Pointer
//*                     : <reg> = Source Register Value Table Pointer
//* Output Parameters   : None
//* Functions called    : None
//*----------------------------------------------------------------------------
void at91_tc_write ( const TCDesc *tc_pt, u_int reg[] )
//* Begin
{
    //* First Value -> Register A
    tc_pt->tc_base->TC_RA = reg[RA] ;
    //* Second Value -> Register B
    tc_pt->tc_base->TC_RB = reg[RB] ;
    //* Third Value -> Register C
    tc_pt->tc_base->TC_RC = reg[RC] ;
}
//* End
