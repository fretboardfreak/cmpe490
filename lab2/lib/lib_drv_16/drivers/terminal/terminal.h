//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : tertminal.h
//* Object              : Terminal Prototyping File.
//*
//* 1.0 13/04/00 EL     : Creation
//*----------------------------------------------------------------------------

#ifndef terminal_h
#define terminal_h

#include    "periph/usart/lib_usart.h"

#define TERMINAL_8_BIT      0x1
#define TERMINAL_NO_PARITY  0x2

#define TERMINAL_ERROR_RX_OVF   0x1
#define TERMINAL_ERROR_TX_OVF   0x2

#define TERMINAL_SIZE_BUFFER     0x100
/*------------------------------------------*/
/* Terminal Descriptor Structure Definition */
/*------------------------------------------*/
typedef struct
{
    u_char          rx_buf[TERMINAL_SIZE_BUFFER] ;
    u_char          tx_buf[TERMINAL_SIZE_BUFFER] ;
    u_char          *rx_in_pt ;
    u_char          *rx_out_pt ;
    u_int           rx_cnt ;
    u_char          *tx_in_pt ;
    u_char          *tx_out_pt ;
    u_int           tx_cnt ;
    u_int           error ;
} TerminalDataDesc ;

typedef struct
{
    const UsartDesc         *usart_desc ;
    TerminalDataDesc        *term_data ;
    u_int                   baud_rate ;
    u_int                   format ;
    TypeAICHandler          *terminal_asm_handler ;
} TerminalDesc ;

/* Function Prototyping */
extern void at91_terminal_c_handler  ( TerminalDesc *terminal_pt ) ;
extern void at91_terminal_open  ( TerminalDesc *terminal_pt ) ;
extern void at91_terminal_close ( TerminalDesc *terminal_pt ) ;
extern void at91_terminal_write ( TerminalDesc *term_desc, char *character ) ;
extern u_int at91_terminal_read  ( TerminalDesc *usart_pt, char *character ) ;

#endif /* terminal_h */
