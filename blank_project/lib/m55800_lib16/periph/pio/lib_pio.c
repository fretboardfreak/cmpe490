//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_pio.c
//* Object              : PIO functions library.
//*
//* 1.0 01/04/00 JCZ    : Creation
//*----------------------------------------------------------------------------

#include    "periph/pio/lib_pio.h"
#include    "periph/power_saving/lib_power_save.h"

//*----------------------------------------------------------------------------
//* Function Name       : at91_pio_open
//* Object              : Setup pins to be Parallel IOs, as managed by the PIO
//* Input Parameters    : <pio_pt> = PIO Controller Descriptor
//*                     : <mask>   = bit mask identifying the PIOs
//*                     : <config> = mask identifying the PIOs configuration
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_pio_open ( const PioCtrlDesc *pio_pt, u_int mask, u_int config )
//* Begin
{
    //* If PIOs required to be output
    if ((config & PIO_SENSE_BIT) != 0 )
    {
        //* Defines the PIOs as output
        pio_pt->pio_base->PIO_OER = mask ;
    }
    //* Else
    else
    {
        //* Defines the PIOs as input
        pio_pt->pio_base->PIO_ODR = mask ;
    }

    //* If PIOs required to be filtered
    if ((config & PIO_FILTER_BIT) != 0 )
    {
        //* Enable the filter on PIOs
        pio_pt->pio_base->PIO_IFER = mask ;
    }
    else
    {
        //* Disable the filter on PIOs
        pio_pt->pio_base->PIO_IFDR = mask ;
    }

    //* If PIOs required to be open-drain
    if ((config & PIO_OPENDRAIN_BIT) != 0 )
    {
        //* Enable the filter on PIOs
        pio_pt->pio_base->PIO_MDER = mask ;
    }
    else
    {
        //* Disable the filter on PIOs
        pio_pt->pio_base->PIO_MDSR = mask ;
    }

    //* If PIOs required for an input change interrupt
    if ((config & PIO_INPUT_IRQ_BIT) != 0 )
    {
        //* Remove any interrupt */
        pio_pt->pio_base->PIO_ISR ; 
        //* Enable the Input Change Interrupt on PIOs
        pio_pt->pio_base->PIO_IER = mask ;
    }
    else
    {
        //* Disable the Input Change Interrupt on PIOs
        pio_pt->pio_base->PIO_IDR = mask ;
    }

    //* Defines the pins to be controlled by PIO Controller
    pio_pt->pio_base->PIO_PER = mask ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_pio_close
//* Object              : Cancel PIO Controller handling from pins managed by
//*                       a peripheral
//* Input Parameters    : <pio_pt> = PIO Descriptor pointer
//*                     : <mask>   = defines the pins to managed by peripheral
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_pio_close ( const PioCtrlDesc *pio_pt, u_int mask )
//* Begin
{
    //* Define PIOs to be controlled by peripherals
    pio_pt->pio_base->PIO_PDR = mask ;

//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_pio_write
//* Object              : Write a data on required PIOs
//* Input Parameters    : <pio_pt> = PIO Controller Descriptor Address
//*                     : <mask>   = defines work pins
//*                     : <state>  = defines set ( =0) or clear ( #0)
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_pio_write ( const PioCtrlDesc *pio_pt, u_int mask, u_int state )
//* Begin
{
    if (state == PIO_CLEAR_OUT )
    {
        //* Clear PIOs with data at 0 in CODR (Clear Output Data Register)
        pio_pt->pio_base->PIO_CODR = mask ;
    }
    else
    {
        //* Set PIOs with data at 1 in SODR (Set Output Data Register)
        pio_pt->pio_base->PIO_SODR = mask ;
    }

//* End
}
//*----------------------------------------------------------------------------
//* Function Name       : at91_pio_read
//* Object              : Read the state of the PIO pins
//* Input Parameters    : <pio_pt> = PIO Controller Descriptor Address
//* Output Parameters   : defines the pins value
//* Functions called    : at91_clock_get_status, at91_clock_open,
//*                       at91_clock_close
//*----------------------------------------------------------------------------
u_int at91_pio_read ( const PioCtrlDesc *pio_pt)

//* Begin
{

    u_int   return_val ;
    u_int   save_clock ;

    //* Get clock Status
    save_clock = at91_clock_get_status ( pio_pt->periph_id ) ;

    //* Enable the PIO Clock
    at91_clock_open ( pio_pt->periph_id ) ;

    //* Read the Data in input of the PIO Controller
    return_val = pio_pt->pio_base->PIO_PDSR ;

    //* If PIO controller clock was disabled
    if (( save_clock & (1 << pio_pt->periph_id)) == 0 )
    {
        //* Disable the PIO Clock
        at91_clock_close ( pio_pt->periph_id ) ;
    }

    return (return_val);
    
//* End
}

//*----------------------------------------------------------------------------
//* Function Name       : at91_pio_set_mode
//* Object              : Modify the mode of PIOs 
//* Input Parameters    : <pio_pt> = PIO Controller Descriptor
//*                     : <mask>   = bit mask identifying the PIOs
//*                     : <mode> = the required PIOs configuration
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void at91_pio_set_mode ( const PioCtrlDesc *pio_pt, u_int mask, u_int mode )
//* Begin
{
    //* If PIOs required to be filtered
    if ((mode & PIO_FILTER_BIT) != 0 )
        //* Enable the filter on PIOs
        pio_pt->pio_base->PIO_IFER = mask ;
    //* Else
    else
        //* Disable the filter on PIOs
        pio_pt->pio_base->PIO_IFDR = mask ;

    //* If PIOs required to be open-drain
    if ((mode & PIO_OPENDRAIN_BIT) != 0 )
        //* Enable the filter on PIOs
        pio_pt->pio_base->PIO_MDER = mask ;
    //* Else
    else
        //* Disable the filter on PIOs
        pio_pt->pio_base->PIO_MDSR = mask ;
//* End
}
