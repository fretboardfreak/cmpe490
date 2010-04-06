#ifdef SEMIHOSTING
#include <stdio.h>
#endif

//include the required stuff for the ATMEL Board
#include <stdlib.h>
#include <string.h>
#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"
#include "periph/usart/lib_usart.h"

//include the ALPL software
//#include "alpl.h"
#include "servo.h"
#include "stepper.h"
#include "image.h"
#include "camera.h"

#define MOTOR_TEST
#define CAMERA_TEST
#define BALLISTIC_TEST
#define ALPL
#define FML

/*
 * #ifdef MOTOR_TEST
 * u_int getMotor( void ){
 *     u_int motor;
 * 	u_int choice;
 *     u_int dummy;
 *     while(1){
 * 	printf("Choose a Motor: 0=Azimuth or 1=Elevation:\n");
 * 	//scanf("%d\n", &choice );
 * 	choice = getchar();
 * 	choice = choice - 0x30;
 * 	dummy = getchar(); //pesky newlines
 * 	if (choice == 0){
 * 	    motor = AZI;
 * 	    return motor;
 * 	}
 * 	else if (choice == 1){
 * 	    motor = ELE;
 * 	    return motor;
 * 	}
 * 	else{
 * 	    printf("You entered an invalid value for motor.\n");
 * 	}
 *     }
 * }
 * 
 * int getDegrees( void ){
 *     int choice = 0, dummy = 0, neg = 0;
 *     printf("Now we need to know where to aim\n");
 *     while(1){
 * 		printf("Enter 0 to aim Left or Down, 1 to aim Right or Up from center.\n");
 * 		neg = getchar();
p * 		neg = neg - 0x30;
 * 		dummy = getchar(); 
 * 		
 * 		printf("Enter the number of decadegrees between 0 and 9:\n");
 * 		choice = getchar();
 * 		choice = choice - 0x30;
 * 		dummy = getchar(); //pesky newlines
 * 		if (choice >= 0 && choice < 10){
 * 			choice = choice * 10;
 * 			break;
 * 		}
 * 		else
 * 			printf("You entered an invalid number of steps.\n");
 * 	}
 * 	if ( neg == 0 )
 * 		return 0-choice;
 * 	else
 * 		return choice;
 * }
 * 
 * u_int unleashHell(void){
 *     u_int choice = 0;
 *     u_int dummy = 0;
 *     while(1){
 * 	printf("Unleash Hell? (1 to fire, 0 to aim)\n");
 * 	choice = getchar();
 * 	choice = choice - 0x30;
 * 	dummy = getchar(); //pesky newlines
 * 	if (choice == 0 || choice == 1){
 * 	    return choice;
 * 	}
 * 	else
 * 	    printf("You entered an invalid option.\n");
 *     }
 *     
 * }
 * 
 * #endif
 */

int main( void ){
  /*
   * #ifdef MOTOR_TEST
   * 	u_int motor;
   * 	int degrees;
   * 	motorStatus azimuth, elevation;
   * 	azimuth.braked = 1;
   * 	elevation.braked = 1;
   * 	
   * 	initHalf();
   *         servoInit();
   * 
   * 	while(1){
   * 		if ( unleashHell() )
   * 			fire();
   * 		else {
   * 			motor = getMotor();
   * 			degrees = getDegrees();
   * 			if ( motor == AZI ){
   * 				elevation = elevationStatus;
   * 				azimuth.angle = degrees;
   * 			}
   * 			else{
   * 				azimuth = azimuthStatus;
   * 				elevation.angle = degrees;
   * 			}
   * 			aim( azimuth, elevation );
   * 		}	
   * 	}
   * #endif 
   */

  /*
   * #ifdef CAMERA_TEST
   *         CameraDesc camera = {&USART2_DESC, CAM1, BAUDS115200, 320, 240, 2};
   *         char *picture, *pic2;
   *         Coordinate *coord1;
   * 
   *         init_ext_ram();
   *        
   *         printf("Synching camera\n");
   *         if ( sync_camera ( &camera ) == FALSE ){
   *           printf("Synchronization failed.\n");
   *           return 0;
   *         }
   *         printf("Initializing camera\n");
   *         if (init_camera( &camera, 
   *                          COLOR_TYPE_16_BIT_COLOR,
   *                          JPEG_RES_320x240,
   *                          JPEG_RES_80x64 ) == FALSE ){
   *           printf("Initialization of camera failed\n");
   *           return 0;
   *         }
   *         printf("taking picture\n");
   *         picture = take_picture( & camera, 
   *                                 SNAPSHOT_TYPE_UNCOMPRESSED,
   *                                 PICTURE_TYPE_SNAPSHOT );
   *         if ( picture == NULL ){
   *           printf("take pucture failed.\n");
   *         }
   *         printf("picture is at %x\n", picture);             
   * 
   *         pic2 = remove_head ( picture );
   *         find_centroid( pic2, coord1 );
   *         printf("Coordinates Are: x=%d, y=%d\n", coord1->x, coord1->y);
   *         getchar();
   * 
   * #endif
   */

  /*
   * #ifdef BALLISTIC_TEST
   *   char choice, dummy;
   *   motorStatus azimuth, elevation;
   *   u_int count = 0;
   * 
   *   azimuth.braked = 1;
   *   elevation.braked = 1;
   * 
   *   initHalf();                            
   *   servoInit();                         
   *   if( !init_ext_ram()){                
   *     printf("failed to init ext ram\n");
   *     return 0;                          
   *   }                                    
   *   init_ext_ram();
   * 
   *   setDirection( ELE , UP );
   *   brake( AZI );
   *   brake( ELE );
   * 
   *   while(1){
   *     printf("count = %d\n",count);
   *     choice = getchar();
   *     choice = choice - 0x30;
   *     dummy = getchar();
   *     if (choice == 0){
   *       step( 1, ELE );
   *       count++;
   *     }
   *     else if (choice == 1){
   *       fire();
   *     }
   *   }
   *    
   * #endif
   */


#ifdef ALPL
  CameraDesc cam1 = {&USART2_DESC, CAM1, BAUDS115200, 80, 60, 2};
  CameraDesc cam2 = {&USART2_DESC, CAM2, BAUDS115200, 80, 60, 2};
  char *pic, *rgbData;
  float offset1, offset2, distance;
  Coordinate coord1, coord2;
  motorStatus azimuth, elevation;
  u_int i;

  //enable external hardware
  //if( !init_ext_ram()){
  //  printf("failed to init ext ram\n");
  //  return 0;
  //}
  //init_ext_ram();
  initHalf();    
  servoInit();   
  initCamMux( );

  while(1){
    //Look for button 1 press to start. Need an interrupt and stuff for
    //this so I'll keep it simple until further notice.
    printf("Press Enter to start\n");
    getchar();
  
    //put both steppers into braking mode
    azimuth.braked = 1;
    azimuth.steps = 0;
    elevation.braked = 1;
    elevation.steps = 0;
    aim( azimuth, elevation );

    //take picture 1 from cam1
    printf("Synching camera\n");
    for( i=0; i<5; i++ ){
      if ( sync_camera ( &cam1 ) == TRUE ){
        printf("Synchronization Succeeded.\n");
        break;
      }
      else if (i == 5){
        printf("Synchronization Failed 5 times.\n");
        return 0;
      }
    }
    printf("Initializing camera\n");
    if (init_camera( &cam1, 
                     COLOR_TYPE_16_BIT_COLOR,
                     PREVIEW_RES_80x60,
                     JPEG_RES_80x64 ) == FALSE ){
      printf("Initialization of camera failed\n");
      return 0;
    }
    printf("taking picture\n");
    pic = take_picture( & cam1, 
                            SNAPSHOT_TYPE_UNCOMPRESSED,
                            PICTURE_TYPE_SNAPSHOT );
    if ( pic == NULL ){
      printf("take picture failed.\n");
    }
    printf("picture is at %x\n", pic);             

    //get the x & y coordinates of the LED from pic
    
    rgbData = remove_head ( pic );
    find_centroid( rgbData, &coord1 );

    printf("First Coordinates Are: x=%d, y=%d\n", coord1.x, coord1.y);
    
    //get the degrees offset from current position
    find_offset( &coord1, &offset1 );

    free( pic );
    free( rgbData );

    //move the azimuth motor to center the LED in cam1
    azimuth.steps = azimuthStatus.steps + getHorSteps( offset1 ) + 1;
    aim( azimuth, elevation );

    //take picture 2 from cam2
    printf("Synching camera\n");
    for( i=0; i<5; i++ ){
      if ( sync_camera ( &cam2 ) == TRUE ){
        printf("Synchronization Succeeded.\n");
        break;
      }
      else if (i == 5){
        printf("Synchronization Failed 5 times.\n");
        return 0;
      }
    }
    printf("Initializing camera\n");
    if (init_camera( &cam2, 
                     COLOR_TYPE_16_BIT_COLOR,
                     PREVIEW_RES_80x60,
                     JPEG_RES_80x64 ) == FALSE ){
      printf("Initialization of camera failed\n");
      return 0;
    }
    printf("taking picture\n");
    pic = take_picture( & cam2, 
                            SNAPSHOT_TYPE_UNCOMPRESSED,
                            PICTURE_TYPE_SNAPSHOT );
    if ( pic == NULL ){
      printf("take pucture failed.\n");
    }
    printf("picture is at %x\n", pic);             
    
     //get the x & y coordinates of the LED from pic2
    
    rgbData = remove_head ( pic );
    find_centroid( rgbData, &coord2 );

    printf("Second Coordinates Are: x=%d, y=%d\n", coord2.x, coord2.y);
    
    //get (and print) the distance to the LED
    find_offset( &coord2, &offset2 );
    find_distance( &offset2, &distance );

    printf("The distance to the target is %f\n", distance );

    //calculate the firing angle
    
    //fire
    
    //return motors 0,0 and put in unbraking mode
  }
  return 0;
#endif


  /*
    * #ifdef FML
    *   //meant to be used with the debugger so things can be changed
    *   motorStatus azimuth, elevation;
    *   int f = 0;
    * 
    *   init_ext_ram();
    *   initHalf();
    *   servoInit();
    * 
    *   azimuth = azimuthStatus;
    *   elevation = elevationStatus;
    * 
    *   while(1){
    *     if( f )
    *       fire();
    *     else
    *       aim( azimuth, elevation );
    *   }
    * #endif
    */
}
