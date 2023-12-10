#include "List.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "partie3.h"
#include <ctype.h>
#include <string.h>
#include <time.h>

/*int main() {
  startTimer();
  t_sk_list* myList = CreateList(5);
  t_sk_cell* cell1 = CreateCell(4,0);
  t_sk_cell* cell2 = CreateCell(1, 3);
  t_sk_cell* cell3 = CreateCell(65, 0);
  t_sk_cell* cell4 = CreateCell(13,1);
  t_sk_cell* cell5 = CreateCell(10,4);
  t_sk_cell* cell6 = CreateCell(35,4);
  add_cell(myList, cell6);
  add_cell(myList, cell5);
  add_cell(myList, cell4);
  add_cell(myList, cell1);
  add_cell(myList, cell2);
  add_cell(myList, cell3);
  printf("- MyList allignée:\n\n");
  display_aligne_list(myList);
  printf("\n\n- MyList non allignée:\n\n");
  display_all_level(myList);
  printf("\n\n- MyList au niveau 0:\n\n");
  display_List(myList,0);
  printf("\n\n- liste_puiss2 allignée qui ajoute une cellule de plus à chaque puissance de 2 de manière symétrique :\n\n");
  t_sk_list* list2 = CreateList(3);
  liste_puiss2(list2->max_level);
  printf("\n\n");
  printf("- recherche dans tous les niveaux:\n\n");
  recherche_tous_niveaux(myList,10);
  recherche_tous_niveaux(list2,4);
  printf("\n\n- recherche dans le niveau 0:\n\n");
  recherche_niveau0(list2, 2);
  printf("\n\n - timer\n\n");
  stopTimer();
  displayTime();
  free(getTimeAsString());

    return 0;
}*/

#define MAX_NOM_LENGTH 100
int main() {
  StringList *contactList = create_char_List(5);
  int choice;
  char searchName[MAX_NOM_LENGTH];
  StringNode *foundContact;
  RendezVous rendezVous;

  do {
            printf("\nMenu:\n");
            printf("1. Recherche d'un contact\n");
            printf("2. Affichage des rendez vous d'un contact\n");
            printf("3. Créer un contact\n");
            printf("4. Créer un rendez-vous pour un contact\n");
            printf("5. Supprimer un rendez-vous\n");
            printf("6. Sauvegarder le fichier pour tous les rendez-vous\n");
            printf("7. Charger le fichier de rendez-vous\n");
            printf("8. Fournir les temps de calcul pour l’insertion d’un nouveau contact\n");
            printf("0. Quitter\n");
            printf("Choix : ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                  printf("Nom du contact recherché : ");
                  scanf("%99s", searchName);
                  foundContact = search_char_Levels(contactList, searchName);
                  if (foundContact != NULL) {
                      printf("Contact '%s' trouvé \n", searchName);
                  } else {
                      printf("Contact pas trouvé.\n");
                  }
                    break;
                case 2:
                  printf("Nom du contact: ");
                  scanf("%s", searchName);
                  StringNode* ctct = search_char_Levels(contactList, searchName);
                  if (ctct != NULL) {
                      displayRendezVous_Contact(ctct);
                  } else {
                      printf("Contact pas trouvé.\n");
                  }
                    break;
                case 3:
                  printf("Nom du nouveau contact : ");
                  char searchName[MAX_NOM_LENGTH];
                  scanf("%99s", searchName);
                  StringNode *newNode = (StringNode *)malloc(sizeof(StringNode));
                  newNode->value = strdup(searchName);
                  newNode->level = 0;
                  newNode->next = NULL;
                  insert_char_tri(contactList, newNode);
                  printf("Contact ajouté avec succés.\n");
                  break;
              case 4:
                printf("Nom du contact : ");
                scanf("%99s", searchName);
                StringNode* contact = recherche_nom_niveau(contactList, searchName);
                if (contact != NULL) {
                    RendezVous rendezVous;
                    printf("Date du rendez-vous (format JJ-MM-AAAA) : ");
                    scanf("%10s", rendezVous.date);
                    printf("Description du rendez-vous : ");
                    scanf("%99s", rendezVous.description);
                    add_rendezvous(contact, rendezVous);
                } else {
                    printf("Contact pas trouvé.\n");
                }
                break;
                case 5:
                  printf("Nom du contact : ");
                  scanf("%s", searchName);
                  StringNode* contactToDelete = recherche_nom_niveau(contactList, searchName);
                  if (contactToDelete != NULL) {
                      deleteRendezVous(contactToDelete);
                  } else {
                      printf("Contact pas trouvé.\n");
                  }
                  break;
                case 6:
                  saveRendezVous_File(contactList);
                  printf("Les rendez-vous sont enregistrés dans un fichier.\n");
                  break;
                case 7:
                  loadRendezVousFile(contactList);
                  printf("Rendez-vous chargés à partir d’un fichier.\n");
                  break;
                case 8:
                  printf("Entrez le niveau maximum : ");
                  int maxlevl;
                  if (scanf("%d", &maxlevl) != 1) {
                      printf("Entrée non valide. Veuillez saisir un entier valide pour le niveau maximum.\n");
                      break;
                  }
                  printf("Temps d’insertion estimé pour le niveau maximum %d: ", maxlevl);
                  startTimer();
                  calculInsertionTemps(maxlevl);
                  stopTimer();
                  displayTime();
                  break;
                case 0:
                    printf("Fin du programme.\n");
                    break;
                default:
                    printf("Choix invalide recommencez.\n");
            }
        } while (choice != 0);
    return 0;

}