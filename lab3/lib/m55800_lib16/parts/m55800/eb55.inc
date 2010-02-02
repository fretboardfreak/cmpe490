;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;-----------------------------------------------------------------------------
;- File Name            : eb55.inc
;- Object               : AT91M55800 Evaluation Board Features Header File.
;-
;- 1.0 25/05/00   PF    : Creation
;- 1.1 31/10/00  JPP    : Additing EBI description
;-----------------------------------------------------------------------------

            INCLUDE     ../../parts/m55800/m55800.inc

;----------------------------------------
;- AT91EB55 External Memories Definition
;----------------------------------------
;- Flash Memory : AT49BV1604 1Mx16
FLASH_BASE      EQU     0x01000000

EXT_SRAM_BASE   EQU     0x02000000
EXT_SRAM_SIZE   EQU     0x00040000              ; 256Kbytes
EXT_SRAM_LIMIT  EQU     (EXT_SRAM_BASE+EXT_SRAM_SIZE)

;------------------------------------------------------------------------------
;- EBI Initialization Data
;-------------------------
;- The EBI User Interface Image which is copied by the boot.
;- 25 MHz master clock assumed.
;- That's hardware! Details in the Electrical Datasheet of the AT91 device.
;- EBI Base Address is added at the end for commodity in copy code.
;------------------------------------------------------------------------------
EBI_CSR_0       EQU     (FLASH_BASE :OR: 0x2529)    ; 0x01000000, 16MB, 2 tdf, 16 bits, 3 WS
EBI_CSR_1       EQU     (EXT_SRAM_BASE :OR: 0x2121) ; 0x02000000, 16MB, 0 hold, 16 bits, 1 WS
EBI_CSR_2       EQU     0x20000000  ; unused
EBI_CSR_3       EQU     0x30000000  ; unused
EBI_CSR_4       EQU     0x40000000  ; unused
EBI_CSR_5       EQU     0x50000000  ; unused
EBI_CSR_6       EQU     0x60000000  ; unused
EBI_CSR_7       EQU     0x70000000  ; unused

;------------------
;- Leds Definition
;------------------

LED1            EQU     PB8         ;- DS1
LED2            EQU     PB9         ;- DS2
LED3            EQU     PB10        ;- DS3
LED4            EQU     PB11        ;- DS4
LED5            EQU     PB12        ;- DS5
LED6            EQU     PB13        ;- DS6
LED7            EQU     PB14        ;- DS7
LED8            EQU     PB15        ;- DS8

LED_PIO_CTRL    EQU     1
LED_MASK        EQU     0x0000FF00

;------------------------
;- Push Button Definition
;------------------------

BP_S1       EQU     PB20
BP_S2       EQU     PA9
BP_S3       EQU     PB17
BP_S4       EQU     PB19

PB_PIO_CTRL     EQU     1


;--------------------------
;- Serial EEPROM Definition
;--------------------------

SCL             EQU     PA1
SDA             EQU     PA2

            END
