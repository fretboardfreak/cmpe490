//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_sf.h
//* Object              : Special Function Library Header File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_sf_h
#define lib_sf_h

#include    "periph/special_function/sf.h"

extern u_int at91_read_chip_id ( u_int extension ) ;
extern void  at91_set_protect_mode ( u_int flag ) ;

#endif /* lib_sf_h */
