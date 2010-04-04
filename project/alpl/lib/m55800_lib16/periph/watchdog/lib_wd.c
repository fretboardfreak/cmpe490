//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_wd.c
//* Object              : Watch Dog Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/watchdog/wd.h"
#include    "periph/watchdog/lib_wd.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/stdc/lib_err.h"

TypeWDHandler       SaveWDHandler ;

//*----------------------------------------------------------------------------
//* Function Name       : at91_no_handler_wd
//* Object              : Default Watch Dog Interrupt Handler
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : at91_error
//*----------------------------------------------------------------------------
static void at91_no_handler_wd ( void )
//* Begin
{
    at91_error ( __FILE__, __LINE__ ) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_watch_dog_init
//* Object              : Initialize The Watch Dog.
//* Input Parameters    : <mode>  = the signals to generate
//*                     : <clock> = the clock selected
//*                     : <count> = the value preloaded in the counter
//*                     : <handler_add> = Handler Address
//* Output Parameters   : none
//* Functions called    : at91_irq_open, at91_irq_close
//*----------------------------------------------------------------------------
void at91_watch_dog_init ( const WDDesc *wd_pt,
                           u_int mode,
                           u_int clock,
                           u_int count,
                           TypeWDHandler handler_add )
//* Begin
{
    //* Disable the Watch Dog
    wd_pt->WDBase->WD_OMR = WD_OKEY ;

    //* If Watch Dog initialized to generate an interrupt
    if (( mode & WD_IRQEN ) != 0 )
    {
        //* Save the address of the interrupt handler
        SaveWDHandler = handler_add ;

        //* Initialize the Interrupt Controller
        at91_irq_open ( wd_pt->PeriphId ,
                         7 ,
                         AIC_SRCTYPE_INT_EDGE_TRIGGERED ,
                         at91_watch_dog_interrupt_handler ) ;
    }
    //* Else
    else
    {
        //* Save the default Watch dog interrupt handler address
        SaveWDHandler = at91_no_handler_wd ;

        //* Disable the Watch Dog Interrupt on the Interrupt Controller
        at91_irq_close ( wd_pt->PeriphId ) ;
    //* EndIf
    }

    //* Store the Clock Mode Register
    wd_pt->WDBase->WD_CMR = WD_CKEY | (((count & 0x0000F000) >> 12) << 2) | clock ;

    //* Restart the Watchdog
    wd_pt->WDBase->WD_CR = WD_RSTKEY ;

    //* Store the Overflow Mode Register
    wd_pt->WDBase->WD_OMR = WD_OKEY | mode | WD_WDEN ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_watch_dog_rearm
//* Object              : Restart the Watch Dog counter.
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_watch_dog_rearm ( const WDDesc *wd_pt )
//* Begin
{
    //* Restart the Watch Dog
    wd_pt->WDBase->WD_CR = WD_RSTKEY ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_watch_dog_disable
//* Object              : Stop the Watch Dog counter.
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : at91_irq_close
//*----------------------------------------------------------------------------
void at91_watch_dog_disable ( const WDDesc *wd_pt )
//* Begin
{
    //* Restart the Watch Dog
    wd_pt->WDBase->WD_CR = WD_RSTKEY ;

    //* Disable the Watch Dog
    wd_pt->WDBase->WD_OMR = WD_OKEY ;

    //* Disable the Watch Dog Interrupt on the Interrupt Controller
    at91_irq_close ( wd_pt->PeriphId ) ;

    //* Define no Watch dog interrupt handler
    SaveWDHandler = at91_no_handler_wd ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_watch_dog_read_status
//* Object              : Read if Watch Dog counter overflowed.
//* Input Parameters    : none
//* Output Parameters   : the value of the Status Register
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_watch_dog_read_status ( const WDDesc *wd_pt )
//* Begin
{
    //* Return the Status Register of the Watch Dog
    return ( wd_pt->WDBase->WD_SR ) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_watch_dog_init_test
//* Object              : Initialize The Watch Dog with the test function.
//* Input Parameters    : <mode>        = the signals to generate
//*                     : <clock>       = the clock selected
//*                     : <count>       = the value preloaded in the counter
//*                     : <handler_add> = Handler Address
//* Output Parameters   : none
//* Functions called    : at91_irq_open, at91_irq_close
//* Comments            : Warning, this function is not documented in the data
//*                       sheet and is only present for test purpose.
//*----------------------------------------------------------------------------
void at91_watch_dog_init_test ( WDDesc *wd_pt,
                                u_int mode,
                                u_int clock,
                                u_int count,
                                TypeWDHandler handler_add )
//* Begin
{
    at91_reg    *pt_testreg = (at91_reg *) 0xFFF00014;

    //* Disable the Watch Dog
    wd_pt->WDBase->WD_OMR = WD_OKEY ;

    //* If Watch Dog initialized to generate an interrupt
    if (( mode & WD_IRQEN ) != 0 )
    {
        //* Save the address of the interrupt handler
        SaveWDHandler = handler_add ;

        //* Initialize the Interrupt Controller
        at91_irq_open ( wd_pt->PeriphId,
                         7,
                         AIC_SRCTYPE_INT_EDGE_TRIGGERED,
                         at91_watch_dog_interrupt_handler ) ;
    }
    //* Else
    else
    {
        //* Save the default Watch dog interrupt handler address
        SaveWDHandler = at91_no_handler_wd ;

        //* Disable the Watch Dog Interrupt on the Interrupt Controller
        at91_irq_close ( wd_pt->PeriphId ) ;
    //* EndIf
    }

    //* Enable the Test Mode of the Chip
    *pt_testreg = WD_TMRKEY | WD_TESTEN ;

    //* Initialize the preload value of the watch dog counter
    wd_pt->WDBase->WD_TLR = count ;

    //* Restart the Watch Dog
    wd_pt->WDBase->WD_CR = WD_RSTKEY ;

    //* Store the Clock Mode Register
    wd_pt->WDBase->WD_CMR = WD_CKEY | clock ;

    //* Store the Overflow Mode Register
    wd_pt->WDBase->WD_OMR = WD_OKEY | mode | WD_WDEN ;

//* End
}
