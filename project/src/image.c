/*Image Module:  
 * This file contains all of the functions related to image
 * processing for the ALPL project.
 */

#include "user/camera.h"
#include "user/image.h"

/*This function takes a picture buffer which is the output of take_picture()
 * with the two packets stripped off the front of the packet. The Coordinate
 * pointer is where the centroid value is returned.
 */
void find_centroid ( char * picture_buffer,
		     Coordinate * centroid )
{
  u_int i, j, x_sum = 0, r_val, g_val, b_val,y_sum = 0, count = 0;

  for ( i = 0 ; i < X_RES ; i += 2 )
    {
      for ( j = 0 ; j < Y_RES ; j += 2 )
	{
	  r_val = ( picture_buffer[j] & 0xF8 ) >> 3;
	  g_val = ( picture_buffer[j] & 0x3 ) << 3 |
	    ( picture_buffer[j+1] & 0xE0 ) >> 5;
	  b_val = picture_buffer[j+1] & 0x1F;

	  if ( r_val + g_val + b_val >= THRESHOLD )
	    {
	      x_sum += i;
	      y_sum += j;
	      count++;
	    }
	}
    }
  if ( count == 0 )
    {
      centroid->x = 0;
      centroid->y = 0;
    }
  else
    {
  centroid->x = x_sum / count;
  centroid->y = y_sum / count;
    }
}

/*This function removes the two packets from the start of the image buffer and
 * returns a pointer to the first byte of the actual image data.  Should be
 * called before calling find_centroid().  Also be aware that you should also
 * hold onto your original pointer so it can be freed after the centroid has
 * been found.
 */
char * remove_head ( char * picture_buffer )
{
  u_int i;
  for ( i = 0 ; i < 2 * CMD_SIZE ; i++ )
    {
      if ( picture_buffer[i] == HEAD )
	{
	  return picture_buffer + i + 2 * CMD_SIZE;
	}
    }
  return 0;
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
