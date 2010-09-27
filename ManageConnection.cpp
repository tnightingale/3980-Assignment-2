#include "Main.h"

HANDLE CreateConnection(LPCTSTR szPortName) {
    return CreateFile (szPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

BOOL PrepareConnection(HANDLE hComm, DCB config) {
    COMMTIMEOUTS comTimeOut;

    comTimeOut.ReadIntervalTimeout = 1;
    comTimeOut.ReadTotalTimeoutMultiplier = 1;
    comTimeOut.ReadTotalTimeoutConstant = 1;
    comTimeOut.WriteTotalTimeoutMultiplier = 1;
    comTimeOut.WriteTotalTimeoutConstant = 1;

    if (!SetCommTimeouts(hComm,&comTimeOut)) {
        MessageBox (NULL, TEXT("Error setting up timeouts"), TEXT(""), MB_OK);
    }
    if (SetCommState(hComm, &config) == 0) {
        MessageBox (NULL, TEXT("Can't set Comm settigs"), TEXT(""), MB_OK);
        return FALSE;
    }

    return TRUE;
}

BOOL OpenConnection(HWND hwnd, HANDLE *hComm, LPCTSTR szPortName) {
    COMMCONFIG	cc;

    cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 1;
	GetCommConfig (*hComm, &cc, &cc.dwSize);
    if (!CommConfigDialog(szPortName, hwnd, &cc)) {
        return FALSE;
    }
    if ((*hComm = CreateConnection(szPortName)) == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    if (!PrepareConnection(*hComm, cc.dcb) ) {
        return FALSE;
    }
    return TRUE;
}
