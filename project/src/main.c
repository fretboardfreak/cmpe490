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

int run_alpl( void ){

#ifdef ALPL
  CameraDesc cam1 = {&USART2_DESC, CAM1, BAUDS115200, 80, 60, 2};
  CameraDesc cam2 = {&USART2_DESC, CAM2, BAUDS115200, 80, 60, 2};
  char *pic, *rgbData;
  float offset1, offset2, distance;
  Coordinate coord1, coord2;
  motorStatus azimuth, elevation;
  u_int i, button_status;
  int steps = 0;
  
  //put both steppers into braking mode
  azimuth.braked = 1;
  azimuth.steps = 0;
  elevation.braked = 1;
  elevation.steps = 0;
  aim( azimuth, elevation );

  change_led( LED1, LED_OFF );
  change_led( LED2, LED_ON );

  //take picture 1 from cam1
  for( i=0; i<5; i++ ){
    if ( sync_camera ( &cam1 ) == TRUE ){
      break;
    }
    else if (i == 5){
      return 0;
    }
  }
  if (init_camera( &cam1, 
                   COLOR_TYPE_16_BIT_COLOR,
                   PREVIEW_RES_80x60,
                   JPEG_RES_80x64 ) == FALSE ){
    return 0;
  }
  pic = take_picture( & cam1, 
                          SNAPSHOT_TYPE_UNCOMPRESSED,
                          PICTURE_TYPE_SNAPSHOT );
  if ( pic == NULL ){
    return 0;
  }

  change_led( LED2, LED_OFF );
  change_led( LED3, LED_ON );

  //get the x & y coordinates of the LED from pic
  rgbData = remove_head ( pic );
  find_centroid( rgbData, &coord1 );

  
  //get the degrees offset from current position
  find_offset( &coord1, &offset1 );

  free( pic );
  free( rgbData );

  //move the azimuth motor to center the LED in cam1
  azimuth.steps = azimuthStatus.steps + getHorSteps( &offset1 ) + 1;
  aim( azimuth, elevation );

  change_led( LED3, LED_OFF );
  change_led( LED4, LED_ON );

  //take picture 2 from cam2
  for( i=0; i<5; i++ ){
    if ( sync_camera ( &cam2 ) == TRUE ){
      break;
    }
    else if (i == 5){
      return 0;
    }
  }
  if (init_camera( &cam2, 
                   COLOR_TYPE_16_BIT_COLOR,
                   PREVIEW_RES_80x60,
                   JPEG_RES_80x64 ) == FALSE ){
    return 0;
  }
  pic = take_picture( & cam2, 
                          SNAPSHOT_TYPE_UNCOMPRESSED,
                          PICTURE_TYPE_SNAPSHOT );
  if ( pic == NULL ){
  }
  
   //get the x & y coordinates of the LED from pic2
  rgbData = remove_head ( pic );
  find_centroid( rgbData, &coord2 );

  //get (and print) the distance to the LED
  find_offset( &coord2, &offset2 );

  change_led( LED3, LED_OFF );
  change_led( LED4, LED_ON );

  find_distance( &offset2, &distance );

  //calculate the firing angle
  distance_to_steps( &distance, &steps );

  distance_to_leds( &distance );

  //fire
  elevation.steps += steps;
  aim( azimuth, elevation );

  wait( SEC );

  fire();

  //return motors 0,0 and put in unbraking mode
  azimuth.braked = 0;
  azimuth.steps = 0;
  elevation.braked = 0;
  elevation.steps = INITIAL_POSITION;
  aim( azimuth, elevation );

  return 0;
#endif


  /*
   * #ifdef FML
   *   //meant to be used with the debugger so things can be changed
   *   motorStatus azimuth, elevation;
   *   int f = 0;
   *   u_int addy = (u_int)&azimuth;
   * 
   *   azimuth.braked = 1;
   *   azimuth.steps = 0;
   *   elevation.braked = 1;
   *   elevation.steps = 0;
   * 
   *   azimuth = azimuthStatus;
   *   elevation = elevationStatus;
   * 
   *   while(1){
   *     if( f ){
   *       fire();
   *     }
   *     else{
   *       aim( azimuth, elevation );
   *     }
   *   }
   * #endif
   */
}

int main( void ){
  //initialize irq for button 2
  //

  int i, count=0;
  u_int leds[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};

  init_led();
  initHalf();    
  servoInit();   
  initCamMux( );

  for(i=0; i<8; i++){
    change_led( leds[i], LED_ON );
    if( i > 0 )
      change_led( leds[i-1], LED_OFF );
    wait( SEC );
  }

  run_alpl();
}
