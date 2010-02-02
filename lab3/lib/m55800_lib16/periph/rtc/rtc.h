//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : rtc.h
//* Object              : Real Time Clock Library File
//*
//* 1.0 17/07/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef rtc_h
#define rtc_h

#include    "periph/stdc/std_c.h"

/*--------------------------------------*/
/* Real Time Clock Structure Definition */
/*--------------------------------------*/
typedef struct
{
    at91_reg       RTC_CR ;     /* Control Register */
    at91_reg       RTC_MR ;     /* Mode Register */
    at91_reg       RTC_TIMR ;   /* Time Register */
    at91_reg       RTC_CALR ;   /* Calendar Register */
    at91_reg       RTC_TAR ;    /* Time Alarm Register */
    at91_reg       RTC_CAR ;    /* Calendar Alarm Register */
    at91_reg       RTC_SR ;     /* Status Register */
    at91_reg       RTC_SCR ;    /* Status Clear Register */
    at91_reg       RTC_IER ;    /* Interrupt Enable Register */
    at91_reg       RTC_IDR ;    /* Interrupt Disable Register */
    at91_reg       RTC_IMR ;    /* Interrupt Mask Register */
    at91_reg       RTC_VER ;    /* Valid Entry Register */
} StructRTC ;

/*--------------------------------------------*/
/* RTC_CR: Control Register bits definition  */
/*-------------------------------------------*/
#define     RTC_UPDTIM              0x00000001     /* Update Request Time Register */
#define     RTC_UPDCAL              0x00000002     /* Update Request Calendar Register */
#define     RTC_UPD_MASQ            0x00000003     /* Update Request masque*/

#define     RTC_TEVSEL_MN_CHG       0x000       /* Time Event Selection : Minute change */
#define     RTC_TEVSEL_HR_CHG       0x100       /* Time Event Selection : Hour change */
#define     RTC_TEVSEL_EVDAY_MD     0x200       /* Time Event Selection : Every Day at Midnight */
#define     RTC_TEVSEL_EVDAY_NOON   0x300       /* Time Event Selection : Every Day at Noon */
#define     RTC_TEVSEL_MASQ         0x300       /* Update TEVSEL masque*/

#define     RTC_CEVSEL_WEEK_CHG     0x00000     /* Calendar Event Selection : Week Change (every Monday @ 00:00:00) */
#define     RTC_CEVSEL_MONTH_CHG    0x10000     /* Calendar Event Selection : Month Change (every 01 of each month @ 00:00:00) */
#define     RTC_CEVSEL_YEAR_CHG     0x20000     /* Calendar Event Selection : Year Change (every january 1st at 00:00:00) */
#define     RTC_CEVSEL_MASQ         0x30000     /* Updat eCEVSEL masque*/

/*-------------------------------------------*/
/* RTC_MR: Mode Register bits definition     */
/*-------------------------------------------*/
#define     RTC_24_HRMOD        0x0     /* 24-Hour Mode is selected */
#define     RTC_12_HRMOD        0x1     /* 12-Hour Mode is selected */

/*---------------------------------------------*/
/* RTC_TIMR: Time Register bits definition     */
/*---------------------------------------------*/
#define     RTC_AM          (0<<22)         /* AM Indicator */
#define     RTC_PM          0x400000        /* PM Indicator */
#define     RTC_MASQ_SEC    0x0000007F
#define     RTC_MIN         8
#define     RTC_MASQ_MIN    0x00007F00
#define     RTC_HOUR        16
#define     RTC_MASQ_HOUR   0x003F0000
#define     RTC_AMPM        22
#define     RTC_MASQ_AMPM   0x00400000

/*--------------------------------------------------*/
/* RTC_CALR:  Calendar Register bits definition     */
/*--------------------------------------------------*/
#define     RTC_CENT        0
#define     RTC_MASQ_CENT   0x0000003F
#define     RTC_YEAR        8
#define     RTC_MASQ_YEAR   0x0000FF00
#define     RTC_MONTH       16
#define     RTC_MASQ_MONTH  0x001F0000
#define     RTC_DAY         21
#define     RTC_MASQ_DAY    0x00E00000
#define     RTC_DATE        24
#define     RTC_MASQ_DATE   0x3F000000


/*----------------------------------------------*/
/* RTC_TAR: Time Alarm Register bits definition */
/*----------------------------------------------*/
#define     RTC_SEC_ALRM_DIS        (0<<7)      /* Second Alarm Disable */
#define     RTC_SEC_ALRM_EN         0x80        /* Second Alarm Enable */

#define     RTC_MIN_ALRM_DIS        (0<<15)     /* Minute Alarm Disable */
#define     RTC_MIN_ALRM_EN         0x8000      /* Minute Alarm Enable */

#define     RTC_HOUR_ALRM_DIS       (0<<23)     /* Hour Alarm Disable */
#define     RTC_HOUR_ALRM_EN        0x800000    /* Hour Alarm Enable */

/*--------------------------------------------------*/
/* RTC_CAR: Calendar Alarm Register bits definition */
/*--------------------------------------------------*/
#define     RTC_MONTH_ALRM_DIS      (0<<23)     /* Month Alarm Disable */
#define     RTC_MONTH_ALRM_EN       0x800000    /* Month Alarm Enable */

#define     RTC_DATE_ALRM_DIS       (0<<31)     /* Date Alarm Disable */
#define     RTC_DATE_ALRM_EN        0x80000000   /* Date Alarm Enable */

/*-------------------------------------------------------------------------------*/
/* RTC Status, Interrupt Clear, Enable,Disable and Mask Register bits definition */
/*-------------------------------------------------------------------------------*/
#define     RTC_ACKUPD              0x1         /* Acknowledge for Update */
#define     RTC_ALARM               0x2         /* Alarm Flag */
#define     RTC_SEC                 0x4         /* Second Event */
#define     RTC_TIMEV               0x8         /* Time Event */
#define     RTC_CALEV               0x10        /* Calendar Event */

/*-------------------------------------------------*/
/* RTC_VER:Valid Entry Register bits definition    */
/*-------------------------------------------------*/
#define     RTC_NVT                 0x1         /* Non-Valid Time */
#define     RTC_NVC                 0x2         /* Non-Valid Calendar */
#define     RTC_NVTAL               0x4         /* Non-Valid Time Alarm */
#define     RTC_NVCAL               0x8         /* Non-Valid Calendar Alarm */

#endif /* rtc_h */
