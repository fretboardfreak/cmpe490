//*---------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : serial_periph_1.h
//* Object              : Serial Peripheral Driver Library Header.
//*
//* 1.0 04/01/00 JCZ    : Creation
//*---------------------------------------------------------------------------

#ifndef serial_periph_1_h
#define serial_periph_1_h

#include    "periph/stdc/std_c.h"
#include    "periph/aic/lib_aic.h"
#include    "periph/spi/lib_spi.h"

/* Driver State */
#define     SERIAL_PERIPH_1_IDLE            0x0
#define     SERIAL_PERIPH_1_TX_CMD_ONLY     0x1
#define     SERIAL_PERIPH_1_RX_CMD_ONLY     0x2
#define     SERIAL_PERIPH_1_TX_CMD          0x3
#define     SERIAL_PERIPH_1_RX_CMD          0x4
#define     SERIAL_PERIPH_1_TX_DATA         0x5
#define     SERIAL_PERIPH_1_RX_DATA         0x6

/* Serial Peripheral Driver Data Descriptor */
typedef struct
{
    u_char      *tx_cmd_pt ;
    u_int       tx_cmd_size ;
    u_char      *rx_cmd_pt ;
    u_int       rx_cmd_size ;
    u_char      *tx_data_pt ;
    u_int       tx_data_size ;
    u_char      *rx_data_pt ;
    u_int       rx_data_size ;
    volatile 	u_char      state ;
    u_int       mode ;

} SerialPeriph1DataDesc ;

/* Serial Peripheral Driver Descriptor */
typedef struct
{
    const SpiDesc           *spi_desc ;
    SerialPeriph1DataDesc   *serial_periph_1_data ;
    u_int                   mode_spi ;
    u_int                   mode_spi_periph ;
    u_int                   mode_pin_spi ;
    TypeAICHandler          *asm_handler ;
    u_char                  spi_periph_id ;
} SerialPeriph1Desc ;

/* Fixed Peripheral SPI Driver function prototypes */
extern  void serial_periph_1_open ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  void serial_periph_1_close ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  void serial_periph_1_set_mode ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  void serial_periph_1_read ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  void serial_periph_1_write ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  u_int serial_periph_1_get_status ( SerialPeriph1Desc *serial_periph_1_desc ) ;
extern  void serial_periph_1_trig_cmd ( SerialPeriph1Desc *serial_periph_1_desc ) ;

#endif /* serial_periph_1_h */
