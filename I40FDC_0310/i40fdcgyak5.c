#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid;
    int status;

    if((pid = fork()) < 0)
        perror("fork hiba");
    else if (pid == 0)
        exit(7); //vagy abort(); vagy 1/0;
    if(wait(&status) != pid)
        perror("wait hiba");
    if(WIFEXITED(status))
        printf("Normalis befejezodes, visszaadott ertek: %d", status);

    return 0;
}
