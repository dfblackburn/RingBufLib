(********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: RingBufLib
 * File: RngBuf_Err.typ
 * Author: David Blackburn
 * Created: November 04, 2011
 ********************************************************************
 * Data types of library RingBufLib
 ********************************************************************)

TYPE
	RNGBUF_WARN_enum : 
		(
		RNGBUF_WARN_MAXDATALENGTH := 500,
		RNGBUF_WARN_
		);
	RNGBUF_ERR_enum : 
		(
		RNGBUF_ERROR := 1000,
		RNGBUF_ERR_BADCFG,
		RNGBUF_ERR_MEMALLOC,
		RNGBUF_ERR_INVALIDINPUT,
		RNGBUF_ERR_BUFFNOTINIT,
		RNGBUF_ERR_CORRUPTBUFFER,
		RNGBUF_ERR_
		);
END_TYPE
