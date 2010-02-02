//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : st.h
//* Object              : System Timer Header File.
//*
//* 1.0 22/05/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef system_timer_h
#define system_timer_h

#include    "periph/stdc/std_c.h"

/*------------------------------------------------*/
/*  System Timer User Interface Structure Definition */
/*------------------------------------------------*/
typedef struct
{
    at91_reg	ST_CR ;     	/* Control Register */
    at91_reg	ST_PIMR ;   	/* Period Interval Mode Register */
    at91_reg	ST_WDMR ;   	/* Watchdog Mode Register */
    at91_reg	ST_RTMR ;   	/* Real Time Mode Register */
    at91_reg	ST_SR ;			/* Status Register */
    at91_reg	ST_IER ;		/* Interrupt Enable Register */
    at91_reg	ST_IDR ;		/* Interrupt Disable Register */
    at91_reg	ST_IMR ;		/* Interrupt Mask Register */
    at91_reg	ST_RTAR ;		/* Real Time Alarm Register */
    at91_reg	ST_CRTR	;		/* Current Real Time Register */
} StructST ;

/*----------------------------------------------------------*/
/* ST_CR: System Timer Control Register Bits Definition 	*/
/*----------------------------------------------------------*/
#define ST_WDRST		0x1			/* Watchdog Timer Restart */

/*--------------------------------------------------------------*/
/* ST_WDMR: System Timer Watchdog Mode Register Bits Definition */
/*--------------------------------------------------------------*/
#define ST_RSTEN		0x10000 	/* WatchDog Overflow Reset Enable */
#define ST_EXTEN		0x20000 	/* External Signal Assertion Enable */

/*--------------------------------------------------------------------------------------------*/
/* ST_SR, ST_IER, ST_IDR, ST_IMR : System Timer Status and Interrupts Register Bits Definition */
/*--------------------------------------------------------------------------------------------*/
#define ST_PITS         0x1         /* Period Interval Timer Status */
#define ST_WDOVF		0x2			/* WatchDog Overflow Status */
#define ST_RTTINC       0x4         /* Real Time Timer Increment */
#define ST_ALMS			0x8			/* Alarm Status */


#endif /* system_timer_h */
