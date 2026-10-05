#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("test.txt", O_RDWR);

    struct stat file_info;

    stat("test.txt", &file_info);

    int file_size = file_info.st_size;

    char *file = mmap(
        NULL,
        file_size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    //Inversement
    for (size_t i = 0; i < file_size / 2; i++)
    {
        char temp = file[i];
        file[i] = file[file_size - 1 - i];
        file[file_size - 1 - i] = temp;
    }

    munmap(file, file_size);
    close(fd);

    return 0;
}