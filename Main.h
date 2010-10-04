#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>

typedef struct _common_params_ {
    HANDLE   hComm;	
    BOOL     connectMode;
    HANDLE   thread;
    PTCHAR   buffer;
    UINT     numChars;
    UINT     maxChars;
} *PCPARAMS, CPARAMS;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
#endif
