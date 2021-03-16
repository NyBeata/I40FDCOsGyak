#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char command[50];

    printf("Adjon meg egy Unix parancsot!\n");
    scanf("%s", command);

    system(command);

    return 0;
}
