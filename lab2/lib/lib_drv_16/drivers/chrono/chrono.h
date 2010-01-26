//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : chrono.h
//* Object              : Chronometer Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef chrono_h
#define chrono_h

#include    "periph/aic/lib_aic.h"
#include    "periph/pio/lib_pio.h"
#include    "periph/timer_counter/lib_tc.h"

#define CHRONO_START        0x1
#define CHRONO_STOP         0x2
#define CHRONO_CONTINUE     0x3

typedef struct
{
    const TCBlockDesc       *tcb_desc ;
    u_int                   frequency_kilohertz ;
} ChronoDesc ; 

extern void  at91_chrono_open ( ChronoDesc *chrono_desc );
extern void  at91_chrono_trig_cmd ( ChronoDesc *chrono_pt, u_int cmd );
extern u_int at91_chrono_read ( ChronoDesc *chrono_pt );
extern void  at91_chrono_close ( ChronoDesc *chrono_pt );

#endif /* chrono_h */
