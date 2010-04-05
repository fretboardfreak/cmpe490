#ifndef ALPL
#define ALPL

#include <stdlib.h>
#include <string.h>

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

#include "image.h"

extern void wake_up_handler (void) ;

WaitDesc WAIT_DESC = { &TC0_DESC, 0, 0, WAIT_DELAY, wake_up_handler } ;

#define SEC 1000000

void delay( float *secs );
int init_ext_ram ( void );
float xpow ( float x, int n );
float sine ( float x );
float cosine ( float x );
float tangent ( float angle );
void find_offset ( Coordinate * centroid, float * offset );
float find_distance ( float * offset );

#endif
