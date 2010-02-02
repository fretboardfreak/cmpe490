//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_dac.h
//* Object              : Digital to Analog Converter Library Function
//*                       Prototyping File.
//*
//* 1.0 25/08/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_dac_h
#define lib_dac_h

#include    "periph/stdc/std_c.h"
#include    "periph/dac/dac.h"
#include    "periph/power_saving/lib_power_save.h"

/*-------------------------------------*/
/* DAC Descriptor Structure Definition */
/*-------------------------------------*/
typedef struct
{
    StructDAC           *dac_base ;
    u_char              periph_id ;
} DacDesc ;

/* Function Prototyping */
extern  void at91_dac_open ( const DacDesc *dac_desc, u_int mode ) ;
extern  void at91_dac_close ( const DacDesc *dac_desc ) ;
extern  void at91_dac_trig_cmd ( const DacDesc *dac_desc, u_int cmd ) ;
extern  void at91_dac_set_mode ( const DacDesc *dac_desc, u_int mode ) ;
extern  void at91_dac_write ( const DacDesc *dac_desc, u_short *data ) ;
extern  u_int at91_dac_get_status ( const DacDesc *dac_desc ) ;

#endif  /* lib_dac_h */
