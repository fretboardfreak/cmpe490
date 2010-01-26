//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_st.c
//* Object              : System Timer Library.
//*
//* 1.0 23/05/00  PF    : Creation
//*----------------------------------------------------------------------------

#include    "periph/system_timer/lib_st.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/stdc/lib_err.h"


//*----------------------------------------------------------------------------
//* Function Name       : at91_no_handler_st
//* Object              : Default System Timer Interrupt Handler
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
#if 0
static void at91_no_handler_st ( void )
//* Begin
{
    at91_error ( __FILE__, __LINE__ ) ;
//* End
}
#endif

//*----------------------------------------------------------------------------
//* Function Name       : at91_st_wd_mode
//* Object              : Initialize the Watch Dog mode of the System Timer.
//* Input Parameters    : <mode>  = mode of watch dog
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_st_wd_mode ( const STDesc *st_pt, u_int mode )
//* Begin
{
    //* Set EXTEN and RSTEN Bit in Watch Dog Mode Register
    st_pt->st_base->ST_WDMR = mode ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_st_wd_rearm
//* Object              : Restart the Watch Dog counter.
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void  at91_st_wd_rearm ( const STDesc *st_pt )
//* Begin
{
    //* Restart the Watch Dog
    st_pt->st_base->ST_CR = ST_WDRST ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_st_get_status
//* Object              : Stop the Watch Dog counter.
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_st_get_status ( const STDesc *st_pt )
//* Begin
{
    //* Return the System Timer status Register
    return ( st_pt->st_base->ST_SR ) ;

//* End
}
