/*************** Vadász Dénes jegyzete alapján ***************

Abstract:   Példa signal kezelésre.
            ctrl/break signal hatására a do_int handler
                működik először, majd ignorálódik ez a
                signal
            A ciklusban másodpercenként alarm generálódik,
                az alarm signal handler-e a do_nothing.
            A pause felfüggeszti a process-t, amíg kap
                egy signalt.

Internals: signal(), alarm(), pause()

**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void do int();

int main()
{
    int i;
    unsigned sec=1;

    for(i=1; i<8; i++){
        alarm(sec);
        signal(SIGALRM, do_nothing);
        printf(" %d varok de meddig?\n", i);
        pause();
    }
}

void do_nothing(){ ;}

void do_int(){
    printf(" int jott ");
    signal(SIGINT, SIG_IGN);
}


