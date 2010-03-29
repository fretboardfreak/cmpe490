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
  return NULL;
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
void init_ext_ram ( ) 
{
  u_int *ebi_csr2 = 0xffe00000 | 0x08;
  u_int ebi_config = 0x004020a6;
  *ebi_csr2 = ebi_config;
}

/*This function approximates the tangent function using degree values by using a
 * look up table and linear interpolation
 */
float tangent ( float angle )
{
  float tans[90] = {0.0, 0.0175, 0.0349, 0.0524, 0.0699, 0.0875, 0.1051, 0.1228, 
		    0.1405, 0.1584, 0.1763, 0.1944, 0.2125, 0.2309, 0.2493,
		    0.2679, 0.2867, 0.3057, 0.3249, 0.3443, 0.3639, 0.3838,
		    0.4040, 0.4244, 0.4452, 0.4663, 0.4877, 0.5059, 0.5317,
		    0.5543, 0.5773, 0.6008, 0.6248, 0.6493, 0.6744, 0.7001,
		    0.7265, 0.7535, 0.7812, 0.8097, 0.8390, 0.8692, 0.9003,
		    0.9324, 0.9656, 1.0000, 1.0354, 1.0722, 1.1105, 1.1502,
		    1.1916, 1.2347, 1.2798, 1.3269, 1.3762, 1.4279, 1.4823,
		    1.5396, 1.6001, 1.6640, 1.7315, 1.8037, 1.8804, 1.9622,
		    2.0499, 2.1440, 2.2455, 2.3553, 2.4745, 2.6044, 2.7467,
		    2.9033, 3.0767, 3.2698, 3.4862, 3.7306, 4.0091, 4.3295,
		    4.7023, 5.1418, 5.6679, 6.3095, 7.1099, 8.1372, 9.5045,
		    11.4157, 14.2780, 19.0404, 28.5437, 56.9168};

  u_int x0, x1;
  float y0, y1;
  x0 = (u_int) angle;
  x1 = x0 + 1;
  y0 = tans[x0];
  y1 = tans[x1];
  return y0 + ( angle - (float)x0 ) * ( ( y1 - y0 ) 
					/ ( (float)x1 -(float)x0 ) );
}

/*This function takes an offset angle and, assuming that the turret has been
 * centered, uses the angle to calculate the distance to the target so the shot
 * elevation may be determined.
 */
float find_distance Angle * offset )
{
  return WIDTH * tangent ( 90.0 - offset->angle );
}
