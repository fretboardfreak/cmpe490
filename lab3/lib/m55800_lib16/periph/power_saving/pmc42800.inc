;------------------------------------------------------------------------------
;-         ATMEL Microcontroller Software Support  -  ROUSSET  -
;------------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;------------------------------------------------------------------------------
;- File Name            : pmc42800.inc
;- Object               : Assembler Power Management Controller Definition File.
;-
;- 1.0 04/07/00  PF     : Creation
;------------------------------------------------------------------------------

;------------------------------------------------------------------
;- Power Management Controller User Interface Structure Definition
;------------------------------------------------------------------
                ^       0
PMC_SCER        #       4       ;- Source Clock Enable Register
PMC_SCDR        #       4       ;- Source Clock Disable Register
PMC_SCSR        #       4       ;- Source Clock Mask Register
                #       4       ;- Reserved
PMC_PCER        #       4       ;- Peripheral Clock Enable Register
PMC_PCDR        #       4       ;- Peripheral Clock Disable Register
PMC_PCSR	#       4       ;- Peripheral Clock Status Register
	        #       4       ;- Reserved
PMC_CGMR	#	4	;- Clock Generator Mode Register
		#	4	;- Reserved
		#	4	;- Reserved
		#	4	;- Reserved
PMC_SR 		#	4	;- Status Register  
PMC_IER		#	4	;- Interrupt Enable Register  
PMC_IDR		#	4	;- Interrupt Disable Register  
PMC_IMR		#	4	;- Interrupt Mask Register  

;------------------------
;- System Clock Registers
;------------------------

ARM7DIS             EQU      0x1

;-------------------------------------------------------
;- PM SR, IER, IDR and IMR Registers Bits Definition   
;-------------------------------------------------------
PMC_PLL_LOCK        EQU     0x1     ;- PLL Lock Status 

;-----------------------------------------
; Power Management Controller Base Address
;-----------------------------------------

PMC_BASE            EQU     0xFFFF4000

            END
