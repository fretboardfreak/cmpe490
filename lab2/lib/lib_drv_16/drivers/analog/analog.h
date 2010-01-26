//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : analog.h
//* Object              : analog Terminal Prototyping File
//*
//* 1.0 31/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

#ifndef analog_h
#define analog_h

#include "periph/stdc/std_c.h"
#include "periph/adc/lib_adc.h"
#include "periph/aic/lib_aic.h"
#include "periph/timer_counter/lib_tc.h"
#include "periph/dac/lib_dac.h"

/*---------------------------  Constants definition -------------------------*/
#define LOOP_DAC       1
#define NO_LOOP_DAC    0

/*---------------------------  Structure definition -------------------------*/
/* Software PDC */
typedef struct
{
   u_short          *base_add;      /* first pdc address */
   u_short          *cur_add;       /* current address */
   u_int            base_cmpt;      /* nb point */
   u_int            cur_cmpt;       /* curent comtteur valure */
} AnalogPdcSoft;

/* descriptor for dac irq mode */
typedef struct
{
   const DacDesc        *dac ;          //* DAC general descriptor for loop
   const TCDesc         *timer;         //* Timer general descriptor for sampling
   AnalogPdcSoft        pdc;            //* Software PDC
   TypeAICHandler       *AsmDacHandler; //* Assembli irq entry point
} AnalogDACTimerIrqDesc;

/* descriptor for adc irq mode */
typedef struct
{
     const AdcDesc      *adc ;          //* ADC general descriptor
     TypeAICHandler     *AsmADCHandler; //* Assembly irq entry point
     u_int              adc_channel;    //* ADC Channel nb 0 to 3
     const DacDesc      *dac_loop;      //* DAC general descriptor for loop
     u_int              loop_mode;      //* loop ADC => DAC
     const TCDesc       *timer;         //* Timer general descriptor for sampling
     AnalogPdcSoft      pdc;            //* Software PDC
} AnalogAdcIrqDesc ;


/* descriptor for adc in polling mode */
typedef struct
{
    const AdcDesc       *adc_desc ;     //* ADC descriptor
    u_int               channel ;       //* ADC Channel 0 to 0xF
} AnalogDescAdc ;

/* descriptor analog DAC */
typedef struct
{
    const DacDesc       *dac ;          //* DAC general descriptor
    const TCDesc        *timer;         //* Timer general descriptor for sampling
} AnalogDescDac;

/*---------------------------  Function Prototyping -------------------------*/
/* Timer function */
extern void at91_analog_open_timer_irq(AnalogDACTimerIrqDesc *DAC_pt, int tioc, int tc_div,const u_short * data,u_int nb_point);
extern void at91_analog_open_timer(const TCDesc *TC_pt, int tioc, int tc_div);
extern void at91_analog_close_timer(const TCDesc *TC_pt);

/* DAC functions */
extern void at91_analog_open_dac( AnalogDescDac *DAC_pt,u_int mode);
extern void at91_analog_write_dac( AnalogDescDac *DAC_pt,u_short * data);
extern void at91_analog_open_dac_loop(AnalogDescDac *DAC_pt,u_int dac_mode, int tioc,int tc_div ,const u_short * data,u_int nb_point);
extern void at91_analog_open_dac_loop_soft(AnalogDACTimerIrqDesc *DAC_pt,u_int dac_mode, int tioc,int tc_div ,const u_short * data,u_int nb_point);
extern void at91_analog_close_dac( AnalogDescDac *DAC_pt);

/* ADC Functions */
extern void at91_analog_c_handler_adc(AnalogAdcIrqDesc *desc);
extern void at91_analog_open_adc_irq( AnalogAdcIrqDesc *ADC_pt,u_int adc_mode, int tioc, int tc_div ,u_short * data,u_int nb_point);
extern void at91_analog_close_adc_irq( AnalogAdcIrqDesc *ADC_pt);

extern void at91_analog_open_adc( AnalogDescAdc *Analog_pt,u_int adc_mode);
extern void at91_analog_close_adc(AnalogDescAdc *Analog_pt);
extern u_short at91_analog_read_adc( AnalogDescAdc *Analog_pt,u_int channel);

#endif /* analog_h */
