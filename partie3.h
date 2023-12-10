
#define MAX_CONTACTS 100
#define MAX_LENGTH 100
#include "List.h"
typedef struct StringNode {
    char *value;
    struct StringNode **next;
    int level;
} StringNode;
typedef struct {
    int max_level;
    StringNode **heads;
} StringList;

typedef struct RendezVous {
    char date[11];  // Date au format "AAAA-MM-JJ"
    char description[100];
} RendezVous;

typedef struct RendezVousNode {
    RendezVous rendezVous;   // Détails du rendez-vous
    struct RendezVousNode* next; // Prochain rendez-vous dans la liste
} RendezVousNode;



void calculInsertionTemps(int maxLevel);
void displayRendezVous_Contact(StringNode* contact);
void insert_char_tri(StringList *mylist, StringNode *newNode);
StringNode* search_char_Levels(StringList* mylist, const char* targetName);
void insert_char_Node(StringList *mylist, StringNode *newNode);
StringList *create_char_List(int n);
StringNode* recherche_nom_niveau(StringList* mylist, const char* targetName);
void add_rendezvous(StringNode* contact, RendezVous rendezVous);
void saveRendezVous_File(StringList* contactList);
void display_char_List(StringList *mylist);
void loadRendezVousFile(StringList* contactList);
void deleteRendezVous(StringNode* contact);