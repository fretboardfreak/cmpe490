//*--------------------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : apmc55800.h
//* Object              : Power Management Controller Header File.
//*
//* 1.0 22/05/00  PF    : Creation
//* 1.1 27/07/00  PF    : Clean up
//*--------------------------------------------------------------------------------------
#ifndef apmc55800_h
#define apmc55800_h

#include    "periph/stdc/std_c.h"

/*---------------------------------------*/
/* Advanced Power Management Controller  */
/*---------------------------------------*/

typedef struct
{
    at91_reg    APMC_SCER ;         /* System Clock Enable  Register */
    at91_reg    APMC_SCDR ;         /* System Clock Disable Register */
    at91_reg    APMC_SCSR ;         /* System Clock Status  Register */
    at91_reg    Reserved0 ;
    at91_reg    APMC_PCER ;         /* Peripheral Clock Enable  Register */
    at91_reg    APMC_PCDR ;         /* Peripheral Clock Disable Register */
    at91_reg    APMC_PCSR ;         /* Peripheral Clock Status  Register */
    at91_reg    Reserved1 ;
    at91_reg    APMC_CGMR ;         /* Clock Generator Mode Register */
    at91_reg    Reserved2 ;
    at91_reg    APMC_PCR ;          /* Power Control Register */
    at91_reg    APMC_PMR ;          /* Power Mode Register */
    at91_reg    APMC_SR ;           /* Status Register */
    at91_reg    APMC_IER ;          /* Interrupt Enable Register */
    at91_reg    APMC_IDR ;          /* Interrupt Disable Register */
    at91_reg    APMC_IMR ;          /* Interrupt Mask Register */
} StructAPMC ;

/*-----------------------------------------------------------*/
/* Advanced Power Managment Control Register Bits Definition */
/*-----------------------------------------------------------*/
#define     APMC_ARM7DIS            0x1

/*------------------------------------------------------------------------*/
/* Advanced Power Managment Clock Generator Mode Register Bits Definition */
/*------------------------------------------------------------------------*/
#define     APMC_MOSC_BYP           0x1     /* Main Oscillator Bypass */
#define     APMC_MOSC_EN            0x2     /* Main Oscillator Enable */
#define     APMC_MCKO_DIS           0x4     /* Disable Master clock output (tri-state) */

#define     APMC_PRES_NONE          0x0     /* No prescaler */
#define     APMC_PRES_DIV2          0x10    /* Selected Clock Divided by 2 */
#define     APMC_PRES_DIV4          0x20    /* Selected Clock Divided by 4 */
#define     APMC_PRES_DIV8          0x30    /* Selected Clock Divided by 8 */
#define     APMC_PRES_DIV16         0x40    /* Selected Clock Divided by 16 */
#define     APMC_PRES_DIV32         0x50    /* Selected Clock Divided by 32 */
#define     APMC_PRES_DIV64         0x60    /* Selected Clock Divided by 64 */

#define     APMC_CSS_LF             0x0     /* Low-Frequency Clock provided by RTC */
#define     APMC_CSS_MOSC           0x4000  /* Main Oscillator Output or External clock */
#define     APMC_CSS_PLL            0x8000  /* Phase Lock Loop Output */

#define     B_MUL                   8
#define     B_OSCOUNT               16
#define     B_PLLCOUNT              24

/*------------------------------------------------*/
/* APM Power Controller Register Bits Definition  */
/*------------------------------------------------*/
#define     APMC_SHDALC             0x1     /* Shut-down or alarm Command */
#define     APMC_WKACKC             0x2     /* Wake-up or Alarm Acknowledge Command */

/*-----------------------------------------------*/
/* APM Power Mode Register Bits Definition       */
/*-----------------------------------------------*/
#define     APMC_SHDALS_OUT_TRIS        0x0     /* SHDALS pin is Tri-State */
#define     APMC_SHDALS_OUT_LEVEL_0     0x1     /* SHDALS pin is LEVEL 0 */
#define     APMC_SHDALS_OUT_LEVEL_1     0x2     /* SHDALS pin LEVEL 1 */

#define     APMC_WKACKS_OUT_TRIS        0x0     /* WKACKS pin is Tri-State */
#define     APMC_WKACKS_OUT_LEVEL_0     0x4     /* WKACKS pin  is LEVEL 0 */
#define     APMC_WKACKS_OUT_LEVEL_1     0x8     /* WKACKS pin  is LEVEL 1 */

#define     APMC_WKEN                   0x10    /* Alarm Wake-up Enable */
#define     APMC_ALSHEN                 0x20    /* Alarm Shut-Down Enable */

#define     APMC_WKEDG_NONE             0x00    /* None. No edge is detected on Wake-up */
#define     APMC_WKEDG_POS_EDG          0x40    /* Positive edge detection */
#define     APMC_WKEDG_NEG_EDG          0x80    /* Negative edge detection */

/*------------------------------------------------------*/
/* APM SR, IER, IDR and IMR Registers Bits Definition   */
/*------------------------------------------------------*/
#define     APMC_MOSCS                  0x1     /* Main Osillator Status */
#define     APMC_PLL_LOCK               0x2     /* PLL Lock Status */

/*---------------------------------------------------*/
/* Advanced Power Management Controller Base Address */
/*---------------------------------------------------*/

#define APMC_BASE        (( StructAPMC *) 0xFFFF4000)

#endif /* apmc55800_h */
