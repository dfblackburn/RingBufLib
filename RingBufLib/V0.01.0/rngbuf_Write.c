/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: rngbuf_Write.c
 * Author: David Blackburn
 * Created: November 04, 2011
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
/* Add an entry to the ring buffer	 								*/
/********************************************************************/


/* Check for invalid inputs		DONE and TESTED DFB 20111108 */
	/* Null pointer				DONE and TESTED DFB 20111108 */
	/* Others					DONE and TESTED DFB 20111108 */
	
/* Check RingBuffer				DONE and TESTED DFB 20111108 */

/* Check valid iWrite			DONE and TESTED DFB 20111107 */
/* Copy to buffer				DONE and TESTED DFB 20111107 */
/* Handle iWrite				DONE and TESTED DFB 20111107 */
/* Handle numEntries			DONE and TESTED DFB 20111107 */
/* Handle iOldestEntry			DONE and TESTED DFB 20111107 */


unsigned short rngbuf_Write(unsigned long pEntry, unsigned long EntrySize, struct RingBuffer_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( 	(pEntry == 0)
	||	(t == 0)
	){
		
	return (UINT)RNGBUF_ERR_INVALIDINPUT;
		
} // Check for null pointer //


if( 	(EntrySize != t->IN.CFG.EntrySize)
	||	(EntrySize == 0)
	){

	return (UINT)RNGBUF_ERR_INVALIDINPUT;
		
} // Check for other bad inputs //


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
/* Write to buffer								*/
/************************************************/


/* Check for valid iWrite */

if( t->Internal.iWrite > t->Internal.iMax ){
	
	return (UINT)RNGBUF_ERR_CORRUPTBUFFER;
	
}


/* iWrite is valid, copy Entry to buffer */

memcpy(	(void*)(t->Internal.pStart + t->Internal.iWrite * t->IN.CFG.EntrySize), 
		(void*)(pEntry), 
		t->IN.CFG.EntrySize );
		

/* Increment iWrite, check for wraparound */

t->Internal.iWrite++;

if( t->Internal.iWrite > t->Internal.iMax ){
	
	t->Internal.iWrite=	0;
	
}


/* Increment NumEntries, check for full buffer */

t->OUT.STAT.NumEntries++;

if( t->OUT.STAT.NumEntries > t->IN.CFG.MaxEntries ){
	
	t->OUT.STAT.NumEntries=	t->IN.CFG.MaxEntries;
	
	
	/* If the buffer is full, then the oldest entry will be the current iWrite */
	/* Set that here and check for wraparound */
	/* If wraparound, then iWrite is bad */
	
	t->Internal.iOldestEntry=	t->Internal.iWrite;
	
	if( t->Internal.iOldestEntry > t->Internal.iMax ){
		
		return (UINT)RNGBUF_ERR_CORRUPTBUFFER;
		
	} // Check iOldestEntry //

	
} // Check NumEntries //


return 0;


} // end fn //
