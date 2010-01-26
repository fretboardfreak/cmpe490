//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : com.c
//* Object              : com port terminal
//*
//* 1.0 25/08/00 JPP    : Creation
//* 1.1 15/11/00 JPP    : additing wait PDC in at91_send_byte
//*----------------------------------------------------------------------------

#include <stdio.h>
#include "com.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_open_com
//* Object              : Open com Usart
//* Input Parameters    : com descriptor & mode
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_open_com(ComDesc *USART_pt, int mode, u_short baud)
//* Begin
{

    //* open usart in Asynchornous no time gard
    at91_usart_open (USART_pt->usart,(mode|US_CLKS_MCK), baud, 0);

    //* masque all interrup and Disable all interrupts
    USART_pt->usart->usart_base->US_IDR = 0xFFFFFFFF ;

    //* Set state
    USART_pt->state = COM_STATE_ENABLE;

}
//* End
//*----------------------------------------------------------------------------
//* Function Name       : at91_close_com
//* Object              : Close com Usart
//* Input Parameters    : com descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_close_com(ComDesc *USART_pt)
//* Begin
{
    //* Close Usart
    at91_usart_close (USART_pt->usart) ;
    //* Set state
    USART_pt->state = COM_STATE_ENABLE;

}
//* End
//*----------------------------------------------------------------------------
//* Function Name       : at91_print_frame
//* Object              : Send a string to USART with the PDC
//* Input Parameters    : com descriptor, String pointer, size
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_print_frame (ComDesc *USART_pt, char * buff , u_short size)
//* Begin
{
    //* Wait end PDC Transmission)
    while(( USART_pt->usart->usart_base->US_TCR) !=0)  {}
    //* Wait USART ready
    while((at91_usart_get_status(USART_pt->usart) & US_TXRDY) ==0)  {}
    //* set the PDC address
    USART_pt->usart->usart_base->US_TPR = (at91_reg) buff;
    //* set the size
    USART_pt->usart->usart_base->US_TCR = size;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_print
//* Object              : Send a string to USART
//* Input Parameters    : com descriptor & String pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_print(ComDesc *USART_pt, char * buff)
//* Begin
{
    u_int   i;
    for (i=0 ; buff[i]!=0;i++)
    {
        //* wait the USART Ready for transmission
        while((at91_usart_get_status(USART_pt->usart) & US_TXRDY) ==0)  {}
        //* write Char
        at91_usart_write(USART_pt->usart,buff[i]);
    }
}
//* End
//*----------------------------------------------------------------------------
//* Function Name       : at91_send_byte
//* Object              : Send a char (one byte to USART)
//* Input Parameters    : com descriptor & String pointer
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_send_byte(ComDesc *USART_pt, char buff)
//* Begin
{
     //* wait the USART Ready for transmission
	 //* PDC wait
	 while(( USART_pt->usart->usart_base->US_TCR) !=0)  {}
	 //* Char wait
     while((at91_usart_get_status(USART_pt->usart) & US_TXRDY) ==0)  {}
     //* write Char
     at91_usart_write(USART_pt->usart,buff);
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : at91_print_crlf
//* Object              : Send  "\n\r"
//* Input Parameters    : com descriptor
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_print_crlf(ComDesc *USART_pt)
{
    char buff[3];
    buff[0]='\n'; buff[1]='\r';buff[2]=0x00;
    at91_print(USART_pt,buff);
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_getch
//* Object              : Chek a char in usart
//* Input Parameters    : com descriptor & pt value
//* Output Parameters   : TRUE if char or FALSE
//*----------------------------------------------------------------------------
int at91_getch(ComDesc *USART_pt ,int * value )
{
    u_int status;

     //* Check the USART Ready for reception
     status =(( at91_usart_get_status(USART_pt->usart) & US_RXRDY) ==0);
     if (! status)
     {
        at91_usart_read (USART_pt->usart,(u_int *) value );
     }
     return status;
}
