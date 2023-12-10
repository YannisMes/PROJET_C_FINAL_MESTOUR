#include "List.h"
#include "Cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>




t_sk_list *CreateList(int niv_max){
    t_sk_list *mylist = (t_sk_list*)malloc(sizeof(t_sk_list));
    mylist->heads =(t_sk_cell**)malloc(niv_max*sizeof(t_sk_cell));
    mylist->max_level = niv_max;
    for(int i = 0;i<niv_max;i++){
        mylist->heads[i] = NULL;
    }
    return mylist;
}
void addHead_list(t_sk_list* mylist,t_sk_cell* cell){
    cell->next[cell->level] = mylist->heads[cell->level];
    mylist->heads[cell->level] =cell;
}
void display_List(t_sk_list* mylist,int niv){
    printf("[list_head_%d] --> ",niv);
    t_sk_cell* c_actuel = mylist->heads[niv];

    while(c_actuel != NULL){
        printf(" [%d|@]--> ",c_actuel->value);
        c_actuel = c_actuel->next[niv];
    }
    printf(" NULL\n");
}
void display_all_level(t_sk_list* mylist){
    for(int i = 0 ; i < mylist->max_level ;i++){
        display_List(mylist,i);
    }

}

void add_cell(t_sk_list* mylist,t_sk_cell* newcell) {
    for (int i = 0; i <= newcell->level; ++i) {
        t_sk_cell* t1_cell = mylist->heads[i];
        t_sk_cell* t2_cell =NULL;
        while ((t1_cell != NULL)&&(newcell->value > t1_cell->value)) {
            t2_cell = t1_cell;
            t1_cell = t1_cell->next[i];
        }

        newcell->next[i] = t1_cell;

        if (t2_cell != NULL) {
            t2_cell->next[i] =newcell;
        }else{
            mylist->heads[i] = newcell;
        }
    }
}

void display_aligne_list(t_sk_list *list) {
    int max_level = list->max_level;
    for (int i = 0; i < max_level; ++i) {
        t_sk_cell *c_actuelle = list->heads[i];
        printf("[List head %d @-]", i);
        t_sk_cell *tmp = list->heads[0];
        while (tmp != NULL) {
            printf("-----");
            if (c_actuelle == NULL || c_actuelle->value != tmp->value) {
                printf("------");
            } else {
                printf(">[%d⎪@]", c_actuelle->value);
                c_actuelle = c_actuelle->next[i];
            }
            tmp = tmp->next[0];
        }
        printf("---> NULL\n");
    }
}
t_sk_cell* recherche_niveau0(t_sk_list* mylist, int chiffre) {
    t_sk_cell* c_actuelle = mylist->heads[0];

    while (c_actuelle != NULL && c_actuelle->value < chiffre) {
        c_actuelle = c_actuelle->next[0];
    }

    if (c_actuelle != NULL && c_actuelle->value == chiffre) {
        printf("%d trouvé au niveau 0\n", chiffre);
        return c_actuelle;
    } else {
        printf("%d pas trouvé au niveau 0\n", chiffre);
        return NULL;
    }
}
t_sk_list* liste_puiss2(int n) {
    t_sk_list *mylist = CreateList(n);
    int max_val = (1 << n) - 1;
    for (int niv = n; niv >= 0; niv--) {
        int val = (1 << niv);
        while (val <= max_val) {
            add_cell(mylist, CreateCell(val, niv));
            val += (1 << (niv + 1));
        }
    }
    display_aligne_list(mylist);
    return mylist;

}
t_sk_cell* recherche_tous_niveaux(t_sk_list* mylist, int cible) {
    int max_level = mylist->max_level;
    for (int i = max_level - 1; i >= 0; --i) {
        t_sk_cell* c_actuelle = mylist->heads[i];
        while (c_actuelle != NULL && c_actuelle->value < cible) {
            c_actuelle = c_actuelle->next[i];
        }
        if (c_actuelle != NULL && c_actuelle->value == cible) {
            printf("%d trouvé au niveau %d\n", c_actuelle->value, i);
            return c_actuelle;
        }
    }
    printf("%d pas trouvé dans tous les niveaux\n", cible);
    return NULL;
}



