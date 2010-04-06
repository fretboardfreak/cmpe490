/*Image Module Header:
 * This file contains all the function prototypes and 
 * macro definitions for the image module of the ALPL project
 */

#ifndef IMAGE_H

#define IMAGE_H

/*Macro Definitions*/
#define THRESHOLD 70
//#define X_RES 320
//#define Y_RES 240
#define X_RES 80
#define Y_RES 60
#define MEMORY 0x400000 /*address of additional ram*/
//#define DEGREES_PER_PIXEL 0.125
#define DEGREES_PER_PIXEL 0.5
#define PI 3.1415926
#define PI2 1.5707963

#define LEFT 0
#define RIGHT 1

#define WIDTH 0.285

/*Coordinate structure definition*/
typedef struct {
  int x;
  int y;
} Coordinate;

/*Angle structure definition*/
typedef struct {
  float angle;
  int direction;
} Angle;

/*Function Prototypes*/
void find_centroid ( char * picture_buffer,
		     Coordinate * centroid );
char * remove_head ( char * picture_buffer );
#endif
