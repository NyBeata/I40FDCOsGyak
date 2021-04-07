#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int child;

    mkfifo("i40fdc", S_IRUSR | S_IWUSR);

    child = fork();

    if(child > 0){
        char s[1024];
        int fd;

        fd = open("i40fdc", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s", s);

        close(fd);
        unlink("i40fdc");
    } else if(child == 0){
        int fd;

        fd = open("i40fdc", O_WRONLY);
        write(fd, "Nyiri Beata\n", 13);
        close(fd);
    }

    return 0;
}
