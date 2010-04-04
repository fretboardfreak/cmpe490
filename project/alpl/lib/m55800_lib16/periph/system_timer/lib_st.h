//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_st.h
//* Object              : System Timer Function Prototyping.
//*
//* 1.0 23/05/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_st_h
#define lib_st_h

#include    "periph/system_timer/st.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/stdc/lib_err.h"

#define ST_BASE         ((StructST *) 0xFFFF8000)    	/* ST: System Timer */

/*-----------------------------------------------*/
/* System Timer Descriptor Structure Definition  */
/*----*------------------------------------------*/
typedef struct
{
    StructST        *st_base ;          /* Peripheral base address */
    TypeAICHandler  *AsmSTHandler ;     /* Assembly interrupt handler */
    u_char          PeriphId ;          /* Peripheral Identifier */
} STDesc ;


/* System Timer Interrupt Handler (written in assembly) */
extern void at91_st_interrupt_handler ( const STDesc *st_pt ) ;

/* Function Prototyping */
extern void at91_st_wd_mode ( const STDesc *st_pt, u_int mode ) ;
extern void  at91_st_wd_rearm ( const STDesc *st_pt ) ;
extern u_int at91_st_get_status ( const STDesc *st_pt ) ;

#endif /* lib_st_h */
