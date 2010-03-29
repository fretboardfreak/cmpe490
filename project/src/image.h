/*Image Module Header:
 * This file contains all the function prototypes and 
 * macro definitions for the image module of the ALPL project
 */

#ifndef IMAGE_H

#define IMAGE_H

/*Macro Definitions*/
#define THRESHOLD 248
#define X_RES 320
#define Y_RES 240
#define MEMORY 0x400000 /*address of additional ram*/
#define DEGREES_PER_PIXEL 0.125

#define LEFT 0;
#define RIGHT 1;

#define WIDTH 0.285

/*Coordinate structure definition*/
typedef struct {
  u_int x;
  u_int y;
} Coordinate;

/*Angle structure definition*/
typedef struct {
  float angle;
  u_int direction;
} Angle;

/*Function Prototypes*/
void find_centroid ( char * picture_buffer,
		     Coordinate * centroid );
char * remove_head ( char * picture_buffer );
Angle * find_offset ( Coordinate * centroid );
float find_distance ( Angle * offset );
void init_ext_ram ( );
float tangent ( float angle );
#endif
