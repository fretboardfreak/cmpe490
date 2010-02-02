//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_rtc.h
//* Object              : Real Time Clock Library Function Prototyping File.
//*
//* 1.0 17/07/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_rtc_h
#define lib_rtc_h

#include    "periph/rtc/rtc.h"

/*-------------------------------------*/
/* RTC Descriptor Structure Definition */
/*-------------------------------------*/
typedef struct
{
    StructRTC           *rtc_base ;
    u_char              periph_id ;
} RtcDesc ;

/* Function Prototyping */
extern void at91_rtc_close ( const RtcDesc *rtc_pt);
extern void at91_rtc_open ( const RtcDesc *rtc_pt);

/* Status register */
extern u_int at91_rtc_get_event ( const RtcDesc *rtc_pt);
extern void at91_rtc_set_event ( const RtcDesc *rtc_pt, u_int mode );
extern u_int at91_rtc_get_status ( const RtcDesc *rtc_pt );
extern void at91_rtc_clear_status ( const RtcDesc *rtc_pt );

/* 24H AQM/ PM  mamagement */
extern void at91_rtc_set_24 ( const RtcDesc *rtc_pt );
extern void at91_rtc_clear_24 ( const RtcDesc *rtc_pt );
extern u_int at91_rtc_get_24 ( const RtcDesc *rtc_pt );

/* Time and calendar */
extern void at91_rtc_set_time ( const RtcDesc *rtc_pt, u_char sec, u_char min, u_char hour, u_char ampm );
extern u_int at91_rtc_get_time ( const RtcDesc *rtc_pt );
extern void at91_rtc_set_calendar ( const RtcDesc *rtc_pt, u_char cent, u_char year, u_char month, u_char day, u_char date );
extern u_int at91_rtc_get_calendar ( const RtcDesc *rtc_pt );

/* Alarm mamagement */
extern void at91_rtc_set_time_alarm ( const RtcDesc *rtc_pt, u_char sec, u_char min, u_char hour, u_char ampm,u_int mode );
extern u_int at91_rtc_get_time_alarm ( const RtcDesc *rtc_pt );
extern void at91_rtc_set_cal_alarm ( const RtcDesc *rtc_pt,u_char month, u_char date, u_int mode );
extern u_int at91_rtc_get_cal_alarm ( const RtcDesc *rtc_pt );

#endif  /* lib_rtc_h */
