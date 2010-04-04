//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : com_baud.c
//* Object              : Baud rate compute com port terminal
//*
//* 1.0 25/08/00 JPP    : Creation
//*----------------------------------------------------------------------------

//#include "com.h"
#include "drivers/com/com.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_baud_com
//* Object              : Compute the baud rate
//* Input Parameters    : <mcki> external mcki if use in usart US_CLKS_MCK8 you
//*                              must be divided mcki by 8
//*                       <baud> use standart baud rate 4800,9600,19200,...
//* Output Parameters   : Usart CD baud value
//*----------------------------------------------------------------------------
u_short at91_baud_com( u_int mcki, u_int baud)
//* Begin
{
    u_short cd;
    u_int   user_baud;

    //* baud rate calculation
    user_baud = ((mcki*10)/(baud*16));
    //*
    cd  = user_baud/10;
    //* compute the error
    user_baud = (user_baud - (cd *10));
    //* aproximation
    if (user_baud >= 5) cd++;
    // return the CD value for the Usart
    return cd;
}
//* End
//*----------------------------------------------------------------------------
//* Function Name       : at91_error_baud_com
//* Object              : Compute the baud rate
//* Input Parameters    : <mcki> external mcki if use in usart US_CLKS_MCK8 you
//*                              must be divided mcki by 8
//*                       <baud> use standart baud rate 4800,9600,19200,...
//* Output Parameters   : baud error rate in % (sup average)
//*----------------------------------------------------------------------------
u_short at91_error_baud_com( u_int mcki, u_int baud)
//* Begin
{
    u_short cd;
    u_int usart_baud;
    //* Calculate the User cd
    cd = at91_baud_com(mcki, baud);

    //* compute the real baud rate
    usart_baud = (mcki/(cd*16));

    //* compute error
    if (usart_baud < (baud))
     cd =  100 - ((usart_baud*100)/baud);
    else
     cd =  100- ((baud*100)/usart_baud) ;

    // return the error value for the Usart
    return  cd;
}
//* End
