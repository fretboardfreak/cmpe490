/*COMedia C328-7640 uart camera driver This file contains the function
 * definitions for the C328-7640 uart camera
 */
#include <stdlib.h>
#include <string.h>

#include "user/camera.h"
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
  CommandFrame ack  = { HEAD, ACK , SYNC , EMPTY, EMPTY, EMPTY };
  CommandFrame rec_ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_sync = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  /*Set clock for wait function*/
  wait_desc.mcki_khz = CLOCK; /*clock speed: 32kHz*/
  wait_desc.period = DELAY; /*time between transmissions: 1s*/

  /*Create the buffer*/
  buffer = malloc ( 3 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 3 * CMD_SIZE );

  /*Open the usart*/
  at91_usart_open ( camera_desc->usart_desc, 
                    US_ASYNC_MODE, 
                    camera_desc->baud_rate, 0 );

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             buffer, 
                             3 * CMD_SIZE, 
                             0 );

  /*Send the sync command*/
  
  /*Camera needs sync sent up to 60 times to detect baudrate*/
  for ( i = 0 ; i < SYNC_ATTEMPTS ; i++ )
    {
      /*Send SYNC*/
      send_command ( camera_desc, & sync );
      /*Delay before next attempt*/
      at91_wait_open ( & wait_desc );
      status = at91_usart_get_status ( camera_desc->usart_desc );

      /*Check if something was received*/                                           
      if ( status & US_RXRDY ) 
	{
          /*Try to get the frames*/
	  if ( get_frame ( buffer, & rec_ack, 3 * CMD_SIZE, 1 )
	       && get_frame (buffer, & rec_sync, 3 * CMD_SIZE, 2 ) )
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
 
  /*Fill the init parameters*/
  init.param2 = colour_type;
  init.param3 = preview_res;
  init.param4 = jpeg_res;

  /*Send INITIAL to the camera and listen for ACK*/
  return send_command_get_ack ( camera_desc, & init );
 
}

/*Gets a picture from the camera Sends all the commands required to get a
 * picture from the camera.  Sends SET_PACKAGE_SIZE, then SNAPSHOT, then
 * GET_PICTURE.  Camera sends DATA command containing the size of the image to
 * be sent to the board.  The image is then sent in packets and the image data
 * is extracted and stored in a buffer.  That buffer is returned.
 */
char * take_picture ( CameraDesc * camera_desc,
                      char snapshot_type,
                      char picture_type,
                      u_int pkg_size )
{
  char * buffer, pkgsize0, pkgsize1, * picture_buffer, num_pkg;
  u_int status, pic_length, pkg_count = 0;
  CommandFrame set_pkg_size = { HEAD, SET_PACKAGE_SIZE, EMPTY, 
				EMPTY, EMPTY, EMPTY };
  CommandFrame snap = { HEAD, SNAPSHOT, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame get_pic = { HEAD, GET_PICTURE, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame ack = { HEAD, ACK, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  CommandFrame rec_data = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
  /*Set clock for wait function*/
  wait_desc.mcki_khz = CLOCK; /*clock speed: 32kHz*/
  wait_desc.period = DELAY; /*time between transmissions: 1s*/

  /*Create the buffer*/
  buffer = malloc ( 3 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 3 * CMD_SIZE );

  /*Calculate values for set_package_size parameters*/
  pkgsize0 = (char) ( pkg_size & 0x00FF );
  pkgsize1 = (char) ( ( pkg_size & 0xFF00 >> 8) );

  /*Fill the frame parameters*/
  snap.param1 = snapshot_type;
  get_pic.param1 = picture_type;
  set_pkg_size.param1 = 0x08;
  set_pkg_size.param2 = pkgsize0;
  set_pkg_size.param3 = pkgsize1;

  /*Send SET_PACKAGE_SIZE to the camera and wait for an ACK*/
  if ( send_command_get_ack ( camera_desc, & set_pkg_size ) == FALSE )
    {
      free ( buffer );
      return NULL; /*Fail if no ACK was received*/
    }

  /*Send SNAPSHOT to the camera and wait for an ACK*/
  if ( send_command_get_ack ( camera_desc, & snap ) == FALSE )
    {
      free ( buffer );
      return NULL; /*Fail if no ACK was received*/
    }

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             buffer, 
                             3 * CMD_SIZE, 
                             0 );
  /*Send GET_PICTURE*/
  send_command ( camera_desc, & get_pic );
  /*Delay before next attempt*/
  at91_wait_open ( & wait_desc );
  status = at91_usart_get_status ( camera_desc->usart_desc );
  
  /*Check if something was received*/                                           
  if ( status & US_RXRDY ) 
    {
      /*Try to get the frames*/
      if ( get_frame ( buffer, & rec_ack, 3 * CMD_SIZE, 1 )
	   && get_frame (buffer, & rec_data, 3 * CMD_SIZE, 2 ) )
	{
	  if ( rec_ack.command == ACK 
	       && rec_ack.param1 == GET_PICTURE 
	       && rec_data.command == DATA )
	    {
	      /*Make a new buffer */
	      free ( buffer );
	      buffer = malloc ( pkg_size );
	      memset( buffer, 0, pkg_size );

	      /*Make the picture buffer*/
	      pic_length = (u_int) ( ( rec_data.param4 << 16 ) |
				     ( rec_data.param3 << 8 ) |
				     rec_data.param2 );
	      picture_buffer = malloc ( pic_length );
	      memset ( picture_buffer, 0, pic_length );

	      /*Calculate number of packages to receive*/
	      num_pkg = pic_length / ( pkg_size - 6 );

	      /*Get the image data*/
	      while ( pkg_count < num_pkg )
		{
		  /*Set up the receive buffer*/
		  at91_usart_receive_frame ( camera_desc->usart_desc, 
					     buffer, 
					     pkg_size, 
					     0 );	 
		  
		  /*calculate next package to receive*/
		  ack.param3 = (char) ( pkg_count & 0xFF );
		  ack.param4 = (char) ( (pkg_count & 0xFF00 ) >> 8 );
		  
		  /*Request the next package*/
		  send_command ( camera_desc, & ack );
		  at91_wait_open ( & wait_desc );

		  status = at91_usart_get_status ( camera_desc->usart_desc );

		  /*Did not get a frame in time*/
		  if ( status & US_RXRDY == 0 )
		    {
		      free ( buffer );
		      free ( picture_buffer );
		      return NULL;
		    }

		  if ( extract_pic_pkg ( buffer, picture_buffer, pkg_size, 
					 pic_length, pkg_count ) )
		    {
		      pkg_count++;
		    }
		}
	      free( buffer );
	      return picture_buffer;
	    }
	}
    }
  free ( buffer );
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
 * acknowledge that they were received before proceeding.  This function tries
 * sending these commands several times and checking for ACK to be received.
 * Returns TRUE or FALSE based on success.
 */
u_int send_command_get_ack ( CameraDesc * camera_desc, 
			     CommandFrame * frame )
{
  char * buffer;
  u_int status, i, return_val = FALSE;
  CommandFrame ack = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };

  /*Set clock for wait function*/
  wait_desc.mcki_khz = CLOCK; /*clock speed: 32kHz*/
  wait_desc.period = DELAY; /*time between transmissions: 1s*/

  /*Create the buffer*/
  buffer = malloc ( 2 * CMD_SIZE ); /*oversized buffer in case of offset*/
  memset ( buffer, 0, 2 * CMD_SIZE );

  /*Set up the receive buffer*/
  at91_usart_receive_frame ( camera_desc->usart_desc, 
                             buffer, 
                             2 * CMD_SIZE, 
                             0 );
  /*Attempt to send command several times*/
  for ( i = 0 ; i < CMD_ATTEMPTS ; i++)
    {
      /*Send command*/
      send_command ( camera_desc, frame );
      /*Delay before checking*/
      at91_wait_open ( & wait_desc );
      /*Check if a frame was received*/
      status = at91_usart_get_status ( camera_desc->usart_desc );

      if ( status & US_RXRDY )
	{
	  /*Try to get a frame from the buffer*/
	  if ( get_frame ( buffer, & ack, 2 * CMD_SIZE, 1 ) )
	    {
	      /*Check if frame was an ACK*/
	      if ( ack.command == ACK && ack.param1 == frame->command )
		{
		  return_val = TRUE;
		  break;
		}
	    }
	}
    }
  free ( buffer );
  return return_val;
}

/*Extracts the picture data from the camera data package and stores it in the
 * picture buffer according to the package number.  Returns TRUE if the checksum
 * passes and the package number matches,and FALSE otherwise.
 */
u_int extract_pic_pkg ( char * buffer,
			char * pic_buffer,
			u_int pkg_size,
			u_int pic_length,
			u_int pkg_number )
{
  char pkg_number_low, pkg_number_high;
  u_int data_size, checksum = 0, checksum_index, i, pic_offset;

  pkg_number_low = (char) ( pkg_number & 0xFF );
  pkg_number_high = (char) ( ( pkg_number & 0xFF00 ) >> 8 );

  if ( pkg_number_low != buffer[0] || pkg_number_high != buffer[1] )
    {
      return FALSE;
    }
  data_size = (u_int) ( buffer[2] | ( buffer[3] << 8 ) );

  checksum_index = data_size + 3;

  for ( i = 0 ; i < checksum_index ; i++ )
    {
      checksum += buffer[i];
    }

  if ( (char) ( checksum & 0xFF ) != buffer[checksum_index] )
    {
      return FALSE;
    }

  pic_offset = pkg_number * ( pkg_size - 6 );
  for ( i = 4 ; i < checksum_index ; i++ )
    {
      pic_buffer [ i - 3 + pic_offset ] = buffer[i];
    }
  return TRUE;
}
