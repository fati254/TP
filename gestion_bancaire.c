#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virement {
    float montant;
    char compte_source[100];
    char compte_beneficiaire[100];
    char date[100];
    int id;
    struct virement* next;
    struct virement* prev;
} virement;

typedef struct pile {
    virement data;
    struct pile* next;
} pile;

typedef struct file {
    virement data;
    struct file* next;
} file;

virement* head = NULL;
pile* sommet = NULL;
file* debut = NULL;
file* fin = NULL;

void ajouterVirementDebut(float montant, char* c_source, char* c_beneficiaire, char* date, int id) {
    virement* v = (virement*)malloc(sizeof(virement));
    if (v == NULL ) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    v->id = id;
    v->montant = montant;
    strcpy(v->compte_source, c_source);
    strcpy(v->compte_beneficiaire, c_beneficiaire);
    strcpy(v->date, date);

    v->prev = NULL;
    v->next = NULL;

    if (head == NULL) {
        head = v;
    }
     else {
         v->next = head ; 
         head->prev = v ; 
         head = v ; 
    }

    printf(" Virement ajouté au début de la liste avec succès.\n");
}

void ajouterVirementFin(float montant, char* c_source, char* c_beneficiaire, char* date, int id) {
    virement* v = (virement*)malloc(sizeof(virement));
    if (v == NULL ) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    v->id = id;
    v->montant = montant;
    strcpy(v->compte_source, c_source);
    strcpy(v->compte_beneficiaire, c_beneficiaire);
    strcpy(v->date, date);

    v->prev = NULL;
    v->next = NULL;

    if (head == NULL) {
        head = v;
    } else {
        virement* tmp = head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        v->prev = tmp;
        tmp->next = v;
    }

    printf(" Virement ajouté à la liste.\n");
}


void ajouterApresID(int id_ref, float montant, char* c_source, char* c_beneficiaire, char* date, int id) {
    virement* temp = head;
    while (temp && temp->id != id_ref)
        temp = temp->next;

    if (!temp) {
        printf(" ID %d non trouvé.\n", id_ref);
        return;
    }

    virement* v = (virement*)malloc(sizeof(virement));
    if (v == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    v->id = id;
    v->montant = montant;
    strcpy(v->compte_source, c_source);
    strcpy(v->compte_beneficiaire, c_beneficiaire);
    strcpy(v->date, date);

    v->prev = temp;
    v->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = v;

    temp->next = v;

    printf(" Virement ajouté après l'ID %d.\n", id_ref);
}


 

void afficherVirements() {
    virement* tmp = head;
    if (tmp == NULL) {
        printf(" Aucun virement à afficher.\n");
        return;
    }
    printf(" Liste des virements :\n");
    while (tmp !=NULL) {
        printf("Virement : \n Id: %d \n compte source: %s \n compte beneficiaire: %s \n Date(YYYY-MM-DD): %s \n Montant: %.2f\n\n",
               tmp->id, tmp->compte_source, tmp->compte_beneficiaire, tmp->date, tmp->montant);
        tmp = tmp->next;
    }
}

void modifierVirement(int id  ,float montant,char* source,char* beneficiaire,char* date) {
    virement* tmp = head;

    while (tmp != NULL && tmp->id != id) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        printf(" Aucun virement trouvé avec l'ID %d.\n", id);
        return;
    }

    printf(" Modification du virement avec ID %d :\n", id);

    printf("Nouveau montant : ");
    scanf("%f", &tmp->montant);

    printf("Nouveau compte source (sans espaces) : ");
    scanf("%s", tmp->compte_source);

    printf("Nouveau compte bénéficiaire (sans espaces) : ");
    scanf("%s", tmp->compte_beneficiaire);

    printf("Nouvelle date (YYYY-MM-DD) : ");
    scanf("%s", tmp->date);

    printf(" Virement modifié avec succès.\n");
}

//on va emplier pour la pile 
void empiler(virement vire) {
    pile* nouvelElement = (pile*)malloc(sizeof(pile));
    if (!nouvelElement) {
        printf(" Erreur d'allocation mémoire.\n");
        return;
    }

    nouvelElement->data = vire;
    nouvelElement->next = sommet;
    sommet = nouvelElement;
}


void supprimerDebut() {
    if (head == NULL) {
        printf(" Liste vide. Rien à supprimer.\n");
        return;
    }

    virement* tmp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;
       
        empiler(*tmp);
    printf("🗑️ Virement avec ID %d supprimé du début.\n", tmp->id);
    free(tmp);
}

void supprimerFin() {
    if (head == NULL) {
        printf(" Liste vide. Rien à supprimer.\n");
        return;
    }

    virement* tmp = head;

    if (tmp->next == NULL) {
        printf(" Virement avec ID %d supprimé de la fin.\n", tmp->id);
        free(tmp);
        head = NULL;
        return;
    }

    while (tmp->next != NULL)
        tmp = tmp->next;
        
        empiler(*tmp);
    tmp->prev->next = NULL;
    printf(" Virement avec ID %d supprimé de la fin.\n", tmp->id);
    free(tmp);
}

void supprimerApresID(int id_ref) {
    virement* tmp = head;

    while (tmp != NULL && tmp->id != id_ref)
        tmp = tmp->next;

    if (tmp == NULL || tmp->next == NULL) {
        printf(" Impossible de supprimer : ID %d inexistant ou aucun virement après lui.\n", id_ref);
        return;
    }

    virement* toDelete = tmp->next;
    tmp->next = toDelete->next;

    if (toDelete->next != NULL)
        toDelete->next->prev = tmp;
         empiler(*tmp);
    printf(" Virement avec ID %d supprimé après ID %d.\n", toDelete->id, id_ref);
    free(toDelete);
}

void rechercherParMontant(float montant) {
    virement* tmp = head;
    int trouve = 0;

    printf("\n Recherche des virements avec montant = %.2f\n", montant);

    while (tmp != NULL) {
        if (tmp->montant == montant) {
            printf("\n Virement trouvé :\n");
            printf("ID : %d\n", tmp->id);
            printf("Compte source : %s\n", tmp->compte_source);
            printf("Compte bénéficiaire : %s\n", tmp->compte_beneficiaire);
            printf("Date : %s\n", tmp->date);
            printf("Montant : %.2f\n", tmp->montant);
            trouve = 1;
        }
        tmp = tmp->next;
    }

    if (!trouve) {
        printf(" Aucun virement trouvé avec ce montant.\n");
    }
}

void rechercherParCompteSource(char* source) {
    virement* tmp = head;
    int trouve = 0;

    while (tmp != NULL) {
        if (strcmp(tmp->compte_source, source) == 0) {
            printf(" Virement trouvé :\n");
            printf("ID: %d | Montant: %.2f | Source: %s | Bénéficiaire: %s | Date: %s\n\n",
                   tmp->id, tmp->montant, tmp->compte_source, tmp->compte_beneficiaire, tmp->date);
            trouve = 1;
        }
        tmp = tmp->next;
    }

    if (!trouve) {
        printf(" Aucun virement trouvé pour le compte source : %s\n", source);
    }
}


void rechercherParBeneficiaire(char* beneficiaire) {
    virement* tmp = head;
    int trouve = 0;

    while (tmp != NULL) {
        if (strcmp(tmp->compte_beneficiaire, beneficiaire) == 0) {
            printf(" Virement trouvé :\n");
            printf("ID: %d | Montant: %.2f | Source: %s | Bénéficiaire: %s | Date: %s\n\n",
                   tmp->id, tmp->montant, tmp->compte_source, tmp->compte_beneficiaire, tmp->date);
            trouve = 1;
        }
        tmp = tmp->next;
    }

    if (!trouve) {
        printf(" Aucun virement trouvé pour le bénéficiaire : %s\n", beneficiaire);
    }
}

void rechercheAvancee(float montantMin, char* source, char* date) {
    virement* tmp = head;
    int trouve = 0;

    while (tmp != NULL) {
        if (tmp->montant >= montantMin &&
            strcmp(tmp->compte_source, source) == 0 &&
            strcmp(tmp->date, date) == 0) {

            printf(" Virement correspondant trouvé :\n");
            printf("ID: %d | Montant: %.2f | Source: %s | Bénéficiaire: %s | Date: %s\n\n",
                   tmp->id, tmp->montant, tmp->compte_source, tmp->compte_beneficiaire, tmp->date);
            trouve = 1;
        }
        tmp = tmp->next;
    }

    if (!trouve) {
        printf(" Aucun virement ne correspond aux critères avancés.\n");
    }
}

 
void restaurerDernierVirementSupprime() {
    if (sommet == NULL) {
        printf(" Aucune suppression à annuler (pile vide).\n");
        return;
    }

    virement vire = sommet->data;

    pile* temp = sommet;
    sommet = sommet->next;
    free(temp);

    ajouterVirementFin(vire.montant, vire.compte_source, vire.compte_beneficiaire, vire.date, vire.id);

    printf(" Virement ID %d restauré avec succès.\n", vire.id);
}

void afficherVirementsSupprimes() {
    if (sommet == NULL) {
        printf(" Aucun virement supprimé à afficher.\n");
        return;
    }

    pile* tmp = sommet;
    printf(" Virements supprimés (pile) :\n");

    while (tmp != NULL) {
        virement v = tmp->data;
        printf("ID: %d | Source: %s | Bénéficiaire: %s | Date: %s | Montant: %.2f\n",
               v.id, v.compte_source, v.compte_beneficiaire, v.date, v.montant);
        tmp = tmp->next;
    }
}

void effectuerVirement(int id) {
    virement* tmp = head;

    while (tmp != NULL && tmp->id != id) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        printf(" Aucun virement trouvé avec l'ID %d.\n", id);
        return;
    }

    file* nouveau = (file*)malloc(sizeof(file));
    if (nouveau == NULL) {
        printf(" Erreur d'allocation mémoire pour la file.\n");
        return;
    }

    nouveau->data = *tmp;
    nouveau->next = NULL;

    if (debut == NULL) {
        debut = nouveau;
        fin = nouveau;
    } else {
        fin->next = nouveau;
        fin = nouveau;
    }

    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else
        head = tmp->next;

    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;

    free(tmp);

    printf(" Virement exécuté et déplacé dans la file avec succès.\n");
}

void afficherFile() {
    file* tmp = debut;
    if (tmp == NULL) {
        printf(" Aucune opération en attente dans la file.\n");
        return;
    }

    printf(" Virements exécutés (dans la file) :\n");
    while (tmp != NULL) {
        printf("ID: %d | Montant: %.2f | Source: %s | Bénéficiaire: %s | Date: %s\n",
               tmp->data.id, tmp->data.montant, tmp->data.compte_source,
               tmp->data.compte_beneficiaire, tmp->data.date);
        tmp = tmp->next;
    }
}

void demanderDonneesVirement(float *montant, char *source, char *beneficiaire, char *date, int *id) {
    printf("\nEntrer ID : ");
    scanf("%d", id);
    printf("\nEntrer montant : ");
    scanf("%f", montant);
    printf("\nEntrer compte source (sans espaces) : ");
    scanf("%s", source);
    printf("\nEntrer compte bénéficiaire (sans espaces) : ");
    scanf("%s", beneficiaire);
    printf("\nEntrer date (YYYY-MM-DD) : ");
    scanf("%s", date);
}

int main() {
    int choixPrincipal, choixAjout, choixModifier, choixSupprimer, choixRechercher;
    int id, idRef;
    float montant;
    char source[100], beneficiaire[100], date[100];

    while (1) {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Ajouter un virement\n");
        printf("2. Modifier un virement\n");
        printf("3. Supprimer un virement\n");
        printf("4. Rechercher un virement\n");
        printf("5. Effectuer un virement\n");
        printf("6. Afficher tous les virements\n");
        printf("7. Restaurer dernier virement supprimé\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choixPrincipal);

        switch (choixPrincipal) {
            case 1: 
                printf("\n-- Ajouter un virement --\n");
                printf("1. Au début\n");
                printf("2. Après un ID donné\n");
                printf("3. À la fin\n");
                printf("Votre choix : ");
                scanf("%d", &choixAjout);
                demanderDonneesVirement(&montant, source, beneficiaire, date, &id);
                switch (choixAjout) {
                    case 1:
                        ajouterVirementDebut(montant, source, beneficiaire, date, id);
                        break;
                    case 2:
                        printf("Entrer l'ID après lequel ajouter : ");
                        scanf("%d", &idRef);
                        ajouterApresID(idRef, montant, source, beneficiaire, date, id);
                        break;
                    case 3:
                        ajouterVirementFin(montant, source, beneficiaire, date, id);
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 2:
                printf("\n-- Modifier un virement --\n");
                printf("Entrer l'ID du virement à modifier : ");
                scanf("%d", &id);
                modifierVirement(id, 0, NULL, NULL, NULL); 
                break;

            case 3:
                printf("\n-- Supprimer un virement --\n");
                printf("1. Au début\n");
                printf("2. Après un ID donné\n");
                printf("3. À la fin\n");
                printf("Votre choix : ");
                scanf("%d", &choixSupprimer);
                switch (choixSupprimer) {
                    case 1:
                        supprimerDebut();
                        break;
                    case 2:
                        printf("Entrer l'ID après lequel supprimer : ");
                        scanf("%d", &idRef);
                        supprimerApresID(idRef);
                        break;
                    case 3:
                        supprimerFin();
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 4:
                printf("\n-- Rechercher un virement --\n");
                printf("1. Par montant\n");
                printf("2. Par compte source\n");
                printf("3. Par compte bénéficiaire\n");
                printf("4. Recherche avancée\n");
                printf("Votre choix : ");
                scanf("%d", &choixRechercher);
                switch (choixRechercher) {
                    case 1:
                        printf("Entrer le montant recherché : ");
                        scanf("%f", &montant);
                        rechercherParMontant(montant);
                        break;
                    case 2:
                        printf("Entrer le compte source : ");
                        scanf("%s", source);
                        rechercherParCompteSource(source);
                        break;
                    case 3:
                        printf("Entrer le compte bénéficiaire : ");
                        scanf("%s", beneficiaire);
                        rechercherParBeneficiaire(beneficiaire);
                        break;
                    case 4:
                        printf("Montant minimum : ");
                        scanf("%f", &montant);
                        printf("Compte source : ");
                        scanf("%s", source);
                        printf("Date (YYYY-MM-DD) : ");
                        scanf("%s", date);
                        rechercheAvancee(montant, source, date);
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 5:
                printf("\n-- Effectuer un virement --\n");
                printf("Entrer l'ID du virement à effectuer : ");
                scanf("%d", &id);
                effectuerVirement(id);
                break;

            case 6:
                afficherVirements();
                break;

            case 7:
                restaurerDernierVirementSupprime();
                break;

            case 0:
                printf("Au revoir !\n");
                exit(0);

            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
