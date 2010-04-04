//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_ext_irq.c
//* Object              : External Interrupt Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//# 1.1 08/25/00 JCZ    : Update description pin
//*----------------------------------------------------------------------------

#include    "periph/aic/ext_irq/lib_ext_irq.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/pio/lib_pio.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_extirq_open
//* Object              : External Interrupt Set up
//* Input Parameters    : <irq_pt>      = External Interrupt Descriptor pointer
//*                     : <priority>    = Interrupt source priority
//*                     : <src_type>    = activation and sense of activation
//*                     : <handler_pt>  = address of the interrupt handler
//* Output Parameters   : none
//* Functions called    : at91_irq_close, at91_pio_close, at91_irq_open
//*----------------------------------------------------------------------------
void at91_extirq_open ( const ExtIrqDesc *irq_pt,
                        u_int priority,
                        u_int src_type,
                        TypeAICHandler handler_pt )
//* Begin
{
    //* description pin
    int mask = 0x1<<(irq_pt-> pin_irq) ;

    //* Make sure the interrupt source is inactive
    at91_irq_close ( irq_pt->source_id ) ;

    //* Define the corresponding IRQ line controlled by peripheral
    at91_pio_close ( irq_pt->pio_ctrl, mask ) ;

    //* Initialize the Interrupt Source on the AIC
    at91_irq_open ( (u_int) irq_pt->source_id,
                     priority,
                     src_type,
                     handler_pt ) ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_extirq_close
//* Object              : Remove an external interrupt
//* Input Parameters    : <irq_pt> = External Interrupt Descriptor pointer
//* Output Parameters   : none
//* Functions called    : at91_irq_close, at91_pio_open
//*----------------------------------------------------------------------------
void at91_extirq_close ( const ExtIrqDesc *irq_pt )
//* Begin
{
     int mask = 0x1<<(irq_pt-> pin_irq) ;
    //* Remove the interrupt source from the AIC
    at91_irq_close ( irq_pt->source_id ) ;

    //* Define the corresponding IRQ line controlled by peripheral
    at91_pio_open ( irq_pt->pio_ctrl, mask, RESET_PIO_CONF ) ;

//* End
}
