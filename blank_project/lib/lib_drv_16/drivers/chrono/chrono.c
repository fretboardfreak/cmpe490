//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : chrono.c
//* Object              : Time counter chronometer function.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*-----------------------------------------------------------------------------

#include    "periph/stdc/lib_err.h"
#include    "periph/timer_counter/lib_tc.h"
#include    "drivers/chrono/chrono.h"

#define     CHRONO_TC_INIT      ( TC_CLKS_MCK2              |\
                                  TC_WAVE | TC_CPCSTOP      |\
                                  TC_ASWTRG_CLEAR_OUTPUT )
                                  
#define     CHRONO_TC0_MODE    ( TC_CLKS_MCK2               |\
                                 TC_WAVE                    |\
                                 TC_CPCTRG                  |\
                                 TC_ACPA_CLEAR_OUTPUT       |\
                                 TC_ACPC_SET_OUTPUT         |\
                                 TC_ASWTRG_SET_OUTPUT )

#define     CHRONO_TC1_MODE    ( TC_CLKS_XC1                |\
                                 TC_WAVE                    |\
                                 TC_CPCTRG                  |\
                                 TC_ACPA_CLEAR_OUTPUT       |\
                                 TC_ACPC_SET_OUTPUT         |\
                                 TC_ASWTRG_SET_OUTPUT )

#define     CHRONO_TC2_MODE    ( TC_CLKS_XC2                |\
                                 TC_WAVE                    |\
                                 TC_CPCTRG                  |\
                                 TC_ACPA_CLEAR_OUTPUT       |\
                                 TC_ACPC_SET_OUTPUT         |\
                                 TC_ASWTRG_SET_OUTPUT )

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chrono_open
//* Object              : Program the Timer Counter channels to use them as chronometer.
//* Input Parameters    : <chrono_pt> = Chronometer Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_chrono_open ( ChronoDesc *chrono_pt )
//* Begin
{   
    StructTCBlock   *tc_ptr = (StructTCBlock *)chrono_pt->tcb_desc->tc0_desc->tc_base ;
    u_int   x ;

    //* Open the Timer Counter channels
    at91_tc_open (chrono_pt->tcb_desc->tc0_desc, CHRONO_TC_INIT, TRUE, FALSE);
    at91_tc_open (chrono_pt->tcb_desc->tc1_desc, CHRONO_TC_INIT, TRUE, FALSE);
    at91_tc_open (chrono_pt->tcb_desc->tc2_desc, CHRONO_TC_INIT, TRUE, FALSE);
    //* Setup TIOA outputs to 0
    tc_ptr->TC[0].TC_RC = 2 ;
    tc_ptr->TC[0].TC_CCR = TC_CLKEN ;
    tc_ptr->TC[1].TC_RC = 2 ;
    tc_ptr->TC[1].TC_CCR = TC_CLKEN ;
    tc_ptr->TC[2].TC_RC = 2 ;
    tc_ptr->TC[2].TC_CCR = TC_CLKEN ;
    tc_ptr->TC_BCR = TC_SYNC ;

    //* Define the Timer Counter channel Chaining
    tc_ptr->TC_BMR = TC_TIOA0XC1 | TC_TIOA1XC2 ;

    //* Setup Timer 0 as millisecond tick
    tc_ptr->TC[0].TC_CMR = CHRONO_TC0_MODE ;
    x = (chrono_pt->frequency_kilohertz >> 1) ;
    tc_ptr->TC[0].TC_RC = x ;
    tc_ptr->TC[0].TC_RA = x >> 1 ;
    tc_ptr->TC[0].TC_CCR = TC_CLKEN ;

    //* Setup Timer 1 as second tick
    tc_ptr->TC[1].TC_CMR = CHRONO_TC1_MODE ;
    tc_ptr->TC[1].TC_RC = 1000 ;
    tc_ptr->TC[1].TC_RA = 500 ;
    tc_ptr->TC[1].TC_CCR = TC_CLKEN ;

    //* Setup Timer 2 as second counter
    tc_ptr->TC[2].TC_CMR = CHRONO_TC2_MODE ;
    tc_ptr->TC[2].TC_RC = 0xFFFF ;
    tc_ptr->TC[2].TC_CCR = TC_CLKEN ;

    //* Clear the status
    x = tc_ptr->TC[0].TC_SR ;
    x = tc_ptr->TC[1].TC_SR ;
    x = tc_ptr->TC[2].TC_SR ;

    //* Trig Timer2
    tc_ptr->TC[2].TC_CCR = TC_SWTRG ;
    //* Trig Timer1, set TIOA and effective clear timer 2
    tc_ptr->TC[1].TC_CCR = TC_SWTRG ;
    
    //* Waits for the Timer Counter channel 0 to be trigged

//* End
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chrono_trig_cmd
//* Object              : Start the Timer.
//* Input Parameters    : <chrono_desc> = Chronometer Descriptor pointer
//* Output Parameters   : number of microseconds 
//*-----------------------------------------------------------------------------
void at91_chrono_trig_cmd ( ChronoDesc *chrono_pt, u_int cmd )
{
    //* Depending on the command
    switch ( cmd ) 
    {
        //* Start the chronometer 
        case CHRONO_START:
            //* Trig succesively the 3 Timer Counter channels
            chrono_pt->tcb_desc->tc2_desc->tc_base->TC_CCR = TC_SWTRG ;
            //* Trig Timer1, set TIOA and effective clear timer 2
            chrono_pt->tcb_desc->tc1_desc->tc_base->TC_CCR = TC_SWTRG ;
            //* Trig Timer0, set TIOA and effective clear timer 1
            chrono_pt->tcb_desc->tc0_desc->tc_base->TC_CCR = TC_SWTRG ;
            break ;

        //* Stop the chronometer
        case CHRONO_STOP:
            //* Disable the clock of the Timer Counter channel 0
            chrono_pt->tcb_desc->tc0_desc->tc_base->TC_CCR = TC_CLKDIS ;
            break ;

        //* Restart the chronometer from where it has been stopped
        case CHRONO_CONTINUE:
            //* Re-enable the clock of the Timer Counter channel 0
            chrono_pt->tcb_desc->tc0_desc->tc_base->TC_CCR = TC_CLKEN ;
            break ;
        
        //* Unkonwn
        default :
            //* Run the AT91 Library Error Macro
            at91_error ("__FILE__","__LINE__") ;
    //* End Switch
    }
//* End
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chrono_read
//* Object              : Return elapsed time in microseconds since the last start
//* Input Parameters    : <chrono_desc> = Chronometer Descriptor pointer
//* Output Parameters   : number of microseconds 
//*-----------------------------------------------------------------------------
u_int at91_chrono_read ( ChronoDesc *chrono_pt )
//* Begin
{
    StructTCBlock   *tc_ptr = (StructTCBlock *)chrono_pt->tcb_desc->tc0_desc->tc_base ;
    u_int microsec ;

    //* Compute number of microseconds from counter values
    microsec = (int) ( tc_ptr->TC[0].TC_CV * 1000 / tc_ptr->TC[0].TC_RC ) ;
    microsec += ( tc_ptr->TC[1].TC_CV * 1000 ) ;
    microsec += ( tc_ptr->TC[2].TC_CV * 1000000 ) ;

    //* Return time
    return ( microsec ) ;
//* End
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chrono_close
//* Object              : Stop the Chronometer.
//* Input Parameters    : <chrono_desc> = Chronometer Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_chrono_close ( ChronoDesc *chrono_pt )
//* Begin
{
    //* Close the Timer Counter channels
    at91_tc_close (chrono_pt->tcb_desc->tc0_desc);
    at91_tc_close (chrono_pt->tcb_desc->tc1_desc);
    at91_tc_close (chrono_pt->tcb_desc->tc2_desc);                                   
//* End
}

