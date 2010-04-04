;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : ebi.inc
;- Object               : Assembler External Bus Interface Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;------------------------------------------------------------------------------

;--------------------------------------------------------
;- Memory Controller User Interface Structure Definition
;--------------------------------------------------------
                    ^       0
EBI_CSR             #       4*8         ; Chip Select Register
EBI_RCR             #       4           ; Remap Command Register
EBI_MCR             #       4           ; Memory Control Register

;---------------------------------
;- EBI_CSR: Chip Select Registers
;---------------------------------

EBI_DBW             EQU     0x03        ;- Data Bus Width
EBI_NWS             EQU     0x1C        ;- Number of Wait States
EBI_WSE             EQU     0x20        ;- Wait State Enable
EBI_PAGES           EQU     0x180       ;- Page size
EBI_TDF             EQU     0xE00       ;- Number of Data Float Output Time Clock Cycle
EBI_BAT             EQU     0x1000      ;- Byte Access Type
EBI_CSE             EQU     0x2000      ;- Chip Select Enable
EBI_BA              EQU     0xFFF00000  ;- Base Address

;----------------------------------
;- EBI_RCR: Remap Control Register
;----------------------------------

EBI_RCB             EQU     0x01    ; Remap Command Bit

;-----------------------------------
;- EBI_MCR: Memory Control Register
;-----------------------------------

EBI_ALE             EQU     0x07    ;- Address Line Enable
EBI_DRP             EQU     0x10    ;- Data Read Protocol

;------------------
;- EBI Base Address
;------------------
EBI_BASE        EQU     0xFFE00000      ;- External Bus Interface

                END
