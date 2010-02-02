//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_ext_irq.h
//* Object              : External Interrupt Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_ext_irq_h
#define lib_ext_irq_h

#include    "periph/aic/aic.h"
#include    "periph/pio/lib_pio.h"

/* External Interrupt Sources Descriptor */
typedef struct
{
    const PioCtrlDesc   *pio_ctrl ;     /* PIO Stucture definition */
    u_char              source_id ;     /* AIC interrupt source Identifier */
    u_char              pin_irq ;       /* internal PIO pin number */
} ExtIrqDesc ;

extern void at91_extirq_open  ( const ExtIrqDesc *irq_pt,
                              u_int priority,
                              u_int src_type,
                              TypeAICHandler handler_pt ) ;
extern void at91_extirq_close ( const ExtIrqDesc *irq_pt ) ;

#endif /* lib_ext_irq_h */
