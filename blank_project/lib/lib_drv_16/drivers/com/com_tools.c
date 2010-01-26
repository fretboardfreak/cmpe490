//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : com_tools.c
//* Object              : com port terminal tools
//*
//* 1.0 19/10/00 JPP    : Creation
//*----------------------------------------------------------------------------

#include <stdio.h>
#include "com.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_scanf
//* Object              : Get a string to USART manage Blackspace and echo
//* Input Parameters    : com descriptor, type string & val return value
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void at91_scanf(ComDesc *USART_pt ,char * type, int * val)
{
    u_int read = 0;
    char buff[10];
    u_int nb_read =0;
    while( (read != 0x0D) & (nb_read != sizeof(buff)) )
    {
        //* wait the USART Ready for reception
        while((at91_usart_get_status(USART_pt->usart) & US_RXRDY) ==0)  {}
        //* Get a char
        at91_usart_read (USART_pt->usart, &read );
        buff[nb_read]= (char)read;

        //* Manage Blackspace
        while((at91_usart_get_status(USART_pt->usart) & US_TXRDY) ==0)  {}
        if ((char)read == 0x08)
        {
            if ( nb_read != 0 )
            {
              nb_read--;
             at91_usart_write(USART_pt->usart,read);
            }
        }
        else
        {
          //* echo
          at91_usart_write(USART_pt->usart,read);
          nb_read++;
        }
    }
    //* scan the value
    sscanf(buff,type,val);
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_get_val
//* Object              : get a integer or no update the value
//* Input Parameters    : <val> value to update
//* Output Parameters   : value updated
//*----------------------------------------------------------------------------
int  at91_get_val(ComDesc *USART_pt , int val )
{
    int     read;
    char    buff [13];
    //* echo
    sprintf(buff,"%d :",val);
    at91_print(USART_pt,buff);

    //* scan new value
    read = 0xFF;
    at91_scanf( USART_pt,"%d",&read);
    //* update if change
    if ( read != 0xFF ) val=read;

    //* send RETURN
    at91_print_crlf(USART_pt);
    return val;
}
