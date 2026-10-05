#include <stdio.h>
#include <stdlib.h>

#define LIST1_SIZE 5
#define LIST2_SIZE 3
#define START_VALUE 100
#define END_VALUE 200

typedef struct cell
{
    int val;
    struct cell* next;
    struct cell* prev;
} Cell;

typedef struct
{
    Cell* first;
} List;

void fill(List* list, int n)
{
    Cell *new_cell, *last;
    for (int i = 0; i < n; i++)
    {
        new_cell = malloc(sizeof(Cell));
        if (new_cell != NULL)
        {
            new_cell->val = i;
            new_cell->next = NULL;
            new_cell->prev = NULL;
            if (list->first == NULL)
                list->first = new_cell;
            else
            {
                new_cell->prev = last;
                last->next = new_cell;
            }
            last = new_cell;
        }
    }
}

int size(List list)
{
    int size = 0;
    Cell* it = list.first;
    while (it != NULL)
    {
        it = it->next;
        size++;
    }
    return size;
}

void print(List list)
{
    Cell* it = list.first;
    while (it != NULL)
    {
        printf("<%p> : %d ", it, it->val);
        it = it->next;
    }
}

void deleteFirst(List* list)
{
    Cell* first = list->first;
    if (first != NULL)
    {
        Cell* next = first->next;
        if (next != NULL)
            next->prev = NULL;
        list->first = next;
        free(first);
    }
}

void deleteLast(List* list)
{
    Cell* it = list->first;
    if (it != NULL)
    {
        Cell* prev;
        while (it->next != NULL)
        {
            prev = it;
            it = it->next;
        }
        if (it == list->first)
            list->first = NULL;
        else
            prev->next = NULL;
        free(it);
    }
}

void addToStart(List* list, int value)
{
    Cell* new_cell = malloc(sizeof(Cell));
    if (new_cell != NULL)
    {
        new_cell->val = value;
        new_cell->next = list->first;
        new_cell->prev = NULL;
        if (list->first != NULL)
            // Le nouvel élément devient le précédent du premier.
            list->first->prev = new_cell;
        list->first = new_cell;
    }
}

void addToEnd(List* list, int value)
{
    Cell* new_cell = malloc(sizeof(Cell));
    if (new_cell != NULL)
    {
        new_cell->val = value;
        new_cell->next = NULL;
        if (list->first == NULL)
        {
            list->first = new_cell;
            new_cell->prev = NULL;
        }
        else
        {
            Cell* it = list->first;
            while (it->next != NULL)
                it = it->next;
            it->next = new_cell;
            new_cell->prev = it;
        }
    }
}

void copyToEnd(List* dest, List src)
{
    Cell* it = src.first;

    while (it != NULL)
    {
        addToEnd(dest, it->val);
        it = it->next;
    }
}

List concat(List list1, List list2)
{
    List new_list = {NULL};

    copyToEnd(&new_list, list1);
    copyToEnd(&new_list, list2);

    return new_list;
}

void applyFunction(List* list, int (*f)(int))
{
    Cell* it = list->first;
    while (it != NULL)
    {
        it->val = f(it->val);
        it = it->next;
    }
}

int square(int x)
{
    return x * x;
}


int main()
{
    List l1 = {NULL};
    printf("===== remplir =====\n");

    fill(&l1, LIST1_SIZE);
    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    printf("===== ajouter_premier =====\n");
    addToStart(&l1, START_VALUE);
    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    printf("===== ajouter_fin =====\n");

    addToEnd(&l1, END_VALUE);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    printf("===== retirer_premier =====\n");

    deleteFirst(&l1);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    printf("===== retirer_fin =====\n");

    deleteLast(&l1);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    printf("===== Deuxième liste =====\n");

    List l2 = {NULL};

    fill(&l2, LIST2_SIZE);

    print(l2);

    printf("\nLongueur : %d\n\n", size(l2));


    printf("===== concatener =====\n");

    List l3 = concat(l1, l2);

    printf("Liste 1 :\n");
    print(l1);

    printf("\nListe 2 :\n");
    print(l2);

    printf("\nListe concaténée :\n");
    print(l3);

    printf("\nLongueur : %d\n\n", size(l3));


    printf("===== apply_fct(square) =====\n");

    printf("Avant :\n");
    print(l3);

    applyFunction(&l3, square);

    printf("\nAprès :\n");
    print(l3);
    printf("\n");


    while (l1.first != NULL)
        deleteFirst(&l1);

    while (l2.first != NULL)
        deleteFirst(&l2);

    while (l3.first != NULL)
        deleteFirst(&l3);


    return 0;
}
