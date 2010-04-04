#include "servo.h"

#include "periph/timer_counter/lib_tc.h"

u_int REG[3] = {COCK, 0, SERVO_PERIOD};

void servoInit(void){
	u_int mode = TC_CLKS_MCK32    |
		TC_EEVT_XC0               |
		TC_CPCTRG                 |
		TC_WAVE                   |
		TC_ACPA_CLEAR_OUTPUT      |
		TC_ACPC_SET_OUTPUT        |
		TC_ASWTRG_SET_OUTPUT;
		
	//initialize/turn on servo
	at91_tc_open ( & TC1_DESC, mode, TRUE, FALSE );
	at91_tc_write ( & TC1_DESC, REG );	
	at91_tc_trig_cmd ( & TC1_DESC, TC_TRIG_CHANNEL );

}

void fire( void ){

	float aDelay = 5.0f;

	REG[0] = FIRE;
        printf("firing\n");

	at91_tc_write ( & TC1_DESC, REG );
        printf("");
	delay( &aDelay );
        printf("");

	//cock
	REG[0] = COCK;
        printf("cocking\n");
	at91_tc_write ( & TC1_DESC, REG );
        printf("");
	delay( &aDelay );
        printf("");

	//turn off servo
	//at91_tc_close( &TC1_DESC );
}
