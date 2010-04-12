/*Image Module:  
 * This file contains all of the functions related to image
 * processing for the ALPL project.
 */

#include "camera.h"
#include "image.h"

/*This function takes a picture buffer which is the output of take_picture()
 * with the two packets stripped off the front of the packet. The Coordinate
 * pointer is where the centroid value is returned.
 */
void find_centroid ( char * picture_buffer,
		     Coordinate * centroid )
{
  unsigned int i, j, x_sum = 0, r_val, g_val, b_val,y_sum = 0, count = 0, tmp, tmp2, thresh=THRESHOLD;
  
  for ( i = 0 ; i < Y_RES ; i++ )
    {
      for ( j = 0 ; j < X_RES * 2 ; j += 2 )
	{
          tmp = ( picture_buffer[i * X_RES * 2 + j] & 0xF8 );
	  r_val = tmp >> 3;
          tmp = ( picture_buffer[i * X_RES * 2 + j] & 0x3 );
          tmp2 = ( picture_buffer[i * X_RES * 2 + j + 1] & 0xE0 ); 
	  g_val = tmp << 3 |
	    tmp2 >> 5;
	  b_val = picture_buffer[i * X_RES * 2 + j + 1] & 0x1F;

	  if ( r_val + g_val + b_val >= thresh )
	    {
	      x_sum += j/2;
	      y_sum += i;
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

