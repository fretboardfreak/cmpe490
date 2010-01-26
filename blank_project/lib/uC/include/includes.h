/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2003, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
*********************************************************************************************************
*/

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>

#include    "user/app_cfg.h"
#include    "ucos_ii.h"
#include    "bsp.h"

#define     AT91_CLK          32000000L

#define     BIT00           0x00000001
#define     BIT01           0x00000002
#define     BIT02           0x00000004
#define     BIT03           0x00000008
#define     BIT04           0x00000010
#define     BIT05           0x00000020
#define     BIT06           0x00000040
#define     BIT07           0x00000080
#define     BIT08           0x00000100
#define     BIT09           0x00000200
#define     BIT10           0x00000400
#define     BIT11           0x00000800
#define     BIT12           0x00001000
#define     BIT13           0x00002000
#define     BIT14           0x00004000
#define     BIT15           0x00008000
#define     BIT16           0x00010000
#define     BIT17           0x00020000
#define     BIT18           0x00040000
#define     BIT19           0x00080000
#define     BIT20           0x00100000
#define     BIT21           0x00200000
#define     BIT22           0x00400000
#define     BIT23           0x00800000
#define     BIT24           0x01000000
#define     BIT25           0x02000000
#define     BIT26           0x04000000
#define     BIT27           0x08000000
#define     BIT28           0x10000000
#define     BIT29           0x20000000
#define     BIT30           0x40000000
#define     BIT31           0x80000000
