/*COMedia C328-7640 uart camera driver This file contains the function
 * definitions for the C328-7640 uart camera
 */
#include <stdlib.h>
#include <string.h>

#include "camera.h"
#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

extern void wake_up_handler (void) ;

WaitDesc wait_desc = { &TC0_DESC, 0, 0, WAIT_DELAY, wake_up_handler } ;

/* Synchronize the camera for use Opens the usart, then goes through
 * the SYNC->, <-ACK SYNC, ACK-> procedure with the camera Returns
 * true on successful synchronization, false otherwise.
 */
u_int sync_camera ( CameraDesc * camera_desc )
{
  u_int i, status, return_val = FALSE;
  char * buffer;
  CommandFrame sync = { HEAD, SYNC, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame ack  = { HEAD, ACK , SYNC , EMPTY, EMPTY, EPMTY };
  CommandFrame rec_ack, rec_sync;
  /*Set clock for wait function*/
  wait_desc.mcki_khz = 32000; /*clock speed: 32kHz*/
  wait_desc.period = 1000; /*time between transmissions: 1s*/

  /*Create the buffer*/
  buffer = malloc ( 2 * CMD_SIZE );
  memset ( buffer, 0, 2 * CMD_SIZE );

  /*Open the usart*/
  at91_usart_open ( camera_desc->usart_desc, 
                    US_ASYNC_MODE, 
                    camera_desc->baud_rate, 0 );

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             buffer, 
                             2 * CMD_SIZE, 
                             0 );

  /*Send the sync command*/
  
  /*Camera needs sync sent up to 60 times to detect baudrate*/
  for ( i = 0 ; i < 60 ; i++ )
    {
      /*Send SYNC*/
      at91_usart_send_frame ( camera_desc->usart_desc, 
                              (char*) sync, CMD_SIZE );
      /*Delay before next attempt*/
      at91_wait_open ( & wait_desc );
      status = at91_usart_get_status ( camera_desc->usart_desc );

      /*Check if something was received, need to refactor this section*/
      /* using get_frame()*/                                            
      if ( status & US_RXRDY ) 
	{
          /*Get first received frame*/
	  rec_ack = (CommandFrame) buffer;
          /*Get second received frame*/
	  rec_sync = (CommandFrame) ( buffer + CMD_SIZE );

	  if ( rec_ack.command == 
               ACK && rec_ack.param1 == 
               SYNC && rec_sync.command == 
               SYNC )
	    {
              /*Send ACK*/
	      at91_usart_send_Frame ( camer_desc->usart_desc, 
                                      (char*) ack, CMD_SIZE );
	      return_val = TRUE;
	    }
	  break;
	}
	 
    }
  free ( buffer );
  return return_val;
}

/*Initializes the camera for use Builds the frame to be used by the camera,
 * sends the INITIAL command to the camera, and receives the ACK from the
 * camera.  Returns true on successful initialization, false otherwise
 */
u_int init_camera ( CameraDesc * camera_desc,
                    char colour_type,
                    char preview_res,
                    char jpeg_res )
{}

/*Gets a picture from the camera Sends all the commands required to get a
 * picture from the camera.  Sends SET_PACKAGE_SIZE, then SNAPSHOT, then
 * GET_PICTURE.  Camera sends DATA command containing the size of the image to
 * be sent to the board.  The image is then sent in packets and the image data
 * is extraced and stored in a buffer.  That buffer is returned
 */
void * take_picture ( CameraDesc * camera_desc,
                      char snapshot_type,
                      char picture_type,
                      u_int pkg_size )
{}

/*Finds a valid frame in a buffer Looks for a 0xAA in the buffer and returns
 * that point as a CommandFrame pointer
 */
CommandFrame * get_frame ( char * buffer )
{}
