#include "Main.h"
#include <tchar.h>

UINT Receive(LPVOID params) {
    TCHAR buffer = NULL;
    DWORD read;
    Pparams tp = (Pparams) params;

    while(*tp->connectMode) {
        if(ReadFile(*tp->hComm, &buffer, sizeof(TCHAR), &read, NULL)) {
            if (buffer != NULL) {
                _stprintf(*tp->buffer, TEXT("%s%c"), *tp->buffer, buffer);
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
