//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : time_rtc.h
//* Object              : Real Time Clock Prototyping File
//*
//* 1.0 07/09/00 JPP    : Creation
//*----------------------------------------------------------------------------

#ifndef time_rtc_h
#define time_rtc_h

#include "periph/stdc/std_c.h"
#include "periph/rtc/lib_rtc.h"
#include "periph/aic/lib_aic.h"

#include "periph/timer_counter/lib_tc.h"
/*---------------------------  Structure definition -------------------------*/
/* time in BCD */
typedef struct
{
    u_char      sec;
    u_char      min;
    u_char      hour;
    u_char      ampm;
    u_char      month;
    u_char      date;
} BcdAlarm ;
/* time in integer */
typedef struct
{
    u_int      sec;
    u_int      min;
    u_int      hour;
    u_int      ampm;
    u_int      month;
    u_int      date;
} IntAlarm ;

/* time in BCD */
typedef struct
{
    u_char      sec;
    u_char      min;
    u_char      hour;
    u_char      ampm;
    u_int       day;
    u_char      year;
    u_char      month;
    u_char      cent;
    u_char      date;
} BcdTime ;
/* time in integer */
typedef struct
{
    u_int      sec;
    u_int      min;
    u_int      hour;
    u_int      ampm;
    u_int      day;
    u_int      month;
    u_int      year;
    u_int      cent;
    u_int      date;
} IntTime ;


/* descriptor for rtc handler */
typedef struct
{
    const RtcDesc          *rtc_desc ;      //* RTC descriptor
    TypeAICHandler         *AsmRtcHandler;
    BcdTime                time_bcd;
    IntTime                time_int;
    BcdAlarm               alarm_bcd;
    IntAlarm               alarm_int;
    u_int                  mode_al_time;
    u_int                  mode_al_cal;
} TimeDescRtc ;


/*---------------------------  Function Prototyping -------------------------*/
/* Tools Function */
extern u_int at91_bcd_int( u_char bcd);
extern u_char at91_int_bcd (u_int value);
extern void at91_time_rtc_int_bdc(TimeDescRtc *RTC_pt);

/* RTC functions */
extern void at91_time_rtc_open( TimeDescRtc *RTC_pt);
extern void at91_time_rtc_close(TimeDescRtc *RTC_pt);

extern void at91_time_rtc_read(TimeDescRtc *RTC_pt);
extern void at91_time_rtc_write_bcd(TimeDescRtc *RTC_pt);
extern void at91_time_rtc_write(TimeDescRtc *RTC_pt);
extern  u_int at91_time_rtc_24mode(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_validity(TimeDescRtc *RTC_pt);

/* Alarm Function */
extern u_int at91_time_rtc_set_time_alarm_bcd(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_set_cal_alarm_bcd(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_set_time_alarm(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_set_cal_alarm(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_read_time_alarm(TimeDescRtc *RTC_pt);
extern u_int at91_time_rtc_read_cal_alarm(TimeDescRtc *RTC_pt);

/* Interrupt Function */
extern void at91_time_rtc_close_irq(TimeDescRtc *RTC_pt);
extern void at91_time_rtc_open_irq( TimeDescRtc *RTC_pt,u_int rtc_mode,u_int level);
extern void at91_time_rtc_c_handler(TimeDescRtc *RTC_pt);

/* Tools function */
extern u_int at91_time_rtc_mcki_round( TimeDescRtc *RTC_pt,const TCDesc *TC_pt );
extern u_int at91_time_rtc_mcki( TimeDescRtc *RTC_pt,const TCBlockDesc *TC_pt );

#endif /* time_rtc_h */
