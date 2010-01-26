//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : time_rtc_tools.c
//* Object              : Real Time Clock driver management
//*
//* 1.0 11/09/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "time_rtc.h"
#include "periph/timer_counter/lib_tc.h"
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

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_mcki_round
//* Object              : Calculate the MCKI
//* Input Parameters    : <RTC_pt> time rtc descriptor
//*                       <TC_pt>  timer descriptor
//* Output Parameters   : MCKI
//*----------------------------------------------------------------------------
u_int at91_time_rtc_mcki_round( TimeDescRtc *RTC_pt,const TCDesc *TC_pt )
//* Begin
{
    u_int mcki;
    //* Open timer for counting
    at91_tc_open( TC_pt, (TC_WAVE|TC_CLKS_MCK1024), FALSE, FALSE ) ;

    //* Clear the seconde status bit
    RTC_pt->rtc_desc->rtc_base->RTC_SCR = RTC_SEC;

    //* wait end of seconde
    while(((volatile int)RTC_pt->rtc_desc->rtc_base->RTC_SR & RTC_SEC) != RTC_SEC) {}

    //* -- Start timer by Software Trigger
    //* -- generates a software trigger simultaneously for each of the channels.
    at91_tc_trig_cmd ( TC_pt, TC_TRIG_CHANNEL ) ;

    //* Clear the seconde status bit
    RTC_pt->rtc_desc->rtc_base->RTC_SCR = RTC_SEC;

    //* wait end of seconde
    while(((volatile int)RTC_pt->rtc_desc->rtc_base->RTC_SR & RTC_SEC) != RTC_SEC) {}

    //* stop the timer
    TC_pt->tc_base->TC_CCR = TC_CLKDIS;
    //* Disable the clock and reset the timer
    mcki = TC_pt->tc_base->TC_CV;
    mcki = mcki *1024;
    // Close the timer
    at91_tc_close( TC_pt);

    return mcki;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_mcki
//* Object              : Calculate the MCKI
//* Input Parameters    : <RTC_pt> time rtc descriptor
//*                       <TC_pt>  timer descriptor
//* Output Parameters   : MCKI
//*----------------------------------------------------------------------------
u_int at91_time_rtc_mcki( TimeDescRtc *RTC_pt,const TCBlockDesc *TC_pt )
//* Begin
{

    u_int mcki;
    StructTCBlock   *tc_ptr = (StructTCBlock *)TC_pt->tc0_desc->tc_base ;

    //* Open timer for counting
    //* Open the Timer Counter channels
    at91_tc_open (TC_pt->tc0_desc, CHRONO_TC_INIT, TRUE, FALSE);
    at91_tc_open (TC_pt->tc1_desc, CHRONO_TC_INIT, TRUE, FALSE);
    at91_tc_open (TC_pt->tc2_desc, CHRONO_TC_INIT, TRUE, FALSE);

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

    //* Setup Timer 0
    tc_ptr->TC[0].TC_CMR = CHRONO_TC0_MODE ;
    tc_ptr->TC[0].TC_RC = 1000 ;
    tc_ptr->TC[0].TC_RA = 500 ;
    tc_ptr->TC[0].TC_CCR = TC_CLKEN ;

    //* Setup Timer 1
    tc_ptr->TC[1].TC_CMR = CHRONO_TC1_MODE ;
    tc_ptr->TC[1].TC_RC = 1000 ;
    tc_ptr->TC[1].TC_RA = 500 ;
    tc_ptr->TC[1].TC_CCR = TC_CLKEN ;

    //* Setup Timer 2
    tc_ptr->TC[2].TC_CMR = CHRONO_TC2_MODE ;
    tc_ptr->TC[2].TC_RC = 0xFFFF ;
    tc_ptr->TC[2].TC_CCR = TC_CLKEN ;

    //* Clear the status
    mcki = tc_ptr->TC[0].TC_SR ;
    mcki = tc_ptr->TC[1].TC_SR ;
    mcki = tc_ptr->TC[2].TC_SR ;

    //* Trig Timer2
    tc_ptr->TC[2].TC_CCR = TC_SWTRG ;

    //* Trig Timer1, set TIOA and effective clear timer 2
    tc_ptr->TC[1].TC_CCR = TC_SWTRG ;

    //* Clear the seconde status bit
    RTC_pt->rtc_desc->rtc_base->RTC_SCR = RTC_SEC;

    //* wait end of seconde
    while(((volatile int)RTC_pt->rtc_desc->rtc_base->RTC_SR & RTC_SEC) != RTC_SEC) {}

    //* -- Start timer by Software Trigger
    //* -- generates a software trigger simultaneously for each of the channels.
    //* Trig succesively the 3 Timer Counter channels
    TC_pt->tc2_desc->tc_base->TC_CCR = TC_SWTRG ;
    //* Trig Timer1, set TIOA and effective clear timer 2
    TC_pt->tc1_desc->tc_base->TC_CCR = TC_SWTRG ;
    //* Trig Timer0, set TIOA and effective clear timer 1
    TC_pt->tc0_desc->tc_base->TC_CCR = TC_SWTRG ;

    //* Clear the seconde status bit
    RTC_pt->rtc_desc->rtc_base->RTC_SCR = RTC_SEC;

    //* wait end of seconde
    while(((volatile int)RTC_pt->rtc_desc->rtc_base->RTC_SR & RTC_SEC) != RTC_SEC) {}
    //* stop the timer
    //* Disable the clock of the Timer Counter channel 0
    TC_pt->tc0_desc->tc_base->TC_CCR = TC_CLKDIS ;

    //* Compute number of microseconds from counter values
    mcki =  tc_ptr->TC[0].TC_CV  ;
    mcki += ( tc_ptr->TC[1].TC_CV * 1000 ) ;
    mcki += ( tc_ptr->TC[2].TC_CV * 1000000 ) ;
    // TIMER CLOCK MCKI / 2
    mcki = mcki*2;

    //* Disable the clock and reset the timer
    // Close the timer
    at91_tc_close (TC_pt->tc0_desc);
    at91_tc_close (TC_pt->tc1_desc);
    at91_tc_close (TC_pt->tc2_desc);

    return mcki;
//* End
}
//* End of file
