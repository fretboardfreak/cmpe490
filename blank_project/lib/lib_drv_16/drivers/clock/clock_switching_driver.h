//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : clock_switching_driver.h
//* Object              :
//*                        Prototyping File.
//* 1.0 17/10/01 S.C    : Creation
//*----------------------------------------------------------------------------

#ifndef clock_switching_driver_h
#define clock_switching_driver_h

//*-----------------------------------------------------------------------------
//* ------------------------- General constant definition ----------------------
//*-----------------------------------------------------------------------------
#define     TO_LF_OSCILLATOR    0x0     /* The target frequency source is the
                                        low frequency oscillator */
#define     TO_HF_OSCILLATOR    0x1     /* The target frequency source is the
                                        main oscillator */
#define     TO_PLL_OUTPUT       0x2     /* The target frequency source is the
                                        PLL output */
#define     CSS_MASK    0xc000              /* All field are masked except CSS */
#define     MAX_MUL     0x3f00              /* Maximum for the Multiplier field
                                        definition */

//*-----------------------------------------------------------------------------
//* --------------------- End of General constant definition -------------------
//*-----------------------------------------------------------------------------

//*-----------------------------------------------------------------------------
//* ------------------------- Preprocessing  -----------------------------------
//*-----------------------------------------------------------------------------

//*-----------------------------------------------------------------------------
//* ------------------------- End of Preprocessing  ----------------------------
//*-----------------------------------------------------------------------------

/* General Function Prototyping */

extern void mck_clock_speed (short source , char frequency_multiplier) ;

#endif  /* clock_switching_driver_h */
