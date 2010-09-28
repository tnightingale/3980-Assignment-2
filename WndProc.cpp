#include "Main.h"
#include <tchar.h>

LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    PCPARAMS    cp;
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        windowRect;
    TEXTMETRIC  tm;
    size_t      i;
    UINT        printableChars;

    switch (Message)
	{

    case WM_COMMAND:
        cp = (PCPARAMS)GetWindowLongPtr(hwnd, 0);
        if (cp->connectMode) {
            MessageBox(NULL, TEXT("Unable to change settings while in Connect Mode, press ESC to return to Command Mode"), TEXT(""), MB_OK);
            return 0;
        }
        if (MainMenu(hwnd, LOWORD (wParam), cp)) {
            cp->connectMode = TRUE;
            if ((cp->thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receive, cp, 0, NULL)) == NULL) {
                MessageBox (NULL, TEXT("Error loading recesive thread"), TEXT(""), MB_OK);
                return 0;
            }
        }
        return 0;

    case WM_CHAR:
        cp = (PCPARAMS) GetWindowLongPtr(hwnd,0);
        if (cp->connectMode) {
            if(VK_ESCAPE == wParam) {
                SetWindowText(hwnd, TEXT("Dumb Terminal - Command Mode"));
                CloseHandle(cp->hComm);
                cp->connectMode = FALSE;
                return 0;
            }
            if(!Transmit(hwnd, wParam, cp)) {
                MessageBox (NULL, TEXT("Error sending data"), TEXT(""), MB_OK);
                return 0;
            }
        }
        return 0;

    case WM_PAINT:
        cp = (PCPARAMS) GetWindowLongPtr(hwnd,0);
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));
        GetTextMetrics(hdc, &tm);
        GetClientRect(hwnd, &windowRect);
        for(i = 0; i <= cp->numChars / (windowRect.right / tm.tmAveCharWidth); i++) {
            if (i * (windowRect.right / tm.tmAveCharWidth) + (windowRect.right / tm.tmAveCharWidth) >= cp->maxChars) {
                printableChars = cp->maxChars - i * (windowRect.right / tm.tmAveCharWidth);
                TextOut(hdc, 0, i * tm.tmHeight, cp->buffer + (i * windowRect.right / tm.tmAveCharWidth), printableChars);
            } else {
                TextOut(hdc, 0, i * tm.tmHeight, cp->buffer + (i * windowRect.right / tm.tmAveCharWidth), (windowRect.right / tm.tmAveCharWidth));
            }
        }

        EndPaint(hwnd,&ps);
        return 0;

    case WM_DESTROY:
        cp = (PCPARAMS) GetWindowLongPtr(hwnd,0);
      	PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc(hwnd, Message, wParam, lParam);
}
