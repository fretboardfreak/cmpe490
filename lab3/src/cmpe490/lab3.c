//* lab3.c file
//* example file for lab #3
//* NM Jan 30, 2006
//* Removed all keypad stuff for old keypad portion of lab
//* nem Jan 25, 2009
//* For atmel_demos verson place all src files in Project_Name/src/projects/led_swing directory
//* For projects based on the lab2 tutorial place the *.h files in Project_Name/include/cmpe490
//* Place the *.c files in Project_Name/src/cmpe490
#ifdef SEMIHOSTING
#include <stdio.h>
#endif



// This set works for the atmel_demo type project
//#include "cmpe490/lcd.h"
//#include "parts/m55800/lib_m55800.h"
//#include "targets/eb55/eb55.h"

//This set works for the lab2_tutorial type project
#include "cmpe490/lcd.h"
#include "parts/m55800/eb55.h"
#include "parts/m55800/lib_m55800.h"
//*----------------------------------------------------------------------------
//* Function Name       : main
//* Object              : Main function of the led swing
//* Input Parameters    : none
//* Output Parameters   : True
//*----------------------------------------------------------------------------
int main( void )
//* Begin
{
    int *aic_ier, *pio_ier, *pio_per;

    //LEDs Initialization to output but off
    at91_pio_open ( &PIOB_DESC, LED_MASK, PIO_OUTPUT ) ;
    at91_pio_write (&PIOB_DESC, LED_MASK, LED_OFF ) ;

    //Interrupt set up
    aic_ier = 0xfffff120;
    pio_ier = 0xfffec040;
    pio_per = 0xfffec000;
    *aic_ier |= 0x10000000;
    *pio_ier |= 0x400;
    *pio_per |= 0x400;
	
	// LCD Initialization and write an initial string
    LCDInit();				
    LCDString("Welcome to Lab #3");
    
    while(1){ 				
    }
    return(0);
//* End
}
#define BUTTON_MASK 0x00078000
void irq_handler(){
    u_int status = at91_pio_read(&PIOA_DESC);
    u_int button = (status & BUTTON_MASK)>>15;
    char* output;
    switch(button) {
	case 0:
	    output = "button 0";
	    break;
	case 1:
	    output = "button 1";
	    break;
	case 2:
	    output = "button 2";
	    break;
	case 3:
	    output = "button 3";
	    break;
	case 4:
	    output = "button 4";
	    break;
	case 5:
	    output = "button 5";
	    break;
	case 6:
	    output = "button 6";
	    break;
	case 7:
	    output = "button 7";
	    break;
	case 8:
	    output = "button 8";
	    break;
	case 9:
	    output = "button 9";
	    break;
	case 10:
	    output = "button 10";
	    break;
	case 11:
	    output = "button 11";
	    break;
	case 12:
	    output = "button 12";
	    break;
	case 13:
	    output = "button 13";
	    break;
	case 14:
	    output = "button 14";
	    break;
	case 15:
	    output = "button 15";
	    break;
	default:
	    output = "unknown button";
    }
    LCDString(output);
}

