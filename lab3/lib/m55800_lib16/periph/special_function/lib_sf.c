//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_sf.c
//* Object              : Special Function Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/special_function/lib_sf.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_read_chip_id
//* Object              : Read one of the Chip Identification Registers.
//* Input Parameters    : <extension> = if not 0 and valid chip id extension
//*                     : exists, extension chip id is returned
//* Output Parameters   : the chip id register value
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_read_chip_id ( u_int extension )
//* Begin
{
    u_int cid ;

    //* Read the Chip Identification Register
    cid = ( SF_BASE->SF_CIDR ) ;
    //* If argument <extension> is not zero
    if (( extension != 0 ) && (( cid & SF_EXT ) != 0 ))
        //* Read the value of the extension Chip ID
        cid = SF_BASE->SF_EXID ;
    //* EndIf
    //* Return the last read register
    return ( cid ) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_set_protect_mode
//* Object              : Set Protect Mode.
//* Input Parameters    : <flag> : indicates to enable or to disable
//* Output Parameters   : None
//* Functions called    : None
//*----------------------------------------------------------------------------
void at91_set_protect_mode ( u_int flag )
//* Begin
{
    //* If Enable Request
    if ( flag == TRUE )
        //* Set the AIC bit in the Protect Mode Register
        SF_BASE->SF_PMR = SF_AIC ;
    //* Else
    else
        //* Clear the AIC bit in the Protect Mode Register
        SF_BASE->SF_PMR = 0 ;
//* End
}
