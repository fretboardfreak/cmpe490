//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : lib_ebi.h
//* Object              : External Bus Interface Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*-----------------------------------------------------------------------------

#ifndef     lib_ebi_h
#define     lib_ebi_h


#include    "periph/stdc/std_c.h"
#include    "periph/ebi/ebi.h"

typedef struct
{
    u_int       base_address ;
    u_char      cs_id ;
    u_char      wait_state ;
    u_char      data_float ;
    u_char      page_size ;
    u_char      byte_access_type ;
    u_char      data_bus_width ;
} ChipSelectDesc ;

#define     CS_8_BIT_BUS    0x1
#define     CS_16_BIT_BUS   0x0

#define     CS_1_MBYTE      0x1
#define     CS_4_MBYTE      0x2
#define     CS_16_MBYTE     0x3
#define     CS_64_MBYTE     0x4

#define     CS_BYTE_WRITE   0x0
#define     CS_BYTE_SELECT  0x1

/* Function Prototyping */
extern void at91_chip_select_open ( ChipSelectDesc *cs_desc ) ;
extern void at91_chip_select_close ( ChipSelectDesc *cs_desc ) ;
extern u_int at91_chip_select_get_status ( ChipSelectDesc *cs_desc ) ;

#endif     /* lib_ebi_h */
