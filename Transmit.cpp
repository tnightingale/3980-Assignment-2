#include "Main.h"

BOOL Transmit(HWND hwnd, TCHAR transmitChar, PCPARAMS cp) {
    DWORD written;
    if (!WriteFile(cp->hComm, &transmitChar, 1, &written ,NULL)) {
        MessageBox (NULL, TEXT("Can't send"), TEXT(""), MB_OK);
        return FALSE;
    }
    return TRUE;
}
