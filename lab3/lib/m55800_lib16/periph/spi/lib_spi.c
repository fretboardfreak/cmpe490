//*---------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : lib_spi.c
//* Object              : Serial Peripheral Interface Library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*---------------------------------------------------------------------------

#include    "periph/spi/lib_spi.h"

//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_open
//* Object              : Open an SPI Channel
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//* Output Parameters   : TRUE
//* Functions called    : define_as_peripheral, init_interrupt
//*-----------------------------------------------------------------------------
void at91_spi_open ( const SpiDesc *spi_desc, u_int mode )
//* Begin
{
    u_int   pin_mask = (1<<spi_desc->pin_miso) |
                       (1<<spi_desc->pin_mosi) |
                       (1<<spi_desc->pin_spck) ;
    u_int   open_drain_mask = 0 ;
    
    //* Enable the SPI Clock
    at91_clock_open ( spi_desc->periph_id ) ;

    //* If Slave mode operation required
    if (( mode & SPI_MASTER ) == 0 )
    {
        //* Setup IOs mask with SPCK, MISO, MOSI and NSS
        pin_mask |= (1<<spi_desc->pin_npcs[0]) ;
    }
    //* Else (if master mode operations required)
    else
    {
        //* If NPCS0 is used
        if (( mode & SPI_NPCS0_USED ) != 0 )
        {
            //* Update the IOs mask accordingly
            pin_mask |= (1<<spi_desc->pin_npcs[0]) ;
            if (( mode & SPI_NPCS0_OPENDRAIN ) != 0 )
            {
                open_drain_mask |= (1<<spi_desc->pin_npcs[0]) ;
            }
        }
        //* If NPCS1 is used
        if (( mode & SPI_NPCS1_USED ) != 0 )
        {
            //* Update the IOs mask accordingly
            pin_mask |= (1<<spi_desc->pin_npcs[1]) ;
            if (( mode & SPI_NPCS1_OPENDRAIN ) != 0 )
            {
                open_drain_mask |= (1<<spi_desc->pin_npcs[1]) ;
            }
        }
        //* If NPCS2 is used
        if (( mode & SPI_NPCS2_USED ) != 0 )
        {
            //* Update the IOs mask accordingly
            pin_mask |= (1<<spi_desc->pin_npcs[2]) ;
            if (( mode & SPI_NPCS2_OPENDRAIN ) != 0 )
            {
                open_drain_mask |= (1<<spi_desc->pin_npcs[2]) ;
            }
        }
        //* If NPCS3 is used
        if (( mode & SPI_NPCS3_USED ) != 0 )
        {
            //* Update the IOs mask accordingly
            pin_mask |= (1<<spi_desc->pin_npcs[3]) ;
            if (( mode & SPI_NPCS3_OPENDRAIN ) != 0 )
            {
                open_drain_mask |= (1<<spi_desc->pin_npcs[3]) ;
            }
        }
        if (( mode & SPI_MISO_OPENDRAIN) != 0 )
        {
            open_drain_mask |= (1<<spi_desc->pin_miso) ;
        }
        if (( mode & SPI_MOSI_OPENDRAIN) != 0 )
        {
            open_drain_mask |= (1<<spi_desc->pin_mosi) ;
        }
        if (( mode & SPI_SPCK_OPENDRAIN) != 0 )
        {
            open_drain_mask |= (1<<spi_desc->pin_spck) ;
        }
    }
    //* Setup IOs according the required configuration
    at91_pio_set_mode ( spi_desc->pio_ctrl_desc, open_drain_mask, PIO_OPENDRAIN_ON ) ;
    at91_pio_close ( spi_desc->pio_ctrl_desc, pin_mask ) ;

    //* Reset the SPI
    spi_desc->spi_base->SP_CR = SP_SWRST ;
    //* Enable the SPI
    spi_desc->spi_base->SP_CR = SP_SPIEN ;
}
//* End

//*P
//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_close
//* Object              : Close an SPI Channel
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//* Output Parameters   : 
//* Functions called    : 
//*-----------------------------------------------------------------------------
void at91_spi_close ( const SpiDesc *spi_desc )
//* Begin
{
    u_int   pin_mask ;
    //* Disable the SPI
    spi_desc->spi_base->SP_CR = SP_SPIDIS ;

    //* Redefine all SPI signals as PIO
    pin_mask = ((1<<spi_desc->pin_spck) ||
                (1<<spi_desc->pin_miso) ||
                (1<<spi_desc->pin_mosi) ||
                (1<<spi_desc->pin_npcs[0]) ||
                (1<<spi_desc->pin_npcs[1]) ||
                (1<<spi_desc->pin_npcs[2]) ||
                (1<<spi_desc->pin_npcs[3])) ;
    at91_pio_open ( spi_desc->pio_ctrl_desc, pin_mask, RESET_PIO_CONF ) ;

     //* Disable the SPI Clock
    at91_clock_close ( spi_desc->periph_id ) ;
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_set_mode
//* Object              : Defines an SPI Mode Register
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//* Output Parameters   : none
//* Functions called    : 
//*-----------------------------------------------------------------------------
void at91_spi_set_mode ( const SpiDesc *spi_desc, u_int mode )
//* Begin
{
    spi_desc->spi_base->SP_MR = mode ;
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_read
//* Object              : 
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//* Output Parameters   : none
//* Functions called    : 
//*-----------------------------------------------------------------------------
void at91_spi_read ( const SpiDesc *spi_desc, short *data )
//* Begin
{
    *data = (spi_desc->spi_base->SP_RDR & SP_RD) ;
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_write
//* Object              : Write data to the SPI
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//*                     : <data> = data buffer pointer
//* Output Parameters   : TRUE
//* Functions called    : 
//*-----------------------------------------------------------------------------
void at91_spi_write ( const SpiDesc *spi_desc, short *data ) 
//* Begin
{
    spi_desc->spi_base->SP_TDR = *data ;
}
//* End
//*-----------------------------------------------------------------------------
//* Function Name       : at91_spi_get_status
//* Object              : Return SPI Status Register
//* Input Parameters    : <spi_desc> = SPI Descriptor pointer
//* Output Parameters   : none
//* Functions called    : 
//*-----------------------------------------------------------------------------
u_int at91_spi_get_status ( const SpiDesc *spi_desc )
//* Begin
{
    return ( spi_desc->spi_base->SP_SR ) ;
}
//* End



