#include <iostream>
#include "runProcess.h"
#include "Menu.h"
#include "cdComand.h"
#include "dirComand.h"
#include <tchar.h>
#include <cstring>
using namespace std;
int main() {
   // size_t MAX_SIZE = STRSAFE_MAX_CCH ;
    TCHAR strInput[100] ;
    TCHAR cmd[100], path[100], CMD[100], PATH[100];
    TCHAR * spacePos ;
    PROCESS_INFORMATION List[100] ;
    int numProcess;
    printMenu() ;

    // get cmd
    numProcess = 0 ;
    while(1)
    {
        printf("SHELL> ");
        fflush(stdin) ;
        gets(strInput) ;

        spacePos = strchr(strInput,' ') ;
        if (spacePos != NULL)
        {
            strcpy(path,spacePos + 1) ;
            strcpy(cmd,strInput);
            cmd[strlen(strInput) - strlen(path) - 1] = '\0';
        }
        else strcpy(cmd,strInput) ;

       if (strcmp(cmd, "run") ==0 )
           runForegr(path,List,&numProcess);
        else if (strcmp(cmd,"cd")== 0 )
            chargeDir( path);
        else if (strcmp(cmd,"dir")== 0)
            dir();
        else if (strcmp(cmd,"path")== 0)
            printPath();
        else if (strcmp(cmd,"killAll")== 0)
            killAll(&numProcess,List);
        else if (strcmp(cmd,"list") ==0 )
            listProcess(&numProcess,List);
        else if (strcmp(cmd,"killId")==0 )
            killbyID(path,&numProcess,List);
        //system(strInput);
        //return(0);
        //else if (strcmp(cmd, ""))
    }


}