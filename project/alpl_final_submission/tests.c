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

void motorTest(void){
	u_int motor;
	int degrees;
	motorStatus azimuth, elevation;
	azimuth.braked = 1;
	elevation.braked = 1;
	
	initHalf();
        servoInit();

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



#ifdef CAMERA_TEST
        CameraDesc camera = {&USART2_DESC, CAM1, BAUDS115200, 320, 240, 2};
        char *picture, *pic2;
        Coordinate *coord1;

        init_ext_ram();
       
        printf("Synching camera\n");
        if ( sync_camera ( &camera ) == FALSE ){
          printf("Synchronization failed.\n");
          return 0;
        }
        printf("Initializing camera\n");
        if (init_camera( &camera, 
                         COLOR_TYPE_16_BIT_COLOR,
                         JPEG_RES_320x240,
                         JPEG_RES_80x64 ) == FALSE ){
          printf("Initialization of camera failed\n");
          return 0;
        }
        printf("taking picture\n");
        picture = take_picture( & camera, 
                                SNAPSHOT_TYPE_UNCOMPRESSED,
                                PICTURE_TYPE_SNAPSHOT );
        if ( picture == NULL ){
          printf("take pucture failed.\n");
        }
        printf("picture is at %x\n", picture);             

        pic2 = remove_head ( picture );
        find_centroid( pic2, coord1 );
        printf("Coordinates Are: x=%d, y=%d\n", coord1->x, coord1->y);
        getchar();

#endif



#ifdef BALLISTIC_TEST
  char choice, dummy;
  motorStatus azimuth, elevation;
  u_int count = 0;

  azimuth.braked = 1;
  elevation.braked = 1;

  initHalf();                            
  servoInit();                         
  if( !init_ext_ram()){                
    printf("failed to init ext ram\n");
    return 0;                          
  }                                    
  init_ext_ram();

  setDirection( ELE , UP );
  brake( AZI );
  brake( ELE );

  while(1){
    printf("count = %d\n",count);
    choice = getchar();
    choice = choice - 0x30;
    dummy = getchar();
    if (choice == 0){
      step( 1, ELE );
      count++;
    }
    else if (choice == 1){
      fire();
    }
  }
} 


