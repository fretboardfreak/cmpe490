//*--------------------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : lib_power_save.h
//* Object              : Power Saving Function Prototyping File.
//*
//* 1.0 01/04/00  JCZ   : Creation
//* 1.1 22/05/00  PFi   : Clean Up
//* 1.2 29/09/00  JPP   : 55800 and 42800
//* 1.3 06/08/01  PFi   : Add r40008
//*--------------------------------------------------------------------------------------
#ifndef lib_power_save_h
#define lib_power_save_h

#include    "periph/stdc/std_c.h"
#include    "periph/stdc/lib_err.h"

#ifdef AT91M40400
#include    "periph/power_saving/ps40400.h"
#endif

#ifdef AT91F40416
#include    "periph/power_saving/ps40400.h"
#endif

#ifdef AT91M40800
#include    "periph/power_saving/ps40800.h"
#endif

#ifdef AT91R40008
#include    "periph/power_saving/ps40008.h"
#endif

#ifdef AT91R40807
#include    "periph/power_saving/ps40800.h"
#endif

#ifdef AT91M42800
#include    "periph/power_saving/pmc42800.h"
#endif

#ifdef AT91M55800
#include    "periph/power_saving/apmc55800.h"
#endif

#ifdef AT91M63200
#include    "periph/power_saving/pmc63200.h"
#endif

#define     PS_MODE_IDLE            0x1
#define     PS_ALL_PERIPH_ACTIVE    0x2
#define     PS_ALL_PERIPH_INACTIVE  0x3

/* -----------------------*/
/* Function Prototyping   */
/* -----------------------*/
/* For AT91M40400, AT91M40800, AT91R40807, AT91R40008, AT91M42800, AT91M55800, AT91M63200 */
extern void at91_clock_set_mode ( u_int mode ) ;
extern u_int at91_clock_get_status ( u_int periph_id ) ;

/* For AT91M40800, AT91R40807, AT91R40008, AT91M42800, AT91M55800, AT91M63200 */
extern void at91_clock_open ( u_int periph_id ) ;
extern void at91_clock_close ( u_int periph_id ) ;

/* For AT91M42800, AT91M55800 */
extern u_int at91_clock_get_pll_status ( void ) ;
extern void at91_clock_generator_mode (u_int mode ) ;
extern u_int at91_clock_generator_state (void) ;

/* For AT91M55800 */
extern void at91_interrupt_enable (u_int source_enable) ;
extern void at91_interrupt_disable (u_int source_disable) ;
extern void at91_power_mode ( u_int mode ) ;
extern void at91_trig_cmd ( u_int cmd ) ;

#endif /* lib_power_save_h */
