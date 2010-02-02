//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name               : lib_flash_at49.c
//* Object                  : FLASH programmer for :
//*                             - AT49BV1604/AT49BV1604T
//*                             - AT49BV1614/AT49BV1604T
//*                             - AT49BV8011/AT49BV8011T
//*                             - AT49BV8011/AT49BV8011T
//*
//* 1.1 06/11/00 JPP        : Creation
//*-----------------------------------------------------------------------------

//* --------------------------- include file ----------------------------------

#include    "lib_flash_at49.h"

//* --------------------------- Static function -------------------------------

//*----------------------------------------------------------------------------
//* Function Name       : Pause
//* Object              : wait flash responce
//* Input Parameters    : none
//* Output Parameters   : none
//*----------------------------------------------------------------------------
static void Pause(void)
{
    int count;
    for (count=0;count < TIME_OUT/10 ;count++)
    {
        /* Do nothing - just wait */
    }
}

//* --------------------------- Export function -------------------------------

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_identify
//* Object              : Get the device id
//* Input Parameters    : <sart_addr> Flash base address
//* Output Parameters   : device_code or 0xFFFF if bad manuf code
//*----------------------------------------------------------------------------
flash_word flash_at49_identify ( flash_word *base_addr )
//* Begin
{
    flash_word      manuf_code ;
    flash_word      device_code ;
    Pause();
    //* Enter Software Product Identification Mode
    *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
    *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
    *(base_addr + FLASH_SEQ_ADD1) = ID_IN_CODE;

    //* Read Manufacturer and device code from the device
    manuf_code  = *base_addr ;
    device_code = *(base_addr + 1) ;

    //* Exit Software Product Identification Mode
    *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
    *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
    *(base_addr + FLASH_SEQ_ADD1) = ID_OUT_CODE;

    if ( manuf_code != ATMEL_MANUFACTURED )
    {
        return (FLASH_AT49BV_UNKNOW);
    }

    //* Return pointer to Flash found
    return ( device_code ) ;
}

//*----------------------------------------------------------------------------
//* Function Name       : flash_wait_flash_ready
//* Object              : wait the end of write
//* Input Parameters    : <address> Adress to write
//*                       <data> data write at the  <address>
//* Output Parameters   : if data write TRUE or FALSE if time out
//*----------------------------------------------------------------------------
int flash_wait_flash_ready ( flash_word *address, flash_word data )
{
//* Begin
    int i = 0 ;

    //* While two consecutive read don't give same value or timeout
    while (( *address != data ) && ( i++ < TIME_OUT )) ;

    //* If timeout
    if ( i < TIME_OUT )
    {
        return ( TRUE ) ;
    }
    //* Else
    else
    {
        return ( FALSE ) ;
    }
    //* Endif
}
//* End
//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_check_sector_erased
//* Object              : check if sector is erased
//* Input Parameters    : <sector_addr> base sector address
//*                       <size> sector size in byte
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
int flash_at49_check_sector_erased ( flash_word *sector_addr,int size)
//* Begin
{
    int     i ;
    flash_word  read_data ;

    //* For each word of the sector
    for ( i = 0 ; i < (size/2) ; i ++ )
    {
        //* Check erased value reading, if not
        if (( read_data = *(sector_addr + i)) != (flash_word)0xFFFF )
        {
            return ( FALSE ) ;
        }
        //* Endif
    }
    //* Endfor

    //* Return True
    return ( TRUE ) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_check_flash_erased
//* Object              : check if all sector are erased
//* Input Parameters    : <flash> Flash descriptor
//*                       <sector_addr> base sector address
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
int flash_at49_check_flash_erased ( FlashAt49BVDef *flash, flash_word *addr_base )
//* Begin
{
    int         i ;
    flash_word  read_data ;
    int         size = flash->flash_size ;

    //* For each word of the flash
    for ( i = 0 ; i < (size/2) ; i ++ )
    {
        //* Check erased value reading, if not
        if (( read_data = *(addr_base + i)) != (flash_word)0xFFFF )
        {
            //*  return False
            return ( FALSE ) ;
        }
        //* Endif
    }
    //* Endfor

    //* Return True
    return ( TRUE ) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_erase_flash
//* Object              : ERASSE FLASH
//* Input Parameters    : <flash> Flash descriptor
//*                       <base_address> base sector address
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
int flash_at49_erase_flash ( FlashAt49BVDef *flash,flash_word *base_addr )
//* Begin
{
    int     trial = 0;
    int     cmpt;
    int     status= TRUE;
    //* While flash is not erased or too much erasing performed
    while (( flash_at49_check_flash_erased ( flash, base_addr ) == FALSE ) &&
           ( trial++ < NB_TRIAL_ERASE ))
    {

        //* Enter Sector Erase Sequence codes
        *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
        *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
        *(base_addr + FLASH_SEQ_ADD1) = ERASE_SECTOR_CODE1;
        *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
        *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
        *(base_addr + FLASH_SEQ_ADD1) = CHIP_ERASE_CODE;

        //* wait
        for ( cmpt = 0 ; cmpt < DELAY_ERASE ; cmpt ++ ) ;

        //* Wait for Flash Ready after Erase, if timeout
        if ( flash_wait_flash_ready ( base_addr,0xFFFF ) == FALSE )
        {
            //* return False
            if ( trial==NB_TRIAL_ERASE) return (FALSE) ;

        }
        //* Endif
    }
    //* EndWhile

    //* Return True
    return ( status ) ;
}
//* End


//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_erase_sector
//* Object              : erase flash sector
//* Input Parameters    : <base_addr> Flash base address
//*                       <sector_addr> Flash sector address
//* Output Parameters   : none
//*----------------------------------------------------------------------------
int  flash_at49_erase_sector ( flash_word *base_addr,flash_word *sector_addr)
//* Begin
{

    //* Enter Sector Erase Sequence codes
    *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
    *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
    *(base_addr + FLASH_SEQ_ADD1) = ERASE_SECTOR_CODE1;
    *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1;
    *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2;
    *sector_addr = ERASE_SECTOR_CODE2 ;
    //* Wait for Flash Ready after Erase, if timeout
    if ( flash_wait_flash_ready ( sector_addr, (flash_word)0xFFFF ) == FALSE )
    {
          return(FALSE);
    }

    return(TRUE);
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_write_flash
//* Object              : Write short in Flash
//* Input Parameters    :
//* Output Parameters   : none
//*----------------------------------------------------------------------------
int flash_at49_write_flash ( flash_word *base_addr,flash_word *load_addr,flash_word data )
{
    flash_word  read_data ;

    //* Enter Programming code sequence
    *(base_addr + FLASH_SEQ_ADD1) = FLASH_CODE1 ;
    *(base_addr + FLASH_SEQ_ADD2) = FLASH_CODE2 ;
    *(base_addr + FLASH_SEQ_ADD1) = WRITE_CODE ;
    *load_addr = data ;

    //* Wait for Flash ready after erasing, if timeout
    if ( flash_wait_flash_ready ( load_addr, data ) != TRUE )
    {
        return ( FALSE ) ;
    }
    //* Endif

    //* If Data written does not equal data
    if (( read_data = *load_addr ) != data )
    {
        //* Return False
        return ( FALSE );
    }
    //* Endif

    //* Return False
    return ( TRUE ) ;
}
//* End

