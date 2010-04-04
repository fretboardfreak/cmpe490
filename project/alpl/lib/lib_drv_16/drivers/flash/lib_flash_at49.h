//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_flash_at49.h
//* Object              : Flash AT49BV Prototyping File
//*                             AT49BV1604/AT49BV1604T
//*                             AT49BV1614/AT49BV1604T
//*                             AT49BV8011/AT49BV8011T
//*                             AT49BV8011/AT49BV8011T
//*
//* 1.0 02/11/00 JPP    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_flash_at49_h
#define lib_flash_at49_h

//* --------------------------- include file ----------------------------------

#include "periph/stdc/std_c.h"

/*---------------------------  Constants definition -------------------------*/

/* Include Standard c Libraries to allow stand alone compiling and operation */
#define TRUE    1
#define FALSE   0

/*Flash type*/
#define ATMEL_MANUFACTURED          0x001F
#define FLASH_AT49BV_UNKNOW         0xFFFF
#define FLASH_AT49BV8011            0x00CB
#define FLASH_AT49BV8011T           0x004A
#define FLASH_AT49BV16x4            0x00C0
#define FLASH_AT49BV16x4T           0x00C2

/* Timeout loop count */
#define TIME_OUT                    1000000
/* Loop count for delay after sequence */
#define DELAY_ERASE                 10000000

/* Trials Number to erase a sector */
#define NB_TRIAL_ERASE              10

/* Define Flash Codes */
#define FLASH_SEQ_ADD1              (0x5555)
#define FLASH_SEQ_ADD2              (0x2AAA)

#define FLASH_CODE1                 ((flash_word)(0xAA))
#define FLASH_CODE2                 ((flash_word)(0x55))
#define ID_IN_CODE                  ((flash_word)(0x90))
#define ID_OUT_CODE                 ((flash_word)(0xF0))
#define WRITE_CODE                  ((flash_word)(0xA0))
#define ERASE_SECTOR_CODE1          ((flash_word)(0x80))
#define ERASE_SECTOR_CODE2          ((flash_word)(0x30))
#define CHIP_ERASE_CODE             ((flash_word)(0x10))

/*---------------------------  Structure definition -------------------------*/

/* Defines organization structure */
typedef struct OrgDef
{
    unsigned int    sector_number ;
    unsigned int    sector_size ;
} OrgDef ;

//* Defines Flash device definition structure
typedef struct FlashAt49BVDef
{
    unsigned int    flash_size;
    char            *flash_name;
    unsigned int    flash_manuf_id;
    unsigned int    flash_id;
    unsigned int    flash_mask;
    OrgDef          *flash_org;
    unsigned int    flash_block_nb;

} FlashAt49BVDef;

#define NB_FLASH_SUPPORTED 4

/*---------------------------  Function Prototyping -------------------------*/

extern flash_word flash_at49_identify ( flash_word *base_addr );
extern int flash_at49_check_sector_erased ( flash_word *sector_addr,int size);
extern int flash_at49_erase_sector ( flash_word *base_addr,flash_word *sector_addr);
extern int flash_at49_write_flash ( flash_word *base_addr,flash_word *load_addr,flash_word data );
extern int flash_at49_check_flash_erased ( FlashAt49BVDef *flash, flash_word *addr_base );
extern int flash_at49_erase_flash ( FlashAt49BVDef *flash,flash_word *base_addr );


/* write tools  defined in flash_atxx_write.c */

extern int flash_at49_erase_write_block ( u_char *buffer,int size);
extern void flash_at49_init_write ( flash_word *address_base,flash_word *address_load,FlashAt49BVDef *flash_type);

#endif  /* lib_flash_at49_h */
