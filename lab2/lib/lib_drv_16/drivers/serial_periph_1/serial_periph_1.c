//*---------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*---------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : serial_periph_1.c
//* Object              : Serial Peripheral Driver Library.
//*
//* 1.0 04/01/00 JCZ    : Creation
//* 1.1 12/03/01 HI     : Multi cs correction
//*---------------------------------------------------------------------------

#include    "serial_periph_1.h"

//*-----------------------------------------------------------------------------
//* Function Name       : serial_periph_1_handler
//* Object              : SPI Fixed Peripheral C interrupt handler.
//* Input Parameters    : <serial_periph_1_desc> = SPI Fixed Descriptor
//* Output Parameters   : none
//* Functions called    : none
//*-----------------------------------------------------------------------------
void serial_periph_1_c_handler ( SerialPeriph1Desc *serial_periph_1_desc )
//* Begin
{
    StructSPI               *spi_pt = serial_periph_1_desc->spi_desc->spi_base ;
    SerialPeriph1DataDesc   *spi_data = serial_periph_1_desc->serial_periph_1_data ;
    u_int       status ;

    while (( status = ( spi_pt->SP_SR & spi_pt->SP_IMR )) != 0 )
    {
        //* If End of Transmit Transfer interrupt occurred
        if (( status & SP_ENDTX) != 0 )
        {
            //* Clear the End Transmit Bit in the status
            status &= ~SP_ENDTX ;
            //* Switch SPI Driver Status
            switch ( spi_data->state )
            {
                case SERIAL_PERIPH_1_TX_CMD_ONLY :
                    //* Disable the Transmit Interrupt
                    spi_pt->SP_IDR = SP_ENDTX ;
		    //* Next State
                    spi_data->state = SERIAL_PERIPH_1_RX_CMD_ONLY ;
                    break ;

                case SERIAL_PERIPH_1_TX_CMD :
                    //* Next State
                    spi_data->state = SERIAL_PERIPH_1_RX_CMD ;
                    //* Initialize the next Transmit Pointer
                    spi_pt->SP_TPR = (u_int) spi_data->tx_data_pt ;
                    //* Intialize the next Transmit Counters
                    spi_pt->SP_TCR = spi_data->tx_data_size ;
                    break ;

                case SERIAL_PERIPH_1_TX_DATA :
                    //* Next State
		    spi_data->state = SERIAL_PERIPH_1_RX_DATA ;
                    //* Disable the Transmit Interrupt
                    spi_pt->SP_IDR = SP_ENDTX ;
                    break ;

                default :
                    spi_data->state = SERIAL_PERIPH_1_IDLE ;
		    spi_pt->SP_IDR = (SP_ENDRX | SP_ENDTX);
            }
            //* EndSwitch
        }
        //* EndIf

        //* If End of Receive Transfer interrupt occurred
        if (( status & SP_ENDRX) != 0 )
        {
            //* Clear the End Receive Bit in the status
            status &= ~SP_ENDRX ;
            //* Switch state of the SPI Driver
            switch ( spi_data->state  )
            {
                case SERIAL_PERIPH_1_RX_CMD_ONLY :
                    //* Disable the Transmit Interrupt
                    spi_pt->SP_IDR = SP_ENDRX ;
                    //* Next State
                    spi_data->state = SERIAL_PERIPH_1_IDLE ;
                    break ;

                case SERIAL_PERIPH_1_RX_CMD :
                    //* Next State
                    spi_data->state = SERIAL_PERIPH_1_TX_DATA ;
                    //* Initialize the next Receive Pointer
                    spi_pt->SP_RPR = (u_int) spi_data->rx_data_pt ;
                    //* Initialize the next Receive Counter
                    spi_pt->SP_RCR = spi_data->rx_data_size ;
                    break ;

                case SERIAL_PERIPH_1_RX_DATA :
                    //* Receive completed
                    spi_data->state = SERIAL_PERIPH_1_IDLE ;
                    //* Disable the Transmit Interrupt
                    spi_pt->SP_IDR = SP_ENDRX ;
                    break ;

                default :
                    spi_data->state = SERIAL_PERIPH_1_IDLE ;
		    spi_pt->SP_IDR = (SP_ENDRX | SP_ENDTX);
            }
            //* EndSwitch
        }
        //* EndIf
        if (( status & SP_OVRES) != 0 )
	{
	    spi_data->state = SERIAL_PERIPH_1_IDLE ;
	    spi_pt->SP_IDR = SP_OVRES ;
	}

    }
    //* EndWhile
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : serial_periph_1_open
//* Object              :
//* Input Parameters    : Peripheral Description address
//* Output Parameters   :
//* Functions called    :
//*-----------------------------------------------------------------------------
void serial_periph_1_open ( SerialPeriph1Desc *serial_periph_1_desc )
//* Begin
{
    u_int       mode_spi = SPI_MASTER ;
	u_int		temp1, temp2, temp3 ;

    StructSPI *spi_pt = serial_periph_1_desc->spi_desc->spi_base ;

	temp1 = serial_periph_1_desc->mode_spi ;  /* NeW */
	temp2 = SP_PCSDEC ;		/* NeW */
	temp3 = temp1 & temp2 ;

	if (temp3 == SP_PCSDEC)
	//*if ((serial_periph_1_desc->mode_spi & SP_PCSDEC ) == SP_PCSDEC)
            mode_spi |= (SPI_NPCS0_USED | SPI_NPCS1_USED | SPI_NPCS2_USED | SPI_NPCS3_USED);
	else
	{
		switch ( serial_periph_1_desc->spi_periph_id )
		{
			case 0: mode_spi |= SPI_NPCS0_USED ; break ;
			case 1: mode_spi |= SPI_NPCS1_USED ; break ;
			case 2: mode_spi |= SPI_NPCS2_USED ; break ;
			case 3: mode_spi |= SPI_NPCS3_USED ; break ;
			default : break;
		}
	}
    //* Open the SPI peripheral
    at91_spi_open ( serial_periph_1_desc->spi_desc, mode_spi ) ;

    //* Initialize the SPI Interrupt
    at91_irq_open ( serial_periph_1_desc->spi_desc->periph_id ,
                    3, AIC_SRCTYPE_INT_LEVEL_SENSITIVE ,
                    serial_periph_1_desc->asm_handler ) ;

    //* Initialize SPI Mode register
    mode_spi = serial_periph_1_desc->mode_spi | SP_MSTR ;

	if (serial_periph_1_desc->mode_spi & SP_PCSDEC == SP_PCSDEC)
            mode_spi |= (serial_periph_1_desc->spi_periph_id << 16) ;
	else
	{
		if (serial_periph_1_desc->spi_periph_id < 4)
		{
			switch ( serial_periph_1_desc->spi_periph_id )
			{
				case 0 : mode_spi |= SP_PCS0 ; break ;
				case 1 : mode_spi |= SP_PCS1 ; break ;
				case 2 : mode_spi |= SP_PCS2 ; break ;
				case 3 : mode_spi |= SP_PCS3 ; break ;
				default : break;
			}
		}
	}

    spi_pt->SP_MR = mode_spi ;

    if ( serial_periph_1_desc->spi_periph_id < 4 )
    {
        //* Program the corresponding Chip Select Register
        spi_pt->SP_CSR[serial_periph_1_desc->spi_periph_id] = serial_periph_1_desc->mode_spi_periph ;
    }
    else
    {
        //* Program the corresponding Chip Select Register
        spi_pt->SP_CSR[serial_periph_1_desc->spi_periph_id >> 2] = serial_periph_1_desc->mode_spi_periph ;
    }
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : serial_periph_1_close
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*-----------------------------------------------------------------------------
void serial_periph_1_close ( SerialPeriph1Desc *serial_periph_1_desc )
//* Begin
{
    //* Close the SPI peripheral
    at91_spi_close ( serial_periph_1_desc->spi_desc ) ;
    //* Close the SPI interrupt
    at91_irq_close ( serial_periph_1_desc->spi_desc->periph_id ) ;
}
//* End

//*-----------------------------------------------------------------------------
//* Function Name       : serial_periph_1_write
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*-----------------------------------------------------------------------------
void serial_periph_1_write ( SerialPeriph1Desc *serial_periph_1_desc )
//* Begin
{
    StructSPI               *spi_pt = serial_periph_1_desc->spi_desc->spi_base ;
    SerialPeriph1DataDesc   *spi_data = serial_periph_1_desc->serial_periph_1_data ;

    if ( spi_data->tx_data_size == 0 )
    {
        spi_data->state = SERIAL_PERIPH_1_TX_CMD_ONLY ;
    }
    else
    {
        spi_data->state = SERIAL_PERIPH_1_TX_CMD ;
    }

    //* Initialize the Transmit and Receive Pointer
    spi_pt->SP_RPR = (u_int)spi_data->rx_cmd_pt ;
    spi_pt->SP_TPR = (u_int)spi_data->tx_cmd_pt ;

   //* Intialize the Transmit and Receive Counters
    spi_pt->SP_RCR = spi_data->rx_cmd_size ;
    spi_pt->SP_TCR = spi_data->tx_cmd_size ;

    //* Enable TDRE and RDRF Interrupt
    spi_pt->SP_IER = SP_ENDRX|SP_ENDTX ;
}
//* End


//*-----------------------------------------------------------------------------
//* Function Name       : get_spi_status
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*-----------------------------------------------------------------------------
u_int serial_periph_1_get_status ( SerialPeriph1Desc *serial_periph_1_desc )
//* Begin
{
    return ( serial_periph_1_desc->serial_periph_1_data->state ) ;
}
//* End

