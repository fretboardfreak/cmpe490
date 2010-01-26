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
#define ENDVAL 0x00

int write_word(char* addr) {
    char val=0xff;
    *addr = val;
    if(*addr != 0xff)
	return -1;
    while(val != ENDVAL) {
	*addr <<= 1;
	val <<= 1;
	val &= 0xfe;
	*addr &= 0xfe;
	if(val != *addr) {
	    return -1;
	}
    }
    return 0;
}

int memcheck(u_int start, u_int end) {
    u_int i;
    if(start < 0x00400000 || start > 0x00408000 ||
	    end < 0x00400000 || end > 0x00408000 ||
	    end < start)
	return -1;
    for(i=start;i<end;i++) {
	if(write_word((char*)i)==-1)
	    return i;
    }
    return 0;
}
//*----------------------------------------------------------------------------
//* Function Name       : main
//* Object              : Main function of the led swing
//* Input Parameters    : none
//* Output Parameters   : True
//*----------------------------------------------------------------------------
int main( void )
//* Begin
{
    u_int *ebi_config = 0xffe00008;
    u_int config_value = 0x00402e3d;
    u_int start, end, memstat;
    *ebi_config = config_value;
    
    while(1) {
	printf("Enter a starting address between 0x00400000 and 0x00408000(entering 0 quits): ");
	scanf("%x", &start);
	if(start == 0)
	    return(TRUE);
	printf("Enter an ending address between your starting value and 0x00408000: ");
	scanf("%x", &end);
	if(end == 0)
	    return(TRUE);

	memstat = memcheck(start, end);
	if(memstat == -1)
	    printf("You entered an invalid address.\n");
	else if(memstat != 0)
	    printf("Memory fault at %x.\n",memstat);
	else
	    printf("Test completed successfully.\n");
    }
    return(TRUE);
//* End
}
