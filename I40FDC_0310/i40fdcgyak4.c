#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *argv[3] = {"Command-line", ".", NULL};

    int pid = fork();

    if (pid == 0)
        execvp("find", argv);

    wait(2);

    printf("A szulo processz befejezodott.");

    return 0;
}
