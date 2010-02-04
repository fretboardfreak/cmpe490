//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_pmc42800.c
//* Object              : Power Management Controller Library.
//*
//* 1.0 22/05/00  PF    : Creation
//*----------------------------------------------------------------------------

#include    "periph/power_saving/lib_power_save.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_set_mode
//* Object              : Set System Clock Mode.
//* Input Parameters    : <mode> =
//* Output Parameters   : none
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
void at91_clock_set_mode ( u_int mode )
//* Begin
{
    //* Depending on the required mode
    switch (mode)
    {
        //* Idle mode required
        case PS_MODE_IDLE:
            //* Write the System Clock Disable Register
            PMC_BASE->PMC_SCDR = PMC_ARM7DIS ;
            break ;

        //* Active all peripheral clocks
        case PS_ALL_PERIPH_ACTIVE:
            //* Enable all the peripheral clocks
            PMC_BASE->PMC_PCER = 0xFFFFFFFF ;
            break ;

        //* Desactive all peripheral clocks
        case PS_ALL_PERIPH_INACTIVE:
            //* Disable all the peripheral clocks
            PMC_BASE->PMC_PCDR = 0xFFFFFFFF ;
            break ;

        //* Unknown
        default:
            //* Run AT91 Library error function
            at91_error (__FILE__, __LINE__) ;
    }
    //* EndSwitch
}
//* End

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
    //* Write the Peripheral Clock Enable Register
    PMC_BASE->PMC_PCER = (1 << periph_id) ;
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
    //* Write the Peripheral Clock Disable Register
    PMC_BASE->PMC_PCDR = (1 << periph_id) ;
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
    return ( PMC_BASE->PMC_PCSR & (1<<periph_id) ) ;
}
//* End


//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_get_pll_status
//* Object              : Return the PMC Status Register
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_clock_get_pll_status ( void )
//* Begin
{
    //* Return the PMC Status Register
    return ( PMC_BASE->PMC_SR ) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_generator_mode
//* Object              : Set PLL mode
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_clock_generator_mode (u_int mode )
//* Begin
{
	PMC_BASE->PMC_CGMR = mode ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_clock_generator_state NEW
//* Object              : Return the Clock Mode Generator
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_clock_generator_state (void)
//* Begin
{
	//* Return the CGMR state
	return ( PMC_BASE->PMC_CGMR ) ;
}
//* End
