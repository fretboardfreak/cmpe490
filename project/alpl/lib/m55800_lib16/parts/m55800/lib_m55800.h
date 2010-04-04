//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_m55800.h
//* Object              : AT91M55800 Architecture Definition File
//*
//* 1.0 11/07/00  PF    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_m55800_h
#define lib_m55800_h

#include    "parts/m55800/m55800.h"

/*----------*/
/* ARM Core */
/*----------*/
#include    "periph/arm7tdmi/arm.h"

/*-------------------------------*/
/* Advanced Interrupt Controller */
/*-------------------------------*/
#include    "periph/aic/lib_aic.h"
#include    "periph/aic/ext_irq/lib_ext_irq.h"

/* Descriptor */
extern const ExtIrqDesc    IRQ0_DESC ;      /* IRQ0 Descriptor */
extern const ExtIrqDesc    IRQ1_DESC ;      /* IRQ1 Descriptor */
extern const ExtIrqDesc    IRQ2_DESC ;      /* IRQ2 Descriptor */
extern const ExtIrqDesc    IRQ3_DESC ;      /* IRQ3 Descriptor */
extern const ExtIrqDesc    IRQ4_DESC ;      /* IRQ4 Descriptor */
extern const ExtIrqDesc    IRQ5_DESC ;      /* IRQ5 Descriptor */
extern const ExtIrqDesc    FIQ_DESC ;       /* FIQ Descriptor  */

/*-------------------------*/
/* Parallel I/O Controller */
/*-------------------------*/
#include    "periph/pio/lib_pio.h"

extern void pioa_asm_irq_handler ( void ) ;
extern void piob_asm_irq_handler ( void ) ;

/* Descriptor */
extern const PioCtrlDesc PIOA_DESC ;        /* PIO Controller A Descriptor */
extern const PioCtrlDesc PIOB_DESC ;        /* PIO Controller B Descriptor */

/*--------*/
/* USARTs */
/*--------*/
/* Definition file */
#include    "periph/usart/lib_usart.h"

/* USART descriptor */
extern const UsartDesc USART0_DESC ;        /* USART 0 Descriptor */
extern const UsartDesc USART1_DESC ;        /* USART 1 Descriptor */
extern const UsartDesc USART2_DESC ;        /* USART 2 Descriptor */

/*---------------*/
/* Timer Counter */
/*---------------*/
#include    "periph/timer_counter/lib_tc.h"

/* Descriptors */
extern const TCDesc TC0_DESC ;          /* Timer Counter Channel 0 Descriptor */
extern const TCDesc TC1_DESC ;          /* Timer Counter Channel 1 Descriptor */
extern const TCDesc TC2_DESC ;          /* Timer Counter Channel 2 Descriptor */
extern const TCDesc TC3_DESC ;          /* Timer Counter Channel 3 Descriptor */
extern const TCDesc TC4_DESC ;          /* Timer Counter Channel 4 Descriptor */
extern const TCDesc TC5_DESC ;          /* Timer Counter Channel 5 Descriptor */

extern const TCBlockDesc TCB0_DESC ;    /* Timer Counter Block 0 Descriptor */
extern const TCBlockDesc TCB1_DESC ;    /* Timer Counter Block 1 Descriptor */

/*-----*/
/* SPI */
/*-----*/
#include    "periph/spi/lib_spi.h"

/* Descriptor */
extern const SpiDesc    SPI_DESC ;      /* Serial Peripheral Interface Descriptor */

/*-----*/
/* RTC */
/*-----*/
#include    "periph/rtc/lib_rtc.h"

/* Descriptor */
extern const RtcDesc    RTC_DESC ;

/*-----*/
/* ADC */
/*-----*/
#include    "periph/adc/lib_adc.h"

/* Descriptor */
extern const AdcDesc    ADC0_DESC ;
extern const AdcDesc    ADC1_DESC ;

/*-----*/
/* DAC */
/*-----*/
#include    "periph/dac/lib_dac.h"

/* Descriptor */
extern const DacDesc    DAC0_DESC ;
extern const DacDesc    DAC1_DESC ;

/*----------*/
/* WatchDog */
/*----------*/
#include	"periph/watchdog/lib_wd.h"

#endif /* lib_m55800_h */
