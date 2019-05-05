//
// Created by Admin on 4/20/2019.
//

#ifndef KHIEMSHELL_MENU_H
#define KHIEMSHELL_MENU_H

void printMenu()
    {
        printf ("\n\n") ;
        printf ("\n------------------------------------------------------");
        printf ("\t\nMy shell supports the following commands:\n") ;
        printf ("\t\t[*] menu    : print menu\n") ;
        printf ("\t\t[*] dir     : list all files in this directory\n") ;
        printf ("\t\t[*] run       : run program in forgeground\n");
        printf ("\t\t[*] list    : list the process id is running\n") ;
        printf ("\t\t[*] killall : kill all process is running\n") ;
        printf ("\t\t[*] kill    : kill process with id is running\n");
        printf ("\t\t[*] debug   : resume a process to debug\n");
        printf ("\t\t[*] stop    : stop a process.\n") ;
        printf ("\t\t[*] resume  : resume a stopping process.\n") ;
        printf ("\t\t[*] time    : print time and date\n") ;
        printf ("\t\t[*] help    : type help for help\n") ;
        printf ("\t\t[*] exit    : exit shell\n") ;
        printf ("------------------------------------------------------");
        printf("\n\n") ;
    }



#endif //KHIEMSHELL_MENU_H
