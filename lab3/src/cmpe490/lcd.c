/*
 *	lcd.c
 *	Currently only writes to the LCD, no reading
 *	The mappings of the pins is in lcd.h
 *	Suitable for any optrex/lumex 2X20 LCD display
 *	This file will not compile without the lib_drv_16_optm_none.gpj also
 *	being present in your project.
 * 	This code should go into the src/projects/sub-directory
 *	of your project and in the same directory as the file that contains.
 *	your main() function if you are using the atmel demos
 *	 
 *	Nancy Minderman
 *	Jan 30, 2005
 *
 * Added lab2_tutorial includes
 * 
 */
#ifdef SEMIHOSTING
#include <stdio.h>
#endif

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"

// atmel includes
//#include "targets/eb55/eb55.h"
//#include "projects/led_swing/lcd.h"

// lab 2 tutorial includes
#include "parts/m55800/eb55.h"
#include "cmpe490/lcd.h"

extern void wake_up_handler (void) ;

//In order for the link to succeed this must be global
WaitDesc wait_desc = { &TC0_DESC, MCK, 0, WAIT_DELAY, wake_up_handler } ;

//*----------------------------------------------------------------------------
//* Function Name       : LCDInit
//* Object              : Sets the LCD to a known state
//* Input Parameters    : none 
//* Output Parameters   : none
//* Side Effects	: changes the LCD pins to PIO_OUTPUT mode
//*			  lcd.h contains the pin mappings
//*		          also sets the enable line low
//*			  Other options are available in LCD.h
//*----------------------------------------------------------------------------
void LCDInit(void) {

    char command = 0;
    
	// turn all pins for the LCD to output mode */
    at91_pio_open ( &PIOA_DESC, LCD_MASK, PIO_OUTPUT);
	
	// turn LCD controller off by setting enable line low
    at91_pio_write (&PIOA_DESC, E, LOW);
	
	
	// before we can use the LCD we need to configure it
    command |= CMD_FUNCTION_SET;
    command |= OPT_DATA_8;		// 8 bit  interface please
    command |= OPT_LINES_2;		// 2 lines pleae
    command |= OPT_FONT_5X10;	// big characters please
    LCDCmd(command); 		

    command = 0;
    command |= CMD_DISPLAY; 	// build command for setting display/cursor/blinking on/off
    command |= OPT_DISPLAY_ON;	// turn on display
    command |= OPT_CURSOR_ON;	// turn on cursor
    command |= OPT_BLINK_ON;	// turn on blinky
    LCDCmd(command);

    command = 0;
    command |= CMD_SHIFT;		// build command for setting shift and direction
    command |= OPT_CURSOR_MOVE;	// set cursor to move
    command |= OPT_RIGHT;		// set direction of move to right
    LCDCmd(command);

    command = 0;
    command |= CMD_CLEAR_DISPLAY; // clear display and home cursor
    LCDCmd(command);
}

//*----------------------------------------------------------------------------
//* Function Name       : ToggleEnableLine
//* Object              : takes enable line from low to high and from high to low
//* Input Parameters    : none
//* Output Parameters   : none
//* Side Effects	: messes with the wait_desc defined elsewhere
//*----------------------------------------------------------------------------
void ToggleEnableLine(void) {
    
    // toggle enable line for TIME_ENABLE HIGH and TIME_ENABLE LOW
    at91_pio_write(&PIOA_DESC, E, HIGH);
    wait_desc.period = TIME_ENABLE;
    at91_wait_open ( &wait_desc );
    at91_pio_write(&PIOA_DESC, E, LOW);
    wait_desc.period = TIME_ENABLE;
    at91_wait_open (&wait_desc);
}

//*----------------------------------------------------------------------------
//* Function Name       : LCDData
//* Object              : Sends data to the LCD
//* Input Parameters    : char byte - data to send
//* Output Parameters   : none
//* Side Effects	: messes with the wait_desc defined elsewhere
//*----------------------------------------------------------------------------
void LCDData(char byte) {
// for this one I need to send data to the lcd
// rs = 1 rw =0 data = byte

    WriteDataLines(byte);
    
    // set rs high
    at91_pio_write(&PIOA_DESC, RS, HIGH);

    // set rw low
    at91_pio_write(&PIOA_DESC, RW, LOW);

    // set enable line
    ToggleEnableLine();

    // wait a bit for instruction to complete
    // at least TIME_WR_DATA time
    wait_desc.period = TIME_WR_DATA;
    at91_wait_open ( &wait_desc );
}

//*----------------------------------------------------------------------------
//* Function Name       : LCDCmd
//* Object              : Write a command to the LCD 
//* Input Parameters    : char command - command to send
//* Output Parameters   : none
//* Side Effects	: messes with the wait_desc defined elsewhere
//*----------------------------------------------------------------------------
void LCDCmd(char command) {
	
// for this one I need to send a command to the lcd
// rs = 0 rw = 0 data = command

    WriteDataLines(command);

    // set rw and rs both low
    at91_pio_write(&PIOA_DESC, RS|RW, LOW);

    // set enable line
    ToggleEnableLine();

    // wait a bit for instructions to complete
    // at least MAX_SLOW time
    wait_desc.period = MAX_SLOW;
    at91_wait_open ( &wait_desc );
}

//*----------------------------------------------------------------------------
//* Function Name       : LCDString
//* Object              : Writes a null-terminated string value to the LCD
//* Input Parameters    : char * pointer to a string. More than 80 chars will
//*			  be truncated on the LCD.
//* Output Parameters   : none
//* Side Effects	: none here
//*----------------------------------------------------------------------------
void LCDString(char * p_Str) {   
    while(*p_Str) {
	LCDData(*p_Str++);
    }
}

//*----------------------------------------------------------------------------
//* Function Name       : WriteDataLines
//* Object              : Sets the proper values for D0-D7
//*			  don't call this this is helper routines only
//*			  call LCDCmd, or LCDData instead
//* Input Parameters    : char byte
//* Output Parameters   : none
//* Side Effects	: none beyond the effects stated above.
//*----------------------------------------------------------------------------
void WriteDataLines(char byte) {
    
   // set data lines
    int i = 0;
    u_int pin_conversions[BITS] = {D0,D1,D2,D3,D4,D5,D6,D7};
    for (i=LSB; i<=MSB; i++) {
	if(((byte & (1<<i)) != 0)) {
	    at91_pio_write(&PIOA_DESC, pin_conversions[i], HIGH);
	} else {
	    at91_pio_write(&PIOA_DESC, pin_conversions[i], LOW);
	}

    }
}
