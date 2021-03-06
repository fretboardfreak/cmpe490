/*COMedia C328-7640 uart camera driver This file contains the function
 * definitions for the C328-7640 uart camera
 */

/*Uncomment this line to get debug messages*/
#define DEBUG

#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "camera.h"

#include "parts/m55800/lib_m55800.h"
#include "drivers/capture/capture.h"
#include "drivers/wait/wait.h"
#include "parts/m55800/eb55.h"

//extern void wake_up_handler (void) ;
//extern WaitDesc alpl_wait_desc;

/* Synchronize the camera for use Opens the usart, then goes through
 * the SYNC->, <-ACK SYNC, ACK-> procedure with the camera Returns
 * true on successful synchronization, false otherwise.
 */
u_int sync_camera ( CameraDesc * camera_desc )
{
  u_int i, status, return_val = FALSE, period;
  char * buffer;
  CommandFrame sync = { HEAD, SYNC, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame ack  = { HEAD, ACK , SYNC , EMPTY, EMPTY, EMPTY };
  CommandFrame rec_ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_sync = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };

  period = DELAY; /*time between transmissions: 1/4s*/

  /*Create the buffer*/
  buffer = malloc ( 2 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 2 * CMD_SIZE );

  /*Set the receive multiplexer to the camera we're using*/
  at91_pio_write (& PIOB_DESC, PB18, camera_desc->camera );
  
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
  for ( i = 0 ; i < SYNC_ATTEMPTS ; i++ )
    {
      /*Send SYNC*/
      send_command ( camera_desc, & sync );
      /*Delay before next attempt*/
      wait( period );
      status = at91_usart_get_status ( camera_desc->usart_desc );

#ifdef DEBUG
      wait( period );
#endif

      /*Check if something was received*/                                           
      if ( status & ( US_ENDRX | US_TIMEOUT ) ) 
	{

#ifdef DEBUG
          wait( period );
#endif
          if ( buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 &&
               buffer[3] == 0 && buffer[4] == 0 && buffer[5] == 0 ){
            free( buffer );
            return FALSE;
          }

          /*Try to get the frames*/
	  if ( get_frame ( buffer, & rec_ack, 2 * CMD_SIZE, 1 )
	       && get_frame ( buffer, & rec_sync, 2 * CMD_SIZE, 2 ) )
	    {
	      if ( rec_ack.command == ACK 
		   && rec_ack.param1 == SYNC 
		   && rec_sync.command == SYNC )
		{
		  /*Send ACK*/
		  send_command ( camera_desc, & ack );
		  return_val = TRUE;
		  break;
		}
	    }
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
{
  CommandFrame init = { HEAD, INITIAL, EMPTY, EMPTY, EMPTY, EMPTY };
  u_int period = DELAY; /*time between transmissions: 1/4s*/
 
  /*Fill the init parameters*/
  init.param2 = colour_type;
  init.param3 = preview_res;
  init.param4 = jpeg_res;

#ifdef DEBUG
  wait( period );
#endif

  /*Send INITIAL to the camera and listen for ACK*/
  return send_command_get_ack ( camera_desc, & init );
 
}

/*Gets a picture from the camera Sends all the commands required to get a
 * picture from the camera.  Sends SNAPSHOT, then GET_PICTURE.  Camera sends
 * DATA command containing the size of the image to be sent to the board.  The
 * image is then sent as a single transmission and stored in a buffer.  That
 * buffer is returned.  The buffer contains the frames for the ACK and DATA
 * packets received after sending GET_PICTURE before the image data.
 */
char * take_picture ( CameraDesc * camera_desc,
                      char snapshot_type,
                      char picture_type )
{
  char * buffer, * picture_buffer;
  u_int status, pic_length, period = DELAY;

  CommandFrame snap = { HEAD, SNAPSHOT, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame get_pic = { HEAD, GET_PICTURE, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_data = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };

  /*Create the buffer*/
  buffer = malloc ( 3 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 3 * CMD_SIZE );

  /*Fill the frame parameters*/
  snap.param1 = snapshot_type;
  get_pic.param1 = picture_type;

  /*Send SNAPSHOT to the camera and wait for an ACK*/
  if ( send_command_get_ack ( camera_desc, & snap ) == FALSE )
    {
      free ( buffer );
      return NULL; /*Fail if no ACK was received*/
    }

  /*Free the command buffer, we won't be using it anymore*/
  free ( buffer );

  /*Make the picture buffer*/
  pic_length = camera_desc->x_res * camera_desc->y_res 
             * camera_desc->pixel_size;

  //picture_buffer = (char*) MEMORY;
  picture_buffer = calloc( pic_length + 3 * CMD_SIZE, 1 );
  if ( picture_buffer == NULL ){
    return NULL;
  }

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             picture_buffer, 
                             pic_length + 3 * CMD_SIZE, 
                             20 );
  /*Send GET_PICTURE*/
  send_command ( camera_desc, & get_pic );

  while ( 1 )
    {
      status = at91_usart_get_status ( camera_desc->usart_desc );

      /*This is a hack to get around the 16-bit receive counter*/
      //if ( camera_desc->usart_desc->usart_base->US_RCR < REFILL )
      //camera_desc->usart_desc->usart_base->US_RCR = pic_length;

      /*Check if something was received*/                                           
      if ( status & ( US_ENDRX | US_TIMEOUT ) ) 
	{

#ifdef DEBUG
          wait(period);
#endif

	  /*Try to get the frames*/
	  if ( get_frame ( picture_buffer, & rec_ack, 3 * CMD_SIZE, 1 )
	       && get_frame ( picture_buffer, & rec_data, 3 * CMD_SIZE, 2 ) )
	    {
	      if ( rec_ack.command == ACK 
		   && rec_ack.param1 == GET_PICTURE 
		   && rec_data.command == DATA )
		{
		  /*Return the picture buffer*/
		  return picture_buffer;
		}
	    }
	}
    }
  return NULL;
}

/*Finds a valid frame in a buffer. Looks for the number'th instance of 0xAA and
 * copies it and the next 5 bytes from the buffer into frame. TRUE or FALSE are
 * returned to indicate success of failure.
 */
u_int get_frame ( char * buffer, 
		  CommandFrame * frame,
		  u_int size, 
		  u_int number )
{
  u_int i;

  for ( i = 0 ; i < size ; i++ )
    {
      if ( buffer[i] == HEAD ) /*found a frame*/
	{
	  if ( --number == 0 )
	    {
	      frame->header = buffer[i]; /*fill the command struct*/
	      frame->command = buffer[i+1];
	      frame->param1 = buffer[i+2];
	      frame->param2 = buffer[i+3];
	      frame->param3 = buffer[i+4];
	      frame->param4 = buffer[i+5];

	      return TRUE; /*return success*/
	    }
	}
    }
  return FALSE; /*couldn't find enough frames in the buffer*/
}

/*Sends commands to the camera.  First packs the command frame into a character
 * array then sends that frame over the usart
 */ 
void send_command ( CameraDesc * camera_desc, CommandFrame * frame ) 
{ 
  char packet[CMD_SIZE];
  packet[0] = frame->header;
  packet[1] = frame->command;
  packet[2] = frame->param1; 
  packet[3] = frame->param2;
  packet[4] = frame->param3; 
  packet[5] = frame->param4;

  at91_usart_send_frame ( camera_desc->usart_desc, packet, CMD_SIZE );
}

/*Many of the commands sent to the camera simply wait for the camera to
 * acknowledge that they were received before proceeding.  This function sends a
 * command then waits a fixed period before checking if an ACK was
 * returned. Returns TRUE or FALSE based on success.
 */
u_int send_command_get_ack ( CameraDesc * camera_desc, 
			     CommandFrame * frame )
{
  char * buffer;
  u_int status, i, period;
  CommandFrame ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };

  period = DELAY;

  /*Create the buffer*/
  buffer = malloc ( 2 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 2 * CMD_SIZE );

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             buffer, 
                             2 * CMD_SIZE, 
                             20 );

  /*Send command*/
  for(i=0; i<CMD_ATTEMPTS; i++){
  /*Check if a frame was received*/
    send_command ( camera_desc, frame );
    while ( 1 )
    {
      status = at91_usart_get_status ( camera_desc->usart_desc );
      
      if ( status & ( US_ENDRX | US_TIMEOUT ) )
	{

#ifdef DEBUG
          wait( period );
#endif

	  /*Try to get a frame from the buffer*/
	  if ( get_frame ( buffer, & ack, 2 * CMD_SIZE, 1 ) )
	    {
	      /*Check if frame was an ACK*/
	      if ( ack.command == ACK && ack.param1 == frame->command )
		{
                  free( buffer );
                  return TRUE;
		}
	    }
          at91_usart_receive_frame ( camera_desc->usart_desc, buffer, 
                                     2 * CMD_SIZE, 20 );
          break;
	}
    }
  }
  free ( buffer );
  return FALSE;
}

