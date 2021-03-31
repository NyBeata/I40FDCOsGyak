/*************** Vadász Dénes jegyzete alapján ***************

Abstract:  Példa signal kezelésre.
           Az alarm signal handler-e a so_nothing.

Internals: signal(), pause()

**************************************************************/

#include <unistd.h>
#include <signal.h>

void do_nothing();

main()
{
    signal(SIGALRM, do_nothing);
    printf(" %d varok de meddig?\n");
    pause();
    printf(" Vegre, itt az alarm\n");
}

void do_nothing(){ ;}
