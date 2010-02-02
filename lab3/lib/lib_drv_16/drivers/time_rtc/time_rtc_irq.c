//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : time_rtc_irq.c
//* Object              : Time RTC driver irq management
//*
//* 1.0 11/09/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "time_rtc.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_open_irq
//* Object              : Open RTC interrupt
//* Input Parameters    : <RTC_pt> time rtc descriptor
//*                     : Timer descriptor , compter value , mcki divisor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_time_rtc_open_irq( TimeDescRtc *RTC_pt,u_int rtc_mode,u_int level)
//* Begin
{
    //* -- Open RTC
    at91_rtc_open (RTC_pt->rtc_desc);

    //* Open Irq
    at91_irq_open ( RTC_pt->rtc_desc->periph_id, level, AIC_SRCTYPE_INT_EDGE_TRIGGERED, RTC_pt->AsmRtcHandler ) ;

    //* Enable the interrup
    RTC_pt->rtc_desc->rtc_base->RTC_IER = rtc_mode;


//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_close_irq
//* Object              : Stop the RTC irq function
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_time_rtc_close_irq(TimeDescRtc *RTC_pt)
//* Begin
{
    //* Close interrupt
    at91_irq_close ( RTC_pt->rtc_desc->periph_id);
    // disable all interrup
    RTC_pt->rtc_desc->rtc_base->RTC_IDR = -1;

//* End
}
//* End of file
