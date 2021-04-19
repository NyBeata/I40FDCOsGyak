#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int main()
{
    printf("************ Masodfoku egyenlet megoldasa *************\n\n");

    int child;
    mkfifo("i40fdc", S_IRUSR | S_IWUSR);
    child = fork();

    if(child > 0){ //Szülő
        /************************fájlból olvasás***********************/
        int i, a, b, c;

        FILE* bemenet = fopen("bemenet.txt", "r");

        if(bemenet == NULL){
            printf("A fajlbol nem lehet olvasni\n");
            exit(-1);
        }

        fscanf(bemenet, "%d\n%d %d %d", &i, &a, &b, &c);

        printf("(Szulo)  Fajlbol beolvasott ertekek darabszama: %d\n",i);
        fflush(stdout);
        /***************************************************************/

        int fd;
        fd = open("i40fdc", O_RDWR);
        write(fd, &a, sizeof(int));     //adatok átadása a gyereknek
        write(fd, &b, sizeof(int));
        write(fd, &c, sizeof(int));

        sleep(1);

        double x, y;
        read(fd, &x, sizeof(double));   //adatok fogadása a gyerektől
        read(fd, &y, sizeof(double));

        close(fd);
        unlink("i40fdc");
        /*****************************fájlba írás*****************************/
            FILE *file;
            file = fopen("kimenet.txt", "w");
            fprintf(file, "%d %d %d %.2f %.2f", a, b, c, x, y);
            printf("\n(Szulo)  A kapott eredmenyeket lementettem egy fajlba");
        /*********************************************************************/

        printf("\n\n*******************************************************\n");


    } else if(child == 0){ //Gyerek
        int fd;
        int a,b,c;

        fd = open("i40fdc", O_RDWR);
        read(fd, &a, sizeof(int));      //adatok fogadása a szülőtől
        read(fd, &b, sizeof(int));
        read(fd, &c, sizeof(int));
        printf("\n(Gyerek) Megkaptam a szamokat: a:%d b:%d c:%d\n",a,b,c);

        /********************************************másodfokú egyenlet**********************************************/
        int d = b*b-4*a*c;
        double x, y;

        x=(-b + sqrt(d)) / (2*a);
        y=(-b - sqrt(d)) / (2*a);

        printf("\n         A masodfoku egyenlet megoldo keplete:\n          (-b +- sqrt(b*b - 4*a*c) ) / (2*a)\n");
        printf("\n         Megoldasok:");
        printf("\n         x1: %.1f  es  x2: %.1f\n", x, y);
        /************************************************************************************************************/

        write(fd, &x, sizeof(double));  //adatok átadása a szülőnek
        write(fd, &y, sizeof(double));

        close(fd);
    }

    return 0;
}
