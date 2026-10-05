#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

//Donnée globale initialisée
int data = 1;

//Donnée globale initialisée à zéro
int bss = 0;

// Str : Chaîne de caractères
char *Str = "Hello World";

int main(void){

    //Données allouées dynamiquement
    int *var_heap = malloc(sizeof(int));

    //Données à portées limitées stockées dans la pile d’exécution
    int var_stack = 30;

    void *mmap_zone = mmap(NULL,1024,PROT_READ,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    printf("Data         : %p\n", (void *)&data);
    printf("BSS          : %p\n", (void *)&bss);
    printf("Str          : %p\n", (void *)Str);
    printf("Heap         : %p\n", (void *)var_heap);
    printf("Stack        : %p\n", (void *)&var_stack);
    printf("Main Function: %p\n", (void *)main);
    printf("LibC Function: %p\n", (void *)printf);
    printf("Mmap         : %p\n", mmap_zone);

    //Execution de la commande
    char pid_str[20];
    snprintf(pid_str, sizeof(pid_str), "%d", getpid());
    execlp("pmap", "pmap", "-X", pid_str, NULL);
}
