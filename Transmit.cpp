#include "Main.h"

BOOL Transmit(HWND hwnd, HANDLE hComm, TCHAR transmitChar) {
    DWORD written;
    if (!WriteFile(hComm, &transmitChar, 1, &written ,NULL)) {
        MessageBox (NULL, TEXT("Can't send"), TEXT(""), MB_OK);
        return FALSE;
    }
    return TRUE;
}
