//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : pioa.h
//* Object              : Parallel I/O Controller A Header File
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef pioa_h
#define pioa_h

/* Port A */
#define PA0             (1<<0)
#define PA1             (1<<1)
#define PA2             (1<<2)
#define PA3             (1<<3)
#define PA4             (1<<4)
#define PA5             (1<<5)
#define PA6             (1<<6)
#define PA7             (1<<7)
#define PA8             (1<<8)
#define PA9             (1<<9)
#define PA10            (1<<10)
#define PA11            (1<<11)
#define PA12            (1<<12)
#define PA13            (1<<13)
#define PA14            (1<<14)
#define PA15            (1<<15)
#define PA16            (1<<16)
#define PA17            (1<<17)
#define PA18            (1<<18)
#define PA19            (1<<19)
#define PA20            (1<<20)
#define PA21            (1<<21)
#define PA22            (1<<22)
#define PA23            (1<<23)
#define PA24            (1<<24)
#define PA25            (1<<25)
#define PA26            (1<<26)
#define PA27            (1<<27)
#define PA28            (1<<28)
#define PA29            (1<<29)
#define PA30            (1<<30)
#define PA31            (1<<31)

extern void pioa_interrupt_handler ( void ) ;

#endif /* pioa_h */
