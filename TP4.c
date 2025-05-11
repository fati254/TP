#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Etudiant {
    int id ; 
    char nom [50];
    float moyenne ; 
    struct Etudiant* next ; 
    struct Etudiant* prev ; 
}Etudiant ; 

//creation d'un etudiant 

Etudiant* creer_etudiant(){
    Etudiant *etu = (Etudiant*)malloc(sizeof(Etudiant));
    if(etu == NULL){
        printf("echec d'allocation \n");
        return NULL ; 
    }
    printf("ID d'etudiant : \n");
    scanf("%d", &etu->id);
    printf("Nom d'etudiant : \n");
    scanf(" %49s", etu->nom);
    printf("Moyenne d'etudiant : \n");
    scanf(" %f", &etu->moyenne);
   etu->next = NULL ; 
   etu->prev = NULL ; 
   return etu ;
    
}

//calculer la longueur 

int longueur(Etudiant* head ){
    Etudiant* tmp =head ; 
    int cpt=0; 
    while(tmp!= NULL){
        cpt++; 
        tmp=tmp->next ; 
    }
    return cpt ; 
}

//Insertion a une position donnee 

Etudiant* ajouter_position(Etudiant* head , Etudiant* nouveau , int pos ){
    if(head == NULL){
        printf("La liste est vide \n");
        return NULL ; 
    }
    Etudiant *etu = creer_etudiant();
    if( pos == 0 ){
        etu->next = head ; 
        head ->prev = etu ; 
        head = etu ; 
        return head ; 
    }
    else if( pos < 0 || pos > longueur(head)+1 ){
        printf("La position Invalide \n");
        return head ; 
    }
    else {
        Etudiant *tmp = head ; 
      for(int i=0; i<pos ;i++)
          tmp=tmp->next ; 

      etu->next = tmp->next ; 
      etu->prev = tmp ; 
      tmp->next = etu ; 
      if(tmp->next != NULL)
      tmp->next->prev = etu;
    
    

    }
    return head ; 
}

//suppresion a une position 

Etudiant* supprimer_position(Etudiant* head, int pos) {
    int len = longueur(head);

    if (head == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    if (pos < 0 || pos >= len) {
        printf("Position invalide.\n");
        return head;
    }

    Etudiant* tmp = head;

    if (pos == 0) {
        head = head->next;
        if (head != NULL)
            head->prev = NULL;

        free(tmp);
        return head;
    }

    for (int i = 0; i < pos; i++) {
        tmp = tmp->next;
    }

    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;

    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;

    free(tmp);
    return head;
}

//affichage direct 

void afficher_liste(Etudiant* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Etudiant* tmp = head;
    int i = 1;

    while (tmp != NULL) {
        printf("\n--- Etudiant %d ---\n", i++);
        printf("ID       : %d\n", tmp->id);
        printf("Nom      : %s\n", tmp->nom);
        printf("Moyenne  : %.2f\n", tmp->moyenne);
        tmp = tmp->next;
    }
}

//Dernier element de la liste 

Etudiant* derniere_cellule(Etudiant* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    Etudiant* tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    return tmp; 
}

//Affichage en sens inverse 

void afficher_liste_inverse(Etudiant* dernier) {
    if (dernier == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Etudiant* tmp = dernier;
    
    while (tmp != NULL) {
        printf("ID d'etudiant : %d\n", tmp->id);
        printf("Nom d'etudiant : %s\n", tmp->nom);
        printf("Moyenne d'etudiant : %.2f\n", tmp->moyenne);
        printf("---------------------------------------------------------\n");

        tmp = tmp->prev; 
    }
}

//rechercher id 

int chercher_etudiant(Etudiant* head, int id) {
    Etudiant* tmp = head;

    while (tmp != NULL) {
        if (tmp->id == id) {
            printf("Etudiant trouvé !\n");
            printf("ID : %d\n", tmp->id);
            printf("Nom : %s\n", tmp->nom);
            printf("Moyenne : %.2f\n", tmp->moyenne);
            return 1;  
        }
        tmp = tmp->next;
    }

    printf("Etudiant avec ID %d non trouvé.\n", id);
    return 0; 
}

//tri en ordre croissant 

Etudiant* tri(Etudiant* head) {
    if (head == NULL || head->next == NULL)
        return head;

    int per ;
    Etudiant* tmp;

    do {
        per = 0;
        tmp = head;

        while (tmp->next != NULL) {
            if (tmp->moyenne > tmp->next->moyenne) {
               
                int id_temp = tmp->id;
                char nom_temp[50];
                float moy_temp = tmp->moyenne;
                strcpy(nom_temp, tmp->nom);

                tmp->id = tmp->next->id;
                strcpy(tmp->nom, tmp->next->nom);
                tmp->moyenne = tmp->next->moyenne;

                tmp->next->id = id_temp;
                strcpy(tmp->next->nom, nom_temp);
                tmp->next->moyenne = moy_temp;

                per = 1;
            }
            tmp = tmp->next;
        }
    } while (per);

    return head;
}

//modifier la moyenne d'un etudiant 

Etudiant* modifier_moyenne(Etudiant* head, int position, float nouvelle_moyenne) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return head;
    }

    int len = longueur(head); 
    if (position < 0 || position >= len) {
        printf("Position invalide.\n");
        return head;
    }

    Etudiant* tmp = head;
    for (int i = 0; i < position; i++) {
        tmp = tmp->next;
    }

    printf("Ancienne moyenne : %.2f\n", tmp->moyenne);
    tmp->moyenne = nouvelle_moyenne;
    printf("Nouvelle moyenne : %.2f\n", tmp->moyenne);

    return head;
}

//maiiiiiiiiiiiiiiiiiiin

int main() {
    Etudiant* liste = NULL;
    int choix, pos, id;
    float nouv_moy;

    while (1) {
        printf("\n========================= MENU ========================\n");
        printf("1. Créer la liste avec un premier étudiant\n");
        printf("2. Ajouter un étudiant à une position\n");
        printf("3. Supprimer un étudiant à une position\n");
        printf("4. Afficher la liste\n");
        printf("5. Afficher la liste en sens inverse\n");
        printf("6. Rechercher un étudiant par ID\n");
        printf("7. Trier la liste par moyenne\n");
        printf("8. Modifier la moyenne d'un étudiant\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                if (liste != NULL) {
                    printf("La liste est déjà créée.\n");
                } else {
                    liste = creer_etudiant();
                }
                break;

            case 2:
                if (liste == NULL) {
                    printf("Veuillez d'abord créer la liste (option 1).\n");
                } else {
                    printf("Position d'insertion : ");
                    scanf("%d", &pos);
                    liste = ajouter_position(liste, NULL, pos);
                }
                break;

            case 3:
                printf("Position à supprimer : ");
                scanf("%d", &pos);
                liste = supprimer_position(liste, pos);
                break;

            case 4:
                afficher_liste(liste);
                break;

            case 5: {
                Etudiant* dernier = derniere_cellule(liste);
                afficher_liste_inverse(dernier);
                break;
            }

            case 6:
                printf("Entrez l'ID de l'étudiant à chercher : ");
                scanf("%d", &id);
                chercher_etudiant(liste, id);
                break;

            case 7:
                liste = tri(liste);
                printf("Liste triée par moyenne !\n");
                break;

            case 8:
                printf("Position de l'étudiant à modifier : ");
                scanf("%d", &pos);
                printf("Nouvelle moyenne : ");
                scanf("%f", &nouv_moy);
                liste = modifier_moyenne(liste, pos, nouv_moy);
                break;

            case 0:
                printf("Fin du programme.\n");
                return 0;

            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
