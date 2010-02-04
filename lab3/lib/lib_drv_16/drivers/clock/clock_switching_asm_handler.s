;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File source          : asm_handler.s
;- Object               : Assembler PIO Controller Interrupt Handler.
;-
;- 1.0 08/01/00 S.C     : Creation
;------------------------------------------------------------------------------

            AREA        Dedicated32k_irq, CODE, READONLY, INTERWORK

            INCLUDE     periph/aic/irq.mac

;------------------------------------------------------------------------------
;- Function             : osc32k_asm_handler
;- Treatments           : 32kHz mode Handler to run with Slow Clock Source
;- Called Functions     : osc32k_c_handler
;- Called Macros        : IRQ_ENTRY, IRQ_EXIT
;------------------------------------------------------------------------------
            IMPORT      osc32k_c_handler
            EXPORT      osc32k_asm_handler
  
osc32k_asm_handler

;- Manage Exception Entry
            IRQ_ENTRY

;- Call  C handler
            ldr         r0, =osc32k_c_handler
            mov         r14, pc
            bx          r0

;- Manage Exception Exit
            IRQ_EXIT
   
;------------------------------------------------------------------------------
;- Function             : osc32k_osc16m_asm_handler
;- Treatments           : Set main oscillator
;- Called Functions     : osc16m_c_handler
;- Called Macros        : IRQ_ENTRY, IRQ_EXIT
;------------------------------------------------------------------------------
            IMPORT      osc32k_osc16m_c_handler
            EXPORT      osc32k_osc16m_asm_handler

osc32k_osc16m_asm_handler

;- Manage Exception Entry
            IRQ_ENTRY

;- Call  C handler
            ldr         r0, =osc32k_osc16m_c_handler
            mov         r14, pc
            bx          r0


;- Manage Exception Exit
            IRQ_EXIT
;------------------------------------------------------------------------------
;- Function             : osc32k_pll_asm_handler
;- Treatments           : 
;- Called Functions     : 
;- Called Macros        : 
;------------------------------------------------------------------------------
            IMPORT      osc32k_pll_c_handler
            EXPORT      osc32k_pll_asm_handler

osc32k_pll_asm_handler

;- Manage Exception Entry
            IRQ_ENTRY

;- Call  C handler
            ldr         r0, =osc32k_pll_c_handler
            mov         r14, pc
            bx          r0


;- Manage Exception Exit
            IRQ_EXIT

            END

