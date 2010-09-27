#include "Main.h"
#include <tchar.h>

LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    static HANDLE hComm;	
    static BOOL   connectMode = FALSE;
    static TCHAR  *buffer = (TCHAR*) calloc(1024, sizeof(TCHAR));
    static HANDLE thread;
    static UINT   cxClient = 600;
    static UINT   cyClient = 400;

    PCPARAMS    commonParams;
    HDC         hdc;
    PAINTSTRUCT ps;
    PPARAMS     threadParams;

    TEXTMETRIC  tm;

    switch (Message)
	{
    case WM_CREATE:
        commonParams = (PCPARAMS)malloc(sizeof(CPARAMS));
        SetWindowLongPtr(hwnd, 0, (LONG) commonParams);
        return 0;

    case WM_COMMAND:
        if (connectMode) {
            MessageBox(NULL, TEXT("Unable to change settings while in Connect Mode, press ESC to return to Command Mode"), TEXT(""), MB_OK);
            return 0;
        }
        if (MainMenu(hwnd, &hComm, LOWORD (wParam))) {
            connectMode = TRUE;
            threadParams = (PPARAMS)malloc(sizeof(PARAMS));
            threadParams->hComm = &hComm;
            threadParams->buffer = &buffer;
            threadParams->connectMode = &connectMode;
            if ((thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receive, threadParams, 0, NULL)) == NULL) {
                MessageBox (NULL, TEXT("Error loading recesive thread"), TEXT(""), MB_OK);
                return 0;
            }
        }
        return 0;

    case WM_CHAR:
        commonParams = (PCPARAMS) GetWindowLongPtr(hwnd,0);
        if (connectMode) {
            if(VK_ESCAPE == wParam) {
                SetWindowText(hwnd, TEXT("Dumb Terminal - Command Mode"));
                CloseHandle(hComm);
                commonParams->connectMode = FALSE;
                return 0;
            }
            if(!Transmit(hwnd,hComm, wParam)) {
                MessageBox (NULL, TEXT("Error sending data"), TEXT(""), MB_OK);
                return 0;
            }
            _stprintf(buffer,TEXT("%s%c"), buffer, wParam);
            InvalidateRect(hwnd,NULL,TRUE);
        }
        return 0;

    case WM_SIZE:
        cxClient = LOWORD (lParam);
        cyClient = HIWORD (lParam);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));
        GetTextMetrics(hdc, &tm);

        for(int i = 0; i < 1024 / (cxClient / tm.tmAveCharWidth); i++) {
            TextOut(hdc, 0, i * tm.tmHeight, buffer + (i * cxClient / tm.tmAveCharWidth), (cxClient / tm.tmAveCharWidth));
        }

        EndPaint(hwnd,&ps);
        return 0;

    case WM_DESTROY:
        CloseHandle(hComm);
      	PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc(hwnd, Message, wParam, lParam);
}
