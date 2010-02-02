//*---------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : adc.h
//* Object              : Analog to Digital Converter Definition File
//*
//* 1.0 25/08/00   JPP  : Creation
//*---------------------------------------------------------------------------

#ifndef adc_h
#define adc_h

#include    "periph/stdc/std_c.h"

/*--------------------------*/
/* ADC Structure Definition */
/*--------------------------*/
typedef struct
{
    at91_reg        ADC_CR ;            /* Control Register */
    at91_reg        ADC_MR ;            /* Mode Register */
    at91_reg        Reserved0 ;
    at91_reg        Reserved1 ;
    at91_reg        ADC_CHER ;          /* Channel Enable Register */
    at91_reg        ADC_CHDR ;          /* Channel Disable Register */
    at91_reg        ADC_CHSR ;          /* Channel Status Register */
    at91_reg        Reserved2 ;
    at91_reg        ADC_SR ;            /* Status Register */
    at91_reg        ADC_IER ;           /* Interrupt Enable Register */
    at91_reg        ADC_IDR ;           /* Interrupt Disable  Register */
    at91_reg        ADC_IMR ;           /* Interrupt Mask Register */
    at91_reg        ADC_CDR[4] ;        /* Channel Data Registers */
} StructADC ;

/*------------------------------------------*/
/* ADC_CR: Control Register Bits Definition */
/*------------------------------------------*/
#define     ADC_SWRST           (1<<0)      /* ADC Software Reset */
#define     ADC_START           (1<<1)      /* ADC Start */

/*---------------------------------------*/
/* ADC_MR: Mode Register Bits Definition */
/*---------------------------------------*/
#define ADC_TRGEN_DIS      0x0         /* Trigger Disable */
#define ADC_TRGEN_EN       0x1         /* Trigger Enable */

/* Trigger Selection */
#define ADC_B_TTRGSEL       1
#define ADC_TRG_TIOA0       0x0         /* TIOA0 Trigger Selection */
#define ADC_TRG_TIOA1       0x2         /* TIOA1 Trigger Selection */
#define ADC_TRG_TIOA2       0x4         /* TIOA2 Trigger Selection */
#define ADC_TRG_TIOA3       0x6         /* TIOA3 Trigger Selection */
#define ADC_TRG_TIOA4       0x8         /* TIOA4 Trigger Selection */
#define ADC_TRG_TIOA5       0xA         /* TIOA5 Trigger Selection */
#define ADC_TRG_EXT         0xC         /* External Trigger Selection */

#define ADC_10_BIT_RES      (0<<4)      /* 10 bits ADC Resolution */
#define ADC_8_BIT_RES       (1<<4)      /*  8 bits ADC Resolution */

#define ADC_NORMAL_MODE     (0<<5)      /* ADC Normal Mode */
#define ADC_SLEEP_MODE      0x20        /* ADC Sleep Mode */

#define ADC_PRESCAL         (0x3F<<8)   /* Max Prescaler value */
#define ADC_B_PRESCAL       8           /* bit shift */

/*--------------------------------------------------------------------------*/
/* ADC_CHER,ADC_CHDR,ADC_CHSR: Channel Enable, Disable and Status Registers */
/*--------------------------------------------------------------------------*/
#define ADC_CH0             0x1     /* Channel 0 Enable/Disable */
#define ADC_CH1             0x2     /* Channel 1 Enable/Disable */
#define ADC_CH2             0x4     /* Channel 2 Enable/Disable */
#define ADC_CH3             0x8     /* Channel 3 Enable/Disable */

/*-------------------------------------------------------------------------*/
/* ADC_SR,ADC_IER,ADC_IDR,ADC_IMR: Status, Enable, Disable, Mask Registers */
/*-------------------------------------------------------------------------*/
#define ADC_EOC0            0x1     /* End of Conversion Channel 0 */
#define ADC_EOC1            0x2     /* End of Conversion Channel 1 */
#define ADC_EOC2            0x4     /* End of Conversion Channel 2 */
#define ADC_EOC3            0x8     /* End of Conversion Channel 3 */

#define ADC_OVRE0           0x1     /* Overrun Interrupt Error Channel 0 */
#define ADC_OVRE1           0x2     /* Overrun Interrupt Error Channel 1 */
#define ADC_OVRE2           0x4     /* Overrun Interrupt Error Channel 2 */
#define ADC_OVRE3           0x8     /* Overrun Interrupt Error Channel 3 */

/*-------------------------------*/
/* ADC_CDR:Convert Data Register */
/*-------------------------------*/

#define ADC_DATA_10BITS    0x3FF
#define ADC_DATA_8BITS     0x0FF

/*---------------------------------------*/
/* ADC Interrupt Handler type definition */
/*---------------------------------------*/

typedef void (*TypeADCHandler) (void) ;

#endif /* adc_h */
