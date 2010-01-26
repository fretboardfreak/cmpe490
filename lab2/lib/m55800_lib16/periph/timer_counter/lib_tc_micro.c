//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_tc_micro.c
//* Object              : Timer Counter Library this function load all ARM
//*                       division library.
//*
//* 1.0 12/10/00 JPP    : Creation by cutting the lib_tc in two files
//*----------------------------------------------------------------------------

#include    "periph/timer_counter/tc.h"
#include    "periph/timer_counter/lib_tc.h"
#include    "periph/stdc/lib_err.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_compute_microsec
//* Object              : Compute Timer Counter register for microsecond
//* Input Parameters    : <reg> = Register Table
//*                       <clk> = Clock Pointer
//*                       <mcki_khz> = Master Clock Frequency in kilohertz
//* Output Parameters   : void
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
void at91_tc_compute_microsec ( u_int *rc, u_int *clk, u_int mcki_khz )
{
//* Begin
    u_int   rc_save ;
    //* Adjust to Microseconds * MHz
    *rc = (*rc / 1000) * mcki_khz ;

    //* If period(microsec) * MCK(MHz) div 2 < 2, error
    if (( rc_save = *rc >> 1 ) < 2 )
        at91_error ("__FILE__","__LINE__") ;

    //* If period(microsec) * MCK(MHz) div 2 < Counter max value
    if ( rc_save < ( 1<<16 ))
        //* Select MCK/2
        *clk = TC_CLKS_MCK2 ;
    //* Else
    else
        //* If period(microsec) * MCK(MHz) div 8 < Counter max value
        if (( rc_save = *rc >> 3 ) < ( 1 << 16 ))
            //* Select MCK/8
            *clk = TC_CLKS_MCK8 ;
        //* Else
        else
            //* If period(microsec) * MCK(MHz) div 32 < Counter max value
            if (( rc_save = *rc >> 5 ) < ( 1 << 16 ))
                //* Select MCK/32
                *clk = TC_CLKS_MCK32 ;
            //* Else
            else
                //* If period(microsec) * MCK(MHz) div 128 < Counter max value
                if (( rc_save = *rc >> 7 ) < ( 1 << 16 ))
                    //* Select MCK/128
                    *clk = TC_CLKS_MCK128 ;
                //* Else
                else
                    //* If period(microsec) * MCK(MHz) div 1024 < Counter max value
                    if (( rc_save = *rc >> 10 ) < ( 1 << 16 ))
                        //* Select MCK/1024
                        *clk = TC_CLKS_MCK1024 ;
                    //* Else
                    else
                        //* Error
                        at91_error ("__FILE__","__LINE__") ;
                //* EndIf
            //* EndIf
        //* EndIf
    //* EndIf
    *rc = rc_save ;
}
//* End
