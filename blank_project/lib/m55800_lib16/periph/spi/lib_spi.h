//*---------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : lib_spi.h
//* Object              : Serial Peripheral Interface Library Header.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*---------------------------------------------------------------------------

#ifndef lib_spi_h
#define lib_spi_h

#include    "periph/stdc/std_c.h"
#include    "periph/spi/spi.h"
#include    "periph/pio/lib_pio.h"
#include    "periph/power_saving/lib_power_save.h"

typedef struct
{
    StructSPI           *spi_base ;
    const PioCtrlDesc   *pio_ctrl_desc ;
    u_char              periph_id ;
    u_char              pin_spck ;
    u_char              pin_miso ;
    u_char              pin_mosi ;
    u_char              pin_npcs[4] ;
} SpiDesc ;

/* SPI Opening mode definition */
#define SPI_MASTER          0x1
#define SPI_NPCS0_USED      0x2
#define SPI_NPCS0_OPENDRAIN 0x4
#define SPI_NPCS1_USED      0x8
#define SPI_NPCS1_OPENDRAIN 0x10
#define SPI_NPCS2_USED      0x20
#define SPI_NPCS2_OPENDRAIN 0x40
#define SPI_NPCS3_USED      0x80
#define SPI_NPCS3_OPENDRAIN 0x100
#define SPI_MISO_OPENDRAIN  0x200
#define SPI_MOSI_OPENDRAIN  0x400
#define SPI_SPCK_OPENDRAIN  0x800

extern  void at91_spi_open ( const SpiDesc *spi_desc, u_int mode ) ;
extern  void at91_spi_close ( const SpiDesc *spi_desc ) ;
extern  void at91_spi_set_mode ( const SpiDesc *spi_desc, u_int mode ) ;
extern  void at91_spi_read ( const SpiDesc *spi_desc, short *data ) ;
extern  void at91_spi_write ( const SpiDesc *spi_desc, short *data ) ;
extern  u_int at91_spi_get_status ( const SpiDesc *spi_desc ) ;
extern  void at91_spi_trig_cmd ( const SpiDesc *spi_desc ) ;

#endif /* lib_spi_h */


