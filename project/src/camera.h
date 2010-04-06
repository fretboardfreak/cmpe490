/*Camera Driver Header file This file contains all the macros,
 * structure definitions, and function prototypes for the C328-7640
 * uart camera driver
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "periph/usart/lib_usart.h"

/*Camera Instruction Set*/     
/*1st Parameter  2nd Parameter  3rd Parameter  4th Parameter  */
#define INITIAL          0x01 
/*0x00           colour type    preview res    jpeg resolution*/
#define GET_PICTURE      0x04 
/*picture type   0x00           0x00           0x00           */
#define SNAPSHOT         0x05 
/*snapshot type  skip byte 0    skip byte 1    0x00           */
#define SET_PACKAGE_SIZE 0x06 
/*0x08           pkg size 0     pkg size 1     0x00           */
#define SET_BAUDRATE     0x07 
/*first divider  second divider 0x00           0x00           */
#define RESET            0x08 
/*reset type     0x00           0x00           0x00           */
#define POWER_OFF        0x09 
/*0x00           0x00           0x00           0x00           */
#define DATA             0x0A 
/*data type      data size 0    data size 1    data size 2    */
#define SYNC             0x0D 
/*0x00           0x00           0x00           0x00           */
#define ACK              0x0E 
/*command id     ack counter    pkg id 0       pkg id 1       */
#define NAK              0x0F 
/*0x00           nak counter    error code     0x00           */
#define LIGHT_FREQUENCY  0x13 
/*frequency type 0x00           0x00           0x00           */

/*Command Header and empty parameters*/
#define HEAD  0xAA
#define EMPTY 0x00

/*INITIAL Parameters*/
/*Color Type*/
#define COLOR_TYPE_2_BIT_GREY   0x01
#define COLOR_TYPE_4_BIT_GREY   0x02
#define COLOR_TYPE_8_BIT_GREY   0x03
#define COLOR_TYPE_12_BIT_COLOR 0x05
#define COLOR_TYPE_16_BIT_COLOR 0x06
#define COLOR_TYPE_JPEG         0x07

/*Preview Resolution*/
#define PREVIEW_RES_80x60   0x01
#define PREVIEW_RES_160x120 0x03
/*note: 0x05 and 0x07 will work here as well, although they are not                                 
        described in the users manual explicitely and will give the                                 
        same resolutions they do for JPEG resolution*/

/*JPEG Resolution*/
#define JPEG_RES_80x64   0x01
#define JPEG_RES_160x128 0x03
#define JPEG_RES_320x240 0x05
#define JPEG_RES_640x480 0x07

/*GET_PICTURE Parameters*/
/*Picture Type*/
#define PICTURE_TYPE_SNAPSHOT 0x01
#define PICTURE_TYPE_PREVIEW  0x02
#define PICTURE_TYPE_JPEG     0x05

/*SNAPSHOT Parameters*/
/*Sanpshot Type*/
#define SNAPSHOT_TYPE_COMPRESSED   0x00
#define SNAPSHOT_TYPE_UNCOMPRESSED 0x01

/*SET_BAUDRATE Parameters*/
/*1st Divider*/
#define BAUDRATE_7200   0xFF
#define BAUDRATE_9600   0xBF
#define BAUDRATE_14400  0x7F
#define BAUDRATE_19200  0x5F
#define BAUDRATE_28800  0x3F
#define BAUDRATE_38400  0x2F
#define BAUDRATE_57600  0x1F
#define BAUDRATE_115200 0x0F

/*2nd Divider*/
#define BAUDRATE_DIVIDER 0x01

/*RESET Parameters*/
/*Reset Type*/
#define RESET_HARD 0x00
#define RESET_SOFT 0x01

/*DATA Parameters*/
/*Data Type*/
#define DATA_TYPE_SNAPSHOT 0x01
#define DATA_TYPE_PREVIEW  0x02
#define DATA_TYPE_JPEG     0x05

/*NAK Parameters*/
/*Error Code*/
#define ERR_PIC_TYPE              0x01
#define ERR_PIC_UP_SCALE          0x02
#define ERR_PIC_SCALE             0x03
#define ERR_UNEXPECTED_REPLY      0x04
#define ERR_SEND_PIC_TIMEOUT      0x05
#define ERR_UNEXPECTED_CMD        0x06
#define ERR_SRAM_JPEG_TYPE        0x07
#define ERR_SRAM_JPEG_SIZE        0x08
#define ERR_PIC_FORMAT            0x09
#define ERR_PIC_SIZE              0x0A
#define ERR_PARAMETER             0x0B
#define ERR_SEND_REGISTER_TIMEOUT 0x0C
#define ERR_CMD_ID                0x0D
#define ERR_PIC_NOT_READY         0x0F
#define ERR_PACKAGE_NUMBER        0x10
#define ERR_WRONG_PACKAGE_SIZE    0x11
#define ERR_CMD_HEADER            0xF0
#define ERR_CMD_LENGTH            0xF1
#define ERR_SEND_PIC              0xF5
#define ERR_SEND_CMD              0xFF

/*Light Frequency Parameters*/
/*Frequency Type*/
#define FREQUENCY_50HZ 0x00
#define FREQUENCY_60HZ 0x01

/*Misc. Definitions*/
#define CMD_SIZE 6       /*Size of a command frame*/
#define SYNC_ATTEMPTS 120 /*Number of attempts for sync command*/
#define CMD_ATTEMPTS 5 /*Number of attempts for other commands*/
#define CLOCK 32000      /*Clock frequency*/
#define DELAY 250000    /*time interval between transmissions*/
#define REFILL 2000     /*Fix for overflowing receive frame counter*/
#define CAM1 1
#define CAM2 0

/*Baudrate dividers for camera descriptors*/
#define BAUDS115200 (32000000 / (16 * 115200))
#define BAUDS57600  (32000000 / (16 * 57600 ))
#define BAUDS38400  (32000000 / (16 * 38400 ))
#define BAUDS14400  (32000000 / (16 * 14400 ))

/*Camera Descriptor Structure Definition*/
typedef struct
{
  const UsartDesc * usart_desc; /*USART descriptor*/
  u_int       camera;
  u_int       baud_rate;
  u_int       x_res;
  u_int       y_res;
  u_int       pixel_size;
  
} CameraDesc;

/*Command Frame Structure definition*/
typedef struct
{
  char header;  /*always 0xAA*/
  char command; /*corresponds to the camera command*/
  char param1;  /*these correspond to parameters for the command*/
  char param2;
  char param3;
  char param4;
} CommandFrame;

/*Function Prototypes*/
u_int sync_camera ( CameraDesc * camera_desc );
u_int init_camera ( CameraDesc * camera_desc, 
                    char colour_type, 
                    char preview_res, 
                    char jpeg_res );
char * take_picture ( CameraDesc * camera_desc, 
                      char snapshot_type, 
                      char picture_type );
u_int get_frame ( char * buffer, 
		  CommandFrame * frame,
		  u_int size, 
		  u_int number );
void send_command ( CameraDesc * camera_desc, 
		    CommandFrame * frame );
u_int send_command_get_ack ( CameraDesc * camera_desc,
			     CommandFrame * frame );

#endif
