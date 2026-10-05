#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

//Donnée globale initialisée
int data = 1;

//Donnée globale initialisée à zéro
int bss = 0;

// Str : Chaîne de caractères
char* Str = "Hello World";

int main(void)
{
    //Données allouées dynamiquement
    int* var_heap = malloc(sizeof(int));

    if (var_heap == NULL)
    {
        perror("malloc");
        return 1;
    }

    //Données à portées limitées stockées dans la pile d’exécution
    int var_stack = 30;

    //allocation mémoire : retourne MAP_FAILED en cas d'échec
    void* mmap_zone = mmap(NULL, 1024,PROT_READ,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mmap_zone == MAP_FAILED)
    {
        perror("mmap");
        free(var_heap);
        return 1;
    }

    printf("Data         : %p\n", (void*)&data);
    printf("BSS          : %p\n", (void*)&bss);
    printf("Str          : %p\n", (void*)Str);
    printf("Heap         : %p\n", (void*)var_heap);
    printf("Stack        : %p\n", (void*)&var_stack);
    printf("Main Function: %p\n", (void*)main);
    printf("LibC Function: %p\n", (void*)printf);
    printf("Mmap         : %p\n", mmap_zone);


    //Execution de la commande
    char pid_str[20];
    snprintf(pid_str, sizeof(pid_str), "%d", getpid());

    //Exécution de la commande : retourne -1 en cas d'échec
    int execlp_result = execlp("pmap", "pmap", "-X", pid_str, NULL);

    if (execlp_result == -1)
    {
        perror("execlp");

        free(var_heap);

        //Liberation de memoire : retourne -1 en cas d'échec
        int munmap_result = munmap(mmap_zone, 1024);

        if (munmap_result == -1)
        {
            perror("munmap");
            return 1;
        }

        return 1;
    }
}
