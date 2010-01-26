//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_ps40400.c
//* Object              : Power Saving Library for 40400.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include "periph/power_saving/lib_power_save.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_set_mode
//* Object              : Disable the clock on the ARM Core.
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*-----------------------------------------------------------------------------
void at91_clock_set_mode ( u_int mode )
//* Begin
{
    //* Depending on the required mode
    switch (mode)
    {
        //* Idle mode required
        case PS_MODE_IDLE:
            //* Write the System Clock Disable Register
            PS_BASE->PS_CR = PS_ARM7DIS ;
            break ;

        //* Unknown
        default:
            //* Run AT91 Library error function
            at91_error (__FILE__, __LINE__) ;
    //* EndSwitch
    }
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_open
//* Object              : Enable the peripheral clock
//* Input Parameters    : <periph_id> = peripheral identifier
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_clock_open ( u_int periph_id )
//* Begin
{
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_close
//* Object              : Disable the clock of a Peripheral
//* Input Parameters    : <periph_id> = peripheral identifier
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_clock_close ( u_int periph_id )
//* Begin
{
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_get_status 
//* Object              : Return the Peripheral clock status 
//* Input Parameters    : <periph_id> = peripheral identifier
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_clock_get_status ( u_int periph_id )
//* Begin
{
    //* Return the Peripheral Clock Status Register
    return ( 1<<periph_id ) ;
//* End
}


