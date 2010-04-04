//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_wd.h
//* Object              : Watch Dog Library Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//* 1.1 26/12/00 JPP    : change at91_watch_dog_disable
//*----------------------------------------------------------------------------

#ifndef lib_wd_h
#define lib_wd_h

#include    "periph/watchdog/wd.h"

typedef void (*TypeWDHandler) (void) ;

/*-------------------------------------------*/
/* Watch Dog Descriptor Structure Definition */
/*-------------------------------------------*/
typedef struct
{
    StructWD        *WDBase ;           /* Peripheral base address */
    TypeAICHandler  *AsmWDHandler ;     /* Assembly interrupt handler */
    u_char          PeriphId ;          /* Peripheral Identifier */
} WDDesc ;



/* Watch Dog Interrupt Handler (written in assembly) */
extern void at91_watch_dog_interrupt_handler ( void ) ;

/* Function Prototyping */
extern void  at91_watch_dog_rearm ( const WDDesc *wd_pt );
extern void  at91_watch_dog_disable ( const WDDesc *wd_pt ) ;
extern u_int at91_read_status_watch_dog ( const WDDesc *wd_pt );
extern void  at91_watch_dog_init ( const WDDesc *wd_pt, u_int mode, u_int clock,
                                   u_int count, TypeWDHandler handler_add );
extern void  at91_init_test_watch_dog ( WDDesc *wd_pt,  u_int mode, u_int clock,
                                        u_int count, TypeWDHandler handler_add );

#endif /* lib_wd_h */
