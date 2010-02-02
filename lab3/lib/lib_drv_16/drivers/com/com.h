//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : com.h
//* Object              : Prototyping File.
//* 1.0 29/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

#ifndef com_h
#define com_h
#include    "periph/usart/lib_usart.h"

//* Data len
#define COM_5_BIT               0x00        /* 5 bits */
#define COM_6_BIT               0x40        /* 6 bits */
#define COM_7_BIT               0x80        /* 7 bits */
#define COM_8_BIT               0xC0        /* 8 bits */
//* Stop bit
#define COM_NBSTOP_1            0x0000      /* 1 Stop Bit */
#define COM_NBSTOP_1_5          0x1000      /* 1.5 Stop Bits */
#define COM_NBSTOP_2            0x2000      /* 2 Stop Bits */
//* Parity
#define COM_PAR_NONE             0x800       /* No Parity */
#define COM_PAR_EVEN             0x00        /* Even Parity */
#define COM_PAR_ODD              0x200       /* Odd Parity */
#define COM_PAR_SPACE            0x400       /* Space Parity to 0 */
#define COM_PAR_MARK             0x600       /* Marked Parity to 1 */
//* Flow Control
#define COM_FLOW_CONTROL_NONE    0x00

/* State */
#define COM_STATE_ENABLE        0x01
#define COM_STATE_DISABLE       0x02

 /* Structure def */
typedef struct
{
    const UsartDesc         *usart;
    int                     state ;
} ComDesc;


/* Function Prototyping com.c*/
extern void at91_open_com(ComDesc *USART_pt, int mode, u_short baub);
extern void at91_close_com(ComDesc *USART_pt);
extern void at91_print(ComDesc *USART_pt, char * buff);
extern void at91_print_frame (ComDesc *USART_pt, char * buff , u_short size);
extern void at91_print_crlf(ComDesc *USART_pt);
extern int  at91_getch(ComDesc *USART_pt ,int * value );
extern void at91_scanf(ComDesc *USART_pt ,char * type, int * val);
extern int  at91_get_val(ComDesc *USART_pt , int val );
extern void at91_send_byte(ComDesc *USART_pt, char buff);

/* Function Prototyping com_baud.c*/
extern u_short at91_baud_com( u_int mcki, u_int baud);
extern u_short at91_error_baud_com( u_int mcki, u_int baud);

#endif  /* com_h */
