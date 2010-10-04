#include "Main.h"

/************************************************************************
* SOURCE FILE : Buffer.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : VOID AddData(TCHAR newData, PCPARAMS cp);
*                    TCHAR newData - A single character of new data to be added to the output array
*                    PCPARAMS cp   - Structure containing the buffer (TCHAR*), maxChars and numChars
* RETURNS     : VOID
* DATE        : September 27, 2010a
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function is called whenever a new character is typed or received.
* It checks if the buffer to store characters in is full and if it is it
* resizes it to occupy twice the original space. This function then adds
* the new character into the buffer and invalidates the window to be refreshed.
*************************************************************************/
VOID AddData(TCHAR newData, PCPARAMS cp) {
    PVOID reallocTest;
    size_t i;
    if (cp->numChars == cp->maxChars - 1) {
        reallocTest = realloc(cp->buffer,cp->maxChars * 2 * sizeof(TCHAR));
        if (reallocTest != NULL) {
            cp->buffer = (TCHAR*)reallocTest;
            cp->maxChars *= 2;
            for (i = cp->numChars + 1; i <= cp->maxChars; i++) {
                cp->buffer[i] = ' ';
            }
        } else {
            //Handle realloc failing
        }
    }
    cp->buffer[cp->numChars++] = newData;

    InvalidateRect(GetActiveWindow(), NULL, TRUE);
    return;
}

/************************************************************************
* SOURCE FILE : Buffer.cpp 
* PROGRAM     : Dumb Terminal
* FUNCTION    : VOID DisplayData(HWND hwnd, HDC hdc, PCPARAMS cp);
*                    HWND hwnd     - A handle to the window
*                    HDC hdc       - Device context to draw with
*                    PCPARAMS cp   - Common parameters, including all the data to display
* RETURNS     : VOID
* DATE        : September 27, 2010a
* REVISIONS   : None
* DESIGNER    : Nick Huber
* PROGRAMMER  : Nick Huber
* NOTES       : 
* 
* This function is called whenever the window needs to be repainted, it draws
* every character that has been received and transmitted.
*************************************************************************/
VOID DisplayData(HWND hwnd, HDC hdc, PCPARAMS cp) {
    TEXTMETRIC tm;
    RECT windowRect;
    UINT charsPerLine;
    UINT printableChars;
    size_t i;

    SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));
    GetTextMetrics(hdc, &tm);
    GetClientRect(hwnd, &windowRect);
    charsPerLine = windowRect.right / tm.tmAveCharWidth;

    for(i = 0; i <= cp->numChars / charsPerLine; i++) {
        if (i * charsPerLine + charsPerLine >= cp->maxChars) {
            printableChars = cp->maxChars - i * charsPerLine;
            TextOut(hdc, 0, i * tm.tmHeight, cp->buffer + (i * charsPerLine), printableChars);
        } else {
            TextOut(hdc, 0, i * tm.tmHeight, cp->buffer + (i * charsPerLine), (charsPerLine));
        }
    }
}
