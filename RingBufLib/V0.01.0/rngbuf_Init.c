/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: rngbuf_Init.c
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
/* Initialize the ring buffer. MUST BE CALLED IN INIT ROUTINE. 		*/
/********************************************************************/


/* Check for null pointer		DONE and TESTED DFB 20111104 */
/* Check CFG data				DONE and TESTED DFB 20111104 */
/* Allocate memory				DONE and TESTED DFB 20111104 */
	/* Set BufferLength			DONE and TESTED DFB 20111104 */
	/* Check TMP_Alloc			DONE and TESTED DFB 20111104 */
/* Initialize buffer			DONE and TESTED DFB 20111104 */


unsigned short rngbuf_Init(struct RingBuffer_typ* t)
{


/************************************************/
/* Check for invalid input						*/
/************************************************/

if( t == 0 ){

	return (UINT)RNGBUF_ERR_INVALIDINPUT;
	
} /* Check for null pointer */


/************************************************/
/* Check for invalid CFG data					*/
/************************************************/

if( 	(t->IN.CFG.EntrySize == 0)
	||	(t->IN.CFG.MaxEntries == 0)
	){
		
		
	/* Bad CFG data */
	/* Set Buffer status */
	
	t->OUT.STAT.Initialized=	0;
	t->OUT.STAT.NumEntries=		0;

	return (UINT)RNGBUF_ERR_BADCFG;
	
	
} /* Check for bad CFG data */


/************************************************/
/* Allocate memory for buffers					*/
/************************************************/

t->Internal.BufferLength=	t->IN.CFG.EntrySize * t->IN.CFG.MaxEntries;

if( (TMP_alloc(t->Internal.BufferLength, (void **)&(t->Internal.pStart)	) != 0) ){

		
	/* Memory allocation error */
	/* Set Buffer status */
	
	t->OUT.STAT.Initialized=	0;
	t->OUT.STAT.NumEntries=		0;

	return (UINT)RNGBUF_ERR_MEMALLOC;
	

}


/* Initialize internals */

memset( (void*)t->Internal.pStart, 0, t->Internal.BufferLength );

t->Internal.iWrite=			0;
t->Internal.iOldestEntry=	0;
t->Internal.iMax=			t->IN.CFG.MaxEntries - 1;


/* Set STAT */

t->OUT.STAT.Initialized=	1;
t->OUT.STAT.NumEntries=		0;

return 0;
	

} // end fn //
