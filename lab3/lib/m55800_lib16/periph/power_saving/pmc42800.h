//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : pmc42800.h
//* Object              : Power Management Controller Header File.
//*
//* 1.0 22/05/00  PF    : Creation
//*----------------------------------------------------------------------------
#ifndef pmc42800_h
#define pmc42800_h

#include    "periph/stdc/std_c.h"

/*--------------------------------------------------*/
/* Power Management Controller Structure Definition */
/*--------------------------------------------------*/

typedef struct
{
    at91_reg    PMC_SCER ;  		/* System Clock Enable  Register */
    at91_reg    PMC_SCDR ;  		/* System Clock Disable Register */
    at91_reg    PMC_SCSR ;  		/* System Clock Status  Register */
    at91_reg    Reserved0 ;
    at91_reg    PMC_PCER ;  		/* Peripheral Clock Enable  Register */
    at91_reg    PMC_PCDR ;  		/* Peripheral Clock Disable Register */
    at91_reg    PMC_PCSR ;  		/* Peripheral Clock Status  Register */
	at91_reg    Reserved1 ;
	at91_reg    PMC_CGMR ;			/* Clock Generator Mode Register */
	at91_reg    Reserved2 ;
	at91_reg    Reserved3 ;
	at91_reg    Reserved4 ;
	at91_reg    PMC_SR ;	  		/* Status Register */
	at91_reg    PMC_IER ;	  		/* Interrupt Enable Register */
	at91_reg    PMC_IDR ;	  		/* Interrupt Disable Register */
	at91_reg    PMC_IMR ;	  		/* Interrupt Mask Register */
} StructPMC ;

/*--------------------------------------------------*/
/* Power Managment Control Register Bits Definition */
/*--------------------------------------------------*/
#define		PMC_ARM7DIS         0x1

/*---------------------------------------------------------------*/
/* Power Managment Clock Generator Mode Register Bits Definition */
/*---------------------------------------------------------------*/
#define		PMC_PRES_NONE		    0x0			/* No prescaler */
#define		PMC_PRES_DIV2			0x1			/* Selected Clock Divided by 2 */
#define		PMC_PRES_DIV4			0x2			/* Selected Clock Divided by 4 */
#define		PMC_PRES_DIV8			0x3			/* Selected Clock Divided by 8 */
#define		PMC_PRES_DIV16			0x4			/* Selected Clock Divided by 16 */
#define		PMC_PRES_DIV32			0x5			/* Selected Clock Divided by 32 */
#define		PMC_PRES_DIV64			0x6			/* Selected Clock Divided by 64 */

#define		PMC_PLL_A				(0<<3)		/* 5-20 MHz PLL selection */
#define		PMC_PLL_B				0x4			/* 20-80 MHz PLL selection */

#define		PMC_MCKOSS_SLCK			0x0			/* Master Clock Output is slow clock */
#define		PMC_MCKOSS_MCK			0x10		/* Master Clock Output is master clock */
#define		PMC_MCKOSS_MCKINV		0x20		/* Master Clock Output is master clock inverted */
#define		PMC_MCKOSS_MCK_DIV2		0x30		/* Master Clock Output is master clock divided by 2 */

#define		PMC_MCKO_DIS			0x40		/* Disable Master clock output (tri-state) */

#define		PMC_CSS_LF				(0<<7)		/* Low-Frequency Clock */
#define		PMC_CSS_PLL				0x80		/* Phase Lock Loop Output */

#define		B_MUL					8			/* First Bit of MUL */
#define 	B_PLL_COUNT				24			/* First Bit of PLL COUNT */

/*------------------------------------------------------*/
/* PM SR, IER, IDR and IMR Registers Bits Definition   */
/*------------------------------------------------------*/
#define		PMC_PLL_LOCK			0x1		/* PLL Lock Status */



/*------------------------------------------*/
/* Power Management Controller Base Address */
/*------------------------------------------*/

#define PMC_BASE        (( StructPMC *) 0xFFFF4000)

#endif /* pmc42800_h */
