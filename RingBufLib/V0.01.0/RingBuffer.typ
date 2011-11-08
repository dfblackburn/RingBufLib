(********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: RingBuffer.typ
 * Author: David Blackburn
 * Created: November 04, 2011
 ********************************************************************
 * Data types of library RingBufLib
 ********************************************************************)

TYPE
	RingBuffer_Internal_typ : 	STRUCT 
		pStart : UDINT;
		BufferLength : UDINT;
		iWrite : UDINT;
		iOldestEntry : UDINT;
		iMax : UDINT;
	END_STRUCT;
	RingBuffer_OUT_STAT_typ : 	STRUCT 
		Initialized : BOOL;
		NumEntries : UDINT;
	END_STRUCT;
	RingBuffer_OUT_typ : 	STRUCT 
		STAT : RingBuffer_OUT_STAT_typ;
	END_STRUCT;
	RingBuffer_IN_CFG_typ : 	STRUCT 
		EntrySize : UDINT;
		MaxEntries : UDINT;
	END_STRUCT;
	RingBuffer_IN_typ : 	STRUCT 
		CFG : RingBuffer_IN_CFG_typ;
	END_STRUCT;
	RingBuffer_typ : 	STRUCT 
		IN : RingBuffer_IN_typ;
		OUT : RingBuffer_OUT_typ;
		Internal : RingBuffer_Internal_typ;
	END_STRUCT;
END_TYPE
