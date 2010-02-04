//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_usart.c
//* Object              : USART functions Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//* 1.1 23/10/00  ED    : New at91_usart_send_frame, correct SYNC mode
//*----------------------------------------------------------------------------

#include    "periph/usart/lib_usart.h"
#include    "periph/power_saving/lib_power_save.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_open
//* Object              : Initialize an USART.
//* Input Parameters    : <usart_pt>  = the USART to initialize
//*                     : <mode>      = the Mode Register to be programmed
//*                     : <speed>     = the BRDR to be programmed
//*                     : <timeguard> = the US_TTGR to be programmed
//* Output Parameters   : None
//* Functions called    : at91_clock_open, at91_pio_close
//*----------------------------------------------------------------------------
void at91_usart_open ( const UsartDesc *usart_pt ,
                       u_int mode ,
                       u_int speed ,
                       u_int timeguard )
//* Begin
{
    //* Enable the clock
    at91_clock_open ( usart_pt->periph_id ) ;

    //* If External clock used
    if (( mode & SCK_USED ) != 0 )
    {
        //* Define RXD, TXD and SCK as peripheral
        at91_pio_close ( usart_pt->pio_ctrl,
                         (1 << usart_pt->pin_txd) |
                         (1 << usart_pt->pin_rxd) |
                         (1 << usart_pt->pin_sck) ) ;
    }
    //* Else
    else
    {
        //* Define RXD and TXD as peripheral
        at91_pio_close ( usart_pt->pio_ctrl,
                         (1 << usart_pt->pin_txd) |
                         (1 << usart_pt->pin_rxd) ) ;
    //* EndIf
    }

    //* Reset receiver and transmitter
    usart_pt->usart_base->US_CR = US_RSTRX | US_RSTTX | US_RXDIS | US_TXDIS ;

    //* Clear Transmit and Receive Counters
    usart_pt->usart_base->US_RCR = 0 ;
    usart_pt->usart_base->US_TCR = 0 ;

    //* Define the baud rate divisor register
    usart_pt->usart_base->US_BRGR = speed ;

    //* Define the USART mode
    usart_pt->usart_base->US_MR = mode  ;

    //* Write the Timeguard Register
    usart_pt->usart_base->US_TTGR = timeguard ;

    //* Enable receiver and transmitter
    usart_pt->usart_base->US_CR = US_RXEN | US_TXEN ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_close
//* Object              : Disable an USART.
//* Input Parameters    : <usart_pt> = USART Descriptor pointer
//* Output Parameters   : none
//* Functions called    : at91_clock_close, at91_pio_open
//*----------------------------------------------------------------------------
void at91_usart_close ( const UsartDesc *usart_pt )
//* Begin
{
    //* Disable the clock on the Peripheral
    at91_clock_close ( usart_pt->periph_id ) ;

    //* Define all USARTs pins as pio
    at91_pio_open ( usart_pt->pio_ctrl,
                    (1 << usart_pt->pin_txd) |
                    (1 << usart_pt->pin_rxd) |
                    (1 << usart_pt->pin_sck),
                    RESET_PIO_CONF ) ;

    //* Disable all interrupts
    usart_pt->usart_base->US_IDR = 0xFFFFFFFF ;

    //* Abort the Peripheral Data Transfers
    usart_pt->usart_base->US_RCR = 0 ;
    usart_pt->usart_base->US_TCR = 0 ;

    //* Disable receiver and transmitter and stop any activity immediately
    usart_pt->usart_base->US_CR = US_TXDIS | US_RXDIS | US_RSTTX | US_RSTRX ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_get_status
//* Object              : Read the Status Register of an USART.
//* Input Parameters    : <usart_pt> = USART Descriptor pointer
//* Output Parameters   : USART Status Register
//* Functions called    : none
//*----------------------------------------------------------------------------
u_int at91_usart_get_status ( const UsartDesc *usart_pt )
//* Begin
{
    //* Return the Control Status Register Value
    return ( usart_pt->usart_base->US_CSR ) ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_trig_cmd
//* Object              : Reset the Status Bits of an USART.
//* Input Parameters    : <usart_pt> = USART Descriptor pointer
//*                     : <cmd>      = command mask
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_usart_trig_cmd ( const UsartDesc *usart_pt, u_int cmd )
//* Begin
{
    //* Write the command in the Control Register
    usart_pt->usart_base->US_CR = cmd ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_write
//* Object              : Store a character in the Transmit hold Register.
//* Input Parameters    : <usart_pt>  = USART Descriptor pointer
//*                     : <character> = character to transmit
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_usart_write ( const UsartDesc *usart_pt, u_int character )
//* Begin
{
    //* Write the character in the Transmit Holding Register
    usart_pt->usart_base->US_THR = character ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_usart_read
//* Object              : Read a character from the Receive Register
//* Input Parameters    : <usart_pt> = USART Descriptor pointer
//*                     : <pt_char>  = point where to save the received character
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_usart_read ( const UsartDesc *usart_pt, u_int *pt_char )
//* Begin
{
    //* Read the received character and store it
    *pt_char = usart_pt->usart_base->US_RHR ;

//* End
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_usart_send_frame
//* Object              : Transmit a complete frame.
//* Input Parameters    : <usart_pt> =  USART pointer
//*                     : <pt_buffer> = the address of the receive buffer
//*                     : <max_size> = the maximum number of bytes to be
//*                     :              received
//*                     : <timeout> = the inter-character time delay in number
//*                     :             of byte
//* Output Parameters   :
//* Functions called    : none
//*-----------------------------------------------------------------------------
u_int at91_usart_send_frame ( const UsartDesc *usart_pt, char *pt_buffer, u_int size_buf )
//* Begin
{

    //* Wait for previous transfer finished
    while (( usart_pt->usart_base->US_CSR & US_ENDTX ) == 0 ) ;

    //* Store the address of the buffer
    usart_pt->usart_base->US_TPR = (u_int) pt_buffer ;

    //* Store the number of bytes to transmit
    usart_pt->usart_base->US_TCR = size_buf ;

    //* Return true
    return ( TRUE ) ;
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_usart_receive_frame
//* Object              : Receive a complete frame.
//* Input Parameters    : <usart_pt> =  USART pointer
//*                     : <pt_buffer> = the address of the receive buffer
//*                     : <max_size> = the maximum number of bytes to be
//*                     :              received
//*                     : <timeout> = the inter-character time delay in number
//*                     :             of byte
//* Output Parameters   :
//* Functions called    : none
//*-----------------------------------------------------------------------------
u_int at91_usart_receive_frame ( const UsartDesc *usart_pt, char *pt_buffer, u_int max_size , u_int timeout )
//* Begin
{

    //* Store the timeout value
    usart_pt->usart_base->US_RTOR = (timeout * 10 / 4) ;

    //* Restart the timeout logic
    usart_pt->usart_base->US_CR = US_STTTO ;

    //* Store the address of the buffer
    usart_pt->usart_base->US_RPR = (u_int) pt_buffer ;

    //* Store the number of bytes to receive
    usart_pt->usart_base->US_RCR = max_size ;

    //* Return true
    return ( TRUE ) ;
}
//* End
