#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int signum);

int main(void)
{
    void (*sigHandlerInterrupt)(int);
    void (*sigHandlerQuit)(int);
    void (*sigHandlerReturn)(int);
    sigHandlerInterrupt = sigHandlerQuit = handleSignals;
    sigHandlerReturn = signal(SIGINT, sigHandlerInterrupt);
    if(sigHandlerReturn == SIG_ERR){
        perror("signal error: ");
        return 1;
    }
    sigHandlerReturn = signal(SIGQUIT, sigHandlerQuit);

    if(sigHandlerReturn == SIG_ERR){
        perror("signal error: ");
        return 1;
    }
    while (1){
        printf("\nA program leallitasahoz a kovetkezoket vegezze el:\n");
        printf("1. Nyisson meg egy masik terminalt.\n");
        printf("2. Adja ki a parancsot: kill %d or issue CTRL+C 2 times\n", getpid());
        sleep(10);
    }
    return 0;
}

void handleSignals(int signum){
    switch(signum){
        case SIGINT:
            printf("\nNyomja meg a CTRL+C billentyukombinaciot!\n");
            printf("Most visszaallitja a SIGINT jelet az alapertelmezett muveletre\n");
            signal(SIGINT, SIG_DFL);
            break;
        case SIGQUIT:
            printf("\nNyomja meg a CTRL+C billentyukombinaciot!\n");
            break;
        default:
            printf("\nFogadott jel szama %d\n", signum);
            break;
    }
    return;
}
