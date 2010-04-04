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

Angle * find_offset ( Coordinate * centroid )
{
  u_int x = centroid->x;
  Angle * offset = malloc ( sizeof ( Angle ) );

  if ( x <= X_RES / 2 )
    {
      offset->direction = LEFT;
      offset->angle = ( X_RES / 2 - x ) * DEGREES_PER_PIXEL;
    }
  else
    {
      offset->direction = RIGHT;
      offset->angle = ( x - X_RES / 2 ) * DEGREES_PER_PIXEL;
    }
  return offset;
}
/*This function simply initializes the external ram we have interfaced so that
 * it can be used to store the large image arrays being processed
 */
void init_ext_ram ( void ) 
{
  u_int *ebi_csr2 = 0xffe00000 | 0x08;
  u_int ebi_config = 0x004020a6;
  //more wait states: u_int ebi_config = 0x004020ae;
  *ebi_csr2 = ebi_config;
}

/*Zach's Ultra-Awesome-Nuclear-Powered-Pseudo-Math-Library
 * (now with 42% more awesome! and 13% less deadly radiation!)
 * xpow returns x raised to the n-th power.
 * sine returns the sine of x degrees
 * cosine returns the cosine of x degrees
 * tangent returns the tangent of x degrees, returns 0 in cases where
 * tan would normally be infinite.
 */
float xpow ( float x, int n )
{
  float product = x;
  if ( n == 0 )
    return (float) 1;
  while( n > 1 )
    {
      product *= x;
      n--;
    }
  return product;
}

float sine ( float x )
{
  float x_rad = x * PI / 180;
  float pivot = x_rad - PI2;
  float sin_rad = 1.0f - xpow ( pivot, 2 ) / 2 + xpow ( pivot, 4 ) / 24 
                  - xpow ( pivot, 6 ) / 720 + xpow ( pivot, 8 ) / 40320;
  return sin_rad; 
}

float cosine ( float x )
{
  float x_rad = x * PI / 180;
  float pivot = x_rad - PI2;
  float cos_rad = 0 - pivot + xpow ( pivot, 3 ) / 6 - xpow ( pivot, 5 ) / 120
                  + xpow ( pivot, 7 ) / 5040 - xpow ( pivot, 9 ) / 362880;
  return cos_rad;
}

float tangent ( float x )
{
  float sin = sine ( x );
  float cos = cosine ( x );
  if ( cos == 0.0f )
    return 0;
  else
    return sin / cos;
}

/*This function takes an offset angle and, assuming that the turret has been
 * centered, uses the angle to calculate the distance to the target so the shot
 * elevation may be determined.
 */
float find_distance ( Angle * offset )
{
  return WIDTH * tangent ( 90.0 - offset->angle );
}
