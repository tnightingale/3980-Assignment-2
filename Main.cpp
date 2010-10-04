/************************************************************************
* SOURCE FILE : Main.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTIONS   : 
*        LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
*        VOID MainMenu(HWND hwnd, UINT param, PCPARAMS cp);
*        BOOL Transmit(TCHAR transmitChar, PCPARAMS cp);
*        VOID Receive(PVOID);
*        HANDLE CreateConnection(LPCTSTR);
*        BOOL PrepareConnection(HANDLE, DCB);
*        BOOL OpenConnection(HWND hwnd, LPCTSTR szPortName, PCPARAMS cp);
*        VOID AddData(TCHAR newData, PCPARAMS cp);
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
*
* This program creates a connection over a serial cable connected to COM1 -> COM4.
* The program operates in 2 different modes, Command Mode and Connect Mode.
*
* Command Mode is for setting up a connection and managing the various settings
* related to a serial port. No communication is done while in Command Mode.
*
* Connect Mode is where the serial communication takes place, no settings are
* allowed to be changed while in this mode. The <ESC> key returns the user to
* Command Mode.
*
* While in Connect Mode any character typed or recieved from the connected peer is
* displayed onto the window.
*
*************************************************************************/

#include "Main.h"

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow) {
	HWND     hwnd;
	MSG      Msg;
    TCHAR    szAppName[] = TEXT("Dumb Terminal - Command Mode");
    WNDCLASS wndclass ;
    CPARAMS *cp;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = WndProc; 
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = sizeof(PCPARAMS);
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);     
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);         
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName  = TEXT("MainMenu");
	
	if (!RegisterClass (&wndclass))
		return 0;

	hwnd = CreateWindow (szAppName, szAppName, WS_OVERLAPPEDWINDOW, 10, 10,
   							600, 400, NULL, NULL, hInst, NULL);
    
    cp = (PCPARAMS)malloc(sizeof(CPARAMS));
    cp->maxChars = 1;
    cp->numChars = 0;
    cp->buffer = (TCHAR*) malloc(cp->maxChars * sizeof(TCHAR));
    cp->buffer[0] = ' ';
    cp->connectMode = FALSE;
    SetWindowLongPtr(hwnd, 0, (LONG) cp);
    
    ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);



	while (GetMessage (&Msg, NULL, 0, 0))
	{
   		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}

	return Msg.wParam;
}
