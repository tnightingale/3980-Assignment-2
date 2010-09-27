#include "Main.h"

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow) {
	HWND     hwnd;
	MSG      Msg;
    TCHAR    szAppName[] = TEXT("Dumb Terminal - Command Mode");
    WNDCLASS wndclass ;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = WndProc; 
    wndclass.cbClsExtra    = sizeof(PCPARAMS);
    wndclass.cbWndExtra    = 0;
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
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	while (GetMessage (&Msg, NULL, 0, 0))
	{
   		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}

	return Msg.wParam;
}
