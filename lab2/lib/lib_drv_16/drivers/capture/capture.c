//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : capture.c
//* Object              : Timer Counter in Capture Mode Drivers.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/stdc/std_c.h"
#include    "periph/timer_counter/lib_tc.h"
#include    "drivers/capture/capture.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_capture_open
//* Object              : Initialize the Timer Counter in Capture Mode
//* Input Parameters    : <tc_pt> = channel to initialize
//*                     : <mode> = Low, High or period Mode
//* Output Parameters   : none
//* Functions called    : at91_tc_open, at91_tc_write
//*----------------------------------------------------------------------------
void at91_capture_open ( const TCDesc *tc_pt, u_int mode )
//* Begin
{
    u_int reg[4] = {0, 0, 0xFFFF, 0} ;
    //* Open the Timer Counter
    at91_tc_open (tc_pt, mode, TRUE, FALSE );
    //* Write the registers values in the Timer Counter
    at91_tc_write ( tc_pt, reg );

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_capture_close
//* Object              : Close the Timer Counter Capture Mode 
//* Input Parameters    : <tc_pt> = channel to close
//* Output Parameters   : none
//* Functions called    : at91_tc_close
//*----------------------------------------------------------------------------
void at91_capture_close ( const TCDesc *tc_pt )
//* Begin
{
   //* Close the Timer Counter
   at91_tc_close ( tc_pt );

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_capture_read
//* Object              : Read 
//* Input Parameters    : <tc_pt> = channel to initialize
//* Output Parameters   : The number of MCKI cycle
//* Functions called    : at91_tc_read
//*----------------------------------------------------------------------------
u_int at91_capture_read ( const TCDesc *tc_pt )
//* Begin
{
    u_int   regs[4] ;
    at91_tc_read ( tc_pt, regs ) ;
    switch (tc_pt->tc_base->TC_CMR& TC_CLKS )
    {
        case TC_CLKS_MCK2 : regs[RA]<<= 1 ; break ;
        case TC_CLKS_MCK8 : regs[RA]<<= 3 ; break ;
        case TC_CLKS_MCK32 : regs[RA]<<= 5 ; break ;
        case TC_CLKS_MCK128 : regs[RA]<<= 7 ; break ;
        case TC_CLKS_MCK1024 : regs[RA]<<= 10 ; break ;
    }
    return (regs[RA]) ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_capture_get_status
//* Object              : Detect the end of capture
//* Input Parameters    : <tc_pt> = channel to initialize
//* Output Parameters   : 
//* Functions Called    : at91_tc_get_status
//*----------------------------------------------------------------------------
u_int at91_capture_get_status ( const TCDesc *tc_pt )
//* Begin
{
    return (( at91_tc_get_status (tc_pt) & (TC_ETRGS|TC_LDRAS)) == (TC_ETRGS|TC_LDRAS)) ;

//* End
}
