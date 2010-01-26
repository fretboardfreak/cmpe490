;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : aic.inc
;- Object               : Assembler Advanced Interrupt Controller Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;- 1.1 15/11/00 JPP     : Update AIC values
;------------------------------------------------------------------------------

;------------------------------------------
;- AIC User Interface Structure Definition
;------------------------------------------
                    ^       0
AIC_SMR             #       32*4        ;- Source Mode Register
AIC_SVR             #       32*4        ;- Source Vector Register
AIC_IVR             #       4           ;- IRQ Vector Register
AIC_FVR             #       4           ;- FIQ Vector Register
AIC_ISR             #       4           ;- Interrupt Status Register
AIC_IPR             #       4           ;- Interrupt Pending Register
AIC_IMR             #       4           ;- Interrupt Mask Register
AIC_CISR            #       4           ;- Core Interrupt Status Register
                    #       4           ;- Reserved 0
                    #       4           ;- Reserved 1
AIC_IECR            #       4           ;- Interrupt Enable Command Register
AIC_IDCR            #       4           ;- Interrupt Disable Command Register
AIC_ICCR            #       4           ;- Interrupt Clear Command Register
AIC_ISCR            #       4           ;- Interrupt Set Command Register
AIC_EOICR           #       4           ;-  of Interrupt Command Register
AIC_SPU             #       4           ;- Spurious Vector Register

;---------------------------------------------
;- AIC_SMR[]: Interrupt Source Mode Registers
;---------------------------------------------

AIC_PRIOR                       EQU     0x07    ;- Priority

AIC_SRCTYPE                     EQU     0x60    ;- Source Type Definition
AIC_SRCTYPE_INT_LEVEL_SENSITIVE EQU     0x00    ;- Level Sensitive
AIC_SRCTYPE_INT_EDGE_TRIGGERED  EQU     0x20    ;- Edge Triggered
AIC_SRCTYPE_EXT_LOW_LEVEL       EQU     0x00    ;- Low Level
AIC_SRCTYPE_EXT_NEGATIVE_EDGE   EQU     0x20    ;- Negative Edge
AIC_SRCTYPE_EXT_HIGH_LEVEL      EQU     0x40    ;- High Level
AIC_SRCTYPE_EXT_POSITIVE_EDGE   EQU     0x60    ;- Positive Edge

;--------------------------------------
;-  AIC_ISR: Interrupt Status Register
;--------------------------------------

AIC_IRQID               EQU     0x1F            ;- Current source interrupt

;-------------------------------------------
;- AIC_CISR: Interrupt Core Status Register
;-------------------------------------------

AIC_NFIQ                EQU     0x01            ;- Core FIQ Status
AIC_NIRQ                EQU     0x02            ;- Core IRQ Status

;--------------------------------------------
;- Advanced Interrupt COntroller BAse Address
;--------------------------------------------

AIC_BASE                EQU     0xFFFFF000

	END
