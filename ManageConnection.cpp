#include "Main.h"

/************************************************************************
* SOURCE FILE : ManageConnections.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : HANDLE CreateConnection(LPCTSTR szPortName)
*                    LPCSTR szPortName - Port name to open a connection to
* RETURNS     : A HANDLE to the COM port
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function opens a file with basic read and write access to the specified serial port.
*************************************************************************/
HANDLE CreateConnection(LPCTSTR szPortName) {
    return CreateFile (szPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

/************************************************************************
* SOURCE FILE : ManageConnections.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : BOOL PrepareConnection(HANDLE hComm, DCB config)
*                    HANDLE hComm - A handle to the COM port to prepare a connection to
*                    DCB config   - DCB struct with settings already set
* RETURNS     : TRUE on success, FALSE on failure
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function prepares a COM port to be opened by setting the timeouts and 
* applying the specified DCB settings. 
*************************************************************************/
BOOL PrepareConnection(HANDLE hComm, DCB config) {
    COMMTIMEOUTS comTimeOut;
    GetCommTimeouts(hComm, &comTimeOut);
    comTimeOut.ReadIntervalTimeout = MAXDWORD;
    comTimeOut.ReadTotalTimeoutMultiplier = 0;
    comTimeOut.ReadTotalTimeoutConstant = 0;
    comTimeOut.WriteTotalTimeoutMultiplier = 10;
    comTimeOut.WriteTotalTimeoutConstant = 1000;

    if (!SetCommTimeouts(hComm,&comTimeOut)) {
        MessageBox (NULL, TEXT("Error setting up timeouts"), TEXT(""), MB_OK);
        return FALSE;
    }
    if (!SetCommState(hComm, &config)) {
        MessageBox (NULL, TEXT("Can't set Comm settigs"), TEXT(""), MB_OK);
        return FALSE;
    }

    return TRUE;
}

/************************************************************************
* SOURCE FILE : ManageConnections.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : BOOL OpenConnection(HWND hwnd, LPCTSTR szPortName, PCPARAMS cp)
*                    HWND hwnd         - Handle to the window, used to launch a dialog box
*                    LPCSTR szPortName - Port name to open a connection to
*                    PCPARAMS cp       - structure containing a HANDLE to the communication device
* RETURNS     : TRUE on success, FALSE on failure
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function begings opening a connection to the specified serial port.
* It launches a dialog box on the specified port for additional settings for the port.
*************************************************************************/
BOOL OpenConnection(HWND hwnd, LPCTSTR szPortName, PCPARAMS cp) {
    COMMCONFIG	cc;

    cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 1;
	GetCommConfig (cp->hComm, &cc, &cc.dwSize);
    if (!CommConfigDialog(szPortName, hwnd, &cc)) {
        return FALSE;
    }
    if ((cp->hComm = CreateConnection(szPortName)) == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    if (!PrepareConnection(cp->hComm, cc.dcb) ) {
        return FALSE;
    }
    return TRUE;
}
