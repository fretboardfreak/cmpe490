#include "servo.h"

#include "periph/timer_counter/lib_tc.h"

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
	at91_tc_write ( & TC1_DESC, reg );	
	at91_tc_trig_cmd ( & TC1_DESC, TC_TRIG_CHANNEL );

}

void fire( void ){
	u_int reg[3] = {COCK, 0, SERVO_PERIOD};
	float aDelay = 5.0f;

	reg[0] = FIRE;
        printf("firing\n");
	at91_tc_write ( & TC1_DESC, reg );
        printf("");
	delay( &aDelay );
        printf("");

	//cock
	reg[0] = COCK;
        printf("cocking\n");
	at91_tc_write ( & TC1_DESC, reg );
        printf("");
	delay( &aDelay );
        printf("");

	//turn off servo
	//at91_tc_close( &TC1_DESC );
}
