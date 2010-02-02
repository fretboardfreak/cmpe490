//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : lib_flash_at29.h
//* Object              : Flash AT29LV Prototyping File
//*                         - AT29LV1024
//*                         - AT29C020
//*
//* 1.0 02/11/00 JPP    : Creation
//*----------------------------------------------------------------------------

#ifndef lib_flash_at29_h
#define lib_flash_at29_h

//* --------------------------- include file ----------------------------------

#include "lib_flash_at49.h"     //* same structure definition

/*---------------------------  Constants definition -------------------------*/

/* Define the specific for the flash memory system */
#define FLASH_AT29LV_UNKNOW         0xFFFF

/*Flash type*/
#define FLASH_AT29LV1024                0X26
#define FLASH_AT29LV1024_SECTOR_SIZE    256     //* in byte
#define FLASH_AT29C020                  0XDA
#define FLASH_AT29C020_SECTOR_SIZE      512     //* in byte

#define FLASH_AT29_MAX_SECTOR_SIZE      FLASH_AT29C020_SECTOR_SIZE

/* Timeout loop count */
#define TIME_OUT_AT29       10000

/* Define Flash Codes */
#define FLASH_SEQ_ADD_1     (0x5555 << 1)
#define FLASH_SEQ_ADD_2     (0x2AAA << 1)

#define FLASH_WORD_COM_1    ((short)0xAAAA)
#define FLASH_WORD_COM_2    ((short)0x5555)
#define PROT_WORD_COM       ((short)0xA0A0)
#define ID_IN_WORD_COM      ((short)0x9090)
#define ID_OUT_WORD_COM     ((short)0xF0F0)

#define NB_FLASH_AT29_SUPPORTED 2

/*---------------------------  Function Prototyping -------------------------*/

extern flash_word flash_at29_identify ( int base_addr );
extern int flash_at29_erase_write_flash_block ( FlashAt49BVDef *flash , int base_addr,flash_word *load_addr,flash_word *data );

/* write tools  defined in flash_atxx_write.c */
extern void  flash_at29_init_write ( flash_word *address_base,flash_word *address_load,FlashAt49BVDef *flash_type);
extern int flash_at29_write_block ( u_char *buffer,int size);
extern int flash_at29_purge_write_block ( void);

#endif  /* lib_flash_at29_h */
