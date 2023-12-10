#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List.h"
#include "Cell.h"
#include "partie3.h"
#include "timer.h"
#define MAX_LENGTH 100
#define MAX_NOM_LENGTH 100
StringNode* search_char_Levels(StringList* mylist, const char* nom) {
    int max_level = mylist->max_level;
    for (int i = max_level; i >= 0; --i) {
        StringNode* actuelle = mylist->heads[i];
        while(actuelle != NULL && strcmp(actuelle->value, nom) < 0) {
            actuelle = actuelle->next[i];
        }
        if(actuelle != NULL && strcmp(actuelle->value, nom) == 0) {
            return actuelle;
        }
    }
    return NULL;
}

void insert_char_tri(StringList *mylist, StringNode *newNode){
    for (int i = 0; i <= newNode->level; ++i) {
        StringNode *actuelle = mylist->heads[i];
        StringNode *previous = NULL;
        while ((actuelle != NULL) && (strcmp(newNode->value, actuelle->value) > 0)) {
            previous = actuelle;
            actuelle = actuelle->next;
        }
        newNode->next = actuelle;
        if (previous != NULL) {
            previous->next = newNode;
        } else {
            mylist->heads[i] = newNode;
        }
    }
}

void insert_char_Node(StringList *mylist, StringNode *newNode){
    for(int i = 0; i <= newNode->level; ++i){
        StringNode *t1_node = mylist->heads[i];
        StringNode *t2_node = NULL;
        while ((t1_node != NULL)&&(strcmp(newNode->value, t1_node->value) > 0)) {
            t2_node = t1_node;
            t1_node = t1_node->next[i];
        }
        newNode->next[i] = t1_node;
        if (t2_node != NULL) {
            t2_node->next[i] = newNode;
        } else {
            mylist->heads[i] = newNode;
        }
    }
}

StringNode* recherche_nom_niveau(StringList* mylist, const char* Nom){
    if(mylist->max_level == 1) {
        StringNode* actuelle = mylist->heads[0];
        if (strcmp(actuelle->value, Nom) == 0) {
            printf("Contact '%s' trouvé\n", Nom);
            return actuelle;
        }
    } else{
        int max_level = mylist->max_level;
        for(int i = max_level - 1; i >= 0; --i) {
            StringNode* actuelle = mylist->heads[i];
            while (actuelle != NULL && strcmp(actuelle->value, Nom) < 0){
                actuelle = actuelle->next[i];
            }
            if(actuelle != NULL && strcmp(actuelle->value, Nom) == 0){
                return actuelle;
            }
        }
    }
    printf("Contact '%s' pas trouvé\n", Nom);
    return NULL;
}
StringList *create_char_List(int n) {
    StringList *mylist = (StringList *)malloc(sizeof(StringList));
    mylist->max_level = n;
    mylist->heads = (StringNode **)calloc(n + 1, sizeof(StringNode *));
    for (int level = 0; level <= n; level++) {
        mylist->heads[level] = NULL;
    }
    return mylist;
}

void display_char_List(StringList *mylist){
    for (int i = mylist->max_level; i >= 0; i--){
        StringNode *actuelle = &(mylist->heads[i]);
        printf("Level %d: ", i);
        while (actuelle != NULL) {
            if (actuelle->value != NULL) {
                printf("%s -> ", actuelle->value);
            }
            actuelle = actuelle->next;
        }
        printf("NULL\n");
    }
}
void add_rendezvous(StringNode* contact, RendezVous rendezVous){
    RendezVousNode* newRendezVous =(RendezVousNode*)malloc(sizeof(RendezVousNode));
    if(newRendezVous == NULL){
        printf("Erreur d'allocation de mémoire\n");
        return;
    }

    newRendezVous->rendezVous = rendezVous;
    newRendezVous->next = NULL;
    RendezVousNode* actuelle = (RendezVousNode*)contact->next;
    if (actuelle == NULL) {
        contact->next = (StringNode*)newRendezVous;}
    else{
        while(actuelle->next != NULL){
            actuelle = actuelle->next;
        }
        actuelle->next = newRendezVous;
    }
    printf("Rendez-Vous ajouté: \nDate : %s\nDescription : %s\n", rendezVous.date, rendezVous.description);
}

void displayRendezVous_Contact(StringNode* contact) {
    if (contact->next == NULL) {
        printf("Pas de rendez-vous pour ce contact\n");
        return;
    }
    RendezVousNode* rendezvous = (RendezVousNode*)contact->next;
    printf("rendez-vous pour '%s':\n", contact->value);
    while (rendezvous != NULL){
        printf("Date: %s\n", rendezvous->rendezVous.date);
        printf("Description: %s\n\n", rendezvous->rendezVous.description);
        rendezvous = rendezvous->next;
    }
}
void saveRendezVous_File(StringList* contactList) {
    FILE *file = fopen("appointments.txt", "w");
    if (file == NULL) {
        printf("Erreur pour ouvrir le fichier.\n");
        return;
    }
    for (int i = contactList->max_level; i >= 0; --i) {
        StringNode *actuelle = contactList->heads[i];
        while (actuelle != NULL) {
            RendezVousNode *rendezvous = (RendezVousNode *) actuelle->next;
            while (rendezvous != NULL) {
                fprintf(file, "%s %s %s\n", actuelle->value, rendezvous->rendezVous.date,
                        rendezvous->rendezVous.description);
                rendezvous = rendezvous->next;
            }
            actuelle = actuelle->next[i];
        }
    }
    fclose(file);
}
void deleteRendezVous(StringNode *contact) {
    if (contact->next == NULL) {
        printf("Pas de rendez_vous pour ce contact.\n");
        return;
    }
    printf("Entrer la date du rendez-vous à supprimer : ");
    char dateToDelete[11];
    scanf("%10s", dateToDelete);
    RendezVousNode *rendezvous = (RendezVousNode *) contact->next;
    RendezVousNode *prev = NULL;
    while (rendezvous != NULL) {
        if (strcmp(rendezvous->rendezVous.date, dateToDelete) == 0) {
            if (prev == NULL) {
                contact->next = rendezvous->next;
            } else {
                prev->next = rendezvous->next;
            }
            free(rendezvous);
            printf("Rendez-Vous supprimé.\n");
            return;
        }
        prev = rendezvous;
        rendezvous = rendezvous->next;
    }
    printf("rendez-vous pas trouvé.\n");
}
    void calculInsertionTemps(int maxLevel) {
        startTimer();
        for (int i = 0; i <= maxLevel; ++i) {
            StringList *contactList = create_char_List(i);
            for (int j = 0; j < 10; ++j) {
                char contactName[MAX_NOM_LENGTH];
                sprintf(contactName, "Contact_%d", j);
                StringNode *newNode = (StringNode *) malloc(sizeof(StringNode));
                newNode->value = strdup(contactName);
                newNode->level = rand() % (i + 1);
                newNode->next = NULL;
                insert_char_tri(contactList, newNode);
            }
            displayTime();
        }
        stopTimer();
    }


    void loadRendezVousFile(StringList *contactList) {
        FILE *file = fopen("appointments.txt", "r");
        if (file == NULL) {
            printf("Erreur pour ouvrir le fichier.\n");
            return;
        }
        char contactName[MAX_NOM_LENGTH];
        char date[11];
        char description[MAX_LENGTH];
        while (fscanf(file, "%s %s %s", contactName, date, description) != EOF) {
            StringNode *contact = recherche_nom_niveau(contactList, contactName);
            if (contact != NULL) {
                RendezVousNode *newRendezVous = (RendezVousNode *) malloc(sizeof(RendezVousNode));
                if (newRendezVous == NULL) {
                    printf("Erreur d'allocation de mémoire\n");
                    return;
                }
                strcpy(newRendezVous->rendezVous.date, date);
                strcpy(newRendezVous->rendezVous.description, description);
                newRendezVous->next = NULL;
                if (contact->next == NULL) {
                    contact->next = (struct StringNode *) newRendezVous;
                } else {
                    StringNode *actuelle = contact->next;
                    while (actuelle->next != NULL) {
                        actuelle = actuelle->next;
                    }
                    actuelle->next = (struct StringNode **) newRendezVous;
                }
            }
        }
        fclose(file);

    }