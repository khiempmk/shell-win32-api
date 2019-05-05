//
// Created by T470S on 4/22/2019.
//
#include <windows.h>
#include <cstring>
#include <signal.h>
#include <stdio.h>
#include <psapi.h>
#include<tlhelp32.h>
#include <tchar.h>

#ifndef KHIEMSHELL_RUNPROCESS_H
#define KHIEMSHELL_RUNPROCESS_H
DWORD id ;
void handle_sigint(int dummy)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,id);
    TerminateProcess(hProcess,1);
    CloseHandle(hProcess) ;
}
void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS |PROCESS_VM_READ,FALSE, processID );

    // Get the process name.

        if (!GetProcessImageFileName(hProcess,szProcessName,sizeof(szProcessName)-1))
        {
            _tprintf(TEXT("GetModuleFile failed"));
        } else {
            TCHAR *token;
            TCHAR kq[MAX_PATH];
            token = strtok(szProcessName, "\\");
            do{
                strcpy(kq,token);
                token = strtok(NULL, "\\");
            } while (token != NULL);

            _tprintf(TEXT("%-30s%-11d\n"), kq, processID);
        }
        CloseHandle( hProcess );
}

void listProcess(int*numProcess, PROCESS_INFORMATION *List)
{
    printf("%-30s%-11s\n", "ProcessName", "ProcessID");
    printf("%-30s%-11s\n", "-------------", "-----------");

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    for ( i = 1; i <= *numProcess; i++ )
    {

            PrintProcessNameAndID( List[i].dwProcessId );
    }
    return ;

}
void killAll(int *numProcess, PROCESS_INFORMATION* List)
{
    for( int i = 1 ; i <= *numProcess ; i++)
    {
        TerminateProcess(List[i].hProcess,1);
        CloseHandle(List[i].hProcess) ;
        CloseHandle(List[i].hThread) ;
    }
    *numProcess = 0;
    printf("Terminated!\n");
}
void killbyID(TCHAR* ID , int *numProcess, PROCESS_INFORMATION* List)
{
   // DWORD id = (DWORD)
   int id = atoi(ID);
   int i;
    for( i= 1 ; i <= *numProcess ; i++)
    if (List[i].dwProcessId == id )
    {
        TerminateProcess(List[i].hProcess,1);
        CloseHandle(List[i].hProcess) ;
        CloseHandle(List[i].hThread) ;
        break;
    }
    printf("Terminated process ID %ld\n",id);
    *numProcess -= 1;
    for (int j = i; j< *numProcess; j++)
            List[j] = List[j+1];
}
int runForegr(TCHAR* filename, PROCESS_INFORMATION* List, int * numProcess)
{
    STARTUPINFO si ;
    PROCESS_INFORMATION pi ;

    if (strchr(filename,'?') != NULL){
        printf("USAGE : r <filename.exe>\n") ;
        exit(0) ;
    }
    ZeroMemory(&si,sizeof(si)) ;
    si.cb = sizeof(si) ;
    if (!CreateProcess(filename,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi))
    {
        printf("Create process fail\n") ;
        return 1;
    }
    int a = *numProcess;
    *numProcess += 1 ;
    List[*numProcess] = pi ;
    printf("running....\n");
  //  signal(SIGINT,handle_sigint) ;
   // WaitForSingleObject(pi.hProcess, INFINITE);
  // TerminateProcess(pi.hProcess,1) ;
  // CloseHandle(pi.hProcess) ;
  // CloseHandle(pi.hThread) ;

    return 0 ;
}
#endif //KHIEMSHELL_RUNPROCESS_H
