#ifndef ALPL
#define ALPL

#include <stdlib.h>
#include <string.h>

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"


#define SEC 1000000

extern void wake_up_handler (void) ;

WaitDesc WAIT_DESC = { &TC0_DESC, 0, 0, WAIT_DELAY, wake_up_handler } ;

void delay( float *secs );

#endif
