//
// Created by T470S on 4/23/2019.
//

#ifndef KHIEMSHELL_CDCOMAND_H
#define KHIEMSHELL_CDCOMAND_H
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define BUFSIZE MAX_PATH
int printPath()
{
    TCHAR Buffer[BUFSIZE];
    DWORD dwRet;
    dwRet = GetCurrentDirectory(BUFSIZE, Buffer);

    if( dwRet == 0 )
    {
        printf("GetCurrentDirectory failed (%d)\n", GetLastError());
        return(0);
    }
    if(dwRet > BUFSIZE)
    {
        printf("Buffer too small; need %d characters\n", dwRet);
        return(0);
    }
    printf("Path %s\n", Buffer);
}
int chargeDir( TCHAR *argv)
{
    TCHAR Buffer[BUFSIZE];
    DWORD dwRet;


    dwRet = GetCurrentDirectory(BUFSIZE, Buffer);

    if( dwRet == 0 )
    {
        printf("GetCurrentDirectory failed (%d)\n", GetLastError());
        return(0);
    }
    if(dwRet > BUFSIZE)
    {
        printf("Buffer too small; need %d characters\n", dwRet);
        return(0);
    }
  //  printf("Path %s\n", Buffer);
    if( !SetCurrentDirectory(argv))
    {
        printf("SetCurrentDirectory failed (%d)\n", GetLastError());
        return(0);
    }
    printf(TEXT("Set current directory to :\n"));
    dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
    printf("\t%s\n", Buffer);

   /* if( !SetCurrentDirectory(Buffer) )
    {
        printf("SetCurrentDirectory failed (%d)\n", GetLastError());
        return(0);
    }
    printf(TEXT("Restored previous directory (%s)\n"), Buffer);*/
}
#endif //KHIEMSHELL_CDCOMAND_H
