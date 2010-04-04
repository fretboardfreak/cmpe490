;----------------------------------------------------------------------------
;         ATMEL Microcontroller Software Support  -  ROUSSET  -
;----------------------------------------------------------------------------
; The software is delivered "AS IS" without warranty or condition of any
; kind, either express, implied or statutory. This includes without
; limitation any warranty or condition with respect to merchantability or
; fitness for any particular purpose, or against the infringements of
; intellectual property rights of others.
;----------------------------------------------------------------------------
; File Name           : st.inc
; Object              : System Timer Assembly File.
;
; 1.0 10/06/01  PF    : Creation
;----------------------------------------------------------------------------

;---------------------------------------------------
;  System Timer User Interface Structure Definition 
;---------------------------------------------------
		^       0
ST_CR		#       4 	; Control Register
ST_PIMR		#       4       ; Period Interval Mode Register
ST_WDMR		#       4       ; Watchdog Mode Register
ST_RTMR		#       4       ; Real Time Mode Register
ST_SR		#       4       ; Status Register
ST_IER		#       4       ; Interrupt Enable Register
ST_IDR		#       4       ; Interrupt Disable Register
ST_IMR		#       4       ; Interrupt Mask Register
ST_RTAR		#       4       ; Real Time Alarm Register
ST_CRTR		#       4       ; Current Real Time Register


;----------------------------------------------------------
; ST_CR: System Timer Control Register Bits Definition 
;---------------------------------------------------------
ST_WDRST	EQU	0x1	; Watchdog Timer Restart

;---------------------------------------------------------------
; ST_WDMR: System Timer Watchdog Mode Register Bits Definition
;---------------------------------------------------------------
ST_RSTEN	EQU	0x10000 	; WatchDog Overflow Reset Enable
ST_EXTEN	EQU	0x20000 	; External Signal Assertion Enable


;--------------------------------------------------------------------------------------------
; ST_SR, ST_IER, ST_IDR, ST_IMR : System Timer Status and Interrupts Register Bits Definition
;--------------------------------------------------------------------------------------------
ST_PITS         EQU	0x1     ; Period Interval Timer Status
ST_WDOVF	EQU	0x2	; WatchDog Overflow Status
ST_RTTINC       EQU	0x4     ; Real Time Timer Increment
ST_ALMS		EQU	0x8	; Alarm Status

	END
