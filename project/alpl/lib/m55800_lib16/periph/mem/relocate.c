//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : relocate.c
//* Object              : Relocation functions.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*-----------------------------------------------------------------------------

#include    "periph/stdc/std_c.h"

//*-----------------------------------------------------------------------------
//* Function Name           : relocate
//* Object                  : RAM test function
//* Input Parameters        : base = fisrt address to test
//*                         : size = memory size to test
//* Output Parameters       : none
//* Functions called        :
//*-----------------------------------------------------------------------------
u_short *relocate ( u_short *base, u_short *dest, u_int size )
//* Begin
{
    u_int           count ;
    u_short         *src ;
    u_short         *save_dest ;

    if (( (u_int)base & 0x1 ) != 0 )
    {
        src = (u_short *) ((u_int)base & ~0x1 );
        save_dest = (u_short *)((u_int)dest | 0x1) ;
    }
    else
    {
        src = base ;
        save_dest = dest ;
    }

    for ( count = 0 ; count < (size/2) ; count ++ )
    {
        *dest ++ = *src ++; 
    }
    return ( save_dest ) ;

//* End
}
