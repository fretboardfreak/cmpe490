//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_rtc.c
//* Object              : Real Time Clock Library File
//*
//* 1.0 06/09/00  JPP    : Creation
//*----------------------------------------------------------------------------

#include "periph/rtc/lib_rtc.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_close
//* Object              : close by stop Real Time Clock count
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_rtc_close ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Stop the Real Time Clock Mode Register
     rtc_pt->rtc_base->RTC_CR |= (RTC_UPDTIM |RTC_UPDCAL) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_open
//* Object              : open Real Time Clock count
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_rtc_open ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Set the Real Time Clock Mode Register
     rtc_pt->rtc_base->RTC_CR  &= ~(RTC_UPDTIM |RTC_UPDCAL) ;

     //* clear status register
     rtc_pt->rtc_base->RTC_SCR = RTC_ACKUPD | RTC_ALARM | RTC_SEC | RTC_TIMEV | RTC_CALEV;

     //* clear all interrup
     rtc_pt->rtc_base->RTC_IDR = RTC_ACKUPD | RTC_ALARM | RTC_SEC | RTC_TIMEV | RTC_CALEV;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_event
//* Object              : Read the event register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
u_int at91_rtc_get_event ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Read the event register
      return ( rtc_pt->rtc_base->RTC_CR ) ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_event
//* Object              : set the event in Mode Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//*                       <mode> new event value
//* Output Parameters   : none

//*----------------------------------------------------------------------------
void at91_rtc_set_event ( const RtcDesc *rtc_pt, u_int mode )
//* Begin
{
        u_int tmp;
        //*  set the event in Mode Register
        // Get the update value
        tmp = rtc_pt->rtc_base->RTC_CR & RTC_UPD_MASQ ;
        // Update othr field
        tmp |= mode;
        rtc_pt->rtc_base->RTC_CR = tmp ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_24
//* Object              : Set Real Time Clock Mode Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//*                     : <mode> = set/clear bits in the mode register
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_rtc_set_24 ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Set the Real Time Clock Mode Register
     rtc_pt->rtc_base->RTC_MR = RTC_24_HRMOD ;
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_clear_24
//* Object              : Set Real Time Clock Mode Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//*                     : <mode> = set/clear bits in the mode register
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_rtc_clear_24 ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Set the Real Time Clock Mode Register
     rtc_pt->rtc_base->RTC_MR = RTC_12_HRMOD ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_24
//* Object              : Read  Real Time Clock Mode Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode>  1 => 24 h 0 => AM / PM
//*----------------------------------------------------------------------------
u_int at91_rtc_get_24 ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Mode Register
    return ( rtc_pt->rtc_base->RTC_MR );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_time
//* Object              : Set Real Time Clock Time Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <sec> = second in BCD
//*                       <min> = minute in BCD
//*                       <hour> = hour in BCD
//*                       <ampm> = 0 for AM or 1 for PM
//*----------------------------------------------------------------------------
void at91_rtc_set_time ( const RtcDesc *rtc_pt, u_char sec, u_char min, u_char hour, u_char ampm )
//* Begin
{
    //* clear status
    rtc_pt->rtc_base->RTC_SCR = RTC_ACKUPD;

    //* Stop the RTC
    rtc_pt->rtc_base->RTC_CR |= RTC_UPDTIM ;

    //* bit RTC_ACKUPD
    while(((volatile int)rtc_pt->rtc_base->RTC_SR & RTC_ACKUPD) != RTC_ACKUPD) {}

    //* Set the Real Time Clock Time Register
    rtc_pt->rtc_base->RTC_TIMR = sec | ( min << RTC_MIN) | (hour <<RTC_HOUR) | ( ampm << RTC_AMPM);

    //* Restart the RTC
    rtc_pt->rtc_base->RTC_CR &= ~(RTC_UPDTIM) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_time
//* Object              : Read Real Time Clock Time Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode> = tim value
//*----------------------------------------------------------------------------
u_int at91_rtc_get_time ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Time Register
     return ( rtc_pt->rtc_base->RTC_TIMR );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_calendar
//* Object              : Set Real Time Clock Calendar Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <cent> = century in BCD (19-20)
//*                       <year> = year in BCD (00-99)
//*                       <month> = month in BCD (01-12)
//*                       <day> = day in BCD (01-07)
//*                       <date> = date in BCD (01-31))
//*----------------------------------------------------------------------------
void at91_rtc_set_calendar ( const RtcDesc *rtc_pt, u_char cent, u_char year, u_char month, u_char day, u_char date )
//* Begin
{
    //* clear status
    rtc_pt->rtc_base->RTC_SCR = RTC_ACKUPD;

    //* Stop the RTC
    rtc_pt->rtc_base->RTC_CR |= RTC_UPDCAL ;

    //* bit RTC_ACKUPD
    while(((volatile int)rtc_pt->rtc_base->RTC_SR & RTC_ACKUPD) != RTC_ACKUPD) {}

    //* Set the Real Time Clock Calendar Register
    rtc_pt->rtc_base->RTC_CALR = cent | ( year << RTC_YEAR) | (month <<RTC_MONTH) | ( day << RTC_DAY)| ( date << RTC_DATE);

    //* Restart the RTC
    rtc_pt->rtc_base->RTC_CR &= ~(RTC_UPDCAL) ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_calendar
//* Object              : Read Real Time Clock Calendar Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode> = Calendar Register
//*----------------------------------------------------------------------------
u_int at91_rtc_get_calendar ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Calendar Register
     return ( rtc_pt->rtc_base->RTC_CALR );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_time_alarm
//* Object              : Set Real Time Clock Time Alarm Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <sec> = second in BCD
//*                       <min> = minute in BCD
//*                       <hour> = hour in BCD
//*                       <ampm> = 0 for AM or 1 for PM
//*                       <mode> = Alarm type sec,  mimute, hours
//*----------------------------------------------------------------------------
void at91_rtc_set_time_alarm ( const RtcDesc *rtc_pt, u_char sec, u_char min, u_char hour, u_char ampm,u_int mode )
//* Begin
{
     //* Set the Real Time Clock Time Alarm Register
    rtc_pt->rtc_base->RTC_TAR = sec | ( min << RTC_MIN) | (hour <<RTC_HOUR) | ( ampm << RTC_AMPM)|mode;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_time_alarm
//* Object              : Read Real Time Clock Time Alarm Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode> = set/clear bits in the mode register
//*----------------------------------------------------------------------------
u_int at91_rtc_get_time_alarm ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Time Alarm Register
     return ( rtc_pt->rtc_base->RTC_TAR );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_set_cal_alarm
//* Object              : Set Real Time Clock Calendar Alarm Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <month> = month in BCD (01-12)
//*                       <date> = date in BCD (01-31))
//*----------------------------------------------------------------------------
void at91_rtc_set_cal_alarm ( const RtcDesc *rtc_pt,u_char month, u_char date, u_int mode )
//* Begin
{
     //* Set the Real Time Clock Calendar Alarm Register
    rtc_pt->rtc_base->RTC_CAR =  (month <<RTC_MONTH) |( date << RTC_DATE) | mode ;
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_cal_alarm
//* Object              : Read Real Time Clock Calendar Alarm Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode> = set/clear bits in the mode register
//*----------------------------------------------------------------------------
u_int at91_rtc_get_cal_alarm ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Calendar Alarm Register
     return ( rtc_pt->rtc_base->RTC_CAR );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_get_status
//* Object              : Read Real Time Clock  Status Register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : <mode> = set/clear bits in the mode register
//*----------------------------------------------------------------------------
u_int at91_rtc_get_status ( const RtcDesc *rtc_pt )
//* Begin
{
     //* Return the Real Time Clock Status Register
     return ( rtc_pt->rtc_base->RTC_SR );
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_rtc_clear_status
//* Object              : Clear status register
//* Input Parameters    : <rtc_desc> = RTC Descriptor pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_rtc_clear_status ( const RtcDesc *rtc_pt )
//* Begin
{
     //* clear status register
     rtc_pt->rtc_base->RTC_SCR = RTC_ACKUPD | RTC_ALARM | RTC_SEC | RTC_TIMEV | RTC_CALEV;
//* End
}
//* End of file
