//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name               : lib_flash_at29.c
//* Object                  : FLASH programmer for :
//*                             - AT29LV1024
//*                             - AT29C020
//*
//* 1.0 22/11/00 JPP        : Creation
//*-----------------------------------------------------------------------------


//* --------------------------- include file ----------------------------------

#include    "lib_flash_at29.h"

//* ------------------------------  Local variable ----------------------------

/* Defines organization structure */
OrgDef OrgAT29LV11024[] =
{
    {
        512,
        256
    }
};
OrgDef OrgAT29C020[] =
{
    {
        512,
        512
    }
};
//* Define supported flash Table
FlashAt49BVDef FlashTableAT29[NB_FLASH_AT29_SUPPORTED] =
{
    {
        512*256,                  //* 128 K Bytes
        "AT29LV1024",
        ATMEL_MANUFACTURED,
        FLASH_AT29LV1024,
        0x000FFFFF,
        OrgAT29LV11024,
        1
    },
    {
        512*512,                  //* 256 K Bytes
        "AT29C020",
        ATMEL_MANUFACTURED,
        FLASH_AT29C020,
        0x000FFFFF,
        OrgAT29C020,
        1
    }

};

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
    for (count=0;count < TIME_OUT_AT29;count++)
    {
        /* Do nothing - just wait */
    }
}
//* --------------------------- Export function -------------------------------

//*----------------------------------------------------------------------------
//* Function Name       : flash_at29_identify
//* Object              : Get the device id
//* Input Parameters    : <base_addr> Flash base address
//* Output Parameters   : device_code or 0xFFFF if bad manuf code
//*----------------------------------------------------------------------------
flash_word flash_at29_identify( int base_addr )
{
    flash_word manuf_code, device_code;
    Pause();

    /* Enter Software Product Identification Mode  */
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = FLASH_WORD_COM_1;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_2)) = FLASH_WORD_COM_2;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = ID_IN_WORD_COM;
    /* Wait 10 ms for the device to change state */
    Pause();

    /* Read Manufacturer and device code from the device */
    manuf_code  = (*((volatile short *) (base_addr + 0))) & 0x00FF;
    device_code = (*((volatile short *) (base_addr + 2))) & 0x00FF;

    /* Exit Software Product Identification Mode  */
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = FLASH_WORD_COM_1;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_2)) = FLASH_WORD_COM_2;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = ID_OUT_WORD_COM;
    /* Wait 20 ms */
    Pause();

    /* Check the Manufacturer - Fail if not known */
    if (manuf_code != ATMEL_MANUFACTURED) {
        return FLASH_AT29LV_UNKNOW;
    }

  return device_code;
}
//*----------------------------------------------------------------------------
//* Function Name       : flash_at29_erase_write_flash_block
//* Object              : Write short in Flash
//* Input Parameters    : <flash> Flash descriptor
//*                       <base_addr> Flash base address
//*                       <load_addr> sector address to load
//*                       <data> data to write
//* Output Parameters   : status TRUE or FALSE
//*----------------------------------------------------------------------------
int flash_at29_erase_write_flash_block ( FlashAt49BVDef *flash , int base_addr,
                                        flash_word *load_addr, flash_word *data )
{
    int count;
    int size_sector;
    flash_word expected;

    //* Get the sector size
    size_sector = flash->flash_org->sector_size /2;

    //* Enter Data protection routine code
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = FLASH_WORD_COM_1;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_2)) = FLASH_WORD_COM_2;
    *((volatile short *)(base_addr + FLASH_SEQ_ADD_1)) = PROT_WORD_COM;

    /* Write the data in full int steps - regardless of FLASH Data bus width */
    for (count = 0; count < (size_sector) ; count++)
    {
         load_addr[count] = data[count];
    }
    /* Check that the final word has been written before continuing */
    expected = data[(size_sector)-1];
    for (count=0;
         expected != load_addr[(size_sector)-1];
         count++)
    {
        if (count == TIME_OUT_AT29)
        {
           return (FALSE);
        }
    }
    /* Reread the sector and check it matches what we wrote */
    for (count = 0; count < (size_sector) ; count++)
    {
        if (load_addr[count] != data[count])
        {
           return (FALSE);
        }
    }

    /* Return  */
    return (TRUE);
}

//* End of file
