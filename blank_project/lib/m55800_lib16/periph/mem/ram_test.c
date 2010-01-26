//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : ram_test.c
//* Object              : Random Access Memory Test functions.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*-----------------------------------------------------------------------------

#include    "periph/stdc/std_c.h"

//*-----------------------------------------------------------------------------
//* Function Name           : ram_test
//* Object                  : RAM test function
//* Input Parameters        : base = fisrt address to test
//*                         : size = memory size to test
//* Output Parameters       : none
//* Functions called        :
//*-----------------------------------------------------------------------------
u_int ram_test ( u_int *base, u_int size )
//* Begin
{
    volatile u_int *wr_pt = (u_int *)base ;
    u_int           count ;
    u_int           save ;
    u_char          *char_wr_pt = (u_char *) wr_pt ;
    u_short         *short_wr_pt = (u_short *) wr_pt ;

    for ( count = 0 ; count < (size/4) ; count ++, wr_pt ++ )
    {
        save = *wr_pt ;

        *wr_pt = 0 ;

        *char_wr_pt++ = 0xAA ;
        *char_wr_pt++ = 0x55 ;
        *char_wr_pt++ = 0x5A ;
        *char_wr_pt++ = 0xA5 ;
        
        if ( *wr_pt != 0xA55A55AA ) return ( FALSE ) ;

        *short_wr_pt++ = 0x5AA5 ;
        *short_wr_pt++ = 0xAA55 ;
        
        if ( *wr_pt != 0xAA555AA5 ) return ( FALSE ) ;

        *wr_pt = save ;
    }
    return ( TRUE ) ;

//* End
}
