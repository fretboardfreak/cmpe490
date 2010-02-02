//*-----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*-----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*-----------------------------------------------------------------------------
//* File Name           : lib_i2c.c
//* Object              : I2C driver functions
//*
//* 1.0 29/05/00  EL    : Creation
//* 2.0 06/09/00  EL    : Clean up
//* 2.1 21/11/00  JPP   : Change Timer interrupt in LEVEL
//* 2.2 14/01/02  JPP   : Send NACK at for read, and add wait function
//*-----------------------------------------------------------------------------

//* --------------------------- include file ----------------------------------

#include    "lib_i2c.h"
#include    "periph/power_saving/lib_power_save.h"
#include    "periph/timer_counter/lib_tc.h"


//*-----------------------------------------------------------------------------
//*                    Internal function prototype
//*-----------------------------------------------------------------------------

void  at91_I2CError(I2Cdesc *I2C_pt);
void  at91_I2CSendStartSDA (I2Cdesc *I2C_pt);
void  at91_I2CTxSendByte (I2Cdesc *I2C_pt);
void  at91_I2CTxSendDeviceAddress (I2Cdesc *I2C_pt);
void  at91_I2CTxSendBit (I2Cdesc *I2C_pt);
void  at91_I2CRxReceiveByte (I2Cdesc *I2C_pt);
void  at91_I2CRxReceiveBit (I2Cdesc *I2C_pt);

void  at91_I2CSendStartSDA (I2Cdesc *I2C_pt);
void  at91_I2CSendStartSCL (I2Cdesc *I2C_pt);
void  at91_I2CPrepareSTOP (I2Cdesc *I2C_pt);

void  at91_I2CPrepareACK (I2Cdesc *I2C_pt);
void  at91_I2CTxWaitACK (I2Cdesc *I2C_pt);
void  at91_I2CRxDoACK (I2Cdesc *I2C_pt);

void  at91_I2CTxSetSCL (I2Cdesc *I2C_pt);
void  at91_I2CTxClearSCL (I2Cdesc *I2C_pt);
void  at91_I2CRxSetSCL (I2Cdesc *I2C_pt);
void  at91_I2CRxClearSCL (I2Cdesc *I2C_pt);

//*-----------------------------------------------------------------------------
//*                    Internal function definition
//*-----------------------------------------------------------------------------

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2C (I2Cdesc *I2C_pt, u_short loadAddress, u_char nbByte)
//* Object              : I2C
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//*         : loadAddress
//*         : nbByte
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CDeviceRead (I2Cdesc *I2C_pt)
{ //* Begin
    I2C_pt->pioa_base->PIO_OER = I2C_pt->SDA_line;          //* set SDA line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;         //* set SDA line
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;         //* set SCL line

    //* get byte to transmit
    I2C_pt->I2CByte = I2C_pt->deviceAddress | READ_BIT ;
    I2C_pt->mode = DATA_READ;                               //* next mode
    I2C_pt->countBit = 8;                                   //* initialize countBit

    //* initialize nb_ACK
    I2C_pt->nb_ACK = 10;

    //* change interrupt handler to at91_I2CSendStartSDA
    I2C_pt->I2CTCHandler = at91_I2CSendStartSDA;

} //* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxSendByte (I2Cdesc *I2C_pt)
//* Object              : I2C
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CTxSendByte (I2Cdesc *I2C_pt)
{ //* Begin
    I2C_pt->pioa_base->PIO_OER = I2C_pt->SDA_line;      //* set SDA line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;     //* set SDA line

    //* get byte to transmit
    switch(I2C_pt->mode)
    {
    case DATA :
            I2C_pt->I2CByte = *(I2C_pt->TxEnd++);

            I2C_pt->nbI2CByte--;
            if(I2C_pt->nbI2CByte == 0)
            //* next mode
                I2C_pt->mode = STOP;
        break;

    case HIGH_ADDRESS_WRITE :
            I2C_pt->I2CByte = (u_char) (I2C_pt->loadAddress >> 8);

            //* next mode
            I2C_pt->mode = LOW_ADDRESS_WRITE;
        break;

    case LOW_ADDRESS_WRITE :
            I2C_pt->I2CByte = (u_char) I2C_pt->loadAddress;

            //* next mode
            I2C_pt->mode = DATA;
        break;

    case HIGH_ADDRESS_READ :
            I2C_pt->I2CByte = (u_char) (I2C_pt->loadAddress >> 8);

            //* next mode
            I2C_pt->mode = LOW_ADDRESS_READ;
        break;

    case LOW_ADDRESS_READ :
            I2C_pt->I2CByte = (u_char) I2C_pt->loadAddress;

            //* next mode
            I2C_pt->mode = DEVICE_READ;
        break;
    }

    I2C_pt->countBit = 8;                   //* initialize countBit
    I2C_pt->nb_ACK = 10;                     //* initialize nb_ACK

    //* change interrupt handler to at91_I2CTxSendBit
    I2C_pt->I2CTCHandler = at91_I2CTxSendBit;

} //* End


//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxSendBit (I2Cdesc *I2C_pt)
//* Object              :
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CTxSendBit (I2Cdesc *I2C_pt)
{//* Begin

    u_char bit_val;

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;      //* Clear SCL line

    //* decrement countBit
    I2C_pt->countBit--;

    //* if bit counter = 0
    if(I2C_pt->countBit >= 0)
    {
    //* get bit to transfert
    bit_val = (I2C_pt->I2CByte >> I2C_pt->countBit) & 1;

    //* Send 0 or 1
    if (bit_val)
        //* Set SDA line
        I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;

        else
        //* Clear SDA line
        I2C_pt->pioa_base->PIO_CODR = I2C_pt->SDA_line;

    //* change interrupt handler to at91_I2CTxSetSCL
    I2C_pt->I2CTCHandler = at91_I2CTxSetSCL;
    }
    else
    {
    //* set SDA line as an input
    I2C_pt->pioa_base->PIO_ODR = I2C_pt->SDA_line;

    //* change interrupt handler to at91_I2CPrepareACK
    I2C_pt->I2CTCHandler = at91_I2CPrepareACK;
    }
}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CSendStartSDA (I2Cdesc *I2C_pt)
//* Object              : clear SDA line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CSendStartSDA (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SDA_line;     //* clear SDA line

    //* change interrupt handler to at91_I2CSendStartSCL
    I2C_pt->I2CTCHandler = at91_I2CSendStartSCL;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxSendStart (I2Cdesc *I2C_pt)
//* Object              : clear SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CSendStartSCL (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;     //* clear SCL line

    //* change interrupt handler to at91_I2CTxSendBit
    I2C_pt->I2CTCHandler = at91_I2CTxSendBit;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CPrepareSTOP (I2Cdesc *I2C_pt)
//* Object              :
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CPrepareSTOP (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_OER = I2C_pt->SDA_line;          //* set SDA line as an output
    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SDA_line;         //* clear SDA line
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;         //* set SCL line

    //* change interrupt handler to at91_I2CSendStopSDA
    I2C_pt->I2CTCHandler = at91_I2CSendStopSDA;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CSendStopEND (I2Cdesc *I2C_pt)
//* Object              : end of transmistion
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CSendStopEND (I2Cdesc *I2C_pt)
{//* Begin

    //* Disable RC compare interrupt
    I2C_pt->timerBase->TC_IDR = TC_CPCS;

    //* change interrupt handler to
    I2C_pt->I2CTCHandler = no_handler_tc;

    //* set the End state
    I2C_pt->state = OK;

}//* End
//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CSendStopSDA (I2Cdesc *I2C_pt)
//* Object              : set SDA and  ans load end for stop
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CSendStopSDA (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;         //* set SDA line

    //* change interrupt handler to
    I2C_pt->I2CTCHandler = at91_I2CSendStopEND;

}//* End


//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CPrepareACK (I2Cdesc *I2C_pt)
//* Object              : set SCL line and load at91_I2CTxWaitACK
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CPrepareACK (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;         //* set SCL line

    //* change interrupt handler to at91_I2CTxWaitACK
    I2C_pt->I2CTCHandler = at91_I2CTxWaitACK;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRxPrepareACK (I2Cdesc *I2C_pt)
//* Object              :
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxPrepareACK (I2Cdesc *I2C_pt)
{//* Begin


    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;         //* set SCL line

    if(I2C_pt->mode == STOP)
        //* change interrupt handler to
        I2C_pt->I2CTCHandler = at91_I2CPrepareSTOP;
    else
        //* change interrupt handler to at91_I2CRxDoACK
        I2C_pt->I2CTCHandler = at91_I2CRxDoACK;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxWaitACK (I2Cdesc *I2C_pt)
//* Object              :
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CTxWaitACK (I2Cdesc *I2C_pt)
//* Begin
{
    //* if ACK (SDA = 0)
    if((I2C_pt->pioa_base->PIO_PDSR & I2C_pt->SDA_line) == 0)
    {
    switch(I2C_pt->mode)
    {
        case STOP :
            //* clear SCL line
            I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;

            //* change interrupt handler to
            I2C_pt->I2CTCHandler = at91_I2CPrepareSTOP;
        break;

        case DEVICE_READ :
            //* clear SCL line
            I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;

            //* change interrupt handler to
            I2C_pt->I2CTCHandler = at91_I2CDeviceRead;
        break;

        case DATA_READ :
            //* change interrupt handler to
            I2C_pt->I2CTCHandler = at91_I2CRxReceiveByte;
        break;

        default :
            //* clear SCL line
            I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;

            //* change interrupt handler to
            I2C_pt->I2CTCHandler = at91_I2CTxSendByte;
        break;
    } //* End switch
    }
    else
    {
        I2C_pt->nb_ACK--;
    if(I2C_pt->nb_ACK == 0)
        //* change interrupt handler to at91_I2C
        I2C_pt->I2CTCHandler = at91_I2CError;
   }
}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRxDoACK (I2Cdesc *I2C_pt)
//* Object              : clear SCL line and load RxReceiveByte
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxDoACK (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;     //* clear SCL line

    //* change interrupt handler to
    I2C_pt->I2CTCHandler = at91_I2CRxReceiveByte;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxSetSCL (I2Cdesc *I2C_pt)
//* Object              : set SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CTxSetSCL (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;     //* set SCL line

    //* change interrupt handler to at91_I2CTxSendBit
     I2C_pt->I2CTCHandler = at91_I2CTxSendBit;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CTxClearSCL (I2Cdesc *I2C_pt)
//* Object              : Clear SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CTxClearSCL (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;     //* Clear SCL line

    if(I2C_pt->countBit == 0)
        //* set SDA line as an input
    I2C_pt->pioa_base->PIO_ODR = I2C_pt->SDA_line;

    //* change interrupt handler to at91_I2CTxSendBit
    I2C_pt->I2CTCHandler = at91_I2CTxSendBit;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRxSetSCL (I2Cdesc *I2C_pt)
//* Object              : set SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxSetSCL (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;         //* set SCL line

    //* change interrupt handler to at91_I2CRxReceiveBit
    I2C_pt->I2CTCHandler = at91_I2CRxReceiveBit;

}//* End


//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRxClearSCL (I2Cdesc *I2C_pt)
//* Object              : Clear SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxClearSCL (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;         //* Clear SCL line

    if(I2C_pt->countBit == 0)
      {
        //* change interrupt handler to at91_I2CI2CRxPrepareACK
        I2C_pt->I2CTCHandler = at91_I2CRxPrepareACK;

        I2C_pt->pioa_base->PIO_OER = I2C_pt->SDA_line;      //* set SDA line as an output

        if(I2C_pt->nbI2CByte == 0)                          //* If last byte
        {
            I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line; //* set SDA line for NACK
        }
        else
        {
            I2C_pt->pioa_base->PIO_CODR = I2C_pt->SDA_line; //* clear SDA line for ACK
        } //* End if last Byte

      }//* End countBit
    else
    //* change interrupt handler to at91_I2CRx
    I2C_pt->I2CTCHandler = at91_I2CRxReceiveBit;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRxReceiveByte (I2Cdesc *I2C_pt)
//* Object              : clear SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxReceiveByte (I2Cdesc *I2C_pt)
{//* Begin

    I2C_pt->pioa_base->PIO_ODR  = I2C_pt->SDA_line;     //* set SDA line as an input
    I2C_pt->pioa_base->PIO_CODR = I2C_pt->SCL_line;     //* clear SCL line

    I2C_pt->countBit = 8;                               //* initialize countBit

    I2C_pt->nbI2CByte--;                                //* decrement byte
        if(I2C_pt->nbI2CByte == 0)
            I2C_pt->mode = STOP;                        //* next mode

    //* change interrupt handler to at91_I2C
    I2C_pt->I2CTCHandler = at91_I2CRxReceiveBit;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : u_char at91_I2CRxReceiveBit (I2Cdesc *I2C_pt)
//* Object              : set SCL line
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRxReceiveBit (I2Cdesc *I2C_pt)
{//* Begin

    u_char bit_val;

    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;     //* set SCL line
    I2C_pt->countBit--;                                 //* decrement countBit

    //* get bit
    if((I2C_pt->pioa_base->PIO_PDSR & I2C_pt->SDA_line) == I2C_pt->SDA_line)
        bit_val = 1;
    else
        bit_val = 0;

    //* if bit counter > 0
    if(I2C_pt->countBit > 0)
        //* update working byte
        *I2C_pt->RxEnd |= (bit_val << I2C_pt->countBit);
    else
         *(I2C_pt->RxEnd++) |= (bit_val << I2C_pt->countBit) ;

    //* change interrupt handler to at91_I2CRxClearSCL
    I2C_pt->I2CTCHandler = at91_I2CRxClearSCL;

}//* End
//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CWait (I2Cdesc *I2C_pt)
//* Object              : Waite Handler
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CWait (I2Cdesc *I2C_pt)
{//* Begin
    I2C_pt->countBit--;                         //* decrement countBit for time

    if(I2C_pt->countBit == 0)                   //* if bit counter = 0
    {
        I2C_pt->timerBase->TC_CCR = TC_CLKDIS ;
        at91_I2C_lineOpen(I2C_pt,I2C_pt->timerMem);
    }

}//* End


//*-----------------------------------------------------------------------------
//*                    Export function prototype
//*-----------------------------------------------------------------------------

//*-----------------------------------------------------------------------------
//* Function Name       : u_char at91_I2CRxReceiveBit (I2Cdesc *I2C_pt)
//* Object              : C Interrupt Handler called by assembly handler
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void I2C_lineHandlerInt (I2Cdesc *I2C_pt)
{//* Begin
u_char dummy;
    //* acknowledge interrupt status
    dummy = I2C_pt->timerBase->TC_SR;

    //* call automate state handler*/
    (*(I2C_pt->I2CTCHandler))(I2C_pt);
}//* End

//*-----------------------------------------------------------------------------
//* Function Name       :  (I2Cdesc *I2C_pt)
//* Object              : Open I2C
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//*         RCValue Timer value for gererate I2C SCL alf periode
//*               RCValue  = ( (MCKI / 2) /2 ) * SCL
//*                              TCCLKS =0
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2C_lineOpen (I2Cdesc *I2C_pt, u_int RCValue)
{//* Begin

    //* line
    I2C_pt->state = OK;

    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SDA_line;     //* set SDA line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;     //* set SDA line
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SCL_line;     //* set SCL line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;     //* set SCL line

    at91_clock_open(I2C_pt->pio_ctrl_desc->periph_id);

    //* TIMER configuration
    //* Set the mode of the timer
    //* Open the clock of the timer
    at91_clock_open(I2C_pt->channelId);

    //*  0x0000C     4     0        0
    //*       1100  01 00 0 0 00  0 000
    //*                             MCK/2
    //*                           CLKI: 0 = Counter is incremented on rising edge of the clock.
    //*                       BURST: The clock is not gated by an external signal.
    //*                     CPCSTOP: Counter clock is not stopped when counter reaches RC.
    //*                   CPCDIS:Counter clock is not disabled when counter reaches RC.
    //*              EEVTEDG:0 1 XC0 Output
    //*          ENETRG:The external event resets the counter and starts the counter clock.
    //*
    //*        CPCTRG:RC Compare resets the counter and starts the counter clock.
    //*       WAVE = 1
    I2C_pt->timerBase->TC_CMR = 0x0000C400;

    //*  Set timer
    I2C_pt->timerBase->TC_RC = RCValue;         //*
    I2C_pt->timerMem = RCValue;                 //* Save Timer value
    //* modificationn set in LEVEL not EDGE
    at91_irq_open(I2C_pt->channelId, 7, AIC_SRCTYPE_INT_LEVEL_SENSITIVE, I2C_pt->AICHandler);

    //* Enable the clock
    I2C_pt->timerBase->TC_CCR = TC_CLKEN;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : I2C_lineClose(I2Cdesc *I2C_pt)
//* Object              : Close I2C
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2C_lineClose (I2Cdesc *I2C_pt)
{//* Begin

    //* Sate
    I2C_pt->state = OK;

    //* set line
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SDA_line; //* set SDA line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line; //* set SDA line
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SCL_line; //* set SCL line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line; //* set SCL line

    //* change interrupt handler to
    I2C_pt->I2CTCHandler = no_handler_tc;

    at91_clock_close(I2C_pt->pio_ctrl_desc->periph_id);

    //* TIMER configuration
    at91_clock_close(I2C_pt->channelId);
    //* Disable the clock and interrupts
    I2C_pt->timerBase->TC_CCR = TC_CLKDIS ;
    I2C_pt->timerBase->TC_IDR = 0xFFFFFFFF ;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CWrite (I2Cdesc *I2C_pt, u_short loadAddress, u_char nbByte)
//* Object              : I2C Write Byte & Write Page
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//*         : loadAddress  Address on slave
//*         : nbByte       Write to bytes
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CWrite (I2Cdesc *I2C_pt, u_short loadAddress, u_int nbByte )
{//* Begin

    //* initialize state
    I2C_pt->state = NOK;
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SDA_line;     //* set SDA line as an output
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SCL_line;     //* set SCL line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;     //* set SCL line
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;     //* set SDA line

    //* get byte to transmit
    I2C_pt->I2CByte = I2C_pt->deviceAddress | WRITE_BIT ;
    I2C_pt->loadAddress = loadAddress;                  //* get address in Target
    I2C_pt->nbI2CByte = nbByte;                         //* get nb byte to transmit
    I2C_pt->countBit = 8;                               //* initialize countBit
    I2C_pt->nb_ACK = 10;                                 //* initialize nb_ACK

    //* Send Write
    I2C_pt->mode = HIGH_ADDRESS_WRITE;                  //* next mode

    //* change interrupt handler to at91_I2CSendStartSDA
    I2C_pt->I2CTCHandler = at91_I2CSendStartSDA;

     //* Enable RC compare interrupt
    I2C_pt->timerBase->TC_IER = TC_CPCS;

}//* End

//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CRead (I2Cdesc *I2C_pt, u_short loadAddress, u_char nbByte)
//* Object              : I2C RANDOM Read & Sequential Read
//*   I2C sequence:
//* start addI2C W ACK loadAddressMSD ACK loadAddressLSB ACK Start addI2C R data NACK stop
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//*         : loadAddress address of return buffer
//*         : nbByte
//* Output Parameters   : none
//*-----------------------------------------------------------------------------
void at91_I2CRead (I2Cdesc *I2C_pt, u_short loadAddress, u_int nbByte )
{//* Begin
    u_int   loop;

    //* clean the rx buff for shifting byte
    for(loop = 0; loop < nbByte ; loop++)
    {
        I2C_pt->RxPtr[loop]=0;
    }

    //* initialize state
    I2C_pt->state = NOK;

    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SDA_line;     //* set SDA line as an output
    I2C_pt->pioa_base->PIO_OER  = I2C_pt->SCL_line;     //* set SCL line as an output
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SCL_line;     //* set SCL line
    I2C_pt->pioa_base->PIO_SODR = I2C_pt->SDA_line;     //* set SDA line

    //* get byte to read
    I2C_pt->I2CByte = I2C_pt->deviceAddress | WRITE_BIT;
    I2C_pt->loadAddress = loadAddress;                  //* get address
    I2C_pt->nbI2CByte = nbByte;                         //* get nb byte to transmit
    I2C_pt->countBit = 8;                               //* initialize countBit
    I2C_pt->nb_ACK = 10;                                //* initialize nb_ACK

    //* next mode
    I2C_pt->mode = HIGH_ADDRESS_READ;

    //* change interrupt handler to at91_I2CSendStartSDA
    I2C_pt->I2CTCHandler = at91_I2CSendStartSDA;

     //* Enable RC compare interrupt
    I2C_pt->timerBase->TC_IER = TC_CPCS;

}//* End


//*-----------------------------------------------------------------------------
//* Function Name       : at91_I2CWaitTime
//* Object              : I2C
//* Input Parameters    : <I2C_pt> = I2C Peripheral Descriptor pointer
//*         loadAddress - Address on slave
//*         nbByte      - Read to bytes
//*         I2C_address -  I2C address Divice
//*         mcki        - MCKI freq in KHz
//* Output Parameters   : FALSE if input parameter are out of range
//*-----------------------------------------------------------------------------
u_int at91_I2CWaitTime (I2Cdesc *I2C_pt,u_int time,u_int mcki)
{//* Begin
    while(I2C_pt->state != OK);

    //* load timer value for 0,2 ms
    mcki = mcki/2;
    //* check input value
    if ((mcki <= 0x0FFFF ) & ((time ) < 128))
    {
        I2C_pt->timerBase->TC_RC = mcki;    /* work in step of 1 ms */

        //* initialize state
        I2C_pt->state = NOK;

        //* initialize countBit time
        I2C_pt->countBit = time ;

        //* change interrupt handler to at91_I2CWait
        I2C_pt->I2CTCHandler = at91_I2CWait;

        //* load timer value for 1 ms
        I2C_pt->timerBase->TC_RC = mcki;

         //* Enable RC compare interrupt
        I2C_pt->timerBase->TC_IER = TC_CPCS;

        //* Trig the timer
        I2C_pt->timerBase->TC_CCR = TC_SWTRG;

    }
    else
    {
        return (FALSE);
    }
    return (TRUE);

}//* End

//*---------------------------------------------------------------------------------------
//* Function Name       : at91_I2CTransfertEnd(I2Cdesc *I2C_pt)
//* Object              : Wait the end I2C transfert when I2C_line.state != OK
//* Input Parameters    : None
//* Output Parameters   : none
//*---------------------------------------------------------------------------------------
void  at91_I2CTransfertEnd(I2Cdesc *I2C_pt)
{//* Begin
    while(I2C_pt->state != OK);

}//* End
