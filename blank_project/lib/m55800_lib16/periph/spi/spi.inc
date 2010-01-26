;-----------------------------------------------------------------------------
;-      ATMEL Microcontroller Software Support  -   ROUSSET -
;-----------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;-----------------------------------------------------------------------------
;- File Name            : spi.inc
;- Object               : Serial Peripheral Interface Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;-----------------------------------------------------------------------------

;--------------------------------------
; Serial Peripheral Interface Structure
;--------------------------------------
                ^       0
SP_CR           #       4       ; Control Register
SP_MR           #       4       ; Mode Register
SP_RDR          #       4       ; Receive Data Register
SP_TDR          #       4       ; Transmit Data Register
SP_SR           #       4       ; Status Register
SP_IER          #       4       ; Interrupt Enable Register
SP_IDR          #       4       ; Interrupt Disable Register
SP_IMR          #       4       ; Interrupt Mask Register
SP_TPR          #       4       ; Transmit Pointer_Register
SP_TCR          #       4       ; Transmit Counter Register
SP_RPR          #       4       ; Receive Pointer_Register
SP_RCR          #       4       ; Receive Counter Register
SP_CSR          #       4       ; Chip Select Register 0 to 3

;-------------------
;- Control Register
;-------------------

SP_SPIEN        EQU         0x1     ;- SPI Enable
SP_SPIDIS       EQU         0x2     ;- SPI Disable
SP_SWRST        EQU         0x80    ;- SPI Software Reset

;----------------
;- Mode Register
;----------------

SP_MSTR         EQU         0x1         ;- Master Mode Select

SP_PS           EQU         0x2         ;- Peripheral Select
SP_PS_FIXED     EQU         0x0         ;- Fixed Peripheral Select
SP_PS_VARIABLE  EQU         0x2         ;- Variable Peripheral Select

SP_PCSDEC       EQU         0x4         ;- Chip Select Peripheral
SP_DIV32        EQU         0x8         ;- Divider by 32 on Master Clock Enable
SP_LLB          EQU         0x80        ;- Local Loopback

SP_PCS          EQU         0xF0000     ;- Peripheral Chip Select
SP_PCS0         EQU         0xE0000     ;- Chip Select 0
SP_PCS1         EQU         0xD0000     ;- Chip Select 1
SP_PCS2         EQU         0xB0000     ;- Chip Select 2
SP_PCS3         EQU         0x70000     ;- Chip Select 3

SP_DLYBCS       EQU         0xFF000000  ;- Delay Between Chip Select

;------------------
;- Status Register
;------------------

SP_RDRF         EQU         0x1         ;- Receive Data Register Full
SP_TDRE         EQU         0x2         ;- Transmitte Data Register Empty
SP_MODF         EQU         0x4         ;- Mode Fault
SP_OVRES        EQU         0x8         ;- Overrun Error Status
SP_ENDRX        EQU         0x10        ;- End of Receiver Transfer
SP_ENDTX        EQU         0x20        ;- End of Transmitter Transfer
SP_SPIENS       EQU         0x10000     ;- SPI Enable Status

;-----------------------
;- Chip Select Register
;-----------------------

SP_CPOL         EQU         0x1         ;- Clock Polarity
SP_NCPHA        EQU         0x2         ;- Clock Phase

SP_BITS         EQU         0xF0        ;- Bits Per Transfer
SP_BITS_8       EQU         0x00        ;- 8 Bits Per Transfer
SP_BITS_9       EQU         0x10        ;- 9 Bits Per Transfer
SP_BITS_10      EQU         0x20        ;- 10 Bits Per Transfer
SP_BITS_11      EQU         0x30        ;- 11 Bits Per Transfer
SP_BITS_12      EQU         0x40        ;- 12 Bits Per Transfer
SP_BITS_13      EQU         0x50        ;- 13 Bits Per Transfer
SP_BITS_14      EQU         0x60        ;- 14 Bits Per Transfer
SP_BITS_15      EQU         0x70        ;- 15 Bits Per Transfer
SP_BITS_16      EQU         0x80        ;- 16 Bits Per Transfer

SP_SCBR         EQU         0xFF00      ;- Serial Clock Baud Rate
SP_DLYBS        EQU         0xFF0000    ;- Delay Before SPCK
SP_DLYBCT       EQU         0xFF000000  ;- Delay Between Consecutive Transfer

                END
