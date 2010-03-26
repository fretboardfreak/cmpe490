#include "stepper.h"
#include stepper.h


motorStatus azimuthStatus;
motorStatus elevationStatus;

void delay( u_int secs ){
  u_int i = 0;
  wait_desc.period = SEC;
  for ( i; i<secs; i++ ){
    at91_wait_open(&wait_desc);
  }
}

void initFull(){
  //setup piob for stepper motor output
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | RESET | CONTROL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  FULL| EN0 | EN1 | CLK0 | CLK1,
                  LOW);

  at91_pio_write( &PIOB_DESC, RESET, LOW );
  wait_desc.period = SEC/2;
  at91_wait_open( &wait_desc );
  at91_pio_write( &PIOB_DESC, RESET, HIGH );
}

void initHalf(){
  //setup piob for stepper motor output
  at91_pio_open( &PIOB_DESC,
                 PB0 | PB1 | PB2 | PB3 | PB4 | PB5 | PB6 | PB7,
                 PIO_OUTPUT );

  //initialize stepper lines
  at91_pio_write( &PIOB_DESC,
                  CW | RESET | FULL,
                  HIGH);
  at91_pio_write( &PIOB_DESC,
                  CONTROL | EN0 | EN1 | CLK0 | CLK1,
                  LOW);

  at91_pio_write( &PIOB_DESC, RESET, LOW );
  wait_desc.period = SEC/2;
  at91_wait_open( &wait_desc );
  at91_pio_write( &PIOB_DESC, RESET, HIGH );
}

void step( u_int *steps, u_int *motor, u_int *clk ){
  /*
    Testing function.  Does not keep the motors in braking mode.
   */
  u_int i;
  u_int divisor;
  //reset the state machine

  /*at91_pio_write( &PIOB_DESC, RESET, LOW );
    wait_desc.period = SEC/DIV;
    at91_wait_open( &wait_desc );
    at91_pio_write( &PIOB_DESC, RESET, HIGH );
  */

  if (*motor == EN0){
    divisor = DIV0;
    /*at91_pio_write( &PIOB_DESC, RESET, LOW );
      wait_desc.period = SEC/2;
      at91_wait_open( &wait_desc );
      at91_pio_write( &PIOB_DESC, RESET, HIGH );*/
  }
  else
    divisor = DIV1;
  printf("divisor = %d\n", divisor);
  at91_pio_write( &PIOB_DESC, *motor, HIGH );
  for(i = 0 ; i < steps; i++){
    at91_pio_write( &PIOB_DESC, *clk, HIGH );
    wait_desc.period = SEC/divisor;
    at91_wait_open( &wait_desc );
    at91_pio_write( &PIOB_DESC, *clk, LOW );
    wait_desc.period = SEC/divisor;
    at91_wait_open( &wait_desc );
  }
  at91_pio_write( &PIOB_DESC, *motor, HIGH );
}

void moveStepper( motorStatus azimuth, motorStatus elevation ){
  /*
    - get angle difference between azimuthStatus and azimuth
    - calc the number of steps to achive the required angle delta
    - if angle is neg then set the CW/CCW line accordingly
    - set enable line to high
    - call step
    - if braked is false then set enable line to low
    - repeat for elevation
   */

  
}
