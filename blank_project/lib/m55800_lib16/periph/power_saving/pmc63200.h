//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : pmc63200.h
//* Object              : Power Management Controller Header File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------
#ifndef pmc63200_h
#define pmc63200_h

#include    "periph/stdc/std_c.h"

/*--------------------------------------------------*/
/* Power Management Controller Structure Definition */
/*--------------------------------------------------*/

typedef struct
{
    at91_reg    PMC_SCER ;  /* System Clock Enable  Register */
    at91_reg    PMC_SCDR ;  /* System Clock Disable Register */
    at91_reg    PMC_SCSR ;  /* System Clock Status  Register */
    at91_reg    Reserved0 ;
    at91_reg    PMC_PCER ;  /* Peripheral Clock Enable  Register */
    at91_reg    PMC_PCDR ;  /* Peripheral Clock Disable Register */
    at91_reg    PMC_PCSR ;  /* Peripheral Clock Status  Register */
} StructPMC ;

/*-----------------------------------------------*/
/* Power Saving Control Register Bits Definition */
/*-----------------------------------------------*/
    
#define PMC_ARM7DIS         0x1

/*------------------------------------------*/ 
/* Power Management Controller Base Address */
/*------------------------------------------*/ 

#define PMC_BASE        (( StructPMC *) 0xFFFF4000)

#endif /* pmc63200_h */
