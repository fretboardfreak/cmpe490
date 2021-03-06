;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : ps40008.inc
;- Object               : AT91R40008 Power Saving Definition Assembly File.
;-
;- 1.0 06/08/01  PF     : Creation
;------------------------------------------------------------------------------

;--------------------------------------------------------------
;- Power Saving Controller User Interface Structure Definition
;--------------------------------------------------------------
                ^       0
PS_CR           #       4       ;- Control Register
PS_PCER         #       4       ;- Peripheral Clock Enable Register
PS_PCDR         #       4       ;- Peripheral Clock Disable Register
PS_PCSR         #       4       ;- Peripheral Clock Status Register

;-----------------------------------------------------------
;- PS_CR: Power Saving Controller Registers Bits Definition
;-----------------------------------------------------------

PS_ARM7DIS          EQU     0x1     ;- Disables the CPU clock

;---------------------------
;- Power Saving Base Address
;---------------------------

PS_BASE             EQU     0xFFFF4000      ;- Disables the CPU clock

            END
