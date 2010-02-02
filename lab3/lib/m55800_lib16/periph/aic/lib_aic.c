//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_aic.c
//* Object              : Advanced Interrupt Controller Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/aic/aic.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/stdc/lib_err.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_default_irq_handler
//* Object              : Default Interrupt Handler
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
void at91_default_irq_handler ( void )
//* Begin
{
    //* Run the Error function
    at91_error (__FILE__, __LINE__) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_default_fiq_handler
//* Object              : Default FIQ Handler
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
void at91_default_fiq_handler ( void )
//* Begin
{
    //* Run the Error function
    at91_error (__FILE__, __LINE__) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_irq_open
//* Object              : Interrupt Handler Initialization
//* Input Parameters    : <irq_id>      = interrupt number to initialize
//*                     : <priority>    = priority to give to the interrupt
//*                     : <src_type>    = activation and sense of activation
//*                     : <handler_pt>  = address of the interrupt handler
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_irq_open ( u_int irq_id,
                     u_int priority,
                     u_int src_type,
                     TypeAICHandler handler_pt )
//* Begin
{
    u_int       mask ;
    mask = 0x1 << irq_id ;
    //* Disable the interrupt on the interrupt controller
    AIC_BASE->AIC_IDCR = mask ;
    //* Save the interrupt handler routine pointer and the interrupt priority
    AIC_BASE->AIC_SVR[irq_id] = (u_int) handler_pt ;
    //* Store the Source Mode Register
    AIC_BASE->AIC_SMR[irq_id] = src_type | priority  ;
    //* Clear the interrupt on the interrupt controller
    AIC_BASE->AIC_ICCR = mask ;
    //* Enable the interrupt on the interrupt controller
    AIC_BASE->AIC_IECR = mask ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_irq_close
//* Object              : Disable Interrupt Source
//* Input Parameters    : <irq_id> = Interrupt Source Identifier
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_irq_close ( u_int irq_id )
//* Begin
{
    u_int       mask ;
    mask = 0x1 << irq_id ;
    //* Disable the interrupt on the interrupt controller
    AIC_BASE->AIC_IDCR = mask ;
    //* Clear the interrupt on the Interrupt Controller ( if one is pending )
    AIC_BASE->AIC_ICCR = mask ;
    //* If removing the FIQ
    if ( irq_id == 0 )
        //* Default FIQ vector to <no_handler_fiq>
        AIC_BASE->AIC_SVR[0] = (u_int) at91_default_fiq_handler ;
    //* Else
    else
        //* Default IRQ vector to <no_handler_irq>
        AIC_BASE->AIC_SVR[irq_id] = (u_int) at91_default_irq_handler ;
    //* EndIf
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_irq_trig_cmd
//* Object              : Interrupt Controller Command Trigger
//* Input Parameters    : <irq_id> = Interrupt Identifier
//*                     : <mask>   = Interrupt Source Mask Identifier
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_irq_trig_cmd ( u_int irq_id, u_int mask  )
//* Begin
{
    //* If Mask is null
    if ( mask == 0 )
        //* Set the interrupt on the interrupt controller
        AIC_BASE->AIC_ISCR = (1 << irq_id) ;
    //* Else
    else
        //* Set the interrupt on the interrupt controller
        AIC_BASE->AIC_ISCR = mask ;
    //* EndIf
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_irq_get_status
//* Object              : Get current interrupt source identifier
//* Input Parameters    : None
//* Output Parameters   : Source identifier of the current interrupt
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_irq_get_status ( void )
//* Begin
{
    //* Return AIC_ISR
    return ( AIC_BASE->AIC_ISR ) ;
//* End
}
