#include "Main.h"
#include "MainMenu.h"
#include "ManageConnection.h"
#include "Receive.h"

/************************************************************************
* SOURCE FILE : MenuItems.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : VOID MainMenu(HWND hwnd, UINT param, PCPARAMS cp)
*                    HWND hwnd     - Handle to the window, needed to launch dialog boxes from functions called
*                    UINT param    - The `LOWORD (wParam)` from the WM_COMMAND message
*                    PCPARAMS cp   - structure containing a HANDLE to the communication device, needed for functions called from the menu
* RETURNS     : VOID
* DATE        : September 27, 2010
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function handles all of the menu items, setting which port to use and configure its settings as
* well as entering connect mode.
*************************************************************************/
VOID MainMenu(HWND hwnd, UINT param, PCPARAMS cp) {
        COMMCONFIG	cc;

		switch (param) {
            case IDM_COM1:
                if (!OpenConnection(hwnd, TEXT("COM1"), cp)) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return;
				
            case IDM_COM2:
                if (!OpenConnection(hwnd, TEXT("COM2"), cp)) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return;

            case IDM_COM3:
                if (!OpenConnection(hwnd, TEXT("COM3"), cp)) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return;
				
            case IDM_COM4:
                if (!OpenConnection(hwnd, TEXT("COM4"), cp)) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return;

            case IDM_HELP:
                MessageBox(hwnd,TEXT("How to use this program: "),TEXT("Help"), MB_OK);
                return;
        
            case IDM_CONNECT:
                SetWindowText(hwnd,TEXT("Dumb Terminal - Connect Mode"));
                cp->connectMode = TRUE;
                if ((cp->thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receive, cp, 0, NULL)) == NULL) {
                    MessageBox (NULL, TEXT("Error loading receive thread"), TEXT(""), MB_OK);
                    return;
                }
                return;
        }

        return ;
}
