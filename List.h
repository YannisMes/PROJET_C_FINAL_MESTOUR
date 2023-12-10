#include "Cell.h"

#ifndef UNTITLED5_LIST_H
#define UNTITLED5_LIST_H

typedef struct s_d_list
{
    t_d_cell *head_0;
    t_d_cell *head_1;
} t_d_list;

typedef struct s_sk_list{

    t_sk_cell ** heads;
    int max_level;
}t_sk_list;


void display_all_level(t_sk_list* mylist);
t_sk_cell* CreateCell(int val,int ht);
t_sk_list* CreateList(int niv_max);
void addHead_list(t_sk_list* list,t_sk_cell * cell);
void display_List(t_sk_list * mylist,int);
void add_cell(t_sk_list* mylist,t_sk_cell * cell);
void display_aligne_list(t_sk_list *list);
t_sk_cell* recherche_niveau0(t_sk_list* mylist, int chiffre);
t_sk_list * liste_puiss2(int);
t_sk_cell* recherche_tous_niveaux(t_sk_list* mylist, int cible);

#endif //UNTITLED5_LIST_