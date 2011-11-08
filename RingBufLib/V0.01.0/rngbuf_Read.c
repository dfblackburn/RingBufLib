/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: rngbuf_Read.c
 * Author: David Blackburn
 * Created: November 08, 2011
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
/* Read entries from the ring buffer 								*/
/********************************************************************/


/* Check for invalid inputs		DONE and TESTED DFB 20111108 */
	/* Null pointer				DONE and TESTED DFB 20111108 */
	/* Others					DONE and TESTED DFB 20111108 */
	
/* Check RingBuffer				DONE and TESTED DFB 20111108 */

/* Limit parameters				DONE and TESTED DFB 20111108 */
	/* NumEntries				DONE and TESTED DFB 20111108 */
	/* MaxDataLength			DONE and TESTED DFB 20111108 */
	/* StartingIndex			DONE and TESTED DFB 20111108 */

/* Copy data					DONE and TESTED DFB 20111108 */
	/* No wraparound			DONE and TESTED DFB 20111108 */
	/* Wraparound				DONE and TESTED DFB 20111108 */


unsigned short rngbuf_Read(	unsigned long pDest, 
							unsigned long MaxDataLength, 
							unsigned long StartingIndex, 
							unsigned long NumEntries, 
							struct RingBuffer_typ* t)
{


/************************************************/
/* Check for invalid input						*/
/************************************************/

if( 	(pDest == 0)
	||	(t == 0)
	){
		
	return (UINT)RNGBUF_ERR_INVALIDINPUT;
	
} /* Check for null pointer */


if( MaxDataLength == 0 ){

	return (UINT)RNGBUF_ERR_INVALIDINPUT;
	
} /* Check for other bad inputs */


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
/* Set parameters to nice values				*/
/************************************************/


/* Limit NumEntries based on t->OUT.STAT.NumEntries */

if( NumEntries > t->OUT.STAT.NumEntries ){
	
	NumEntries=	t->OUT.STAT.NumEntries;
	
}


/* Limit NumEntries based on MaxDataLength */

BOOL	MaxDataLengthTooSmall = 0;


if( NumEntries > (MaxDataLength / t->IN.CFG.EntrySize) ){
	
	NumEntries=	MaxDataLength / t->IN.CFG.EntrySize;
	
	MaxDataLengthTooSmall=	1;
	
}


/* Set MaxDataLength to a nice value based on the properly limited NumEntries */

MaxDataLength=	NumEntries * t->IN.CFG.EntrySize;;


/* Limit StartingIndex based on t->OUT.STAT.NumEntries and NumEntries */

if( StartingIndex > (t->OUT.STAT.NumEntries - NumEntries) ){
	
	StartingIndex=	t->OUT.STAT.NumEntries - NumEntries;
	
}


/************************************************/
/* Check for Wrap around and copy data			*/
/************************************************/

UDINT	iStart,
		pDestCurr,
		CurrNumToRead;

/* Wrap around will depend on StartingIndex and NumEntries */
/* StartingIndex + NumEntries is already limited to t->OUT.STAT.NumEntries,
	so there is no danger of rollover */
	
if( (StartingIndex + NumEntries) > t->Internal.iWrite ){
	

	/* wrap around; copy high indices first, then go back to low indices */
	/* High indices */

	pDestCurr=		pDest;
	CurrNumToRead=	(StartingIndex + NumEntries) - t->Internal.iWrite;
	iStart=			(t->Internal.iMax + 1) - CurrNumToRead;
	

	/* Limit CurrNumToRead to NumEntries */
	/* Do this after setting iStart. This allows you to easily get the
		desired iStart and still not overrun the buffer */
	
	if( CurrNumToRead > NumEntries ){

		CurrNumToRead=	NumEntries;

	}


	memcpy( (void*)pDestCurr,
			(void*)t->Internal.pStart + (iStart * t->IN.CFG.EntrySize),
			CurrNumToRead * t->IN.CFG.EntrySize );

	
	/* Low indices */

	pDestCurr=		pDest + (CurrNumToRead * t->IN.CFG.EntrySize);
	CurrNumToRead=	NumEntries - CurrNumToRead;
	iStart=			0;

	memcpy( (void*)pDestCurr,
			(void*)t->Internal.pStart + (iStart * t->IN.CFG.EntrySize),
			CurrNumToRead * t->IN.CFG.EntrySize );
			
	if( MaxDataLengthTooSmall ){
		return RNGBUF_WARN_MAXDATALENGTH;
	}
	else{	
		return 0;
	}
		
} // wrap //

else{
	

	/* No need to wrap */

	pDestCurr=		pDest;
	CurrNumToRead=	NumEntries;
	iStart=			t->Internal.iWrite - StartingIndex - NumEntries;

	memcpy( (void*)pDestCurr,
			(void*)t->Internal.pStart + (iStart * t->IN.CFG.EntrySize),
			CurrNumToRead * t->IN.CFG.EntrySize );
	
	if( MaxDataLengthTooSmall ){
		return RNGBUF_WARN_MAXDATALENGTH;
	}
	else{	
		return 0;
	}
		
} // no wrap //


} // end fn //
