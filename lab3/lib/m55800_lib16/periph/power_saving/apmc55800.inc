;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : apmc55800.inc
;- Object               : Assembler Power Management Controller Definition File.
;-
;- 1.0 04/07/00  PF     : Creation
;------------------------------------------------------------------------------

;--------------------------------------------------------------------------
;- Advanced Power Management Controller User Interface Structure Definition
;--------------------------------------------------------------------------
                ^       0
APMC_SCER       #       4       ;- Source Clock Enable Register
APMC_SCDR       #       4       ;- Source Clock Disable Register
APMC_SCSR       #       4       ;- Source Clock Mask Register
                #       4       ;- Reserved
APMC_PCER       #       4       ;- Peripheral Clock Enable Register
APMC_PCDR       #       4       ;- Peripheral Clock Disable Register
APMC_PCSR       #       4       ;- Peripheral Clock Status Register
                #       4       ;- Reserved
APMC_CGMR       #       4       ;- Clock Generator Mode Register
                #       4       ;- Reserved
APMC_PCR        #       4       ;- Power Control Register
APMC_PMR        #       4       ;- Power Mode Register
APMC_SR         #       4       ;- Status Register  
APMC_IER        #       4       ;- Interrupt Enable Register  
APMC_IDR        #       4       ;- Interrupt Disable Register  
APMC_IMR        #       4       ;- Interrupt Mask Register  

;------------------------
;- System Clock Registers
;------------------------

ARM7DIS                 EQU     0x1

;------------------------------------------------------------
;- Advanced Power Managment Control Register Bits Definition 
;------------------------------------------------------------
APMC_ARM7DIS            EQU     0x1

;-------------------------------------------------------------------------
;- Advanced Power Managment Clock Generator Mode Register Bits Definition 
;-------------------------------------------------------------------------
APMC_MOSC_BYP           EQU     0x1     ;- Main Oscillator Bypass
MOSCS_MASK          EQU         0x1
PLL_LOCK_MASK       EQU         0x2

APMC_MOSC_EN            EQU     0x2     ;- Main Oscillator Enable 
APMC_MCKO_DIS           EQU     0x4     ;- Disable Master clock output (tri-state) 

APMC_PRES_NONE          EQU     0x0     ;- No prescaler 
APMC_PRES_DIV2          EQU     0x10    ;- Selected Clock Divided by 2 
APMC_PRES_DIV4          EQU     0x20    ;- Selected Clock Divided by 4 
APMC_PRES_DIV8          EQU     0x30    ;- Selected Clock Divided by 8 
APMC_PRES_DIV16         EQU     0x40    ;- Selected Clock Divided by 16 
APMC_PRES_DIV32         EQU     0x50    ;- Selected Clock Divided by 32 
APMC_PRES_DIV64         EQU     0x60    ;- Selected Clock Divided by 64 

APMC_CSS_LF             EQU     0x0     ;- Low-Frequency Clock provided by RTC 
APMC_CSS_MOSC           EQU     0x4000  ;- Main Oscillator Output or External clock 
APMC_CSS_PLL            EQU     0x8000  ;- Phase Lock Loop Output 

B_MUL                   EQU     8
B_OSCOUNT               EQU     16
B_PLLCOUNT              EQU     24

;-------------------------------------------------
;- APM Power Controller Register Bits Definition  
;-------------------------------------------------
APMC_SHDALC             EQU     0x1     ;- Shut-down or alarm Command 
APMC_WKACKC             EQU     0x2     ;- Wake-up or Alarm Acknowledge Command     

;------------------------------------------------
;- APM Power Mode Register Bits Definition       
;------------------------------------------------
APMC_SHDALS_OUT_TRIS    EQU     0x0     ;- SHDALS pin is Tri-State 
APMC_SHDALS_OUT_LEVEL_0 EQU     0x1     ;- SHDALS pin is LEVEL 0 
APMC_SHDALS_OUT_LEVEL_1 EQU     0x2     ;- SHDALS pin LEVEL 1 

APMC_WKACKS_OUT_TRIS    EQU     0x0     ;- WKACKS pin is Tri-State 
APMC_WKACKS_OUT_LEVEL_0 EQU     0x4     ;- WKACKS pin  is LEVEL 0 
APMC_WKACKS_OUT_LEVEL_1 EQU     0x8     ;- WKACKS pin  is LEVEL 1 

APMC_WKEN               EQU     0x10    ;- Alarm Wake-up Enable 
APMC_ALSHEN             EQU     0x20    ;- Alarm Shut-Down Enable 

APMC_WKEDG_NONE         EQU     0x00    ;- None. No edge is detected on Wake-up 
APMC_WKEDG_POS_EDG      EQU     0x40    ;- Positive edge detection 
APMC_WKEDG_NEG_EDG      EQU     0x80    ;- Negative edge detection 

;-------------------------------------------------------
;- APM SR, IER, IDR and IMR Registers Bits Definition   
;-------------------------------------------------------
APMC_MOSCS              EQU     0x1     ;- Main Osillator Status 
APMC_PLL_LOCK           EQU     0x2     ;- PLL Lock Status 


;-----------------------------------------
; Power Management Controller Base Address
;-----------------------------------------

APMC_BASE               EQU     0xFFFF4000

            END
