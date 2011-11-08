/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: rngbuf_Reset.c
 * Author: David Blackburn
 * Created: November 07, 2011
 ********************************************************************
 * Implementation of library RingBufLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

	#include "RingBufLib.h"

#ifdef __cplusplus
};
#endif


#include <string.h>


/********************************************************************/
/* Reset the ring buffer to the newly initialized state 			*/
/********************************************************************/


/* Check for null pointer		DONE and TESTED DFB 20111107 */
/* Check RingBuffer				DONE and TESTED DFB 20111107 */
/* Reset buffer					DONE and TESTED DFB 20111107 */


unsigned short rngbuf_Reset(struct RingBuffer_typ* t)
{
	
	
/************************************************/
/* Check for invalid input						*/
/************************************************/

if( t == 0 ){

	return (UINT)RNGBUF_ERR_INVALIDINPUT;
	
} /* Check for null pointer */


/************************************************/
/* Check for invalid buffer						*/
/************************************************/

if( 	(t->IN.CFG.EntrySize == 0)
	||	(t->IN.CFG.MaxEntries == 0)
	||	!(t->OUT.STAT.Initialized)
	||	(t->Internal.pStart == 0)
	||	(t->Internal.BufferLength == 0)
	){
		
	return (UINT)RNGBUF_ERR_BUFFNOTINIT;
	
} /* Check for bad buffer */


/************************************************/
/* Reset buffer									*/
/************************************************/

/* Reset internals */

memset( (void*)t->Internal.pStart, 0, t->Internal.BufferLength );

t->Internal.iWrite=			0;
t->Internal.iOldestEntry=	0;


/* Set STAT */

t->OUT.STAT.NumEntries=		0;

return 0;
	

} // end fn //
