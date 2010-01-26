//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : clock_switching_driver.c
//* Object              : Driver to switch the clock source in the AT91M55800A
//*
//* 1.0 08/01/01 S.C    : Creation
//* Note : The switching times are specified in he software.
//*----------------------------------------------------------------------------


/*------------------ Files to be included Definition ------------------------*/

#include "parts/m55800/m55800.h"
#include "parts/m55800/lib_m55800.h"
#include "periph/power_saving/lib_power_save.h"

#include "clock_switching_driver.h"

/*----- Assembler Handler files for SLCKIRQ and APMC interrupt source ----------*/

extern void osc32k_asm_handler (void) 			; //* .asm handler
extern void osc32k_osc16m_asm_handler (void)	; //* .asm handler
extern void osc32k_pll_asm_handler (void)		; //* .asm handler

/*---------------------------- Global Variable ------------------------------*/
char switching_conducted = 0 ; //* Allows to know when the switching is achieved

//*----------------------------------------------------------------------------
//* Function Name       : osc32k_c_handler
//* Object              : C Handler to switch to 32kHz oscillator and stop other
//*                     : sources
//* Input Parameters    : none
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void osc32k_c_handler (void)
{
        //* Shutdown the PLL by default
        at91_clock_generator_mode (APMC_BASE->APMC_CGMR & (~MAX_MUL) ) ;

        //* Shutdown the Main Oscillator by default
        at91_clock_generator_mode (APMC_BASE->APMC_CGMR & (~APMC_MOSC_EN)) ;

        at91_irq_close ( SLCKIRQ_ID) ;

        switching_conducted = TRUE ;
}

//*----------------------------------------------------------------------------
//* Function Name       : osc32k_osc16m_c_handler
//* Object              : C Handler to switch to 32k oscillator before to switch
//*						: to 16 MHz and shutdown the PLL.
//* Input Parameters    : none
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void osc32k_osc16m_c_handler (void)
{
    u_int apmc_cgmr_status ;

        //* Shutdown the PLL by default
        at91_clock_generator_mode (APMC_BASE->APMC_CGMR & (~MAX_MUL) ) ;

        //* APMC_CGMR reading
        apmc_cgmr_status = at91_clock_generator_state () ;

        //* Switching to the HF output oscillator
        at91_clock_generator_mode ( apmc_cgmr_status | APMC_CSS_MOSC) ;

		at91_irq_close ( SLCKIRQ_ID ) ;

		switching_conducted = TRUE ;
}

//*----------------------------------------------------------------------------
//* Function Name       : osc32k_pll_c_handler
//* Object              : C Handler to switch to 32k oscillator before to switch
//*						: to PLL output.
//* Input Parameters    : none
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void osc32k_pll_c_handler (void)
{
		at91_clock_generator_mode ( at91_clock_generator_state ()  | APMC_CSS_PLL ) ;

		at91_irq_close ( SLCKIRQ_ID) ;

		switching_conducted = TRUE ;
}

//*----------------------------------------------------------------------------
//* Function Name       : mck_clock_speed
//* Object              : Driver to choice the clock source and the PLL
//*                       frequency output
//* Input Parameters    :<target_source> clock source
//*                 'source' = 0 : low frequency oscillator output => MCK
//*                 'source' = 1 : main oscillator output => MCK
//*                 'source' = 2 : PLL output =MCK
//*                      <frequency_multiplier> allows to multiply the main
//*                       oscillator frequency ( field B_MUL +1).
//* Output Parameters   : None
//*----------------------------------------------------------------------------
void mck_clock_speed (short target_source, char frequency_multiplier)
{
    u_int apmc_cgmr_status ;
    u_int switch_choice ;

    	switching_conducted = FALSE ;

		frequency_multiplier = frequency_multiplier - 1 ;

		apmc_cgmr_status = at91_clock_generator_state () ;  //* APMC_CGMR reading NEW

        switch_choice = apmc_cgmr_status & CSS_MASK ;

        switch (switch_choice)
        {
            case APMC_CSS_LF:                               //* The actual source clock is the LF osc.

                switch (target_source)
                {
                    case TO_LF_OSCILLATOR :								//* It's the actual clock source
                    break ;

                    case TO_HF_OSCILLATOR :                              //* To the HF osc.(Switching Time = 15.5 ms)

                        apmc_cgmr_status |= APMC_MOSC_EN ;

                        //* Main oscillator start-up
                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        /* It's no good to enable interrupt because the handling by interrupt, approximatively, cost
                        the same time (32kHz clock) that the oscillator startup */
                        while ((at91_clock_get_pll_status () & APMC_MOSCS) == 0) {} ;

                        //* Switching to the HF output oscillator
                        at91_clock_generator_mode ( apmc_cgmr_status | APMC_CSS_MOSC ) ;

                        break ;


                    case TO_PLL_OUTPUT :								//* To the PLL output ((Switching Time = 18 ms
                    													//*						with PLLCOUNT = 3 and
                    													//*						OSCOUNT = 0x2f)

                        apmc_cgmr_status |= APMC_MOSC_EN ;

                        //* First part : Main oscillator start-up
                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        while ((at91_clock_get_pll_status () & APMC_MOSCS) ==0 ) {} ;

                        //* Second part : PLL starting

						apmc_cgmr_status |= (frequency_multiplier <<B_MUL) ;

                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        while ((at91_clock_get_pll_status () & APMC_PLL_LOCK) ==0 ) {} ;

                        at91_clock_generator_mode ( apmc_cgmr_status | APMC_CSS_PLL ) ;

                        break ;
                }
            break ;
            case APMC_CSS_MOSC:                             //* The actual source clock is the HF osc.
                switch (target_source)
                {
                    case TO_LF_OSCILLATOR :                               //* To the LF osc.(Switching Time = 14 ms)

                        //* Switching from interrupt event (SLCKIRQ)
                        at91_irq_open ( SLCKIRQ_ID , 6 , AIC_SRCTYPE_EXT_LOW_LEVEL , osc32k_asm_handler ) ;

                        apmc_cgmr_status &= ~CSS_MASK ;

                        //* Switching to the HF output oscillator
                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        while (switching_conducted != TRUE ) {} ;

                        break ;

                    case TO_HF_OSCILLATOR :								//* It's the actual clock source
                        break ;

                    case TO_PLL_OUTPUT :                               //* To the PLL output(Switching Time = 5.8 ms with
                    													//*					PLLCOUNT = 3)

                        /* First: PLL start-up */

                        apmc_cgmr_status |= (frequency_multiplier << B_MUL) ;

						at91_clock_generator_mode ( apmc_cgmr_status ) ;

						while ((at91_clock_get_pll_status () & APMC_PLL_LOCK) ==0 ) {} ;

						/* Second: switching to 32 kHz */

						apmc_cgmr_status &= ~CSS_MASK ;

						/* Switching to the LF output oscillator */
						at91_clock_generator_mode ( apmc_cgmr_status ) ;

						at91_irq_open ( SLCKIRQ_ID , 6 , AIC_SRCTYPE_EXT_LOW_LEVEL , osc32k_pll_asm_handler ) ;

                        while (switching_conducted != TRUE ) {} ;

                        break ;
                }
            break ;
            case APMC_CSS_PLL:                              //* The actual source clock is the internal PLL
                switch (target_source)
                {
                    case TO_LF_OSCILLATOR :                               //* To the LF osc.(Switching Time = 14 ms)

                        /* Switching when the dedicated interrupt occures */
                        at91_irq_open ( SLCKIRQ_ID , 6 , AIC_SRCTYPE_EXT_LOW_LEVEL , osc32k_asm_handler ) ;

                        apmc_cgmr_status &= ~CSS_MASK ;

                        /* Switching to the LF output oscillator */
                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        while (switching_conducted != TRUE ) {} ;

                        break ;

                    case TO_HF_OSCILLATOR :                              //* To the HF osc.(Switching Time = 7 ms)

                     	//* Switching from interrupt event (32k_mode)
                        at91_irq_open ( SLCKIRQ_ID , 6 , AIC_SRCTYPE_EXT_LOW_LEVEL , osc32k_osc16m_asm_handler ) ;

                        apmc_cgmr_status &= ~CSS_MASK ;

                        //* Switching to the LF output oscillator
                        at91_clock_generator_mode ( apmc_cgmr_status ) ;

                        while (switching_conducted != TRUE ) {} ;

                        break ;

                    case TO_PLL_OUTPUT :                               //* It's the actual clock source
                        break ;
                }
        }
}
