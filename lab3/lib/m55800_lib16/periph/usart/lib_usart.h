//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_usart.h
//* Object              : USART Library Function Prototyping File.
//*
//* 1.0 01/04/00 JCZ    : Creation
//* 1.1 23/10/00  ED    : New at91_usart_send_frame
//* 1.2 15/12/00  PF	: Change the second "at91_usart_receive_frame"
//*						: declaration by "at91_usart_send_frame"
//*----------------------------------------------------------------------------

#ifndef lib_usart_h
#define lib_usart_h

#include    "periph/usart/usart.h"

/*---------------------------------------*/
/* USART Descriptor Structure Definition */
/*---------------------------------------*/
typedef struct
{
    StructUSART             *usart_base ;   /* Peripheral base */
    const PioCtrlDesc       *pio_ctrl ;     /* IO controller descriptor */
    u_char                  pin_rxd ;       /* RXD pin number in the PIO */
    u_char                  pin_txd ;       /* TXD pin number in the PIO */
    u_char                  pin_sck ;       /* SCK pin number in the PIO */
    u_char                  periph_id ;     /* USART Peripheral Identifier */
} UsartDesc ;

/* Function Prototyping */
extern void at91_usart_open  ( const UsartDesc *usart_pt , u_int mode , u_int speed , u_int timeguard ) ;
extern void at91_usart_close ( const UsartDesc *usart_pt ) ;
extern u_int at91_usart_get_status ( const UsartDesc *usart_pt ) ;
extern void at91_usart_trig_cmd ( const UsartDesc *usart_pt, u_int cmd ) ;
extern void at91_usart_write ( const UsartDesc *usart_pt, u_int character ) ;
extern void at91_usart_read  ( const UsartDesc *usart_pt, u_int *pt_char ) ;
extern u_int at91_usart_receive_frame ( const UsartDesc *usart_pt, char *pt_buffer, u_int max_size , u_int timeout );
extern u_int at91_usart_send_frame ( const UsartDesc *usart_pt, char *pt_buffer, u_int size_buf ) ;

#endif /* lib_usart_h */
