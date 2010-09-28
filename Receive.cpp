#include "Main.h"
#include <tchar.h>

UINT Receive(LPVOID params) {
    TCHAR buffer = NULL;
    DWORD read;
    PCPARAMS cp = (PCPARAMS) params;

    while(cp->connectMode) {
        if(ReadFile(cp->hComm, &buffer, 1, &read, NULL)) {
            if (buffer != NULL) {
                _stprintf(cp->buffer, TEXT("%s%c"), cp->buffer, buffer);
            }
        } else {
            MessageBox (NULL, TEXT("Error reading file"), TEXT(""), MB_OK);
        }
        buffer = NULL;
        // Sleep to prevent hogging CPU time
        Sleep(10);
    }

    return 0;
}
