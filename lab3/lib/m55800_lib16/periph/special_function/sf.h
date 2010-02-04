//*--------------------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : sf.h
//* Object              : Special Function Header File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//* 1.1 10/01/02 PFi    : Conditionnal compilation added in StructSF for the AT91R40807
//*--------------------------------------------------------------------------------------

#ifndef sf_h
#define sf_h

#include    "periph/stdc/std_c.h"

/*---------------------------------------------------------*/
/* Chip Identification User Interface Structure Definition */
/*---------------------------------------------------------*/

typedef struct
{
    at91_reg    SF_CIDR ;       /* Chip Identification Register */
    at91_reg    SF_EXID ;       /* Chip Identification Extension */
    at91_reg    SF_RSR ;        /* Reset Status Flag */

#ifdef AT91R40807
    at91_reg    SF_MMR ;        /* Memory Mode Register */
#endif

#ifndef AT91R40807
    at91_reg    Reserved0 ;
#endif

    at91_reg    Reserved1 ;
    at91_reg    Reserved2 ;
    at91_reg    SF_PMR ;        /* Protect Mode Register */
} StructSF ;



/*-------------------------------------------------------*/
/* SF_CIDR: Chip Identification Register Bits Definition */
/*-------------------------------------------------------*/

#define SF_VERSION          0x1F                 /* Version Number */
#define SF_NVPSIZ           0xF00                /* Non Volatile Program Memory Size */
#define SF_NVDSIZ           (0x0F<<12)           /* Non Volatile Data Memory Size */
#define SF_VDSIZ            (0x0F<<16)           /* Volatile Data Memory Size */
#define SF_ARCH             (0xFF<<20)           /* Architecture Code */
#define SF_NVPTYP           (0x07<<28)           /* Non Volatile Program Memory Type */
#define SF_EXT              ((u_int)0x01<<31)    /* Extension Flag */


/* SF_ARCH: */
#define SF_ARCH_AT91x63     (0x63<<20)
#define SF_ARCH_AT91x40     (0x40<<20)
#define SF_ARCH_AT91x55     (0x55<<20)

/* SF_NVPSIZ */
#define SF_NVPSIZ_NONE      (0<<8)
#define SF_NVPSIZ_32K       (3<<8)
#define SF_NVPSIZ_64K       (5<<8)
#define SF_NVPSIZ_128K      (7<<8)
#define SF_NVPSIZ_256K      (9<<8)

/* SF_NVDSIZ */
#define SF_NVDSIZ_NONE      0
/* SF_VDSIZ */
#define SF_VDSIZ_NONE       (0<<16)
#define SF_VDSIZ_1K         (1<<16)
#define SF_VDSIZ_2K         (2<<16)
#define SF_VDSIZ_4K         (4<<16)
#define SF_VDSIZ_8K         (8<<16)

/* SF_NVPTYP */
#define SF_NVPTYP_M         (1<<28)     /* M or F series */
#define SF_NVPTYP_C         (2<<28)     /* C series */
#define SF_NVPTYP_S         (3<<28)     /* S series */
#define SF_NVPTYP_R         (4<<28)     /* R series */
/*--------------------------------------*/
/* SF_RSR: Reset Status Flag Definition */
/*--------------------------------------*/

#define SF_EXT_RESET       0x6C                 /* External pin Cause Reset */
#define SF_WD_RESET        0x53                 /* Internal WatchDog Cause Reset */

/*----------------------------------*/
/* SF_PMR: Protect Control Register */
/*----------------------------------*/

#define SF_AIC             (0x1<<5)


/*--------------------------------*/
/* Sspecial Function Base Address */
/*--------------------------------*/

#define SF_BASE            ((StructSF *)  0xFFF00000)

#endif /* sf_h */
