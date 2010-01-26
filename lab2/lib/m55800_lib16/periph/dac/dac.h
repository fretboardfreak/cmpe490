//*---------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : dac.h
//* Object              : Digital to Analog Converter Definition File
//*
//* 1.0 25/08/00 JPP    : Creation
//* 2.0 10/12/01 PFi    : Data Pointer/Counter Registers in the StructDAC
//*                     : has been removed.The RevA of the M558000 does not
//*                     : features DAC PDC.
//*---------------------------------------------------------------------------

#ifndef dac_h
#define dac_h

/*--------------------------*/
/* DAC Structure Definition */
/*--------------------------*/

typedef struct
{
    at91_reg        DAC_CR ;            /* Control Register */
    at91_reg        DAC_MR ;            /* Mode Register */
    at91_reg        DAC_DHR ;           /* Data Holding Register */
    at91_reg        DAC_DOR ;           /* Data Output Register */
    at91_reg        DAC_SR ;            /* Status Register */
    at91_reg        DAC_IER ;           /* Interrupt Enable Register */
    at91_reg        DAC_IDR ;           /* Interrupt Disable  Register */
    at91_reg        DAC_IMR ;           /* Interrupt Mask Register */
} StructDAC ;

/*--------------------------*/
/* DAC_CR: Control Register */
/*--------------------------*/

#define DAC_SWRST       (1<<0)          //* Reset the DAC
#define DAC_LOOPEN      (1<<1)          //* Automatic reaload
#define DAC_LOOPDIS     (1<<2)          //* WAVEND interrupt at the end of PDC

/*-----------------------*/
/* DAC_MR: Mode Register */
/*-----------------------*/

#define DAC_TTRGEN_DIS      0x0         /* Trigger Disable */
#define DAC_TTRGEN_EN       0x1         /* Trigger Enable */
/* Trigger Selection */
#define DAC_B_TTRGSEL       1
#define DAC_TTRGSEL         (7<<DAC_B_TTRGSEL)  /* TIOA0 Trigger Selection */
#define DAC_TRG_TIOA0       (0<<DAC_B_TTRGSEL)  /* TIOA1 Trigger Selection */
#define DAC_TRG_TIOA1       (1<<DAC_B_TTRGSEL)  /* TIOA2 Trigger Selection */
#define DAC_TRG_TIOA2       (2<<DAC_B_TTRGSEL)  /* TIOA3 Trigger Selection */
#define DAC_TRG_TIOA3       (3<<DAC_B_TTRGSEL)  /* TIOA4 Trigger Selection */
#define DAC_TRG_TIOA4       (4<<DAC_B_TTRGSEL)  /* TIOA5 Trigger Selection */
#define DAC_TRG_TIOA5       (5<<DAC_B_TTRGSEL)  /* External Trigger Selection */

#define DAC_10_BIT_RES      (0<<4)      /* 10 bits DAC Resolution */
#define DAC_8_BIT_RES       (1<<4)      /*  8 bits DAC Resolution */

/*----------------------------------------------------------*/
/* DAC_DHR, DAC_DOR: Data Holding and Data Output Registers */
/*----------------------------------------------------------*/

#define DAC_DATA_10BITS    0x3FF
#define DAC_DATA_8BITS     0x0FF

/*---------------------------------------------------------------*/
/* DAC_SR,DAC_IER,DAC_IDR,DAC_IMR: Status and Interrupt Register */
/*---------------------------------------------------------------*/

#define DAC_DATRDY          (1<<0)          //* End transfert
#define DAC_WAVEND          (1<<1)          //* End wave generation
#define DAC_LOOP            (1<<16)         //* Loop mode Status register only

#endif /* dac_h */
