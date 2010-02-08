/* main.c for Lab #1
    Nancy Minderman 
    April 20, 2007
    This file should be useable by all three programs in the lab1 project
    */


#ifdef SEMIHOSTING
#include <stdio.h>
#endif

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

extern void wake_up_handler (void) ;

/* Global Variable */
WaitDesc wait_desc = { &TC0_DESC, 0, 0, WAIT_DELAY, wake_up_handler } ;
u_int   LedSpeed ;

//*----------------------------------------------------------------------------
//* Function Name       : change_speed
//* Object              : Adjust led speed depending on SW1 and SW3
//* Input Parameters    : none
//* Output Parameters   : none
//*----------------------------------------------------------------------------
void change_speed ( void )
//* Begin
{
    u_int status = at91_pio_read (&PIOB_DESC) ;
    if (( status & (1<<PIO_SW1) ) == 0 )
    {
        if ( LedSpeed > 10000 ) LedSpeed -=1000 ;
    }
    if (( status & (1<<PIO_SW3) ) == 0 )
    {
        if ( LedSpeed < 2000000 ) LedSpeed +=1000 ;
    }
}
//* End

//*----------------------------------------------------------------------------
//* Function Name       : main
//* Object              : Main function of the led swing
//* Input Parameters    : none
//* Output Parameters   : True
//*----------------------------------------------------------------------------
int main( void )
//* Begin
{
    u_int   loop_count = 0 ;
    u_int   i;
	u_int 	led_start=LED1;
    LedSpeed = 80000 ;
#ifdef RAM
	led_start=LED2;
	
#elif ROMRUN
	led_start=LED3;
	
#elif ROMRUN_EXTRA
	led_start=LED4;
	
#elif ROMCOPY
	led_start=LED5;
	
#elif ROMCOPY_EXTRA
	led_start=LED6;
	
#endif

    //* -- Set up PIO
    at91_pio_open ( &PIOB_DESC, LED_MASK, PIO_OUTPUT ) ;
    at91_pio_write (&PIOB_DESC, LED_MASK, LED_OFF ) ;

    //* Detect Master Clock
    wait_desc.mcki_khz = 32000 ;

    //* Loop forever
    for (;;)
    {
        //* Once a Shot on each led
        for ( i=led_start ; i <= LED8 ; i<<=1 )
        {
            change_speed () ;
            at91_pio_write (&PIOB_DESC, i, LED_ON ) ;
            wait_desc.period = LedSpeed ;
            at91_wait_open ( &wait_desc ) ;
            at91_pio_write (&PIOB_DESC, i, LED_OFF ) ;
        }
        //* Once a Shot on each led
        for ( i=LED8 ; i >= led_start ; i>>=1 )
        {
            change_speed () ;
            at91_pio_write (&PIOB_DESC, i, LED_ON ) ;
            at91_wait_open ( &wait_desc ) ;
            at91_pio_write (&PIOB_DESC, i, LED_OFF ) ;
        }
#ifdef SEMIHOSTING
       printf ( "Loop %d\n", loop_count ) ;
#endif
        loop_count ++ ;

    }
    return(TRUE);
//* End
}
