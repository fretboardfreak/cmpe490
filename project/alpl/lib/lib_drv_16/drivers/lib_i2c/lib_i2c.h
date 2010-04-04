//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_i2c.h
//* Object              : I2C driver Function Prototyping File.
//*
//* 1.0 25/05/00 EL     : Creation
//* 1.1 06/09/00 EL     : Clean up
//* 2.1 15/01/02 JPP    : New functions added :
//*                         - at91_I2C_lineClose,
//*                         - at91_I2CWaitTime,
//*                         - at91_I2CTransfertEnd
//*----------------------------------------------------------------------------

#ifndef lib_i2c_h
#define lib_i2c_h

/*------------------- Include AT91 Library function -------------------------*/

#include    "periph/pio/lib_pio.h"
#include    "periph/timer_counter/lib_tc.h"

/*---------------------------  Constants definition -------------------------*/

//* I2C drivers internal mode
#define WRITE_BIT               0
#define READ_BIT                1
#define STOP                    2
#define DATA                    3
#define LOW_ADDRESS_WRITE       4
#define HIGH_ADDRESS_WRITE      5
#define LOW_ADDRESS_READ        6
#define HIGH_ADDRESS_READ       7
#define DEVICE_READ             8
#define DATA_READ               9

//* I2C drivers state
#define OK                      0   //* waiting new command
#define NOK                     1   //* working

/*---------------------------  Structure definition -------------------------*/

//* I2C structure for driver
typedef struct I2C
{
    u_char          *RxPtr;             //* Buffers address
    u_char          *RxEnd;
    u_char          *TxPtr;
    u_char          *TxEnd;

    u_char          deviceAddress;      //* work variables
    u_short         loadAddress;
    u_char          nb_ACK;
    u_int           nbI2CByte;
    u_char          mode;
    signed char     countBit;
    u_char          I2CByte;
    volatile u_char state;

    StructPIO           *pioa_base;     //* PIO field
    const PioCtrlDesc   *pio_ctrl_desc ;
    u_int               SDA_line;
    u_int               SCL_line;

    StructTCBlock       *TCBase;        //* Timer Counter field
    StructTC            *timerBase;
    u_char              channelId;
    u_int               timerMem;

    TypeAICHandler      *AICHandler;    //* IRQ field
    void (*I2CTCHandler) (struct I2C *);

} I2Cdesc ;

/*---------------------------  Function Prototyping -------------------------*/

//* Drivers function
extern void  at91_I2C_lineOpen(I2Cdesc *I2C_pt, u_int RCValue);
extern void  at91_I2C_lineClose(I2Cdesc *I2C_pt);
extern u_int at91_I2CWaitTime (I2Cdesc *I2C_pt,u_int time,u_int mcki);
extern void  at91_I2CWrite (I2Cdesc *I2C_pt, u_short loadAddress, u_int nbByte );
extern void  at91_I2CRead (I2Cdesc *I2C_pt, u_short loadAddress, u_int nbByte );
extern void  at91_I2CSendStopSDA (I2Cdesc *I2C_pt);
extern void  at91_I2CTransfertEnd(I2Cdesc *I2C_pt);

//* external Assembly interrupt entry point
extern void  I2C_lineHandlerInt(I2Cdesc *I2C_pt);

//* external error function interrupt entry point
extern void at91_I2CError(I2Cdesc *I2C_pt);
extern void no_handler_tc(I2Cdesc *I2C_pt);

#endif /* lib_i2c_h */
