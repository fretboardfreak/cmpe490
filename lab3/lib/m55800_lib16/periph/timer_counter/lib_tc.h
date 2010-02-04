//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_tc.h
//* Object              : Timer Counter Library Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_tc_h
#define lib_tc_h

#include    "periph/aic/lib_aic.h"
#include    "periph/pio/lib_pio.h"
#include    "periph/timer_counter/tc.h"
#include    "periph/timer_counter/lib_tc.h"

//* Define Register coding for <reg_id>
#define RA  0
#define RB  1
#define RC  2
#define CV  3

//* at91_tc_trig_cmd <cmd> parameter
#define TC_TRIG_CHANNEL         0x1
#define TC_TRIG_BLOCK           0x2

typedef void (*TypeTCHandler) (void) ;

/*------------------------------------*/
/* Timer Counter Descriptor Structure */
/*------------------------------------*/

typedef struct
{
    StructTC                *tc_base ;
    const PioCtrlDesc       *pio_ctrl ;
    u_char                  periph_id ;
    u_char                  pin_tioa ;
    u_char                  pin_tiob ;
    u_char                  pin_tclk ;
} TCDesc ;

/*------------------------------------------*/
/* Timer Counter Block Descriptor Structure */
/*------------------------------------------*/
typedef struct
{
    const TCDesc    *tc0_desc ;
    const TCDesc    *tc1_desc ;
    const TCDesc    *tc2_desc ;
} TCBlockDesc ;

extern void at91_tc_open ( const TCDesc *tc_pt, u_int mode, u_int tioa, u_int tiob );
extern void at91_tc_close ( const TCDesc *tc_pt );
extern u_int at91_tc_get_status ( const TCDesc *tc_pt );
extern void at91_tc_trig_cmd ( const TCDesc *tc_pt, u_int cmd );
extern void at91_tc_set_mode ( const TCDesc *tc_pt, u_int mask, u_int data );
extern void at91_tc_read ( const TCDesc *tc_pt, u_int reg[] );
extern void at91_tc_write ( const TCDesc *tc_pt, u_int reg[] );
extern void at91_tc_compute_microsec ( u_int *rc, u_int *clk, u_int mcki_khz ) ;

#endif /* lib_tc_h */
