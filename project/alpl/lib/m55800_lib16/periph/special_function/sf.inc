;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : sf.inc
;- Object               : Assembler Special Function Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;------------------------------------------------------------------------------

;---------------------------------------------------------
; Chip Identification User Interface Structure Definition
;---------------------------------------------------------
                ^       0
SF_CIDR         #       4       ;- Chip ID Register
SF_EXID         #       4       ;- Chip ID Extension Register
SF_RSR          #       4       ;- Reset Status Register
                #       4       ;- Reserved 0
                #       4       ;- Reserved 1
                #       4       ;- Reserved 2
SF_PMR          #       4       ;- Protect Mode Register

;--------------------------------------------------------
;- SF_CIDR: Chip Identification Register Bits Definition
;--------------------------------------------------------

SF_VERSION          EQU     0x0000001F      ;- Version Number
SF_NVPSIZ           EQU     0x00000F00      ;- Non Volatile Program Memory Size
SF_NVDSIZ           EQU     0x0000F000      ;- Non Volatile Data Memory Size
SF_VDSIZ            EQU     0x000F0000      ;- Volatile Data Memory Size
SF_ARCH             EQU     0x0FF00000      ;- Architecture Code
SF_NVPTYP           EQU     0x70000000      ;- Non Volatile Program Memory Type
SF_EXT              EQU     0x10000000      ;- Extension Flag

;---------------------------------------
;- SF_RSR: Reset Status Flag Definition
;---------------------------------------

SF_EXT_RESET        EQU     0x6C            ;- External pin Cause Reset
SF_WD_RESET         EQU     0x53            ;- Internal WatchDog Cause Reset

SF_VDSIZ_MASK_SHIFT EQU     0x3C00          ;- SF_NVDSIZ shifted by 6

SF_ARCH_AT91x63     EQU     0x06300000
SF_ARCH_AT91x40     EQU     0x04000000
SF_ARCH_AT91x55     EQU     0x05500000

;--------------------------------
;- SF_PMR: Protect Mode Register
;--------------------------------

SF_AIC              EQU     0x20            ;- Protect Mode Enable

;-------------------------------
;- Special Function Base Address 
;-------------------------------

SF_BASE             EQU     0xFFF00000

        END
