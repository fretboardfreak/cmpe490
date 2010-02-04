//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_m55800.c
//* Object              : AT91M55800 Descriptor File.
//*
//* 1.0 11/07/00  PF    : Creation
//* 1.1 03/08/01  PF	: IRQ6 Descriptor Removed
//*----------------------------------------------------------------------------

#include    "parts/m55800/lib_m55800.h"

/*-----------------*/
/* PIO Controllers */
/*-----------------*/

/* Instantiate PIO Controllers Pointers */
const StructPIO *Pioa   = PIOA_BASE ;
const StructPIO *Piob   = PIOB_BASE ;

/* PIO Controller A Descriptor */
const PioCtrlDesc PIOA_DESC =
{
    PIOA_BASE,
    PIOA_ID,
    NB_PIOA
} ;

/* PIO Controller B Descriptor */
const PioCtrlDesc PIOB_DESC =
{
    PIOB_BASE,
    PIOB_ID,
    NB_PIOB
} ;

/*-------------------------------*/
/* Advanced Interrupt Controller */
/*-------------------------------*/

/* IRQ0 Descriptor */
const ExtIrqDesc    IRQ0_DESC =
{
    &PIOA_DESC,
    IRQ0_ID,
    PIOIRQ0
} ;

/* IRQ1 Descriptor */
const ExtIrqDesc    IRQ1_DESC =
{
    &PIOA_DESC,
    IRQ1_ID,
    PIOIRQ1
} ;

/* IRQ2 Descriptor */
const ExtIrqDesc    IRQ2_DESC =
{
    &PIOA_DESC,
    IRQ2_ID,
    PIOIRQ2
} ;

/* IRQ3 Descriptor */
const ExtIrqDesc    IRQ3_DESC =
{
    &PIOA_DESC,
    IRQ3_ID,
    PIOIRQ3
} ;

/* IRQ4 Descriptor */
const ExtIrqDesc    IRQ4_DESC =
{
    &PIOB_DESC,
    IRQ4_ID,
    PIOIRQ4
} ;

/* IRQ5 Descriptor */
const ExtIrqDesc    IRQ5_DESC =
{
    &PIOB_DESC,
    IRQ5_ID,
    PIOIRQ5
} ;

/* FIQ Descriptor */
const ExtIrqDesc    FIQ_DESC =
{
    &PIOA_DESC,
    FIQ_ID,
    PIOFIQ,
} ;

/*-------*/
/* USART */
/*-------*/

/* Usart 0 Descriptor */
const UsartDesc USART0_DESC =
{
    USART0_BASE,
    &PIOA_DESC,
    PIORXD0,
    PIOTXD0,
    PIOSCK0,
    US0_ID ,
} ;

/* Usart 1 Descriptor */
const UsartDesc USART1_DESC =
{
    USART1_BASE ,
    &PIOA_DESC,
    PIORXD1,
    PIOTXD1,
    PIOSCK1,
    US1_ID ,
} ;

/* Usart 2 Descriptor */
const UsartDesc USART2_DESC =
{
    USART2_BASE ,
    &PIOA_DESC,
    PIORXD2,
    PIOTXD2,
    PIOSCK2,
    US2_ID ,
} ;


/*------------------------*/
/* Timer Counter Channels */
/*------------------------*/

/* Timer Counter Channel 0 Descriptor */
const TCDesc TC0_DESC =
{
    &(TCB0_BASE->TC[0]),
    &PIOB_DESC,
    TC0_ID,
    PIOTIOA0,
    PIOTIOB0,
    PIOTCLK0
} ;

/* Timer Counter Channel 1 Descriptor */
const TCDesc TC1_DESC =
{
    &TCB0_BASE->TC[1],
    &PIOB_DESC,
    TC1_ID,
    PIOTIOA1,
    PIOTIOB1,
    PIOTCLK1
} ;

/* Timer Counter Channel 2 Descriptor */
const TCDesc TC2_DESC =
{
    &TCB0_BASE->TC[2],
    &PIOB_DESC,
    TC2_ID,
    PIOTIOA2,
    PIOTIOB2,
    PIOTCLK2
} ;

/* Timer Counter Channel 3 Descriptor */
const TCDesc TC3_DESC =
{
    &TCB1_BASE->TC[0],
    &PIOA_DESC,
    TC3_ID,
    PIOTIOA3,
    PIOTIOB3,
    PIOTCLK3
} ;

/* Timer Counter Channel 4 Descriptor */
const TCDesc TC4_DESC =
{
    &TCB1_BASE->TC[1],
    &PIOA_DESC,
    TC4_ID,
    PIOTIOA4,
    PIOTIOB4,
    PIOTCLK4
} ;

/* Timer Counter Channel 5 Descriptor */
const TCDesc TC5_DESC =
{
    &TCB1_BASE->TC[2],
    &PIOA_DESC,
    TC5_ID,
    PIOTIOA5,
    PIOTIOB5,
    PIOTCLK5
} ;

/* Timer Counter Block 0 Descriptor */
const TCBlockDesc TCB0_DESC =
{
    &TC0_DESC,
    &TC1_DESC,
    &TC2_DESC,
} ;

/* Timer Counter Block 1 Descriptor */
const TCBlockDesc TCB1_DESC =
{
    &TC3_DESC,
    &TC4_DESC,
    &TC5_DESC,
} ;

/*-----*/
/* SPI */
/*-----*/

const SpiDesc SPI_DESC =
{
    SPI_BASE,
    &PIOA_DESC,
    SPI_ID,
    PIOSPCK,
    PIOMISO,
    PIOMOSI,
    {
        PIONPCS0,
        PIONPCS1,
        PIONPCS2,
        PIONPCS3
    }
} ;

/*-----*/
/* DAC */
/*-----*/

const DacDesc DAC0_DESC =
{
    DAC0_BASE,
    DAC0_ID
} ;

const DacDesc DAC1_DESC =
{
    DAC1_BASE,
    DAC1_ID
} ;
/*-----*/
/* ADC */
/*-----*/

const AdcDesc ADC0_DESC =
{
    ADC0_BASE,
    AD0_ID
} ;

const AdcDesc ADC1_DESC =
{
    ADC1_BASE,
    AD1_ID
} ;

/*-----*/
/* RTC */
/*-----*/

const RtcDesc RTC_DESC =
{
    RTC_BASE,
    RTC_ID
} ;
