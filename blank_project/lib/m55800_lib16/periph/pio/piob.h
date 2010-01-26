//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : piob.h
//* Object              : Parallel I/O Controller B Header File
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef piob_h
#define piob_h

/* Port B */
#define PB0             (1<<0)
#define PB1             (1<<1)
#define PB2             (1<<2)
#define PB3             (1<<3)
#define PB4             (1<<4)
#define PB5             (1<<5)
#define PB6             (1<<6)
#define PB7             (1<<7)
#define PB8             (1<<8)
#define PB9             (1<<9)
#define PB10            (1<<10)
#define PB11            (1<<11)
#define PB12            (1<<12)
#define PB13            (1<<13)
#define PB14            (1<<14)
#define PB15            (1<<15)
#define PB16            (1<<16)
#define PB17            (1<<17)
#define PB18            (1<<18)
#define PB19            (1<<19)
#define PB20            (1<<20)
#define PB21            (1<<21)
#define PB22            (1<<22)
#define PB23            (1<<23)
#define PB24            (1<<24)
#define PB25            (1<<25)
#define PB26            (1<<26)
#define PB27            (1<<27)
#define PB28            (1<<28)
#define PB29            (1<<29)
#define PB30            (1<<30)
#define PB31            (1<<31)

extern void piob_interrupt_handler ( void ) ;

#endif /* piob_h */
