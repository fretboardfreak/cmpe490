//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : terminal.c
//* Object              : Terminal functions Library.
//*
//* 1.0 13/04/00 EL     : Creation
//*----------------------------------------------------------------------------

#include    "terminal.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_terminal_c_handler
//* Object              :
//* Input Parameters    : terminal descriptor
//* Output Parameters   : None
//* Functions called    :
//*----------------------------------------------------------------------------
void at91_terminal_c_handler ( TerminalDesc *term_desc )
//* Begin
{
    u_int   status ;
    StructUSART         *usart = term_desc->usart_desc->usart_base ;
    TerminalDataDesc    *data = term_desc->term_data ;

    while (( status = ( usart->US_CSR & usart->US_IMR )) != 0 )
    {
        //* If a reception error occured
        if (( status & US_MASK_IRQ_ERROR ) != 0 )
        {
            status &= ~US_RXRDY ;
            usart->US_CR = US_RSTSTA ;
            usart->US_RHR ;
        }

        //* RXRDY interrupt
        if (( status & US_RXRDY ) != 0 )
        {
            if ((u_int)data->rx_cnt == TERMINAL_SIZE_BUFFER)
            {
                data->error |= TERMINAL_ERROR_RX_OVF ;
            }
            else
            {
                data->rx_cnt++;

                //* reception
                *(data->rx_in_pt) = usart->US_RHR ;

                //* transmission
                usart->US_THR = *(data->rx_in_pt);

                data->rx_in_pt++;
                if ((u_int)data->rx_in_pt >= (u_int)data->rx_buf + TERMINAL_SIZE_BUFFER)
                {
                    data->rx_in_pt = data->rx_buf ;
                }
            }
        }

        //* TXRDY interrupt
        if (( status & US_TXRDY ) != 0 )
        {
            if ((u_int)data->tx_cnt > 0)
            {
                data->tx_cnt--;

                //* transmission
                usart->US_THR = *(data->tx_out_pt)++ ;

                if ((u_int)data->tx_out_pt >= (u_int)data->tx_buf + TERMINAL_SIZE_BUFFER)
                {
                    data->tx_out_pt = data->tx_buf ;
                    data->tx_cnt = 0;
                }
            }
            else
            {

        //* reset tx pointer
        data->tx_in_pt = data->tx_buf;
        data->tx_out_pt = data->tx_buf;

            //* Disable the TXRDY interrupt
                usart->US_IDR = 0x02;
            }
        }
    }
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_terminal_open
//* Object              :
//* Input Parameters    : terminal descriptor
//* Output Parameters   : None
//* Functions called    : at91_usart_open
//*----------------------------------------------------------------------------
void at91_terminal_open ( TerminalDesc *term_desc )
//* Begin
{
    TerminalDataDesc    *data = term_desc->term_data ;

    at91_usart_open ( term_desc->usart_desc, term_desc->format,term_desc->baud_rate, 0 ) ;

    data->rx_in_pt = data->rx_buf ;
    data->tx_in_pt = data->tx_buf ;
    data->rx_out_pt = data->rx_buf ;
    data->tx_out_pt = data->tx_buf ;
    data->rx_cnt = 0 ;
    data->tx_cnt = 0 ;

}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_terminal_close
//* Object              :
//* Input Parameters    : terminal descriptor
//* Output Parameters   : None
//* Functions called    : at91_usart_close
//*----------------------------------------------------------------------------
void at91_terminal_close ( TerminalDesc *term_desc )
//* Begin
{
    at91_usart_close(term_desc->usart_desc);
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_terminal_read
//* Object              :
//* Input Parameters    : terminal descriptor
//* Output Parameters   : The number of character read
//* Functions called    :
//*----------------------------------------------------------------------------
u_int at91_terminal_read ( TerminalDesc *term_desc, char *character )
//* Begin
{

    TerminalDataDesc    *data = term_desc->term_data ;

    if ( data->rx_cnt > 0 )
    {
        data->rx_cnt-- ;
        *character = *(data->rx_out_pt)++ ;
    if ((u_int)data->rx_out_pt >= (u_int)data->rx_buf + TERMINAL_SIZE_BUFFER)
        data->rx_out_pt = data->rx_buf;
        return (1) ;
    }
    return (0) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_terminal_write
//* Object              :
//* Input Parameters    : terminal_descritor, string to write
//* Output Parameters   : None
//* Functions called    :
//*----------------------------------------------------------------------------
void at91_terminal_write (TerminalDesc *term_desc, char *character)
//* Begin
{
    TerminalDataDesc    *data=term_desc->term_data;

    if (data->tx_cnt < TERMINAL_SIZE_BUFFER)
    {
       data->tx_cnt++ ;
       *(data->tx_in_pt)++ = *character ;
    }
    else
    {
        data->error |= TERMINAL_ERROR_TX_OVF ;
    data->tx_in_pt = data->tx_buf;
    data->tx_cnt = 0;
    }
}
//* End
