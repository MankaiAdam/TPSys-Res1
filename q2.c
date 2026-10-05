#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("test.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    struct stat file_info;

    // Récupération de la taille du fichier.
    int stat_result = stat("test.txt", &file_info);

    if (stat_result == -1)
    {
        perror("stat");
        close(fd);
        return 1;
    }

    int file_size = file_info.st_size;

    // Projection du fichier en mémoire pour pouvoir modifier directement son contenu
    // retourne MAP_FAILED en cas d'échec
    char* file = mmap(
        NULL,
        file_size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    if (file == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    // Inversion des octets du fichier
    for (size_t i = 0; i < file_size / 2; i++)
    {
        char temp = file[i];
        file[i] = file[file_size - 1 - i];
        file[file_size - 1 - i] = temp;
    }

    //Liberation de memoire : retourne -1 en cas d'échec
    int munmap_result = munmap(file, file_size);

    if (munmap_result == -1)
    {
        perror("munmap");
        close(fd);
        return 1;
    }

    int close_result = close(fd);

    if (close_result == -1)
    {
        perror("close");
        return 1;
    }

    return 0;
}
