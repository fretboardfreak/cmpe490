//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : capture.h
//* Object              : Capture Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef capture_h
#define capture_h

#define MODE_TIOA_LOW       TC_ETRGEDG_FALLING_EDGE   |\
                            TC_ABETRG_TIOA            |\
                            TC_LDRA_RISING_EDGE       |\
                            TC_LDRB_FALLING_EDGE      |\
                            TC_LDBDIS


#define MODE_TIOA_HIGH      TC_ETRGEDG_RISING_EDGE    |\
                            TC_ABETRG_TIOA            |\
                            TC_LDRA_FALLING_EDGE      |\
                            TC_LDRB_RISING_EDGE       |\
                            TC_LDBDIS


#define MODE_TIOA_PERIOD    TC_ETRGEDG_RISING_EDGE    |\
                            TC_ABETRG_TIOA            |\
                            TC_LDRA_RISING_EDGE       |\
                            TC_LDRB_FALLING_EDGE      |\
                            TC_LDBDIS

#include    "periph/timer_counter/lib_tc.h"

extern void at91_capture_open ( const TCDesc *tc_pt, u_int mode );
extern void at91_capture_close ( const TCDesc *tc_pt );
extern u_int at91_capture_read ( const TCDesc *tc_pt );
extern u_int at91_capture_get_status ( const TCDesc *tc_pt );


#endif /* capture_h */
