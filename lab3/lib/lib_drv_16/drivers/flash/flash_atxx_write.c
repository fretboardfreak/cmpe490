//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : flash_atxx_write.c
//* Object              : Write flash function
//*                         - AT29LV1024
//*                         - AT29C020
//*                         - AT49BV1604/AT49BV1604T
//*                         - AT49BV1614/AT49BV1604T
//*                         - AT49BV8011/AT49BV8011T
//*                         - AT49BV8011/AT49BV8011T
//*
//* 1.0 02/11/00 JPP    : Creation
//*-----------------------------------------------------------------------------

#include    "drivers/flash/lib_flash_at49.h"
#include    "drivers/flash/lib_flash_at29.h"


//* Static data for AT29 and AT49
static  flash_word *addr_base;
static  flash_word *addr_load;
static  FlashAt49BVDef *flash;

//* Static Variable for AT49
static  flash_word  *addr_prg_sector ;
static  unsigned int block  ;
static  int         nb_sector  ;
static  int         first ;
static  int         erase  ;

//* AT29 static information
static int pt_tmp_data_sector;
static flash_word  tmp_data_sector[FLASH_AT29_MAX_SECTOR_SIZE/2] ;

//*----------------------------------------------------------------------------
//* Function Name       : flash_at29_init_write
//* Object              : check if sector is erased if not erase
//* Input Parameters    :
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
void  flash_at29_init_write ( flash_word *address_base,flash_word *address_load,FlashAt49BVDef *flash_type)
//* Begin
{
    int count;
        //* init the AT29 static data
        //* Address information
        addr_base = address_base ;
        addr_load= address_load;
        //* Data tampon
        for (count = 0 ; count < FLASH_AT29_MAX_SECTOR_SIZE/2 ; count++)
        {
            tmp_data_sector[count]=0;
        }
        // data tampon pointeur
        pt_tmp_data_sector =0;
        // sector info
        flash=flash_type;
}


//*----------------------------------------------------------------------------
//* Function Name       : flash_at29_purge_write_block
//* Object              :  write
//* Input Parameters    : <buffer> data block addressFlash
//*                       <size> sector size in byte
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
 int flash_at29_purge_write_block ( void)
//* Begin

{

    if ( pt_tmp_data_sector !=0)
    {
        if (!flash_at29_erase_write_flash_block (
                    flash ,(int) addr_base,addr_load,tmp_data_sector))
        {
            return (FALSE);
        }
        addr_load += pt_tmp_data_sector;
        pt_tmp_data_sector=0;
    }
    return (TRUE);
}

//*----------------------------------------------------------------------------
//* Function Name       : flash_at29_write_block
//* Object              :  write
//* Input Parameters    : <buffer> data block addressFlash
//*                       <size> sector size in byte
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
 int flash_at29_write_block ( u_char *buffer,int size)
//* Begin

{
    unsigned int    count;
    u_char * tmp;
    tmp = (u_char *) &tmp_data_sector[pt_tmp_data_sector];
    //* copy the input buffer in flash buffer
    for  ( count =0 ; count < size ; count ++)
    {
        tmp[count] = buffer[count];
    }
    pt_tmp_data_sector +=size/2;

    //* check if buffer full, ready for write

    if ( pt_tmp_data_sector == flash->flash_org->sector_size/2)
    {

        if (!flash_at29_erase_write_flash_block (
                    flash ,(int) addr_base,addr_load,tmp_data_sector))
        {
            return (FALSE);
        }
        addr_load += pt_tmp_data_sector;
        pt_tmp_data_sector=0;
    }
    return (TRUE);

}

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_init_write
//* Object              : check if sector is erased if not erase
//* Input Parameters    :
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
void  flash_at49_init_write ( flash_word *address_base,flash_word *address_load,FlashAt49BVDef *flash_type)
//* Begin
{
        addr_prg_sector = address_base ;
        addr_base = address_base ;
        addr_load= address_load;
        block = 0 ;
        nb_sector = 0 ;

        first = TRUE ;
        erase = FALSE ;
        flash=flash_type;
}
//*----------------------------------------------------------------------------
//* Function Name       : erase_sector
//* Object              : check if sector is erased if not erase
//* Input Parameters    : <base_addr> Flash base address
//*                       <sector_addr> base sector address
//*                       <size> sector size in byte
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
static int erase_sector ( flash_word *base_addr,flash_word *sector_addr,int size )
//* Begin
{
    int     trial = 0 ;
    //* While flash is not erased or too much erasing performed
    while (( flash_at49_check_sector_erased ( sector_addr, size ) == FALSE ) &&
           ( trial++ < NB_TRIAL_ERASE ))
    {
        if ( flash_at49_erase_sector(base_addr,sector_addr)  == FALSE )
        {
            //* return False
            return ( FALSE ) ;
        } //* Endif
    }//* EndWhile

    //* Return True
    return ( TRUE ) ;
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : flash_at49_erase_write_block
//* Object              : check if sector is erased if not erase erase and write
//* Input Parameters    : <buffer> data block addressFlash
//*                       <size> sector size in byte
//* Output Parameters   : if data sector erase TRUE or FALSE
//*----------------------------------------------------------------------------
int flash_at49_erase_write_block ( u_char *buffer,int size)
//* Begin

{
    unsigned short  data ;
    unsigned int    count;
    int         sector_found ;
    int         change_sector ;

    //* For each word read from the file
    for  ( count =0 ; count < size ; count +=2 )
    {
    //data = buffer[count];
         data =  (unsigned short) buffer[count]| (unsigned short)buffer[count+1]  << 8 ;
        //* Clear sector found flag
        sector_found = FALSE ;
        //* Clear Sector change flag
        change_sector = FALSE ;
        //* While sector not found
        while ( sector_found == FALSE )
        {
            //* If program address lower than current sector address + its size
            if (( addr_prg_sector + (flash->flash_org[block].sector_size/2) )
                > addr_load )
            {
                //* Flag sector found
                sector_found = TRUE ;
            }
            //* Else
            else
            {
                //* Flag sector change
                change_sector = TRUE ;
                //* Add current sector size to program address
                addr_prg_sector += (flash->flash_org[block].sector_size/2) ;

                //* Increment the sector number
                nb_sector++ ;
                //* If last sector in block tested
                if ( nb_sector >= flash->flash_org[block].sector_number )
                {
                    //* Re-initialize sector number in block
                    nb_sector = 0 ;
                    //* Increment block number
                    block ++ ;
                    //* If last block tested
                    if ( block >= flash->flash_block_nb )
                    {
                        //*  Error Address not found in the Flash Address Field Return False
                        return ( FALSE ) ;
                    }
                    //* Endif
                }
                //* Endif
            }
            //* EndIf
        }
        //* EndWhile

        //* Unflag Erasing
        erase = FALSE ;
        //* If new sector or first sector
        if (( change_sector == TRUE ) || ( first == TRUE ))
        {
            //* If not first sector
            if ( first == FALSE )
            {
                //* Flag Erasing
                erase = TRUE ;
            }
            //* Else, if first sector
            else
            {
                //* Flag to erase the sector
                erase = TRUE ;

            }
            //* Endif
        }
        //* Endif

        //* If Erasing flagged
        if ( erase == TRUE )
        {
            //* Erase, if Timeout
            if ( erase_sector ( addr_base,
                                addr_prg_sector,
                                flash->flash_org[block].sector_size) != TRUE )
            {
                //* Return False
                return ( FALSE ) ;
            }
            //* Endif
        }
        //* Endif


        //* Write the value read in Flash, if error
        if ( flash_at49_write_flash ( addr_base,addr_load, data )!= TRUE )
        {
            //* Return False
            return ( FALSE ) ;
        }
        //* Endif

        //* Increment load address
        addr_load ++ ;

        //* Remove first address to program flag
        first = FALSE ;
    }
    //* EndWhile

    //* Return True
    return ( TRUE ) ;
}
//* End

