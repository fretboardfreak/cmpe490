//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : reg_m55800.h
//* Object              : AT91M55800 Registers Definition File
//*
//* 1.0 11/07/00  PFi   : Creation
//* 2.0 10/12/01  PFi   : Data Pointer/Counter Registers has been removed.
//*                     : The RevA of the M558000 does not features DAC PDC.
//*-----------------------------------------------------------------------------

#ifndef reg_m55800_h
#define reg_m55800_h

#include    "m55800.h"

/*----------------------------------*/
/* External Bus Interface Registers */
/*----------------------------------*/

#define EBI_CSR0        (EBI_BASE->EBI_CSR[0])
#define EBI_CSR1        (EBI_BASE->EBI_CSR[1])
#define EBI_CSR2        (EBI_BASE->EBI_CSR[2])
#define EBI_CSR3        (EBI_BASE->EBI_CSR[3])
#define EBI_CSR4        (EBI_BASE->EBI_CSR[4])
#define EBI_CSR5        (EBI_BASE->EBI_CSR[5])
#define EBI_CSR6        (EBI_BASE->EBI_CSR[6])
#define EBI_CSR7        (EBI_BASE->EBI_CSR[7])
#define EBI_RCR         (EBI_BASE->EBI_RCR)
#define EBI_MCR         (EBI_BASE->EBI_MCR)

/*------------------------------------------------*/
/* Advanced Power Management Controller Registers */
/*------------------------------------------------*/

#define APMC_SCER       (APMC_BASE->APMC_SCER)
#define APMC_SCDR       (APMC_BASE->APMC_SCDR)
#define APMC_SCSR       (APMC_BASE->APMC_SCSR)
#define APMC_PCER       (APMC_BASE->APMC_PCER)
#define APMC_PCDR       (APMC_BASE->APMC_PCDR)
#define APMC_PCSR       (APMC_BASE->APMC_PCSR)
#define APMC_CGMR       (APMC_BASE->APMC_CGMR)
#define APMC_PCR        (APMC_BASE->APMC_PCR)
#define APMC_PMR        (APMC_BASE->APMC_PMR)
#define APMC_SR         (APMC_BASE->APMC_SR)
#define APMC_IER        (APMC_BASE->APMC_IER)
#define APMC_IDR        (APMC_BASE->APMC_IDR)
#define APMC_IMR        (APMC_BASE->APMC_IMR)


/*-----------------------------------------*/
/* Advanced Interrupt Controller Registers */
/*-----------------------------------------*/

#define AIC_SMR0        (AIC_BASE->AIC_SMR[0])
#define AIC_SMR1        (AIC_BASE->AIC_SMR[1])
#define AIC_SMR2        (AIC_BASE->AIC_SMR[2])
#define AIC_SMR3        (AIC_BASE->AIC_SMR[3])
#define AIC_SMR4        (AIC_BASE->AIC_SMR[4])
#define AIC_SMR5        (AIC_BASE->AIC_SMR[5])
#define AIC_SMR6        (AIC_BASE->AIC_SMR[6])
#define AIC_SMR7        (AIC_BASE->AIC_SMR[7])
#define AIC_SMR8        (AIC_BASE->AIC_SMR[8])
#define AIC_SMR9        (AIC_BASE->AIC_SMR[9])
#define AIC_SMR10       (AIC_BASE->AIC_SMR[10])
#define AIC_SMR11       (AIC_BASE->AIC_SMR[11])
#define AIC_SMR12       (AIC_BASE->AIC_SMR[12])
#define AIC_SMR13       (AIC_BASE->AIC_SMR[13])
#define AIC_SMR14       (AIC_BASE->AIC_SMR[14])
#define AIC_SMR15       (AIC_BASE->AIC_SMR[15])
#define AIC_SMR16       (AIC_BASE->AIC_SMR[16])
#define AIC_SMR17       (AIC_BASE->AIC_SMR[17])
#define AIC_SMR18       (AIC_BASE->AIC_SMR[18])
#define AIC_SMR19       (AIC_BASE->AIC_SMR[19])
#define AIC_SMR20       (AIC_BASE->AIC_SMR[20])
#define AIC_SMR21       (AIC_BASE->AIC_SMR[21])
#define AIC_SMR22       (AIC_BASE->AIC_SMR[22])
#define AIC_SMR23       (AIC_BASE->AIC_SMR[23])
#define AIC_SMR24       (AIC_BASE->AIC_SMR[24])
#define AIC_SMR25       (AIC_BASE->AIC_SMR[25])
#define AIC_SMR26       (AIC_BASE->AIC_SMR[26])
#define AIC_SMR27       (AIC_BASE->AIC_SMR[27])
#define AIC_SMR28       (AIC_BASE->AIC_SMR[28])
#define AIC_SMR29       (AIC_BASE->AIC_SMR[29])
#define AIC_SMR30       (AIC_BASE->AIC_SMR[30])
#define AIC_SMR31       (AIC_BASE->AIC_SMR[31])

#define AIC_SVR0        (AIC_BASE->AIC_SVR[0])
#define AIC_SVR1        (AIC_BASE->AIC_SVR[1])
#define AIC_SVR2        (AIC_BASE->AIC_SVR[2])
#define AIC_SVR3        (AIC_BASE->AIC_SVR[3])
#define AIC_SVR4        (AIC_BASE->AIC_SVR[4])
#define AIC_SVR5        (AIC_BASE->AIC_SVR[5])
#define AIC_SVR6        (AIC_BASE->AIC_SVR[6])
#define AIC_SVR7        (AIC_BASE->AIC_SVR[7])
#define AIC_SVR8        (AIC_BASE->AIC_SVR[8])
#define AIC_SVR9        (AIC_BASE->AIC_SVR[9])
#define AIC_SVR10       (AIC_BASE->AIC_SVR[10])
#define AIC_SVR11       (AIC_BASE->AIC_SVR[11])
#define AIC_SVR12       (AIC_BASE->AIC_SVR[12])
#define AIC_SVR13       (AIC_BASE->AIC_SVR[13])
#define AIC_SVR14       (AIC_BASE->AIC_SVR[14])
#define AIC_SVR15       (AIC_BASE->AIC_SVR[15])
#define AIC_SVR16       (AIC_BASE->AIC_SVR[16])
#define AIC_SVR17       (AIC_BASE->AIC_SVR[17])
#define AIC_SVR18       (AIC_BASE->AIC_SVR[18])
#define AIC_SVR19       (AIC_BASE->AIC_SVR[19])
#define AIC_SVR20       (AIC_BASE->AIC_SVR[20])
#define AIC_SVR21       (AIC_BASE->AIC_SVR[21])
#define AIC_SVR22       (AIC_BASE->AIC_SVR[22])
#define AIC_SVR23       (AIC_BASE->AIC_SVR[23])
#define AIC_SVR24       (AIC_BASE->AIC_SVR[24])
#define AIC_SVR25       (AIC_BASE->AIC_SVR[25])
#define AIC_SVR26       (AIC_BASE->AIC_SVR[26])
#define AIC_SVR27       (AIC_BASE->AIC_SVR[27])
#define AIC_SVR28       (AIC_BASE->AIC_SVR[28])
#define AIC_SVR29       (AIC_BASE->AIC_SVR[29])
#define AIC_SVR30       (AIC_BASE->AIC_SVR[30])
#define AIC_SVR31       (AIC_BASE->AIC_SVR[31])


#define AIC_IVR         (AIC_BASE->AIC_IVR)
#define AIC_FVR         (AIC_BASE->AIC_FVR)
#define AIC_ISR         (AIC_BASE->AIC_ISR)
#define AIC_IPR         (AIC_BASE->AIC_IPR)
#define AIC_IMR         (AIC_BASE->AIC_IMR)
#define AIC_CISR        (AIC_BASE->AIC_CISR)
#define AIC_IECR        (AIC_BASE->AIC_IECR)
#define AIC_IDCR        (AIC_BASE->AIC_IDCR)
#define AIC_ICCR        (AIC_BASE->AIC_ICCR)
#define AIC_ISCR        (AIC_BASE->AIC_ISCR)
#define AIC_EOICR       (AIC_BASE->AIC_EOICR)
#define AIC_SPU         (AIC_BASE->AIC_SPU)


/*----------------------------------*/
/* Parallel IO Controller Registers */
/*----------------------------------*/
/* PIOA */
#define PIOA_PER     (PIOA_BASE->PIO_PER)
#define PIOA_PDR     (PIOA_BASE->PIO_PDR)
#define PIOA_PSR     (PIOA_BASE->PIO_PSR)

#define PIOA_OER     (PIOA_BASE->PIO_OER)
#define PIOA_ODR     (PIOA_BASE->PIO_ODR)
#define PIOA_OSR     (PIOA_BASE->PIO_OSR)

#define PIOA_IFER    (PIOA_BASE->PIO_IFER)
#define PIOA_IFDR    (PIOA_BASE->PIO_IFDR)
#define PIOA_IFSR    (PIOA_BASE->PIO_IFSR)

#define PIOA_SODR    (PIOA_BASE->PIO_SODR)
#define PIOA_CODR    (PIOA_BASE->PIO_CODR)
#define PIOA_ODSR    (PIOA_BASE->PIO_ODSR)
#define PIOA_PDSR    (PIOA_BASE->PIO_PDSR)

#define PIOA_IER     (PIOA_BASE->PIO_IER)
#define PIOA_IDR     (PIOA_BASE->PIO_IDR)
#define PIOA_IMR     (PIOA_BASE->PIO_IMR)
#define PIOA_ISR     (PIOA_BASE->PIO_ISR)

#define PIOA_MDER    (PIOA_BASE->PIO_MDER)
#define PIOA_MDDR    (PIOA_BASE->PIO_MDDR)
#define PIOA_MDSR    (PIOA_BASE->PIO_MDSR)

/* PIOB */
#define PIOB_PER     (PIOB_BASE->PIO_PER)
#define PIOB_PDR     (PIOB_BASE->PIO_PDR)
#define PIOB_PSR     (PIOB_BASE->PIO_PSR)

#define PIOB_OER     (PIOB_BASE->PIO_OER)
#define PIOB_ODR     (PIOB_BASE->PIO_ODR)
#define PIOB_OSR     (PIOB_BASE->PIO_OSR)

#define PIOB_IFER    (PIOB_BASE->PIO_IFER)
#define PIOB_IFDR    (PIOB_BASE->PIO_IFDR)
#define PIOB_IFSR    (PIOB_BASE->PIO_IFSR)

#define PIOB_SODR    (PIOB_BASE->PIO_SODR)
#define PIOB_CODR    (PIOB_BASE->PIO_CODR)
#define PIOB_ODSR    (PIOB_BASE->PIO_ODSR)
#define PIOB_PDSR    (PIOB_BASE->PIO_PDSR)

#define PIOB_IER     (PIOB_BASE->PIO_IER)
#define PIOB_IDR     (PIOB_BASE->PIO_IDR)
#define PIOB_IMR     (PIOB_BASE->PIO_IMR)
#define PIOB_ISR     (PIOB_BASE->PIO_ISR)

#define PIOB_MDER    (PIOB_BASE->PIO_MDER)
#define PIOB_MDDR    (PIOB_BASE->PIO_MDDR)
#define PIOB_MDSR    (PIOB_BASE->PIO_MDSR)


/*-------------------------------*/
/* USART 0, 1 and 2 Registers    */
/*-------------------------------*/

#define US0_CR      (USART0_BASE->US_CR)
#define US1_CR      (USART1_BASE->US_CR)
#define US2_CR      (USART2_BASE->US_CR)

#define US0_MR      (USART0_BASE->US_MR)
#define US1_MR      (USART1_BASE->US_MR)
#define US2_MR      (USART2_BASE->US_MR)

#define US0_IER     (USART0_BASE->US_IER)
#define US1_IER     (USART1_BASE->US_IER)
#define US2_IER     (USART2_BASE->US_IER)

#define US0_IDR     (USART0_BASE->US_IDR)
#define US1_IDR     (USART1_BASE->US_IDR)
#define US2_IDR     (USART2_BASE->US_IDR)

#define US0_IMR     (USART0_BASE->US_IMR)
#define US1_IMR     (USART1_BASE->US_IMR)
#define US2_IMR     (USART2_BASE->US_IMR)

#define US0_CSR     (USART0_BASE->US_CSR)
#define US1_CSR     (USART1_BASE->US_CSR)
#define US2_CSR     (USART2_BASE->US_CSR)

#define US0_RHR     (USART0_BASE->US_RHR)
#define US1_RHR     (USART1_BASE->US_RHR)
#define US2_RHR     (USART2_BASE->US_RHR)

#define US0_THR     (USART0_BASE->US_THR)
#define US1_THR     (USART1_BASE->US_THR)
#define US2_THR     (USART2_BASE->US_THR)

#define US0_BRGR    (USART0_BASE->US_BRGR)
#define US1_BRGR    (USART1_BASE->US_BRGR)
#define US2_BRGR    (USART2_BASE->US_BRGR)

#define US0_RTOR    (USART0_BASE->US_RTOR)
#define US1_RTOR    (USART1_BASE->US_RTOR)
#define US2_RTOR    (USART2_BASE->US_RTOR)

#define US0_TTGR    (USART0_BASE->US_TTGR)
#define US1_TTGR    (USART1_BASE->US_TTGR)
#define US2_TTGR    (USART2_BASE->US_TTGR)

#define US0_RPR     (USART0_BASE->US_RPR)
#define US1_RPR     (USART1_BASE->US_RPR)
#define US2_RPR     (USART2_BASE->US_RPR)

#define US0_RCR     (USART0_BASE->US_RCR)
#define US1_RCR     (USART1_BASE->US_RCR)
#define US2_RCR     (USART2_BASE->US_RCR)

#define US0_TPR     (USART0_BASE->US_TPR)
#define US1_TPR     (USART1_BASE->US_TPR)
#define US2_TPR     (USART2_BASE->US_TPR)

#define US0_TCR     (USART0_BASE->US_TCR)
#define US1_TCR     (USART1_BASE->US_TCR)
#define US2_TCR     (USART2_BASE->US_TCR)

/*-------------------------*/
/* Timer Counter Registers */
/*-------------------------*/

#define TC0_BASE    (TCB0_BASE->TC[0])
#define TC1_BASE    (TCB0_BASE->TC[1])
#define TC2_BASE    (TCB0_BASE->TC[2])
#define TC3_BASE    (TCB1_BASE->TC[0])
#define TC4_BASE    (TCB1_BASE->TC[1])
#define TC5_BASE    (TCB1_BASE->TC[2])

#define TC0_BCR     (TCB0_BASE->TC_BCR)
#define TC1_BCR     (TCB0_BASE->TC_BCR)
#define TC2_BCR     (TCB0_BASE->TC_BCR)
#define TC3_BCR     (TCB1_BASE->TC_BCR)
#define TC4_BCR     (TCB1_BASE->TC_BCR)
#define TC5_BCR     (TCB1_BASE->TC_BCR)

#define TC0_BMR     (TCB0_BASE->TC_BMR)
#define TC1_BMR     (TCB0_BASE->TC_BMR)
#define TC2_BMR     (TCB0_BASE->TC_BMR)
#define TC3_BMR     (TCB1_BASE->TC_BMR)
#define TC4_BMR     (TCB1_BASE->TC_BMR)
#define TC5_BMR     (TCB1_BASE->TC_BMR)

#define TC0_CCR     (TC0_BASE.TC_CCR)
#define TC0_CMR     (TC0_BASE.TC_CMR)
#define TC0_CV      (TC0_BASE.TC_CV)
#define TC0_RA      (TC0_BASE.TC_RA)
#define TC0_RB      (TC0_BASE.TC_RB)
#define TC0_RC      (TC0_BASE.TC_RC)
#define TC0_SR      (TC0_BASE.TC_SR)
#define TC0_IER     (TC0_BASE.TC_IER)
#define TC0_IDR     (TC0_BASE.TC_IDR)
#define TC0_IMR     (TC0_BASE.TC_IMR)

#define TC1_CCR     (TC1_BASE.TC_CCR)
#define TC1_CMR     (TC1_BASE.TC_CMR)
#define TC1_CV      (TC1_BASE.TC_CV)
#define TC1_RA      (TC1_BASE.TC_RA)
#define TC1_RB      (TC1_BASE.TC_RB)
#define TC1_RC      (TC1_BASE.TC_RC)
#define TC1_SR      (TC1_BASE.TC_SR)
#define TC1_IER     (TC1_BASE.TC_IER)
#define TC1_IDR     (TC1_BASE.TC_IDR)
#define TC1_IMR     (TC1_BASE.TC_IMR)

#define TC2_CCR     (TC2_BASE.TC_CCR)
#define TC2_CMR     (TC2_BASE.TC_CMR)
#define TC2_CV      (TC2_BASE.TC_CV)
#define TC2_RA      (TC2_BASE.TC_RA)
#define TC2_RB      (TC2_BASE.TC_RB)
#define TC2_RC      (TC2_BASE.TC_RC)
#define TC2_SR      (TC2_BASE.TC_SR)
#define TC2_IER     (TC2_BASE.TC_IER)
#define TC2_IDR     (TC2_BASE.TC_IDR)
#define TC2_IMR     (TC2_BASE.TC_IMR)

#define TC3_CCR     (TC3_BASE.TC_CCR)
#define TC3_CMR     (TC3_BASE.TC_CMR)
#define TC3_CV      (TC3_BASE.TC_CV)
#define TC3_RA      (TC3_BASE.TC_RA)
#define TC3_RB      (TC3_BASE.TC_RB)
#define TC3_RC      (TC3_BASE.TC_RC)
#define TC3_SR      (TC3_BASE.TC_SR)
#define TC3_IER     (TC3_BASE.TC_IER)
#define TC3_IDR     (TC3_BASE.TC_IDR)
#define TC3_IMR     (TC3_BASE.TC_IMR)

#define TC4_CCR     (TC4_BASE.TC_CCR)
#define TC4_CMR     (TC4_BASE.TC_CMR)
#define TC4_CV      (TC4_BASE.TC_CV)
#define TC4_RA      (TC4_BASE.TC_RA)
#define TC4_RB      (TC4_BASE.TC_RB)
#define TC4_RC      (TC4_BASE.TC_RC)
#define TC4_SR      (TC4_BASE.TC_SR)
#define TC4_IER     (TC4_BASE.TC_IER)
#define TC4_IDR     (TC4_BASE.TC_IDR)
#define TC4_IMR     (TC4_BASE.TC_IMR)

#define TC5_CCR     (TC5_BASE.TC_CCR)
#define TC5_CMR     (TC5_BASE.TC_CMR)
#define TC5_CV      (TC5_BASE.TC_CV)
#define TC5_RA      (TC5_BASE.TC_RA)
#define TC5_RB      (TC5_BASE.TC_RB)
#define TC5_RC      (TC5_BASE.TC_RC)
#define TC5_SR      (TC5_BASE.TC_SR)
#define TC5_IER     (TC5_BASE.TC_IER)
#define TC5_IDR     (TC5_BASE.TC_IDR)
#define TC5_IMR     (TC5_BASE.TC_IMR)


/*----------------------------*/
/* Real Time Clock Registers  */
/*----------------------------*/

#define RTC_CR      (RTC_BASE->RTC_CR)
#define RTC_MR      (RTC_BASE->RTC_MR)
#define RTC_TIMR    (RTC_BASE->RTC_TIMR)
#define RTC_CALR    (RTC_BASE->RTC_CALR)
#define RTC_TAR     (RTC_BASE->RTC_TAR)
#define RTC_CAR     (RTC_BASE->RTC_CAR)
#define RTC_SR      (RTC_BASE->RTC_SR)
#define RTC_SCCR    (RTC_BASE->RTC_SCCR)

#define RTC_IER     (RTC_BASE->RTC_IER)
#define RTC_IDR     (RTC_BASE->RTC_IDR)
#define RTC_IMR     (RTC_BASE->RTC_IMR)
#define RTC_VER     (RTC_BASE->RTC_VER)


/*---------------------------------------*/
/* Serial Peripheral Interface Registers */
/*---------------------------------------*/

#define SPI_CR      (SPI_BASE->SP_CR)
#define SPI_MR      (SPI_BASE->SP_MR)
#define SPI_RDR     (SPI_BASE->SP_RDR)
#define SPI_TDR     (SPI_BASE->SP_TDR)
#define SPI_SR      (SPI_BASE->SP_SR)

#define SPI_IER     (SPI_BASE->SP_IER)
#define SPI_IDR     (SPI_BASE->SP_IDR)
#define SPI_IMR     (SPI_BASE->SP_IMR)

#define SPI_RPR     (SPI_BASE->SP_RPR)
#define SPI_RCR     (SPI_BASE->SP_RCR)
#define SPI_TPR     (SPI_BASE->SP_TPR)
#define SPI_TCR     (SPI_BASE->SP_TCR)

#define SPI_CSR0    (SPI_BASE->SP_CSR[0])
#define SPI_CSR1    (SPI_BASE->SP_CSR[1])
#define SPI_CSR2    (SPI_BASE->SP_CSR[2])
#define SPI_CSR3    (SPI_BASE->SP_CSR[3])

/*-----------------------*/
/* DAC 0 and 1 Registers */
/*-----------------------*/

#define DAC0_CR      (DAC0_BASE->DAC_CR)
#define DAC1_CR      (DAC1_BASE->DAC_CR)

#define DAC0_MR      (DAC0_BASE->DAC_MR)
#define DAC1_MR      (DAC1_BASE->DAC_MR)

#define DAC0_DHR     (DAC0_BASE->DAC_DHR)
#define DAC1_DHR     (DAC1_BASE->DAC_DHR)

#define DAC0_DOR     (DAC0_BASE->DAC_DOR)
#define DAC1_DOR     (DAC1_BASE->DAC_DOR)

#define DAC0_SR      (DAC0_BASE->DAC_SR)
#define DAC1_SR      (DAC1_BASE->DAC_SR)

#define DAC0_IER     (DAC0_BASE->DAC_IER)
#define DAC1_IER     (DAC1_BASE->DAC_IER)

#define DAC0_IDR     (DAC0_BASE->DAC_IDR)
#define DAC1_IDR     (DAC1_BASE->DAC_IDR)

#define DAC0_IMR     (DAC0_BASE->DAC_IMR)
#define DAC1_IMR     (DAC1_BASE->DAC_IMR)

/*-----------------------*/
/* ADC 0 and 1 Registers */
/*-----------------------*/
#define ADC0_CR      (ADC0_BASE->ADC_CR)
#define ADC1_CR      (ADC1_BASE->ADC_CR)

#define ADC0_MR      (ADC0_BASE->ADC_MR)
#define ADC1_MR      (ADC1_BASE->ADC_MR)

#define ADC0_CHER    (ADC0_BASE->ADC_CHER)
#define ADC1_CHER    (ADC1_BASE->ADC_CHER)

#define ADC0_CHDR    (ADC0_BASE->ADC_CHDR)
#define ADC1_CHDR    (ADC1_BASE->ADC_CHDR)

#define ADC0_CHSR    (ADC0_BASE->ADC_CHSR)
#define ADC1_CHSR    (ADC1_BASE->ADC_CHSR)

#define ADC0_SR      (ADC0_BASE->ADC_SR)
#define ADC1_SR      (ADC1_BASE->ADC_SR)

#define ADC0_IER     (ADC0_BASE->ADC_IER)
#define ADC1_IER     (ADC1_BASE->ADC_IER)

#define ADC0_IDR     (ADC0_BASE->ADC_IDR)
#define ADC1_IDR     (ADC1_BASE->ADC_IDR)

#define ADC0_IMR     (ADC0_BASE->ADC_IMR)
#define ADC1_IMR     (ADC1_BASE->ADC_IMR)

#define ADC0_CDR0    (ADC0_BASE->ADC_CDR0)
#define ADC1_CDR0    (ADC1_BASE->ADC_CDR0)

#define ADC0_CDR1    (ADC0_BASE->ADC_CDR1)
#define ADC1_CDR1    (ADC1_BASE->ADC_CDR1)

#define ADC0_CDR2    (ADC0_BASE->ADC_CDR2)
#define ADC1_CDR2    (ADC1_BASE->ADC_CDR2)

#define ADC0_CDR3    (ADC0_BASE->ADC_CDR3)
#define ADC1_CDR3    (ADC1_BASE->ADC_CDR3)

/*-----------*/
/* Watchdog  */
/*-----------*/
#define WD_OMR      (WD_BASE->WD_OMR)
#define WD_CMR      (WD_BASE->WD_CMR)
#define WD_CR       (WD_BASE->WD_CR)


#endif /* reg_m55800_h */
