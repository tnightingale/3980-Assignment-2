#include "Main.h"
#include "MenuItems.h"
#include "Transmit.h"
#include "Receive.h"
#include "Buffer.h"

/************************************************************************
* SOURCE FILE : WndProc.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
*                    HWND hwnd     - A handle to the window
*                    UINT Message  - The message to handle
*                    WPARAM wParam - wParam parameters
*                    LPARAM lParam - lParam parameters
* RETURNS     : LRESULT
* DATE        : September 27, 2010a
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* The WndProc for the terminal program, all messages are handled here
*************************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    PCPARAMS    cp;
    HDC         hdc;
    PAINTSTRUCT ps;

    switch (Message)
	{

    case WM_COMMAND:
        cp = (PCPARAMS)GetWindowLongPtr(hwnd, 0);
        if (cp->connectMode) {
            MessageBox(NULL, TEXT("Unable to change settings while in Connect Mode, press ESC to return to Command Mode"), TEXT(""), MB_OK);
            return 0;
        }
        MainMenu(hwnd, LOWORD (wParam), cp);
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
            if(!Transmit(wParam, cp)) {
                MessageBox (NULL, TEXT("Error sending data"), TEXT(""), MB_OK);
                return 0;
            }
        }
        return 0;

    case WM_PAINT:
        cp = (PCPARAMS) GetWindowLongPtr(hwnd,0);
        hdc = BeginPaint(hwnd, &ps);

        DisplayData(hwnd, hdc, cp);

        EndPaint(hwnd,&ps);
        return 0;

    case WM_DESTROY:
        cp = (PCPARAMS) GetWindowLongPtr(hwnd,0);
      	PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc(hwnd, Message, wParam, lParam);
}
