/*
*********************************************************************************************************
*                                               Atmel AT91
*                                        EB55 Board Support Package
*
*                            (c) Copyright 2003, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*
* File : BSP.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#include "include/includes.h"
#include "include/ucos_ii.h"
#include "include/bsp.h"

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"
#include "parts/m55800/reg_m55800.h"
#include "periph/special_function/sf.h"
/*
*********************************************************************************************************
*                                             CONSTANTS
*********************************************************************************************************
*/

#define  BSP_UNDEF_INSTRUCTION_VECTOR_ADDR   (*(INT32U *)0x00000004L)
#define  BSP_SWI_VECTOR_ADDR                 (*(INT32U *)0x00000008L)
#define  BSP_PREFETCH_ABORT_VECTOR_ADDR      (*(INT32U *)0x0000000CL)
#define  BSP_DATA_ABORT_VECTOR_ADDR          (*(INT32U *)0x00000010L)
#define  BSP_IRQ_VECTOR_ADDR                 (*(INT32U *)0x00000018L)
#define  BSP_FIQ_VECTOR_ADDR                 (*(INT32U *)0x0000001CL)

#define  BSP_IRQ_ISR_ADDR                    (*(INT32U *)0x00000038L)
#define  BSP_FIQ_ISR_ADDR                    (*(INT32U *)0x0000003CL)


#define  BSP_LED_1                           BIT08
#define  BSP_LED_2                           BIT09
#define  BSP_LED_3                           BIT10
#define  BSP_LED_4                           BIT11
#define  BSP_LED_5                           BIT12
#define  BSP_LED_6                           BIT13
#define  BSP_LED_7                           BIT14
#define  BSP_LED_8                           BIT15
#define  BSP_LED_ALL                        (BSP_LED_1 | BSP_LED_2 | BSP_LED_3 | BSP_LED_4 | BSP_LED_5 | BSP_LED_6 | BSP_LED_7 | BSP_LED_8)

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          INITIALIZATION
*
* Description : This function is called by the first task that starts under uC/OS-II to initialize CPU
*               specific I/Os and possibly memory.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    BSP_IRQ_VECTOR_ADDR               = 0xE59FF018;               /* LDR PC,[PC,#0x18] instruction    */
    BSP_IRQ_ISR_ADDR                  = (INT32U)OS_CPU_IRQ_ISR;   /* IRQ exception vector address     */

    BSP_FIQ_VECTOR_ADDR               = 0xE59FF018;               /* LDR PC,[PC,#0x18] instruction    */
    BSP_FIQ_ISR_ADDR                  = (INT32U)OS_CPU_FIQ_ISR;   /* FIQ exception vector address     */


    //BSP_UNDEF_INSTRUCTION_VECTOR_ADDR = 0xEAFFFFFE;     /* Jump to itself                             */
    //BSP_SWI_VECTOR_ADDR               = 0xEAFFFFFE;
    //BSP_PREFETCH_ABORT_VECTOR_ADDR    = 0xEAFFFFFE;
    //BSP_DATA_ABORT_VECTOR_ADDR        = 0xEAFFFFFE;
    //BSP_FIQ_VECTOR_ADDR               = 0xEAFFFFFE;

    //APMC_SCER                         = 0x00000001;     /* Enable the system clock                    */

    APMC_PCER                         = 0x0007EFFC;     /* Enable the peripheral clock to ALL periph. */

                                                        /* AIC: Advanced Interrupt Controller         */
    SF_BASE->SF_PMR                   = 0x27A80020;     /* AIC Protect mode enable                    */

    AIC_IDCR                          = 0xFFFFFFFF;     /* Disable all interrupts                     */
    AIC_EOICR                         = 0xFFFFFFFF;     /* End-of-interrupt command                   */
    AIC_IVR                           = 0xFFFFFFFF;
    Tmr_TickInit();
}

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

void  LED_Init (void)
{
    PIOB_PER  = BSP_LED_ALL;                       /* Enable register                                   */
    PIOB_OER  = BSP_LED_ALL;                       /* Output enable                                     */
    LED_Off(0);                                    /* LED's off                                         */
}

/*
*********************************************************************************************************
*                                             LED ON
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to be ON
*                      1    turns ON LED1 on the board
*                      .
*                      .
*                      8    turns ON LED8 on the board
*********************************************************************************************************
*/

void  LED_On (INT8U led)
{
    switch (led) {
        case 0:
             PIOB_CODR = BSP_LED_ALL;
             break;

        case 1:
             PIOB_CODR = BSP_LED_1;
             break;

        case 2:
             PIOB_CODR = BSP_LED_2;
             break;

        case 3:
             PIOB_CODR = BSP_LED_3;
             break;

        case 4:
             PIOB_CODR = BSP_LED_4;
             break;

        case 5:
             PIOB_CODR = BSP_LED_5;
             break;

        case 6:
             PIOB_CODR = BSP_LED_6;
             break;

        case 7:
             PIOB_CODR = BSP_LED_7;
             break;

        case 8:
             PIOB_CODR = BSP_LED_8;
             break;
    }
}

/*
*********************************************************************************************************
*                                             LED OFF
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF
*                      0    indicates that you want ALL the LEDs to be OFF
*                      1    turns OFF LED1 on the board
*                      .
*                      .
*                      8    turns OFF LED8 on the board
*********************************************************************************************************
*/

void  LED_Off (INT8U led)
{
    switch (led) {
        case 0:
             PIOB_SODR = BSP_LED_ALL;
             break;

        case 1:
             PIOB_SODR = BSP_LED_1;
             break;

        case 2:
             PIOB_SODR = BSP_LED_2;
             break;

        case 3:
             PIOB_SODR = BSP_LED_3;
             break;

        case 4:
             PIOB_SODR = BSP_LED_4;
             break;

        case 5:
             PIOB_SODR = BSP_LED_5;
             break;

        case 6:
             PIOB_SODR = BSP_LED_6;
             break;

        case 7:
             PIOB_SODR = BSP_LED_7;
             break;

        case 8:
             PIOB_SODR = BSP_LED_8;
             break;
    }
}

/*
*********************************************************************************************************
*                                       TICKER INITIALIZATION
*
* Description : This function is called to initialize uC/OS-II's tick source (typically a timer generating
*               interrupts every 1 to 100 mS).
*
* Arguments   : none
*
* Notes       : TC_CMR_0:
*
*                 B2  B1  B0   010   MCLK / 32
*                 B3           0     Counter is incremented on RISING edge
*                 B5  B4       00    Clock is NOT gated
*                 B6           0     Counter clock is NOT stopped  on RC
*                 B7           0     Counter clock is NOT disabled on RC
*
*                 B9  B8       00    No externel event edge selection
*                 B11 B10      01    No externel event      selection
*                 B12          0     External event has no effect on TIOA
*                 B14          0     RC Compare resets the counter and starts the counter clock
*                 B15          1     WAVEFORM mode is enabled
*
*                 B17 B16      10    Clear TIOA when RA compares
*                 B19 B18      01    Set   TIOA when RC compares
*                 B21 B20      00    External event   has NO effect on TIOA
*                 B23 B22      00    Software trigger has NO effect on TIOA
*
*                 B25 B24      10    Clear TIOA when RA compares
*                 B27 B26      01    Set   TIOA when RC compares
*                 B29 B28      00    External event   has NO effect on TIOA
*                 B31 B30      00    Software trigger has NO effect on TIOA
*********************************************************************************************************
*/

static  void  Tmr_TickInit (void)
{
    volatile  INT32U  flags;


    TC0_IDR   = 0x000000FF;                   /* Disable all Timer #0 interrupts                       */
    flags     = TC0_SR;                       /* Read Status Register to clear flags                   */

    AIC_SVR6  = (INT32U)Tmr_TickISR_Handler;  /* Set the vector address for Timer #0                   */
    AIC_SMR6  = 0x00000026;                   /* SRCTYPE=1, PRIO=6, Edge triggered at priority 6       */
    AIC_ICCR  = (1 << TC0_ID);                /* Clear timer/counter #0 interrupt                      */

    TC0_CMR   = 0x0606C402;                   /* Waveform mode (see Notes)                             */
    TC0_RC    = AT91_CLK / 32 / OS_TICKS_PER_SEC;      /* Register C reload value for tick rate        */
    TC0_RA    = AT91_CLK / 32 / OS_TICKS_PER_SEC / 2;  /* Register A reload value for 50% cycle        */
    TC0_CCR   = 0x00000001;                   /* Enable the clock                                      */
    TC0_CCR   = 0x00000005;                   /* Software trigger and Enable the clock                 */
    flags     = TC0_SR;                       /* Read Status Register to clear flags                   */

    TC0_IER   = 0x00000010;                   /* Enable RC Compare Interrupts                          */
    AIC_IECR  = (1 << TC0_ID);                /* Enable timer #0 interrupt*/
   
}


/*
*********************************************************************************************************
*                                         TIMER #0 IRQ HANDLER
*
* Description : This function handles the timer interrupt that is used to generate TICKs for uC/OS-II.
*
* Arguments   : none
*********************************************************************************************************
*/

void  Tmr_TickISR_Handler (void)
{
    volatile  INT32U  sr;


    AIC_IVR   = 0;                      /* Debug variant of vector read (protect mode is used)         */
    sr        = TC0_SR;                 /* Read timer/counter status register to clear interrupt       */
    AIC_ICCR  = (1 << TC0_ID);          /* Clear  timer #0 interrupt                                   */
    AIC_EOICR = 0;                      /* Signal end of interrupt                                     */
    OSTimeTick();                       /* If the interrupt is from the tick source, call OSTimeTick() */
}

void OS_CPU_IRQ_ISR_Handler (void)
{

    PFNCT pfnct;

#if 1
    pfnct = (PFNCT) AIC_IVR;
    if(pfnct != (PFNCT)0) {
	(*pfnct) ();
    }
#else
    pfnct = (PFNCT) AIC_IVR;
    while (pfnct != (PFNCT)0) {
	(*pfnct) ();
	pfnct = (PFNCT)AIC_IVR;
    }
#endif
}

void OS_CPU_FIQ_ISR_Handler (void)
{
    PFNCT pfnct;

#if 1
    pfnct = (PFNCT) AIC_IVR;
    if(pfnct != (PFNCT)0) {
	(*pfnct) ();
    }
#else
    pfnct = (PFNCT) AIC_IVR;
    while (pfnct != (PFNCT)0) {
	(*pfnct) ();
	pfnct = (PFNCT)AIC_IVR;
    }
#endif
}
