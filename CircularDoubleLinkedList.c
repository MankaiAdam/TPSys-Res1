#include <stdio.h>
#include <stdlib.h>

#define LIST1_SIZE 5
#define LIST2_SIZE 3
#define START_VALUE 100
#define END_VALUE 200

typedef struct cell
{
	int val;
	struct cell *next;
	struct cell *prev;
}Cell;

typedef struct {
	Cell *first;
}List;

void fill(List *list , int n){
	for(int i = 0; i < n ; i++){
		Cell* new_cell = malloc(sizeof(Cell));
		if(new_cell != NULL){
			new_cell->val = i;
			new_cell->next = NULL;
			if(list->first == NULL) {
				list->first = new_cell;
				new_cell->next = new_cell;
				new_cell->prev = new_cell;
			}
			else{
				Cell* last = list->first->prev;
				new_cell->prev = last;
				last->next=new_cell;
				list->first->prev=new_cell;
				new_cell->next = list->first;
			}
		}
	}
}

int size(List list)
{
	if (list.first == NULL)
		return 0;

	int size = 0;
	Cell* it = list.first;
	Cell* first = it;
	do{
		it = it->next;
		size++;
	}while(it != first);
	return size;
}

void print(List list)
{
	if (list.first == NULL)
		return;

	Cell* it = list.first;
	Cell* first = it;
	do{
		printf("<%p> : %d ",it,it->val);
		it = it->next;
	}while (it != first);
}

void deleteFirst (List* list) {
	Cell* first = list->first;
	if (first != NULL){
		if (first->next == first)
		{
			// Only one element
			list->first = NULL;
			free(first);
		}
		else
		{
			Cell* last = first->prev;
			Cell* next = first->next;

			last->next = next;
			next->prev = last;

			list->first = next;

			free(first);
		}
	}

}
void deleteLast(List* list) {
	Cell* first = list->first;
	if (first != NULL){
		Cell* last = first->prev;
		if (first == last) {
			list->first = NULL;
		}else {
			Cell* beforeLast = last->prev;
			first->prev = beforeLast;
			beforeLast->next = first;
		}
		free(last);
	}
}

void addToStart (List* list, int value){
	Cell * new_cell  = malloc (sizeof(Cell)) ;
	if (new_cell!=NULL){
		new_cell -> val = value;
		Cell* first = list->first;
		if (first != NULL){
			Cell* last = first->prev;
			new_cell -> prev = last;
			new_cell -> next = first;
			first->prev = new_cell;
			last->next = new_cell;
		}else {
			new_cell->next = new_cell;
			new_cell->prev = new_cell;
		}
		list-> first = new_cell ;
	}
}

void addToEnd(List *list,int value){
	Cell* new_cell = malloc(sizeof(Cell));
	if (new_cell != NULL)
	{
		new_cell->val = value;
		new_cell->next = NULL;
		if (list->first == NULL)
		{
			list->first = new_cell;

			// La seule cellule pointe vers elle-même dans les deux directions.
			new_cell->next = new_cell;
			new_cell->prev = new_cell;
		}
		else{
			Cell* last = list->first->prev;
			new_cell->prev = last;
			last->next=new_cell;
			list->first->prev=new_cell;
			new_cell->next = list->first;
		}
	}
}

void copyToEnd(List *dest, List src)
{
	if (src.first == NULL)
		return;

	Cell *it = src.first;

	do
	{
		addToEnd(dest, it->val);
		it = it->next;
	} while (it != src.first);
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
	Cell* first = it;

	if (it != NULL)
	{
		do{
			it->val = f(it->val);
			it = it->next;
		}while(it != first);
	}
}

int square(int x)
{
	return x * x;
}


int main()
{
    //Création d'une list
    List l1 = {NULL};
    printf("===== remplir =====\n");

    fill(&l1, LIST1_SIZE);
    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    //ajouter_premier
    printf("===== ajouter_premier =====\n");
    addToStart(&l1, START_VALUE);
    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    //ajouter_fin
    printf("===== ajouter_fin =====\n");

    addToEnd(&l1, END_VALUE);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    //retirer_premier
    printf("===== retirer_premier =====\n");

    deleteFirst(&l1);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    //retirer_fin
    printf("===== retirer_fin =====\n");

    deleteLast(&l1);

    print(l1);

    printf("\nLongueur : %d\n\n", size(l1));


    //Deuxième liste
    printf("===== Deuxième liste =====\n");

    List l2 = {NULL};

    fill(&l2, LIST2_SIZE);

    print(l2);

    printf("\nLongueur : %d\n\n", size(l2));

    //concatener

    printf("===== concatener =====\n");

    List l3 = concat(l1, l2);

    printf("Liste 1 :\n");
    print(l1);

    printf("\nListe 2 :\n");
    print(l2);

    printf("\nListe concaténée :\n");
    print(l3);

    printf("\nLongueur : %d\n\n", size(l3));


    //apply_fct

    printf("===== apply_fct(square) =====\n");

    printf("Avant :\n");
    print(l3);

    applyFunction(&l3, square);

    printf("\nAprès :\n");
    print(l3);
	printf("\n");

    //Libération de la mémoire

    while (l1.first != NULL)
        deleteFirst(&l1);

    while (l2.first != NULL)
        deleteFirst(&l2);

    while (l3.first != NULL)
        deleteFirst(&l3);

    return 0;
}
