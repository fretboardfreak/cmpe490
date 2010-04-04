;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : tc.inc
;- Object               : Assembler Timer Counter Definition File.
;-
;- 1.0 01/04/00 JCZ     : Creation
;------------------------------------------------------------------------------

;----------------------------------------------------
; Timer Counter  User Interface Structure Definition
;----------------------------------------------------
                ^       0
TC_CCR          #       4           ;- Channel Control Register
TC_CMR          #       4           ;- Channel Mode Register
                #       4           ;- Reserved 0
                #       4           ;- Reserved 1
TC_CV           #       4           ;- Counter Value
TC_RA           #       4           ;- Register A
TC_RB           #       4           ;- Register B
TC_RC           #       4           ;- Register C
TC_SR           #       4           ;- Status Register
TC_IER          #       4           ;- Interrupt Enable Register
TC_IDR          #       4           ;- Interrupt Disable Register
TC_IMR          #       4           ;- Interrupt Mask Register
                #       4           ;- Reserved 2
                #       4           ;- Reserved 3
                #       4           ;- Reserved 4
                #       4           ;- Reserved 5
TC_SIZE         #       0

;------------------------------
; Timer Counter Block Structure
;------------------------------
NB_TC_CHANNEL   EQU     3

                ^       0
TC0             #       TC_SIZE
TC1             #       TC_SIZE
TC2             #       TC_SIZE
TC_BCR          #       4
TC_BMR          #       4

;---------------------------------------------------------
;- TC_CCR: Timer Counter Control Register Bits Definition
;---------------------------------------------------------

TC_CLKEN        EQU     0x1             ;- Counter Clock Enable
TC_CLKDIS       EQU     0x2             ;- Counter Clock Disable
TC_SWTRG        EQU     0x4             ;- Software Trigger

;------------------------------------------------------
;- TC_CMR: Timer Counter Mode Register Bits Definition
;------------------------------------------------------

TC_TCCLKS       EQU     0x00000007      ;- Clock Selection
TC_CLKI         EQU     0x00000008      ;- Clock Inversion
TC_BURST        EQU     0x00000030      ;- Burst Signal Selection

TC_LDBSTOP      EQU     0x00000040      ;- Capture Mode : Counter Clock Stopped with RB Loading
TC_CPCSTOP      EQU     0x00000040      ;- Waveform Mode : Counter Clock Stopped with RC Compare

TC_LDBDIS       EQU     0x00000080      ;- Capture Mode : Counter Clock Disabled with RB Loading
TC_CPCDIS       EQU     0x00000080      ;- Waveform Mode : Counter Clock Disabled with RC Compare

TC_ETRGEDG      EQU     0x00000300      ;- Capture Mode : External Trigger Edge Selection
TC_EEVTEDG      EQU     0x00000300      ;- Waveform Mode : External Event Edge Selection

TC_ABETRG       EQU     0x00000400      ;- Capture Mode : TIOA or TIOB External Trigger Selection

TC_EEVT         EQU     0x00000C00      ;- Waveform Mode : External Event Selection
TC_ENETRG       EQU     0x00001000      ;- Waveform Mode : Enable Trigger on External Event
TC_CPCTRG       EQU     0x00004000      ;- RC Compare Enable Trigger Enable
TC_WAVE         EQU     0x00008000      ;- Mode Selection
TC_LDRA         EQU     0x00030000      ;- Capture Mode : RA Loading Selection
TC_ACPA         EQU     0x00030000      ;- Waveform Mode : RA Compare Effect on TIOA
TC_LDRB         EQU     0x000C0000      ;- Capture Mode : RB Loading Selection
TC_ACPC         EQU     0x000C0000      ;- Waveform Mode : RC Compare Effect on TIOA
TC_AEEVT        EQU     0x00300000      ;- Waveform Mode : External Event Effect on TIOA
TC_ASWTRG       EQU     0x00C00000      ;- Waveform Mode : Software Trigger Effect on TIOA
TC_BCPB         EQU     0x03000000      ;- Waveform Mode : RB Compare Effect on TIOB
TC_BCPC         EQU     0x0C000000      ;- Waveform Mode : RC Compare Effect on TIOB
TC_BEEVT        EQU     0x30000000      ;- Waveform Mode : External Event Effect on TIOB
TC_BSWTRG       EQU     0xC0000000      ;- Waveform Mode : Software Trigger Effect on TIOB

;------------------------------------------------
;- TC_SR: Timer Counter Status Register Bits Definition
;------------------------------------------------

TC_COVFS        EQU     0x01        ;- Counter Overflow Status
TC_LOVRS        EQU     0x02        ;- Load Overrun Status
TC_CPAS         EQU     0x04        ;- RA Compare Status
TC_CPBS         EQU     0x08        ;- RB Compare Status
TC_CPCS         EQU     0x10        ;- RC Compare Status
TC_LDRAS        EQU     0x20        ;- RA Loading Status
TC_LDRBS        EQU     0x40        ;- RB Loading Status
TC_ETRGS        EQU     0x80        ;- External Trigger Status
TC_CLKSTA       EQU     0x10000     ;- Clock Status
TC_MTIOA        EQU     0x20000     ;- TIOA Mirror
TC_MTIOB        EQU     0x40000     ;- TIOB Status

;----------------------------------------------------------------
;- TC_BCR: Timer Counter Block Control Register Bits Definition
;----------------------------------------------------------------

TC_SYNC         EQU     0x1         ;- Synchronisation Trigger

;------------------------------------------------------------
;- TC_BMR: Timer Counter Block Mode Register Bits Definition
;------------------------------------------------------------

TC_TC0XC0S      EQU     (0x3:SHL:0)     ;- External Clock Signal 0 Selection
TC_TC1XC1S      EQU     (0x3:SHL:2)     ;- External Clock Signal 1 Selection
TC_TC2XC2S      EQU     (0x3:SHL:4)     ;- External Clock Signal 2 Selection

;- Timer Counter Channel Descriptor Structure
                        ^       0
TCDesc_TCBase           #       4       ;- Peripheral base address
TCDesc_PioCtrl          #       4       ;- IO controller descriptor
TCDesc_AsmTCHandler     #       4       ;- Assembly interrupt handler
TCDesc_TCHandler        #       4
TCDesc_PeriphId         #       1       ;- Peripheral Identifier
TCDesc_PioTioa          #       1       ;- TIOA pin number in the PIO
TCDesc_PioTiob          #       1       ;- TIOB pin number in the PIO
TCDesc_PioTclk          #       1       ;- TCLK pin number in the PIO

            END
