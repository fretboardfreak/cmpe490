//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : lib_ebi.c
//* Object              : External Bus Interface Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*-----------------------------------------------------------------------------

#include    "periph/ebi/lib_ebi.h"

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chip_select_open
//* Object              : Enable a chip select line according the required configuration
//* Input Parameters    : <cs_desc> = chip select descriptor
//* Output Parameters   : none
//* Functions called    : none
//*-----------------------------------------------------------------------------
void at91_chip_select_open ( ChipSelectDesc *cs_desc )
{
    u_int   csr = EBI_CSEN ;
    if ( cs_desc->wait_state > 0 )
    {
        csr |= (EBI_WSE | ((cs_desc->wait_state-1)<<2 )) ;
    }
    csr |= cs_desc->data_float ;
	if ( cs_desc->page_size == CS_1_MBYTE)
		 csr |=	EBI_PAGES_1M;
	else if ( cs_desc->page_size == CS_4_MBYTE)
		 csr |=	EBI_PAGES_4M;
    else if ( cs_desc->page_size == CS_16_MBYTE)
		 csr |=	EBI_PAGES_16M;
	else if ( cs_desc->page_size == CS_64_MBYTE)
		  csr |= EBI_PAGES_64M;
    csr |= cs_desc->base_address ;
    csr |= ( cs_desc->data_bus_width == CS_8_BIT_BUS ? EBI_DBW_8 : EBI_DBW_16 ) ;
    csr |= ( cs_desc->byte_access_type == CS_BYTE_SELECT ?
             EBI_BAT_BYTE_SELECT : EBI_BAT_BYTE_WRITE ) ;

    EBI_BASE->EBI_CSR[cs_desc->cs_id] = csr ;
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chip_select_close
//* Object              : Disable a chip select line
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    : None
//*-----------------------------------------------------------------------------
void at91_chip_select_close ( ChipSelectDesc *cs_desc )
{
    EBI_BASE->EBI_CSR[cs_desc->cs_id] &= ~EBI_CSEN ;
}

//*-----------------------------------------------------------------------------
//* Function Name       : at91_chip_select_get_status
//* Object              : Read a chip select line configuration
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    : None
//*-----------------------------------------------------------------------------
u_int at91_chip_select_get_status ( ChipSelectDesc *cs_desc )
{
    u_int csr = EBI_BASE->EBI_CSR[cs_desc->cs_id] ;

    return (  csr ) ;

}

