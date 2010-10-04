#include "Main.h"
#include "Buffer.h"

/************************************************************************
* SOURCE FILE : Transmit.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : BOOL Transmit(TCHAR transmitChar, PCPARAMS cp)
*                    TCHAR transmitChar - Character to send over the serial connection
*                    PCPARAMS cp        - structure containing the handle to the communication device
* RETURNS     : TRUE on success, FALSE on failure
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function transmits a single character over an established serial connection. If
* it encountered no errors it returns TRUE otherwise it returns FALSE.
*************************************************************************/
BOOL Transmit(TCHAR transmitChar, PCPARAMS cp) {
    DWORD written;
    if (!WriteFile(cp->hComm, &transmitChar, 1, &written ,NULL)) {
        return FALSE;
    }
    AddData(transmitChar, cp);
    return TRUE;
}
