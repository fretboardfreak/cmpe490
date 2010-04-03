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


#define MOTOR_TEST 1
#ifdef MOTOR_TEST
u_int getMotor( void ){
    u_int motor;
	u_int choice;
    u_int dummy;
    while(1){
	printf("Choose a Motor: 0=Azimuth or 1=Elevation:\n");
	//scanf("%d\n", &choice );
	choice = getchar();
	choice = choice - 0x30;
	dummy = getchar(); //pesky newlines
	if (choice == 0){
	    motor = AZI;
	    return motor;
	}
	else if (choice == 1){
	    motor = ELE;
	    return motor;
	}
	else{
	    printf("You entered an invalid value for motor.\n");
	}
    }
}

int getDegrees( void ){
    int choice = 0, dummy = 0, neg = 0;
    printf("Now we need to know where to aim\n");
    while(1){
		printf("Enter 0 to aim Left or Down, 1 to aim Right or Up from center.\n");
		neg = getchar();
		neg = neg - 0x30;
		dummy = getchar(); 
		
		printf("Enter the number of decadegrees between 0 and 9:\n");
		choice = getchar();
		choice = choice - 0x30;
		dummy = getchar(); //pesky newlines
		if (choice >= 0 && choice < 10){
			choice = choice * 10;
			break;
		}
		else
			printf("You entered an invalid number of steps.\n");
	}
	if ( neg == 0 )
		return 0-choice;
	else
		return choice;
}

u_int unleashHell(void){
    u_int choice = 0;
    u_int dummy = 0;
    while(1){
	printf("Unleash Hell? (1 to fire, 0 to aim)\n");
	choice = getchar();
	choice = choice - 0x30;
	dummy = getchar(); //pesky newlines
	if (choice == 0 || choice == 1){
	    return choice;
	}
	else
	    printf("You entered an invalid option.\n");
    }
    
}

#endif

int main( void ){
#ifdef MOTOR_TEST
	u_int motor;
	int degrees;
	motorStatus azimuth, elevation;
	azimuth.braked = 1;
	elevation.braked = 1;
	
	initHalf();

	while(1){
		if ( unleashHell() )
			fire();
		else {
			motor = getMotor();
			degrees = getDegrees();
			if ( motor == AZI ){
				elevation = elevationStatus;
				azimuth.angle = degrees;
			}
			else{
				azimuth = azimuthStatus;
				elevation.angle = degrees;
			}
			aim( azimuth, elevation );
		}	
	}
#endif 

}
