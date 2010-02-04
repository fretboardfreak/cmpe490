#ifndef _h_lcd_h_
#define _h_lcd_h_

// atmel includes
//#include "parts/m55800/lib_m55800.h"
//#include "targets/eb55/eb55.h"

// lab2 tutorial includes
#include "parts/m55800/eb55.h"
#include "parts/m55800/lib_m55800.h"

void LCDInit(void);
void ToggleEnableLine(void);
void LCDData(char);
void LCDCmd(char);
void LCDString(char* );
void WriteDataLines(char);

#define	 E 	PA19		// enable line for LCD
#define	 RW PA20		// R/W line for LCD
#define  RS	PA21		// Register Select line for LCD

#define	 D0	PA0
#define	 D1	PA1
#define  D2	PA2
#define	 D3	PA3
#define	 D4	PA4
#define	 D5	PA5
#define  D6	PA6
#define	 D7	PA7

#define  DATA_MASK 	D0|D1|D2|D3|D4|D5|D6|D7
#define  CONTROL_MASK 	E|RW|RS
#define  LCD_MASK 	DATA_MASK|CONTROL_MASK

#define  LOW	PIO_CLEAR_OUT
#define  HIGH	PIO_SET_OUT

#define  MAX_SLOW	2000	// max poss time for slow instructions
#define	 MAX_FAST	1000	// max poss time for fast instructions

#define  TIME_CLEAR_DISPLAY		MAX_SLOW
#define  TIME_RETURN_HOME   	MAX_SLOW
#define	 TIME_ENTRYMODE_SET		MAX_FAST
#define	 TIME_DISPLAY_ON_OFF	MAX_FAST
#define	 TIME_CURS_DISP_SHIFT	MAX_FAST
#define	 TIME_FUNCTION_SET		MAX_FAST
#define	 TIME_CG_RAM_SET		MAX_FAST
#define	 TIME_DD_ARM_SET		MAX_FAST
#define	 TIME_READ_BF_ADD		MAX_FAST
#define	 TIME_WR_DATA			MAX_FAST
#define	 TIME_READ_DATA			MAX_FAST
#define	 TIME_ENABLE			MAX_FAST

/* #defines for the various features based on function */
/* for all of these RS = 0 and r/w = 0 */
#define	  CMD_CLEAR_DISPLAY	0x01
#define   CMD_RETURN_HOME	0x02	// DB0 is a don't care


#define	  CMD_ENTRY_MODE_SET	0x04	// set other options as well
#define   OPT_MODE_INC		0x02	// set cursor to increment mode
#define	  OPT_MODE_DEC		0x00	// set cursor to decrement mode
#define	  OPT_MODE_SHIFT	0x01 	// shift display enable
#define	  OPT_MODE_NO_SHIFT	0x00	// shift display disable

#define   CMD_DISPLAY		0x08	// display on and off control
#define	  OPT_DISPLAY_ON	0x04	// display on
#define	  OPT_DISPLAY_OFF	0x00	// display off
#define	  OPT_CURSOR_ON		0x02	// cursor on
#define   OPT_CURSOR_OFF	0x00	// cursor off
#define	  OPT_BLINK_ON		0x01	// blink on
#define	  OPT_BLINK_OFF		0x00	// blink off

#define	  CMD_SHIFT			0x10	// set cursor moving and display shift
#define	  OPT_DISPLAY_SHIFT	0x08	// shift display
#define	  OPT_CURSOR_MOVE	0x00	// shift cursor
#define	  OPT_RIGHT			0x04	// move right
#define	  OPT_LEFT			0x00	// move left

#define	  CMD_FUNCTION_SET	0x20	// initialize display parameters
#define	  OPT_DATA_8		0x10	// 8 bit interface
#define	  OPT_DATA_4		0x00	// 4 bit interface
#define	  OPT_LINES_2		0x08	// 2 lines used
#define	  OPT_LINES_1		0x00	// 1 line used
#define	  OPT_FONT_5X10		0x04	// fonts are 5x10 dots
#define	  OPT_FONT_5X7		0x00	// fonts are 5x7 dots

#define	  CMD_SET_CGRAM_ADD	0x40	// set CGRAM address
// you must provide the address in DB5-DB

#define	  CMD_SET_DDRAM_ADD	0x80	// set DDRAM address
// you must provide the address in DB6-DB0

// to read the busy flag rs = 0 and r/w = 1 BF is in DB7
// to write data rs = 1 and r/w = 0
// to read data rs = 1 and r/w = 1

#define   LSB	0
#define	  MSB	7
#define	  BITS	8

#define   HALF_SECOND 		500000	// about .5 seconds in uS 

#endif
