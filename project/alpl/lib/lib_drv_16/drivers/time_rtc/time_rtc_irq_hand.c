//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : time_rtc_irq_hand.c
//* Object              : time rtc irq C handler
//*
//* 1.0 24/10/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "time_rtc.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_c_handler
//* Object              : C handler interrup function called by the interrups
//*                       assembling routine
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_time_rtc_c_handler(TimeDescRtc *RTC_pt)
{
    u_int imr,status;
    //get curent interrupt
    imr = RTC_pt->rtc_desc->rtc_base->RTC_IMR;
    //* driver user defined
    //get curent interrupt
    status = RTC_pt->rtc_desc->rtc_base->RTC_SR;
    //* driver user defined
#ifndef PROJECT
    // user project must be define
    for (;;) {}
#endif

    //* Enable next interrpt
    RTC_pt->rtc_desc->rtc_base->RTC_SCR = imr;

}
//* End of file
