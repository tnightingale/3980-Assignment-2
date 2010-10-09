#include "Main.h"
#include "Buffer.h"

/************************************************************************
* SOURCE FILE : Receive.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : VOID Receive(LPVOID params)
*                    LPVOID params   - PCPARAMS struct containing all the data needed to read from an
*                                      open file and record the data to a buffer
* RETURNS     : VOID
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function is spawned as a thread which runs until Connect Mode is ended.
* It polls the device until it finds a character and then calls AddData() to 
* add it into the output.
*************************************************************************/
/*
VOID Receive(LPVOID params) {
    TCHAR buffer = NULL;
    DWORD read;
    PCPARAMS cp = (PCPARAMS) params;

    while(cp->connectMode) {
        if(ReadFile(cp->hComm, &buffer, 1, &read, NULL)) {
            if (buffer != NULL) {
                AddData(buffer, cp);
            }
        } else {
            continue;
        }
        buffer = NULL;
    }

    return;
}
*/

VOID Receive(LPVOID params) {
TCHAR inbuff[128];
DWORD nBytesRead, dwEvent, dwError;
COMSTAT cs;
PCPARAMS cp = (PCPARAMS) params;

	/* generate event whenever a byte arives */
	SetCommMask (cp->hComm, EV_RXCHAR);
	
	/* read a byte whenever one is received */
	while (cp->connectMode) {
		/* wait for event */
		if (WaitCommEvent (cp->hComm, &dwEvent, NULL)){
			/* read all available bytes */
			ClearCommError (cp->hComm, &dwError, &cs);
			if ((dwEvent & EV_RXCHAR) && cs.cbInQue) {
				if (!ReadFile(cp->hComm, inbuff, cs.cbInQue, &nBytesRead, NULL)){
					/* handle error */
				} /* end if (error reading bytes) */
				else {
					if (nBytesRead) {
						AddMultiData(inbuff, nBytesRead, cp);//Add nBytesRead to the input buffer
					}
				}
			}
		} else {
			// other error
		}
	} /* end while (reading bytes in loop) */
	/* clean out any pending bytes in the receive buffer */
	PurgeComm(cp->hComm, PURGE_RXCLEAR);
}
