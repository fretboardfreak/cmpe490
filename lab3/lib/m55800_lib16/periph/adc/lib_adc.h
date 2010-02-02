//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_adc.h
//* Object              : Analog to Digital Converter Library Function
//*                       Prototyping File.
//*
//* 1.0 25/08/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_adc_h
#define lib_adc_h

#include    "periph/stdc/std_c.h"
#include    "periph/adc/adc.h"
#include    "periph/power_saving/lib_power_save.h"

/*-------------------------------------*/
/* ADC Descriptor Structure Definition */
/*-------------------------------------*/
typedef struct
{
    StructADC           *adc_base ;
    u_char              periph_id ;
} AdcDesc ;

/* Function Prototyping */
extern  void at91_adc_open ( const AdcDesc *adc_desc, u_int mode ) ;
extern  void at91_adc_close ( const AdcDesc *adc_desc ) ;
extern  void at91_adc_trig_cmd ( const AdcDesc *adc_desc, u_int cmd ) ;
extern  u_int at91_adc_get_status ( const AdcDesc *adc_desc ) ;
extern  void at91_adc_channel_open ( const AdcDesc *adc_desc, u_int channel ) ;
extern  void at91_adc_channel_close ( const AdcDesc *adc_desc, u_int channel ) ;
extern  u_int at91_adc_channel_get_status ( const AdcDesc *adc_desc ) ;
extern  void at91_adc_read ( const AdcDesc *adc_desc, u_int reg[] ) ;

#endif  /* lib_adc_h */
