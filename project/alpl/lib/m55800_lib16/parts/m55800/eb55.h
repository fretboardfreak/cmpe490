//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : eb55.h
//* Object              : AT91M55800 Evaluation Board Features Definition File.
//*
//* 1.0 23/05/00  PF    : Creation
//* 1.0 25/08/00  JPP   : Additing DAC description and Quartz
//*----------------------------------------------------------------------------
#ifndef eb55_h
#define eb55_h

#include    "parts/m55800/m55800.h"      /* library definition */


/*---------------------------------------*/
/* AT91EB55 External Memories Definition */
/*---------------------------------------*/

/* Flash Memory : AT49BV1604 1M*16 */
#define FLASH_BASE      ((u_int *)0x01000000)
#define FLASH_SIZE      (2*1024*1024)                /* byte */

/* SRAM : size is depending on the devices fitted on the board */
#define EXT_SRAM_BASE           ((u_int *)0x02000000)
#define EXT_SRAM_DEFAULT_SIZE   (256*1024)
#define EXT_SRAM_LIMIT  (EXT_SRAM_BASE+EXT_SRAM_SIZE)

/*---------------------------------------------------------------------------*/
/* EBI Initialization Data                                                   */
/*---------------------------------------------------------------------------*/
/* The EBI User Interface Image which is copied by the boot.                 */
/* 32 MHz master clock assumed.                                           */
/* That's hardware! Details in the Electrical Datasheet of the AT91 device.  */
/* EBI Base Address is added at the end for commodity in copy code.          */
/*---------------------------------------------------------------------------*/
#define EBI_CSR_0       ((u_int *)(FLASH_BASE | 0x2529)     /* 0x01000000, 16MB, 2 tdf, 16 bits, 3 WS  */
#define EBI_CSR_1       ((u_int *)(EXT_SRAM_BASE | 0x2121)  /* 0x02000000, 16MB, 0 hold, 16 bits, 1 WS */
#define EBI_CSR_2       ((u_int *)0x20000000)               /* unused */
#define EBI_CSR_3       ((u_int *)0x30000000)               /* unused */
#define EBI_CSR_4       ((u_int *)0x40000000)               /* unused */
#define EBI_CSR_5       ((u_int *)0x50000000)               /* unused */
#define EBI_CSR_6       ((u_int *)0x60000000)               /* unused */
#define EBI_CSR_7       ((u_int *)0x70000000)               /* unused */

/*-----------------*/
/* Leds Definition */
/*-----------------*/
#define LED1            PB8
#define LED2            PB9
#define LED3            PB10
#define LED4            PB11
#define LED5            PB12
#define LED6            PB13
#define LED7            PB14
#define LED8            PB15

#define LED_PIO_CTRL    1
#define LED_MASK        0x0000FF00

#define LED_ON          PIO_CLEAR_OUT
#define LED_OFF         PIO_SET_OUT

/*-------------------------*/
/* Push Buttons Definition */
/*-------------------------*/
#define SW1_MASK        PB20
#define SW2_MASK        PA9
#define SW3_MASK        PB17
#define SW4_MASK        PB19
#define SW_MASK         (SW1_MASK|SW2_MASK|SW3_MASK)

#define PIO_SW1         20
#define PIO_SW2         9
#define PIO_SW3         17
#define PIO_SW4         19

#define SW1_PIO_CTRL    PIOB_CTRL
#define SW2_PIO_CTRL    PIOA_CTRL
#define SW3_PIO_CTRL    PIOB_CTRL
#define SW4_PIO_CTRL    PIOB_CTRL

/*--------------------------*/
/* Serial EEPROM Definition */
/*--------------------------*/

#define SCL             PA1
#define SDA             PA2
#define PIO_SCL         1
#define PIO_SDA         2

/*--------------*/
/* Battery      */
/*--------------*/

#define FASTCHG_CTRL    PB18
#define FASTCHG_ON      0x0
#define FASTCHG_OFF     0x1

/*-----------------*/
/*  A/D Converter  */
/*-----------------*/
#define AD_NCONVST      PB19
#define START_CONV      0x0

#define LOOP_DAC1_AD0   //* with CB6 Closed
#define LOOP_DAC0_AD4   //* with CB5 Closed

/*--------------*/
/* Master Clock */
/*--------------*/

#define MCK             32768
#define MCKKHz          (MCK/1000)

#define EXT_QUARTZ      16000000


#endif /* eb55_h */
