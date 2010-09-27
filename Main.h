#ifndef MAIN_H
#define MAIN_H
    #include <Windows.h>
    LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
    BOOL MainMenu(HWND hwnd, HANDLE *hComm, UINT param);
    BOOL Transmit(HWND hwnd, HANDLE hcomm, TCHAR transmitChar);
    UINT Receive(PVOID);
    HANDLE CreateConnection(LPCTSTR);
    BOOL PrepareConnection(HANDLE, DCB);
    BOOL OpenConnection(HWND hwnd, HANDLE *hComm, LPCTSTR szPortName);

    typedef struct threadParams {
        HANDLE* hComm;
        TCHAR** buffer;
        BOOL* connectMode;
    } *PPARAMS, PARAMS;

    typedef struct commonParams {
        HANDLE hComm;	
        BOOL   connectMode;
        TCHAR  *buffer;
        HANDLE thread;
        UINT   cxClient;
        UINT   cyClient;
    } *PCPARAMS, CPARAMS;

#endif
