;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : usart.inc
;- Object               : Assembler USART Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;------------------------------------------------------------------------------

;-------------------------------------------
; USART User Interface Structure Definition
;-------------------------------------------
                ^       0
US_CR           #       4       ;- Control Register
US_MR           #       4       ;- Mode Register
US_IER          #       4       ;- Interrupt Enable Register
US_IDR          #       4       ;- Interrupt Disable Register
US_IMR          #       4       ;- Interrupt Mask Register
US_CSR          #       4       ;- Channel Status Register
US_RHR          #       4       ;- Receive Holding Register
US_THR          #       4       ;- Transmit Holding Register
US_BRGR         #       4       ;- Baud Rate Generator Register
US_RTOR         #       4       ;- Receiver Timeout Register
US_TTGR         #       4       ;- Transmitter Time-guard Register
                #       4       ;- Reserved
US_RPR          #       4       ;- Receiver Pointer Register
US_RCR          #       4       ;- Receiver Counter Register
US_TPR          #       4       ;- Transmitter Pointer Register
US_TCR          #       4       ;- Transmitter Counter Register

;---------------------------
;- US_CR : Control Register
;---------------------------
US_RSTRX            EQU     0x0004      ;- Reset Receiver
US_RSTTX            EQU     0x0008      ;- Reset Transmitter
US_RXEN             EQU     0x0010      ;- Receiver Enable
US_RXDIS            EQU     0x0020      ;- Receiver Disable
US_TXEN             EQU     0x0040      ;- Transmitter Enable
US_TXDIS            EQU     0x0080      ;- Transmitter Disable
US_RSTSTA           EQU     0x0100      ;- Reset Status Bits
US_STTBRK           EQU     0x0200      ;- Start Break
US_STPBRK           EQU     0x0400      ;- Stop Break
US_STTTO            EQU     0x0800      ;- Start Time-out
US_SENDA            EQU     0x1000      ;- Send Address

;------------------------
;- US_MR : Mode Register
;------------------------

US_CLKS             EQU     0x0030      ;- Clock Selection
US_CLKS_MCKI        EQU     0x00        ;- Master Clock
US_CLKS_MCKI8       EQU     0x10        ;- Master Clock divided by 8
US_CLKS_SCK         EQU     0x20        ;- External Clock
US_CLKS_SLCK        EQU     0x30        ;- Slow Clock

US_CHRL             EQU     0x00C0      ;- Byte Length
US_CHRL_5           EQU     0x00        ;- 5 bits
US_CHRL_6           EQU     0x40        ;- 6 bits
US_CHRL_7           EQU     0x80        ;- 7 bits
US_CHRL_8           EQU     0xC0        ;- 8 bits

US_SYNC             EQU     0x0100      ;- Synchronous Mode Enable

US_PAR              EQU     0x0E00      ;- Parity Mode
US_PAR_EVEN         EQU     0x00        ;- Even Parity
US_PAR_ODD          EQU     0x20        ;- Odd Parity
US_PAR_SPACE        EQU     0x40        ;- Space Parity to 0
US_PAR_MARK         EQU     0x60        ;- Marked Parity to 1
US_PAR_NO           EQU     0x80        ;- No Parity
US_PAR_MULTIDROP    EQU     0xA0        ;- Multi-drop Mode

US_NBSTOP           EQU     0x3000      ;- Stop Bit Number
US_NBSTOP_1         EQU     0x0000      ;- 1 Stop Bit
US_NBSTOP_1_5       EQU     0x1000      ;- 1.5 Stop Bits
US_NBSTOP_2         EQU     0x2000      ;- 2 Stop Bits

US_CHMODE                   EQU     0xC000  ;- Channel Mode
US_CHMODE_NORMAL            EQU     0x0000  ;- Normal Mode
US_CHMODE_AUTOMATIC_ECHO    EQU     0x4000  ;- Automatic Echo
US_CHMODE_LOCAL_LOOPBACK    EQU     0x8000  ;- Local Loopback
US_CHMODE_REMOTE_LOOPBACK   EQU     0xC000  ;- Remote Loopback

US_MODE9            EQU     0x20000     ;- 9 Bit Mode

US_CLKO             EQU     0x40000     ;- Baud Rate Output Enable

;------------------------------------------------------------------
;-  US_IER, US_IDR, US_IMR, US_IMR: Status and Interrupt Registers
;------------------------------------------------------------------

US_RXRDY            EQU     0x001       ;- Receiver Ready
US_TXRDY            EQU     0x002       ;- Transmitter Ready
US_RXBRK            EQU     0x004       ;- Receiver Break
US_ENDRX            EQU     0x008       ;- End of Receiver PDC Transfer
US_ENDTX            EQU     0x010       ;- End of Transmitter PDC Transfer
US_OVRE             EQU     0x020       ;- Overrun Error
US_FRAME            EQU     0x040       ;- Framing Error
US_PARE             EQU     0x080       ;- Parity Error
US_TIMEOUT          EQU     0x100       ;- Receiver Timeout
US_TXEMPTY          EQU     0x200       ;- Transmitter Empty

;------------------------------
;- USART Descriptor Structure
;------------------------------
                            ^       0
UsartDesc_UsartBase         #       4       ;- Peripheral base address
UsartDesc_PioCtrl           #       4       ;- IO controller descriptor
UsartDesc_PinRXD            #       1       ;- RXD pin number in the PIO
UsartDesc_PinTXD            #       1       ;- TXD pin number in the PIO
UsartDesc_PinSCK            #       1       ;- SCK pin number in the PIO
UsartDesc_PeriphId          #       1       ;- USART Peripheral Identifier

                END
