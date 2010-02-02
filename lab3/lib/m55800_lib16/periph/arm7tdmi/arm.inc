;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : arm.inc
;- Object               : Assembler Arm7TDMI Core Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;------------------------------------------------------------------------------

;--------------------------------
;- ARM Core Mode and Status Bits
;--------------------------------

ARM_MODE_USER           EQU     0x10
ARM_MODE_FIQ            EQU     0x11
ARM_MODE_IRQ            EQU     0x12
ARM_MODE_SVC            EQU     0x13
ARM_MODE_ABORT          EQU     0x17
ARM_MODE_UNDEF          EQU     0x1B
ARM_MODE_SYS            EQU     0x1F

I_BIT                   EQU     0x80
F_BIT                   EQU     0x40
T_BIT                   EQU     0x20

            END
