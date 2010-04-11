#ifndef STEPPER
#define STEPPER

#include <stdlib.h>
#include <string.h>

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

//modes
#define ACCELERATION 1
#define HALFSTEP 1
#define FULLSTEP 2

#define INITIAL_POSITION -21

#define AZI PB0
#define ELE PB1

//timing thingies
#define SEC 31250
#define DIV_AZI 40
#define DIV_ELE 20
#define DIVELE 2


//ENABLE is active low
#define EN_AZI PB0
#define EN_ELE PB1

//CW is active low
#define CW PB2

#define LEFT HIGH
#define RIGHT LOW
#define UP LOW
#define DOWN HIGH

//FULL is active low
#define FULL PB3

//RESET is active low
#define STEPPER_RESET PB4

//CONTROL should be opposite value of the FULL line for a bipolar
// motor
#define CONTROL PB5

//CLOCKS
#define CLK_AZI PB6
#define CLK_ELE PB7

//Line Values
#define LOW PIO_CLEAR_OUT
#define HIGH PIO_SET_OUT

#define VDEGPSTEP 1.8
#define HDEGPSTEP 0.58

/*
  motorStatus keeps holds the status of a motor: braked = 0 if free
  spinning, 1 if braked: angle = current angle of motor

  The elevation motor will be initialized at its lowest point. The
  azimuth motor will be initialized at its center.

  Motor movement will be done by passing a motorStatus struct into the
  moveStepper function.
 */
typedef struct motorStatus_struct {
  u_int braked;
  int steps;
} motorStatus; 

motorStatus azimuthStatus;
motorStatus elevationStatus;

//Functions

//initialize the IO pins
void initFull();
void initHalf();

//Low level
void brake( u_int motor );
void unbrake( u_int motor );
void setdirection( u_int motor, u_int dir );
void step( u_int steps, u_int motor);
void accelStep( u_int steps, u_int motor );
int getVertSteps( float *degrees );
int getHorSteps( float *degrees );

//High Level, easy access to accurate movements
void aim( motorStatus azimuth, motorStatus elevation );

#endif

