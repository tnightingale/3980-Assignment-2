#include "Main.h"
#include "MainMenu.h"

/*
Returns TRUE if connectMode is being entered 
*/

BOOL MainMenu(HWND hwnd, HANDLE *hComm, UINT param) {
        COMMCONFIG	cc;

		switch (param) {
            case IDM_COM1:
                if (!OpenConnection(hwnd, hComm, TEXT("COM1"))) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return FALSE;
				
            case IDM_COM2:
                if (!OpenConnection(hwnd, hComm, TEXT("COM2"))) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return FALSE;

            case IDM_COM3:
                if (!OpenConnection(hwnd, hComm, TEXT("COM3"))) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return FALSE;
				
            case IDM_COM4:
                if (!OpenConnection(hwnd, hComm, TEXT("COM4"))) {
                    MessageBox (NULL, TEXT("Error setting up com port"), TEXT(""), MB_OK);
                }
                return FALSE;

            case IDM_HELP:
                MessageBox(hwnd,TEXT("How to use this program: "),TEXT("Help"), MB_OK);
                return FALSE;
        
            case IDM_CONNECT:
                SetWindowText(hwnd,TEXT("Dumb Terminal - Connect Mode"));
                return TRUE;
        }
        // Menu item not handled by the function or encountered an error
        return FALSE;
}
