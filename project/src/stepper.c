#include "stepper.h"

u_int MODE;

u_int getVertSteps( float degrees ){
  float tmp = abs( degrees / (float) (VDEGPSTEP * MODE));
  return (u_int) tmp;
}

u_int getHorSteps( float degrees ){
  float tmp = abs(degrees / (float) (HDEGPSTEP * MODE));
  return (u_int) tmp;
}

void initHalf(){
  //setup piob for stepper motor output
  float halfSec = 0.5f;
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | RESET | CONTROL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  FULL| EN_AZI | EN_ELE | CLK_AZI | CLK_ELE,
                  LOW);

  at91_pio_write( &PIOB_DESC, RESET, LOW );

  delay(&halfSec);

  at91_pio_write( &PIOB_DESC, RESET, HIGH );

  MODE = HALFSTEP;
  azimuthStatus.braked = 0;
  azimuthStatus.angle = 0.0f;
  elevationStatus.braked = 0;
  elevationStatus.angle = -28.2f;
}

void initFull(){
  //setup piob for stepper motor output
  float halfSec = 0.5f;
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | RESET | FULL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  CONTROL | EN_AZI | EN_ELE | CLK_AZI | CLK_ELE,
                  LOW);

  at91_pio_write( &PIOB_DESC, RESET, LOW );
  
  delay(&halfSec);
  printf("");
  at91_pio_write( &PIOB_DESC, RESET, HIGH );

  MODE = FULLSTEP;
  azimuthStatus.braked = 0;
  azimuthStatus.angle = 0.0f;
  elevationStatus.braked = 0;
  elevationStatus.angle = -28.2f;
}

void brake( u_int motor ){
	motorStatus motorToBrake;
	if( motor == AZI )
		motorToBrake = azimuthStatus;
	else
		motorToBrake = elevationStatus;

	at91_pio_write( &PIOB_DESC, motor, HIGH );
	motorToBrake.braked = 1;
}

void unbrake( u_int motor ){
	motorStatus motorToUnbrake;
	if( motor == AZI )
		motorToUnbrake = azimuthStatus;
	else
		motorToUnbrake = elevationStatus;

	at91_pio_write( &PIOB_DESC, motor, LOW );
	motorToUnbrake.braked = 0;	
}

void setDirection( u_int motor, u_int dir ) {
	at91_pio_write( &PIOB_DESC, CW, dir );
}

void step( u_int steps, u_int motor){ 
  /* toggle the clock line a number af times. order for this to do
     anything the motor needs to be in 'braked' mode.
   */
	u_int i;
	float divisor, period;
	u_int clk;
	
	if (motor == AZI){
		divisor = (float)DIV_AZI;
		clk = CLK_AZI;
	}
	else {
		divisor = (float) DIV_ELE;
		clk = CLK_ELE;
	}
	period = (float)1.0/divisor;
	
	for(i = 0 ; i < steps; i++){
		at91_pio_write( &PIOB_DESC, clk, HIGH );
		delay(&period);
		at91_pio_write( &PIOB_DESC, clk, LOW );
		delay(&period);
	}
}

void accelStep( u_int steps, u_int motor ){
  /* Same as step except 10% of the steps at the beginning of the move
     and 10% at the end of the move will be
     accelleration/decelleration.
   */
  u_int accelSteps = steps/10;
  u_int startDecel = steps - accelSteps;

  u_int i, clk;
  float divisor, period, accelerator, accelDelta;

  if ( steps <= 15 ){
    step( steps, motor );
    return;
  }

  if (motor == AZI){
    divisor = (float)DIV_AZI;
    clk = CLK_AZI;
  }
  else {
    divisor = (float) DIV_ELE;
    clk = CLK_ELE;
  }
  period = (float)1.0/divisor;
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
      period = (float)1.0/divisor;
    at91_pio_write( &PIOB_DESC, clk, HIGH );
    delay(&period);
    at91_pio_write( &PIOB_DESC, clk, LOW );
    delay(&period);
  }
  
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
	int azi_delta, ele_delta, horSteps, vertSteps;

	azi_delta = azimuthStatus.angle + azimuth.angle;
	ele_delta = elevationStatus.angle + elevation.angle;
	
	printf("azi = %d, ele = %d\n", azi_delta, ele_delta);
	
	if ( azi_delta < 0 )
		setDirection( AZI, LEFT );
	else
		setDirection( AZI, RIGHT );
	
	brake( AZI );
	horSteps = getHorSteps( azi_delta );
#ifdef ACCELERATION
        accelStep( horSteps, AZI );
#endif
#ifndef ACCELERATION
	step( horSteps, AZI );
#endif
	if ( ele_delta < 0 )
		setDirection( ELE, DOWN );
	else
		setDirection( ELE, UP );
	
	brake( ELE );
	vertSteps = getVertSteps( ele_delta );
#ifdef ACCELERATION
        accelStep( vertSteps, ELE );
#endif
#ifndef ACCELERATION
	step( vertSteps, ELE );	
#endif
	if ( azimuth.braked == 0 )
		unbrake( AZI );
	if ( elevation.braked == 0)
		unbrake( ELE );

        //update the current status of the motors
        azimuthStatus = azimuth;
        elevationStatus = elevation;
}
