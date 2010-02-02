//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : flash_at49_data.c
//* Object              : FLASH description for :
//*
//* 1.0 02/11/00 JPP    : Creation
//*-----------------------------------------------------------------------------

#include    "lib_flash_at49.h"
//* Global Variable

/* Defines supported flash organizations */
OrgDef OrgAT49BV8011[] =
{
    /* 1 x 16kbytes sectors */
    {
        1,
        16*1024
    },
    /* 1 x 32 kbytes sectors */
    {
        1,
        32*1024,
    },
    /* 4 x 8 kbytes sectors */
    {
        4,
        8*1024,
    },
    /* 1 x 32 kbytes sectors */
    {
        1,
        32*1024,
    },
    /* 1 x 16kbytes sectors */
    {
        1,
        16*1024
    },
    /* 14 x 64 kbytes sectors */
    {
        14,
        64*1024,
    }
};

OrgDef OrgAT49BV8011T[] =
{
    /* 14 x 64 kbytes sectors */
    {
        14,
        64*1024,
    },
    /* 1 x 16kbytes sectors */
    {
        1,
        16*1024
    },
    /* 1 x 32 kbytes sectors */
    {
        1,
        32*1024,
    },
    /* 4 x 8 kbytes sectors */
    {
        4,
        8*1024,
    },
    /* 1 x 32 kbytes sectors */
    {
        1,
        32*1024,
    },
    /* 1 x 16kbytes sectors */
    {
        1,
        16*1024
    }
};

OrgDef OrgAT49BV16x4[] =
{
    /* 8 x 8kbytes sectors */
    {
        8,
        8*1024
    },
    /* 2 x 32 kbytes sectors */
    {
        2,
        32*1024,
    },
    /* 30 x 64 kbytes sectors */
    {
        30,
        64*1024,
    }
};

OrgDef OrgAT49BV16x4T[] =
{
    /* 30 x 64 kbytes sectors */
    {
        30,
        64*1024,
    },
    /* 2 x 32 kbytes sectors */
    {
        2,
        32*1024,
    },
    /* 8 x 8kbytes sectors */
    {
        8,
        8*1024
    }
};


/* Define supported flash Table */
FlashAt49BVDef FlashTable[NB_FLASH_SUPPORTED] =
{
    {
        1024*1024,                  /* 1 M Bytes */
        "AT49BV8011",
        ATMEL_MANUFACTURED,
        FLASH_AT49BV8011,
        0x000FFFFF,
        OrgAT49BV8011,
        sizeof(OrgAT49BV8011)/sizeof(OrgDef)
    },
    {
        1024*1024,                  /* 1 M Bytes */
        "AT49BV8011",
        ATMEL_MANUFACTURED,
        FLASH_AT49BV8011T,
        0x000FFFFF,
        OrgAT49BV8011T,
        sizeof(OrgAT49BV8011T)/sizeof(OrgDef)
    },
    {
        2*1024*1024,                /* 2 M Bytes */
        "AT49BV16x4",
        ATMEL_MANUFACTURED,
        FLASH_AT49BV16x4,
        0x001FFFFF,
        OrgAT49BV16x4,
        sizeof(OrgAT49BV16x4)/sizeof(OrgDef)
    },
    {
        2*1024*1024,                /* 2 M Bytes */
        "AT49BV16x4T",
        ATMEL_MANUFACTURED,
        FLASH_AT49BV16x4T,
        0x001FFFFF,
        OrgAT49BV16x4T,
        sizeof(OrgAT49BV16x4T)/sizeof(OrgDef)
    }

};

//* End
