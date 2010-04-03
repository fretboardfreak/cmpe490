#include "alpl.h"

void delay( float *secs ){
	u_int i = 0;
	float tmp;
	WAIT_DESC.mcki_khz = 32000;
        //don't want to wait for more than 5 secs
	if ( *secs > 5.0f )
	    *secs = 5.0f ;
        //make sure to use a sensible period
	if ( *secs <= 0.0f )
	    *secs = 1.0f;
        //if larger than one second, only wait whole secs
	if ( *secs >= 1.0f ){
	    WAIT_DESC.period = SEC;
	    for ( i=0; i<*secs; i++ ){
			//printf("Second # %d\n", i );
			at91_wait_open(&WAIT_DESC);
	    }
	}
	else{
	    tmp = SEC * *secs;
	    //printf("tmp = %d\n", tmp);
	    WAIT_DESC.period = (u_int) tmp;
	    at91_wait_open(&WAIT_DESC);
		//printf("Wait done\n");
		
	}
}
