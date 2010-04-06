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
void xpow ( float *x, int n, float *ans );
void sine ( float *x, float *ans );
void cosine ( float *x, float *ans );
void tangent ( float *angle, float *ans );
void find_offset ( Coordinate * centroid, float * offset );
void find_distance ( float * offset, float * distance );
void initCamMux( void );
#endif
