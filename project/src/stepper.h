#ifndef STEPPER
#define STEPPER

//timing thingies
#define SEC 1000000
#define DIV0 50
#define DIV1 100

//ENABLE is active low
#define EN0 PB0
#define EN1 PB1

//CW is active low
#define CW PB2

//FULL is active low
#define FULL PB3

//RESET is active low
#define RESET PB4

//CONTROL should be opposite value of the FULL line for a bipolar
// motor
#define CONTROL PB5

//CLOCKS
#define CLK0 PB6
#define CLK1 PB7

//Line Values
#define LOW PIO_CLEAR_OUT
#define HIGH PIO_SET_OUT

#define VDEGPSTEP 1.8
#define HDEGPSTEP 0.58

/*
  motorStatus keeps holds the status of a motor: braked = 0 if free
  spinning, 1 if braked: angle = current angle of motor

  The elevation motor will be initialized at its lowest point. The
  azimuth motor will be initialized at one of it's extremes.

  Motor movement will be done by passing a motorStatus struct into the
  moveStepper function.
 */
struct motorStatus_struct {
  u_int braked;
  int angle;
}; typedef motorStatus_struct motorStatus

//Functions

//helper functions
void delay(u_int secs);

//initialize the IO pins
void initFull();
void initHalf();

//Low level
void step( u_int *steps, u_int *motor, u_int *clk );

//High Level, easy access to accurate movements
void moveStepper( motorStatus azimuth, motorStatus elevation );

//High Level helper functions
u_int getVertSteps( u_int degrees );
u_int getHorSteps( u_int degrees );

#endif STEPPER
