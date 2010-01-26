//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_err.c
//* Object              : Error default Handling.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/stdc/std_c.h"
#include    "periph/stdc/lib_err.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_default_error
//* Object              : Default AT91 Library Error detection handling
//* Input Parameters    : None
//* Output Parameters   : Never
//* Functions called    : None
//*----------------------------------------------------------------------------
void at91_default_error ( void )
//* Begin
{
    //* Loop Forever
    while ( TRUE ) ;

//* End
}

