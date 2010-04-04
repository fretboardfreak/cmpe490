//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : wait.h
//* Object              : Wait Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef wait_h
#define wait_h

#include    "periph/timer_counter/lib_tc.h"

#define WAIT_NEXT_EVENT                 0x1     // Idle mode until next interrupt
#define WAIT_NEXT_EVENT_MAX_DELAY       0x2     // Idle mode until next interrupt with a maximum delay
#define WAIT_DELAY                      0x3     // Wait for a delay specified in <period> expressed in microsec


/* Wait Structure Definition */
typedef struct
{
    const TCDesc    *tc_desc ;
    u_int           mcki_khz ;
    u_int           period ;
    u_int           mode ;
    TypeAICHandler  *handler ;
} WaitDesc ;

extern void at91_wait_open ( WaitDesc *tc_pt ) ;

#endif /* wait_h */
