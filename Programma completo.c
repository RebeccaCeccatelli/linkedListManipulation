//Esercizio 5, programma completo per prova orale.

//inclusioni per l'uso di funzioni di libreria
#include <stdio.h>
#include <stdlib.h>

//definizioni per l'uso dei booleani
typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

//definizione di tipo strutturato
struct list{
    int value;
    struct list* next_ptr;
};

//dichiarazioni di funzione
int main();
void initialization (struct list **ptrptr);
void get_value (int *value_ptr);
boolean pre_insert(struct list **ptrptr, int value);
boolean suf_insert(struct list **ptrptr, int value);
void visit(struct list *ptr);
void swap_consecutives (struct list **ptrptr1, struct list **ptrptr2 );
boolean bubble_sort ( struct list **ptrptr);

//funzione principale
int main(){
    int choice, value;
    struct list *ptr, **list=&ptr;

    initialization(list);
    boolean again;
    do{
        printf ( "\n\nSelezionare operazione da eseguire sulla lista (1-Inserimento in coda, 2-Ordinamento):");
        scanf ( "%d", &choice);
        switch (choice){
            case 1:
                get_value(&value);
                if ( suf_insert(list, value) )
                    printf ("\nInserimento avvenuto correttamente.\nLa lista e': ");
                visit(ptr);
                again = TRUE;
                break;

            case 2:
                printf ( "\nOrdinamento in corso...");
                bubble_sort(list);
                printf ( "\nLa lista ordinata e': ");
                visit(ptr);
                again =FALSE;
                break;
            default:
                again = FALSE;
        }
    }
    while ( again == TRUE );

    return 0;
}

//definizioni di funzione

//Initialization
void initialization (struct list** ptrptr) {
    *ptrptr = NULL;
}

//Get value
void get_value (int* value_ptr) {
    printf ("Valore da inserire:");
    scanf ("%d", value_ptr);
}

//Head insert
boolean pre_insert(struct list** ptrptr, int value) {
    struct list* tmp;
    tmp = (struct list* )malloc(sizeof(struct list));
    if ( tmp != NULL ) {
        tmp->value = value;
        tmp->next_ptr = *ptrptr;
        *ptrptr = tmp;
        return TRUE;
    }
    else
        return FALSE;
}

//Tail insert
boolean suf_insert(struct list** ptrptr, int value) {
    while( *ptrptr != NULL )
        ptrptr = &((*ptrptr)->next_ptr);
    if ( pre_insert(ptrptr,value) )
        return TRUE;
    else
        return FALSE;
}

//Visit
void visit(struct list* ptr) {
    while ( ptr != NULL ) {
        printf("%d, ", ptr->value);
        ptr = ptr->next_ptr;
    }
    printf ( "\b\b.");
}

//Swap consecutive elements
void swap_consecutives (struct list** ptrptr1, struct list** ptrptr2 ){
    struct list* tmp;

    tmp = *ptrptr2;
    *ptrptr2 = (*ptrptr2)->next_ptr;
    tmp->next_ptr = *ptrptr1;
    *ptrptr1 = tmp;
}

//Bubble sort
boolean bubble_sort ( struct list** ptrptr) {
    struct list **ptrptr1, **ptrptr2;  //doppi puntatori, rispettivamente, ad un elemento ed al suo successivo
    struct list *done;
    boolean swap_found;

    
    if(*ptrptr!= NULL ){
        done = NULL;
        do{
            ptrptr1=ptrptr;
            swap_found=FALSE;
            while ( (*ptrptr1)->next_ptr != done ){     //da done in poi gli elementi sono ordinati
                ptrptr2 = &((*ptrptr1)->next_ptr);
                if ( (*ptrptr1)->value > (*ptrptr2)->value ){
                    swap_found = TRUE;
                    swap_consecutives(ptrptr1, ptrptr2);
                }
                ptrptr1 = &((*ptrptr1)->next_ptr);
            }
            done = *ptrptr1;
        }
        while ( swap_found == TRUE );
        return TRUE;
    }
    else
        return FALSE;
}