#ifndef ALPL
#define ALPL

#include <stdlib.h>
#include <string.h>

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

#include "image.h"
#include "servo.h"
#include "stepper.h"
#include "image.h"
#include "camera.h"

#define CLOCK 32000
#define SEC 31250
#define MAXVERTSTEPS 40

u_int wait_semaphore;

//void delay( float *secs );
int init_ext_ram ( void );
void init_led( void );
void change_led( u_int led, u_int status );
void distance_to_leds( float *distance );
void xpow ( float *x, int n, float *ans );
void sine ( float *x, float *ans );
void cosine ( float *x, float *ans );
void tangent ( float *angle, float *ans );
void find_offset ( Coordinate * centroid, float * offset );
void find_distance ( float * offset, float * distance );
void initCamMux( void );
void distance_to_steps( float *distance, int *steps );
void wait( u_int clkCycles );
#endif
