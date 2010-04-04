//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : wait.c
//* Object              : Wait Fucntions.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/timer_counter/lib_tc.h"
#include    "periph/power_saving/lib_power_save.h"
#include    "drivers/wait/wait.h"
#include    "periph/stdc/lib_err.h"

extern void wait_irq ( void ) ;

//*----------------------------------------------------------------------------
//* Function Name       : at91_tc_wait_open
//* Object              : Stop the ARM core during <microsec> us
//* Input Parameters    : <wait_desc> = Wait Descriptor pointer.
//* Output Parameters   : None
//* Functions called    : 
//*----------------------------------------------------------------------------
void at91_wait_open ( WaitDesc *wait_desc )
//* Begin
{
    u_int   clock_select ;
    u_int   regs[4] ;

    switch ( wait_desc->mode )
    {
        case WAIT_DELAY :
        case WAIT_NEXT_EVENT_MAX_DELAY :
            //* Startup the Timer Counter Channel
            at91_tc_open ( wait_desc->tc_desc, TC_WAVE | TC_CPCDIS, FALSE, FALSE) ;
            //* Compute and Setup register C for period depending on master clock
            regs[RA] = 0 ;
            regs[RC] = wait_desc->period ;
            //* Setup registers according master clock and required timings 
            at91_tc_compute_microsec ( &regs[RC], &clock_select, wait_desc->mcki_khz ) ;
            regs[RB] = regs[RC] ;
            at91_tc_set_mode (wait_desc->tc_desc, clock_select, 1) ;
            at91_tc_write (wait_desc->tc_desc, regs ) ;
            //* Open the interrupt on the AIC
            at91_irq_open ( wait_desc->tc_desc->periph_id, 7, AIC_SRCTYPE_INT_EDGE_TRIGGERED, wait_desc->handler ) ;
            //* Enable the RC Compare interrupt
            wait_desc->tc_desc->tc_base->TC_IER = TC_CPCS ;
            //* Trig the timer
            at91_tc_trig_cmd ( wait_desc->tc_desc, TC_TRIG_CHANNEL ) ;
            break ;
    }
    
    switch ( wait_desc->mode )
    {
        case WAIT_DELAY :
        case WAIT_NEXT_EVENT :
            //* Enter Idle Mode
            at91_clock_set_mode ( PS_MODE_IDLE ) ;
            break ;

        case WAIT_NEXT_EVENT_MAX_DELAY :
            //* While the Timer Counter hasn't reached the end
            while (( wait_desc->tc_desc->tc_base->TC_SR & TC_CPCS ) == 0 ) 
                //* Enter Idle Mode
                at91_clock_set_mode ( PS_MODE_IDLE ) ;
            break ;         
    }

    switch ( wait_desc->mode )
    {
        case WAIT_DELAY :
        case WAIT_NEXT_EVENT_MAX_DELAY :
            //* Close the interrupt on the AIC
            at91_irq_close ( wait_desc->tc_desc->periph_id ) ;
            //* Close the Timer Counter Channel
            at91_tc_close ( wait_desc->tc_desc );
            break ;
    }
//* End
}

