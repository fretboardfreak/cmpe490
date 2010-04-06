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

/*This function takes a centroid value and approximates the angle from the
 * centre of the image to the centroid point.
 */

void find_offset ( Coordinate * centroid, float *offset )
{
  float tmp = ( centroid->x - X_RES / 2 );
  printf("find_offset: number of pixels from center = %f\n", tmp);
  *offset = tmp * DEGREES_PER_PIXEL;
}
/*This function simply initializes the external ram we have interfaced so that
 * it can be used to store the large image arrays being processed
 */
int init_ext_ram ( void ) 
{
  u_int *ebi_csr2 = 0xffe00000 | 0x08;
  //u_int ebi_config = 0x004020a6;
  //more wait states 0x004020ae;
  u_int ebi_config = 0x004020ae;
  u_int *memory = 0x400000, *i, x=0xaa;
  *ebi_csr2 = ebi_config;

  for(i=memory; i<0x400100; i++){
    *i = x;
  }
  for(i=memory; i<0x400100; i++){
    if ( *i != x ){
      return 0;
    }
  }
  return 1;
}

/*Zach's Ultra-Awesome-Nuclear-Powered-Pseudo-Math-Library
 * (now with 42% more awesome! and 13% less deadly radiation!)
 * xpow returns x raised to the n-th power.
 * sine returns the sine of x degrees
 * cosine returns the cosine of x degrees
 * tangent returns the tangent of x degrees, returns 0 in cases where
 * tan would normally be infinite.
 */
void xpow ( float *x, int n, float *ans )
{
  float product = *x;
  if ( n == 0 )
    *ans = 1.0f;
  while( n > 1 )
    {
      product *= *x;
      n--;
    }
  *ans = (float) product;
}

void sine ( float *x, float *ans )
{
  float x_rad = *x * PI / 180.0f;
  float pivot = x_rad - PI2;
  float pivotP2, pivotP4, pivotP6, pivotP8;
  xpow( &pivot, 2, &pivotP2 );
  xpow( &pivot, 4, &pivotP4 );
  xpow( &pivot, 6, &pivotP6 );
  xpow( &pivot, 8, &pivotP8 );
  //*ans = 1.0f - xpow ( pivot, 2 ) / 2 + xpow ( pivot, 4 ) / 24 
  //       - xpow ( pivot, 6 ) / 720 + xpow ( pivot, 8 ) / 40320;
  *ans = 1.0f - pivotP2 / 2.0f + pivotP4 / 24.0f - pivotP6 / 720.0f 
         + pivotP8 / 40320.0f;
}

void cosine ( float *x, float *ans )
{
  float x_rad = *x * PI / 180.0f;
  float pivot = x_rad - PI2;
  float pivotP3, pivotP5, pivotP7, pivotP9;
  xpow( &pivot, 3, &pivotP3 );
  xpow( &pivot, 5, &pivotP5 );
  xpow( &pivot, 7, &pivotP7 );
  xpow( &pivot, 9, &pivotP9 );
  //*ans = 0 - pivot + xpow ( pivot, 3 ) / 6 - xpow ( pivot, 5 ) / 120
  //       + xpow ( pivot, 7 ) / 5040 - xpow ( pivot, 9 ) / 362880;
  *ans = 0.0f - pivot + pivotP3 / 6.0f - pivotP5 / 120.0f + pivotP7 / 5040.0f 
         - pivotP9 / 362880.0f;
}

void tangent ( float *x, float *ans )
{
  float sin, cos;
  sine ( x, &sin );
  cosine ( x, &cos );
  if ( cos == 0.0f )
    *ans = 0;
  else
    *ans = sin / cos;
}

/*This function takes an offset angle and, assuming that the turret has been
 * centered, uses the angle to calculate the distance to the target so the shot
 * elevation may be determined.
 */
void find_distance ( float * offset, float * distance )
{
  float tan, tmp;
  if( *offset < 0 )
    *offset = 0 - *offset;
  tmp = 90.0 - *offset;
  printf("find offset tmp = %f\n", tmp );
  tangent( &tmp, &tan );
  *distance = WIDTH * tan ;
}

void initCamMux( void ){
  at91_pio_open( &PIOB_DESC, PB18, PIO_OUTPUT );
}
