#include "Main.h"
#include <tchar.h>

UINT Receive(LPVOID params) {
    TCHAR buffer = NULL;
    DWORD read;
    PCPARAMS cp = (PCPARAMS) params;

    while(cp->connectMode) {
        if(ReadFile(cp->hComm, &buffer, 1, &read, NULL)) {
            if (buffer != NULL) {
                AddData(buffer, cp);
            }
        } else {
            MessageBox (NULL, TEXT("Error reading file"), TEXT(""), MB_OK);
        }
        buffer = NULL;

        // prevent this thread from hogging CPU time
        Sleep(10);
    }

    return 0;
}
