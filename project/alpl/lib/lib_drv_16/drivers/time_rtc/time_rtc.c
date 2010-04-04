//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : time_rtc.c
//* Object              : Real Time Clock driver management
//*
//* 1.0 07/09/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include "time_rtc.h"

#include <stdio.h>

//*----------------------------------------------------------------------------
//* Function Name       : at91_bcd_int
//* Object              : Translate bcd to unsigned int
//* Input Parameters    : <bcd> BCD value
//* Output Parameters   : integer value
//*----------------------------------------------------------------------------
u_int at91_bcd_int( u_char bcd)
//* Begin
{
     return ( (bcd & 0x0F) + (((bcd & 0xF0)>>4) *10));
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_int_bcd
//* Object              : Translate int to bcd
//* Input Parameters    : <value> in int
//* Output Parameters   : <bcd> BCD value
//*----------------------------------------------------------------------------
u_char at91_int_bcd (u_int value)
//* Begin
{
    char tmp[3];

    sprintf(tmp,"%02d",value);
    return ((tmp[1] & 0x0F) | ((tmp[0] & 0x0F)<<4));
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_open
//* Object              : Open the rtc
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_time_rtc_open( TimeDescRtc *RTC_pt)
//* Begin
{
    //* -- Open Real Time Clock
    at91_rtc_open(RTC_pt->rtc_desc);

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc
//* Object              : Close the RTC
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_time_rtc_close(TimeDescRtc *RTC_pt)
//* Begin
{
    //* -- Close Real Time Clock
        at91_rtc_close(RTC_pt->rtc_desc);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_read
//* Object              : Read rtc value
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : update descriptor
//*----------------------------------------------------------------------------
void at91_time_rtc_read(TimeDescRtc *RTC_pt)
//* Begin
{
    u_int time;
    //* get time value
    time = at91_rtc_get_time (RTC_pt->rtc_desc);
    RTC_pt->time_bcd.sec = time & RTC_MASQ_SEC ;
    RTC_pt->time_bcd.min = (time & RTC_MASQ_MIN)>>RTC_MIN ;
    RTC_pt->time_bcd.hour = (time & RTC_MASQ_HOUR)>>RTC_HOUR ;
    RTC_pt->time_bcd.ampm = (time & RTC_MASQ_AMPM)>>RTC_AMPM ;
    //* get calendar value
    time = at91_rtc_get_calendar (RTC_pt->rtc_desc);
    RTC_pt->time_bcd.day = (time & RTC_MASQ_DAY)>>RTC_DAY ;
    RTC_pt->time_bcd.month = (time & RTC_MASQ_MONTH)>>RTC_MONTH ;
    RTC_pt->time_bcd.year = (time & RTC_MASQ_YEAR)>>RTC_YEAR ;
    RTC_pt->time_bcd.cent = (time & RTC_MASQ_CENT)>>RTC_CENT;
    RTC_pt->time_bcd.date = (time & RTC_MASQ_DATE)>>RTC_DATE ;
    // translate bcd to int
    RTC_pt->time_int.sec = at91_bcd_int( RTC_pt->time_bcd.sec);
    RTC_pt->time_int.min = at91_bcd_int( RTC_pt->time_bcd.min);
    RTC_pt->time_int.hour = at91_bcd_int( RTC_pt->time_bcd.hour);
    RTC_pt->time_int.ampm = at91_bcd_int( RTC_pt->time_bcd.ampm);
    RTC_pt->time_int.day = at91_bcd_int( RTC_pt->time_bcd.day);
    RTC_pt->time_int.month = at91_bcd_int( RTC_pt->time_bcd.month);
    RTC_pt->time_int.year = at91_bcd_int( RTC_pt->time_bcd.year);
    RTC_pt->time_int.cent = at91_bcd_int( RTC_pt->time_bcd.cent);
    RTC_pt->time_int.date = at91_bcd_int( RTC_pt->time_bcd.date);

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_int_bdc
//* Object              : Translate the rrtc descriptor value int to BCD
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : update descriptor
//*----------------------------------------------------------------------------
void at91_time_rtc_int_bdc(TimeDescRtc *RTC_pt)
//* Begin
{
    // translate int to bcd
    RTC_pt->time_bcd.sec = at91_int_bcd( RTC_pt->time_int.sec);
    RTC_pt->time_bcd.min = at91_int_bcd( RTC_pt->time_int.min);
    RTC_pt->time_bcd.hour = at91_int_bcd( RTC_pt->time_int.hour);
    RTC_pt->time_bcd.day = at91_int_bcd( RTC_pt->time_int.day);
    RTC_pt->time_bcd.month = at91_int_bcd( RTC_pt->time_int.month);
    RTC_pt->time_bcd.year = at91_int_bcd( RTC_pt->time_int.year);
    RTC_pt->time_bcd.cent = at91_int_bcd( RTC_pt->time_int.cent);
    RTC_pt->time_bcd.date = at91_int_bcd( RTC_pt->time_int.date);
    RTC_pt->time_bcd.ampm = (u_char) RTC_pt->time_int.ampm;

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_write_bcd
//* Object              : Read rtc value
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : update descriptor
//*----------------------------------------------------------------------------
void at91_time_rtc_write_bcd(TimeDescRtc *RTC_pt)
//* Begin
{
    if (at91_time_rtc_24mode(RTC_pt)==RTC_24_HRMOD)
    {
        //* set ampm at 0
        RTC_pt->time_bcd.ampm = 0;
    }
    // set time
    at91_rtc_set_time (RTC_pt->rtc_desc,RTC_pt->time_bcd.sec, RTC_pt->time_bcd.min, RTC_pt->time_bcd.hour, RTC_pt->time_bcd.ampm );

    // set date
    at91_rtc_set_calendar (RTC_pt->rtc_desc, RTC_pt->time_bcd.cent, RTC_pt->time_bcd.year, RTC_pt->time_bcd.month, RTC_pt->time_bcd.day, RTC_pt->time_bcd.date );
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_write
//* Object              : Read rtc value
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : update descriptor
//*----------------------------------------------------------------------------
void at91_time_rtc_write(TimeDescRtc *RTC_pt)
//* Begin
{
    // translate int to BCD
    at91_time_rtc_int_bdc(RTC_pt);

    // set in BCD
    at91_time_rtc_write_bcd(RTC_pt);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_validity
//* Object              : Return date validity
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : see Valid Entry Register bits definition
//*----------------------------------------------------------------------------
 u_int at91_time_rtc_validity(TimeDescRtc *RTC_pt)
//* Begin
{
    // Read register
    return (RTC_pt->rtc_desc->rtc_base->RTC_VER);
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_24mode
//* Object              : Return the 24 H mode
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : RTC_24_HRMOD or RTC_12_HRMOD
//*----------------------------------------------------------------------------
 u_int at91_time_rtc_24mode(TimeDescRtc *RTC_pt)
//* Begin
{
    // read mode
    return (at91_rtc_get_24(RTC_pt->rtc_desc));
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_set_time_alarm_bcd
//* Object              : Write Time Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide time
//*----------------------------------------------------------------------------
u_int at91_time_rtc_set_time_alarm_bcd(TimeDescRtc *RTC_pt)
//* Begin
{
   // Set Alarm
    at91_rtc_set_time_alarm ( RTC_pt->rtc_desc,RTC_pt->alarm_bcd.sec,RTC_pt->alarm_bcd.min,
                              RTC_pt->alarm_bcd.hour,RTC_pt->alarm_bcd.ampm,RTC_pt->mode_al_time );

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVTAL );
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_set_cal_alarm_bcd
//* Object              : Write Calandar Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide Calendar
//*----------------------------------------------------------------------------
u_int at91_time_rtc_set_cal_alarm_bcd(TimeDescRtc *RTC_pt)
//* Begin
{
    // Set Alarm
    at91_rtc_set_cal_alarm ( RTC_pt->rtc_desc,RTC_pt->alarm_bcd.month,RTC_pt->alarm_bcd.date,RTC_pt->mode_al_cal );

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVCAL );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_set_time_alarm
//* Object              : Write Time Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide time
//*----------------------------------------------------------------------------
u_int at91_time_rtc_set_time_alarm(TimeDescRtc *RTC_pt)
//* Begin
{
    RTC_pt->alarm_bcd.sec = at91_int_bcd(RTC_pt->alarm_int.sec);
    RTC_pt->alarm_bcd.min = at91_int_bcd(RTC_pt->alarm_int.min);
    RTC_pt->alarm_bcd.hour = at91_int_bcd(RTC_pt->alarm_int.hour);
    RTC_pt->alarm_bcd.ampm = RTC_pt->alarm_int.ampm;
    // Set Alarm
    at91_rtc_set_time_alarm ( RTC_pt->rtc_desc,RTC_pt->alarm_bcd.sec,RTC_pt->alarm_bcd.min,
                              RTC_pt->alarm_bcd.hour,RTC_pt->alarm_bcd.ampm,RTC_pt->mode_al_time );

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVTAL );
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_set_cal_alarm
//* Object              : Write Calandar Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide Calendar
//*----------------------------------------------------------------------------
u_int at91_time_rtc_set_cal_alarm(TimeDescRtc *RTC_pt)
//* Begin
{
    RTC_pt->alarm_bcd.date = at91_int_bcd(RTC_pt->alarm_int.date);
    RTC_pt->alarm_bcd.month = at91_int_bcd(RTC_pt->alarm_int.month);
    // Set Alarm
    at91_rtc_set_cal_alarm ( RTC_pt->rtc_desc,RTC_pt->alarm_bcd.month,RTC_pt->alarm_bcd.date,RTC_pt->mode_al_cal );

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVCAL );
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_read_cal_alarm
//* Object              : Read Calandar Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide Calendar
//*----------------------------------------------------------------------------
u_int at91_time_rtc_read_cal_alarm(TimeDescRtc *RTC_pt)
//* Begin
{
    u_int cal;
    // get Alarm
    cal = at91_rtc_get_cal_alarm ( RTC_pt->rtc_desc);

    RTC_pt->alarm_bcd.month = (cal & RTC_MASQ_MONTH)>>RTC_MONTH ;
    RTC_pt->alarm_bcd.date = (cal & RTC_MASQ_DATE)>>RTC_DATE ;

    //* Tranlate in int
    RTC_pt->alarm_int.month = at91_bcd_int(RTC_pt->alarm_bcd.month );
    RTC_pt->alarm_int.date = at91_bcd_int(RTC_pt->alarm_bcd.date);

    //* Read Alarm mode
    RTC_pt->mode_al_cal = (cal & RTC_MONTH_ALRM_EN);
    RTC_pt->mode_al_cal |= (cal & RTC_DATE_ALRM_EN);

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVCAL );
//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_time_rtc_read_time_alarm
//* Object              : Read Calandar Alarm
//* Input Parameters    : <RTC_pt> time rtc descriptor
//* Output Parameters   : != 0 invalide Calendar
//*----------------------------------------------------------------------------
u_int at91_time_rtc_read_time_alarm(TimeDescRtc *RTC_pt)
//* Begin
{
    u_int time;
    // get Alarm
    time = at91_rtc_get_time_alarm ( RTC_pt->rtc_desc);

    RTC_pt->alarm_bcd.sec = time & RTC_MASQ_SEC ;
    RTC_pt->alarm_bcd.min = (time & RTC_MASQ_MIN)>>RTC_MIN ;
    RTC_pt->alarm_bcd.hour = (time & RTC_MASQ_HOUR)>>RTC_HOUR ;
    RTC_pt->alarm_bcd.ampm = (time & RTC_MASQ_AMPM)>>RTC_AMPM ;

    //* Tranlate in int
    RTC_pt->alarm_int.sec = at91_bcd_int(RTC_pt->alarm_bcd.sec );
    RTC_pt->alarm_int.min = at91_bcd_int(RTC_pt->alarm_bcd.min);
    RTC_pt->alarm_int.hour = at91_bcd_int(RTC_pt->alarm_bcd.hour);
    RTC_pt->alarm_int.ampm =  at91_bcd_int(RTC_pt->alarm_bcd.ampm);

    //* Read Alarm mode
    RTC_pt->mode_al_time = (time & RTC_SEC_ALRM_EN);
    RTC_pt->mode_al_time |= (time & RTC_MIN_ALRM_EN);
    RTC_pt->mode_al_time |= (time & RTC_HOUR_ALRM_EN);

    return (RTC_pt->rtc_desc->rtc_base->RTC_VER & RTC_NVTAL );
//* End
}
//* End of file
