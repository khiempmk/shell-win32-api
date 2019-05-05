//
// Created by T470S on 4/26/2019.
//

#ifndef KHIEMSHELL_DIRCOMAND_H
#define KHIEMSHELL_DIRCOMAND_H
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
//#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#define BUFSIZE MAX_PATH
void DisplayErrorBox(LPTSTR lpszFunction);

int dir()
{
    TCHAR Buffer[BUFSIZE];
    DWORD dwRet;
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    dwRet = GetCurrentDirectory(BUFSIZE, Buffer);

    length_of_arg = strlen(Buffer);

    if (length_of_arg > (MAX_PATH - 3))
    {
        _tprintf(TEXT("\nDirectory path is too long.\n"));
        return (-1);
    }

    _tprintf(TEXT("\nTarget directory is %s\n\n"), Buffer);

    strcpy(szDir, Buffer);
 //   StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
    strcat(szDir,"\\*");
    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        DisplayErrorBox(TEXT("FindFirstFile"));
        return dwError;
    }

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT("%-30s<DIR>\n"), ffd.cFileName);
        }
        else
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            _tprintf(TEXT("%-30s%-11ld bytes\n"), ffd.cFileName, filesize.QuadPart);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        DisplayErrorBox(TEXT("FindFirstFile"));
    }

    FindClose(hFind);
    return dwError;
}


void DisplayErrorBox(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

    // Display the error message and clean up

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                                      (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));
    //StringCchPrintf((LPTSTR)lpDisplayBuf,
                  //  LocalSize(lpDisplayBuf) / sizeof(TCHAR),
             printf( TEXT("%s failed with error %d: %s"),
                    lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
#endif //KHIEMSHELL_DIRCOMAND_H
