#include "alpl.h"

#include "periph/timer_counter/lib_tc.h"

extern void irq_asm_irq_handler(void);


u_int irq_led_status = 0;

void alpl_irq_handler(void){
  u_int dummy;
  wait_semaphore = 0;
  irq_led_status = (irq_led_status +1)%2;
  change_led( LED8, irq_led_status );
  dummy = TC0_DESC.tc_base->TC_SR;
}

/*This function takes a centroid value and approximates the angle from the
 * centre of the image to the centroid point.
 */
void find_offset ( Coordinate * centroid, float *offset )
{
  float tmp = ( centroid->x - X_RES / 2 );
  *offset = tmp * DEGREES_PER_PIXEL;
}

/*This function simply initializes the external ram we have interfaced so that
 * it can be used to store the large image arrays being processed
 */
int init_ext_ram ( void ) 
{
  u_int *ebi_csr2 = 0xffe00000 | 0x08;
  //u_int ebi_config = 0x004020a6;
  //more wait states 0x004020ae;
  u_int ebi_config = 0x004020ae;
  u_int *memory = 0x400000, *i, x=0xaa;
  *ebi_csr2 = ebi_config;

  for(i=memory; i<0x400100; i++){
    *i = x;
  }
  for(i=memory; i<0x400100; i++){
    if ( *i != x ){
      return 0;
    }
  }
  return 1;
}

/*Zach's Ultra-Awesome-Nuclear-Powered-Pseudo-Math-Library
 * (now with 42% more awesome! and 13% less deadly radiation!)
 * xpow returns x raised to the n-th power.
 * sine returns the sine of x degrees
 * cosine returns the cosine of x degrees
 * tangent returns the tangent of x degrees, returns 0 in cases where
 * tan would normally be infinite.
 */
void xpow ( float *x, int n, float *ans )
{
  float product = *x;
  if ( n == 0 )
    *ans = 1.0f;
  while( n > 1 )
    {
      product *= *x;
      n--;
    }
  *ans = (float) product;
}

void sine ( float *x, float *ans )
{
  float x_rad = *x * PI / 180.0f;
  float pivot = x_rad - PI2;
  float pivotP2, pivotP4, pivotP6, pivotP8;
  xpow( &pivot, 2, &pivotP2 );
  xpow( &pivot, 4, &pivotP4 );
  xpow( &pivot, 6, &pivotP6 );
  xpow( &pivot, 8, &pivotP8 );
  //*ans = 1.0f - xpow ( pivot, 2 ) / 2 + xpow ( pivot, 4 ) / 24 
  //       - xpow ( pivot, 6 ) / 720 + xpow ( pivot, 8 ) / 40320;
  *ans = 1.0f - pivotP2 / 2.0f + pivotP4 / 24.0f - pivotP6 / 720.0f 
         + pivotP8 / 40320.0f;
}

void cosine ( float *x, float *ans )
{
  float x_rad = *x * PI / 180.0f;
  float pivot = x_rad - PI2;
  float pivotP3, pivotP5, pivotP7, pivotP9;
  xpow( &pivot, 3, &pivotP3 );
  xpow( &pivot, 5, &pivotP5 );
  xpow( &pivot, 7, &pivotP7 );
  xpow( &pivot, 9, &pivotP9 );
  //*ans = 0 - pivot + xpow ( pivot, 3 ) / 6 - xpow ( pivot, 5 ) / 120
  //       + xpow ( pivot, 7 ) / 5040 - xpow ( pivot, 9 ) / 362880;
  *ans = 0.0f - pivot + pivotP3 / 6.0f - pivotP5 / 120.0f + pivotP7 / 5040.0f 
         - pivotP9 / 362880.0f;
}

void tangent ( float *x, float *ans )
{
  float sin, cos;
  sine ( x, &sin );
  cosine ( x, &cos );
  if ( cos == 0.0f )
    *ans = 0;
  else
    *ans = sin / cos;
}

/*This function takes an offset angle and, assuming that the turret has been
 * centered, uses the angle to calculate the distance to the target so the shot
 * elevation may be determined.
 */
void find_distance ( float * offset, float * distance )
{
  float tan, tmp;
  if( *offset < 0 )
    *offset = 0 - *offset;
  tmp = 90.0 - *offset;
  tangent( &tmp, &tan );
  *distance = WIDTH * tan ;
}

void initCamMux( void ){
  at91_pio_open( &PIOB_DESC, PB18, PIO_OUTPUT );
}

void fill_lut( int *lut ){
  float indexP2 = 0;
  float index;
  
  for( index = 0; index <= MAXVERTSTEPS-1; index++ ){
    xpow( &index, 2, &indexP2 );
    lut[(int)index] = (int)((-0.0058f * indexP2 + 0.27f * index + 1.3f)*10);
  }
}

void distance_to_steps( float *distance, int *steps ){
  int lut[MAXVERTSTEPS], i;
  int lookup = (int)*distance * 10;
  int current, difference, lastDiff, closest;

  //lut contents is distance
  fill_lut( lut );

  lastDiff = abs(lookup - lut[MAXVERTSTEPS -1]);

  for( i=MAXVERTSTEPS-2; i>=0; i-- ){
    current = lut[i];

    difference = abs(lookup - current);

    if ( difference < lastDiff )
      closest = i;

    lastDiff = difference;
  }
  *steps = closest;
}

void init_led( void ){
  at91_pio_open( &PIOB_DESC, LED_MASK, PIO_OUTPUT );
  at91_pio_write( &PIOB_DESC, LED_MASK, LED_OFF );
}

void change_led( u_int led, u_int status ){
  /*
   * led = LED_MASK, LED1, LED2, ..., LED8
   * status = LED_ON, LED_OFF
   */
  at91_pio_write( &PIOB_DESC, led, status );
}

void distance_to_leds( float *distance ){
  int dig1, dig2;
  float tmp1, tmp2;
  u_int led_mask = 0;
  dig1 = (int)*distance;
  tmp1 = *distance * 10;
  tmp2 = dig1 * 10;
  
  dig2 = (int)(tmp1 - tmp2); //(int)((*distance - dig1) * 10);
  
  if( dig1 - 8 >= 0 ){
    led_mask = led_mask | LED1;
    dig1 = dig1 - 8;
  }
  if( dig1 - 4 >= 0 ){
    led_mask = led_mask | LED2;
    dig1 = dig1 - 4;
  }
  if( dig1 - 2 >= 0 ){
    led_mask = led_mask | LED3;
    dig1 = dig1 - 2;
  }
  if( dig1 - 1 >= 0 ){
    led_mask = led_mask | LED4;
    dig1 = dig1 - 1;
  }

  if( dig2 - 8 >= 0 ){
    led_mask = led_mask | LED5;
    dig2 = dig2 - 8;
  }
  if( dig2 - 4 >= 0 ){
    led_mask = led_mask | LED6;
    dig2 = dig2 - 4;
  }
  if( dig2 - 2 >= 0 ){
    led_mask = led_mask | LED7;
    dig2 = dig2 - 2;
  }
  if( dig2 - 1 >= 0 ){
    led_mask = led_mask | LED8;
    dig2 = dig2 - 1;
  }
  change_led( LED_MASK, LED_OFF );
  change_led( led_mask, LED_ON );
}

void wait( u_int clkCycles ){
  u_int mode = TC_CLKS_MCK1024    |
    TC_CPCDIS                     |
    TC_WAVE;

  u_int reg[4];
  reg[RA] = 0;
  reg[RB] = 0;
  reg[RC] = clkCycles;

  at91_tc_open ( & TC0_DESC, mode, FALSE, FALSE );

  at91_irq_open( TC0_DESC.periph_id, 5,   //periph_id maybe be 6 or 7
                 AIC_SRCTYPE_INT_LEVEL_SENSITIVE,
                 irq_asm_irq_handler );

  TC0_DESC.tc_base->TC_IER = TC_CPCS;

  at91_tc_write ( & TC0_DESC, reg );	
  at91_tc_trig_cmd ( & TC0_DESC, TC_TRIG_CHANNEL );

  wait_semaphore = 1;

  while(wait_semaphore);

}
