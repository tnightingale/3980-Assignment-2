#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>

typedef struct _common_params_ {
    HANDLE  hComm;	
    BOOL    connectMode;
    TCHAR   *buffer;
    UINT    numChars;
    HANDLE  thread;
} *PCPARAMS, CPARAMS;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL MainMenu(HWND hwnd, UINT param, PCPARAMS cp);
BOOL Transmit(HWND hwnd, TCHAR transmitChar, PCPARAMS cp);
UINT Receive(PVOID);
HANDLE CreateConnection(LPCTSTR);
BOOL PrepareConnection(HANDLE, DCB);
BOOL OpenConnection(HWND hwnd, LPCTSTR szPortName, PCPARAMS cp);
#endif
