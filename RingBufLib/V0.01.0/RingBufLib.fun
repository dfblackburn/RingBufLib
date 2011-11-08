(********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: RingBufLib.fun
 * Author: David Blackburn
 * Created: November 04, 2011
 ********************************************************************
 * Functions and function blocks of library RingBufLib
 ********************************************************************)

FUNCTION rngbuf_Init : UINT (*Initialize the ring buffer. MUST BE CALLED IN INIT ROUTINE.*)
	VAR_IN_OUT
		t : RingBuffer_typ; (*RingBuffer object*)
	END_VAR
END_FUNCTION

FUNCTION rngbuf_Reset : UINT (*Reset the ring buffer to the newly initialized state*)
	VAR_IN_OUT
		t : RingBuffer_typ; (*RingBuffer object*)
	END_VAR
END_FUNCTION

FUNCTION rngbuf_Write : UINT (*Add an entry to the ring buffer*)
	VAR_INPUT
		pEntry : UDINT; (*Pointer to the entry to add to the ring buffer*)
		EntrySize : UDINT; (*Size of the entry to add to the ring buffer. Added as check value. Must match RingBuffer.IN.CFG.EntrySize*)
	END_VAR
	VAR_IN_OUT
		t : RingBuffer_typ; (*RingBuffer object*)
	END_VAR
END_FUNCTION

FUNCTION rngbuf_Read : UINT (*Read entries from the ring buffer*)
	VAR_INPUT
		pDest : UDINT; (*Destination address*)
		MaxDataLength : UDINT; (*Maximum amount of data to copy [bytes]*)
		StartingIndex : UDINT; (*Number of entries before most recent to start reading. 0 implies newest entries. 10 implies 10 entries before the newest entry*)
		NumEntries : UDINT; (*Number of entries to copy [entries]. Limited to RingBuffer.OUT.STAT.NumEntries*)
	END_VAR
	VAR_IN_OUT
		t : RingBuffer_typ; (*RingBuffer object*)
	END_VAR
END_FUNCTION
