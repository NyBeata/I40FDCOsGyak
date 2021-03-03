#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    FILE *file;
    file = fopen("i40fdc.txt", "r");
    if (file)
    {
        while ((c = getc(file)) != EOF)
            putchar(c);
    }
    else
    {
        file = fopen("i40fdc.txt", "w");
        fprintf(file, "Nyiri Beata \nProgramtervezo Informatikus \nI40FDC");
        printf("Fajl letrehozva");
    }
    fclose(file);

    return 0;
}
