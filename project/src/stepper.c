#include "stepper.h"

//extern void wake_up_handler (void) ;
//extern WaitDesc alpl_wait_desc;


u_int MODE;

int getVertSteps( float *degrees ){
  float tmp = *degrees / (float) (VDEGPSTEP * MODE);
  return (int) tmp;
}

int getHorSteps( float *degrees ){
  float tmp = *degrees / (float) (HDEGPSTEP * MODE);
  return (int) tmp;
}

void initHalf(){
  //setup piob for stepper motor output
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | STEPPER_RESET | FULL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  CONTROL | EN_AZI | EN_ELE | CLK_AZI | CLK_ELE,
                  LOW);

  at91_pio_write( &PIOB_DESC, STEPPER_RESET, LOW );

  wait( SEC/2 );

  at91_pio_write( &PIOB_DESC, STEPPER_RESET, HIGH );

  MODE = HALFSTEP;
  azimuthStatus.braked = 0;
  azimuthStatus.steps = 0;
  elevationStatus.braked = 0;
  elevationStatus.steps = INITIAL_POSITION;
  return;
}

void initFull(){
  //setup piob for stepper motor output
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | STEPPER_RESET | CONTROL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  FULL| EN_AZI | EN_ELE | CLK_AZI | CLK_ELE,
                  LOW);

  at91_pio_write( &PIOB_DESC, STEPPER_RESET, LOW );
  
  wait( SEC/2 );

  at91_pio_write( &PIOB_DESC, STEPPER_RESET, HIGH );

  MODE = HALFSTEP;
  azimuthStatus.braked = 0;
  azimuthStatus.steps = 0;
  elevationStatus.braked = 0;
  elevationStatus.steps = -10;
}

void brake( u_int motor ){
	at91_pio_write( &PIOB_DESC, motor, HIGH );
	if( motor == AZI )
          azimuthStatus.braked = 1;
	else
          elevationStatus.braked = 1;;
        return;
}

void unbrake( u_int motor ){
	at91_pio_write( &PIOB_DESC, motor, LOW );
	if( motor == AZI )
          azimuthStatus.braked = 0;
	else
          elevationStatus.braked = 0;
        return;
}

void setDirection( u_int motor, u_int dir ) {
	at91_pio_write( &PIOB_DESC, CW, dir );
        return;
}

void step( u_int steps, u_int motor){ 
  /* toggle the clock line a number af times. order for this to do
     anything the motor needs to be in 'braked' mode.
   */
  u_int i, divisor, clk, period;
  
  if (motor == AZI){
    divisor = DIV_AZI;
    clk = CLK_AZI;
  }
  else {
    divisor = DIV_ELE;
    clk = CLK_ELE;
  }
  period = SEC/divisor;

  for(i = 0 ; i < steps; i++){
    at91_pio_write( &PIOB_DESC, clk, HIGH );
    wait( period );
    at91_pio_write( &PIOB_DESC, clk, LOW );
    wait( period );
  }
  return;
}

void accelStep( u_int steps, u_int motor ){
  /* Same as step except accelSteps steps at the beginning of the move
     and accelSteps at the end of the move will be
     accelleration/decelleration.

     steps/5 = 20% of the steps
     steps/4 = 25%
   */
  u_int accelSteps = steps/5;
  u_int i, clk, divisor, accelerator, accelDelta, period;

  if (motor == AZI){
    divisor = DIV_AZI;
    clk = CLK_AZI;
  }
  else {
    divisor = DIV_ELE;
    clk = CLK_ELE;
  }
  period = SEC/divisor;
  accelerator = period / 2;
  accelDelta = accelerator / accelSteps;

  for(i = 0 ; i < steps; i++){
    if ( i <= accelSteps ){ //in acceleration mode
      period = accelerator;
      accelerator = accelerator + accelDelta;
    }
    else if ( i >= steps - accelSteps ){
      period = accelerator;
      accelerator = accelerator - accelDelta;
    }
    else
      period = SEC/divisor;

    at91_pio_write( &PIOB_DESC, clk, HIGH );
    wait( period );
    at91_pio_write( &PIOB_DESC, clk, LOW );
    wait( period );
  }
  return;
}

void aim( motorStatus azimuth, motorStatus elevation ){
  /*
    - get angle difference between azimuthStatus and azimuth
    - calc the number of steps to achive the required angle delta
    - if angle is neg then set the CW/CCW line LEFT or DOWN
    - set enable line to high
    - call step
    - if braked is false then set enable line to low
    - repeat for elevation
   */
  int azi_delta, ele_delta;
  
  azi_delta = azimuth.steps - azimuthStatus.steps;
  ele_delta = elevation.steps - elevationStatus.steps;
  
  if ( azi_delta < 0 )
    setDirection( AZI, LEFT );
  else
    setDirection( AZI, RIGHT );
  
  brake( AZI );

  accelStep( abs(azi_delta), AZI );

  if ( ele_delta < 0 )
    setDirection( ELE, DOWN );
  else
    setDirection( ELE, UP );
  
  brake( ELE );

  accelStep( abs(ele_delta), ELE );
  //step( abs(ele_delta), ELE );
  
  if ( azimuth.braked == 0 )
    unbrake( AZI );
  if ( elevation.braked == 0)
    unbrake( ELE );
  
  //update the current status of the motors
  azimuthStatus = azimuth;
  elevationStatus = elevation;
  return;
}
