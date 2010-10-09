#ifndef BUFFER_H
#define BUFFER_H
VOID AddData(TCHAR newData, PCPARAMS cp);
VOID AddMultiData(PTCHAR newData, UINT numNewItems, PCPARAMS cp);
VOID DisplayData(HWND hwnd, HDC hdc, PCPARAMS cp);
#endif