#ifndef MANAGECONNECTIONS_H
#define MANAGECONNECTIONS_H
HANDLE CreateConnection(LPCTSTR);
BOOL PrepareConnection(HANDLE, DCB);
BOOL OpenConnection(HWND hwnd, LPCTSTR szPortName, PCPARAMS cp);
#endif