#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct Date
{
    char jour[3];
    char mois[3];
    char annee[5];
} date;
typedef struct Produit
{
    char *Nom_produit;
    char Reference[100];
    float Montant;
    date DateAchat;
} produit;
typedef struct Liste
{
    produit cellule;
    struct Liste *next;
} liste;

// liste produit
liste *creer_liste_produits()
{
    liste *tmp = NULL;
    liste *head = NULL;

    int nbr;
    printf("Combien le nbr de produits : \n");
    scanf("%d", &nbr);

    for (int i = 0; i < nbr; i++)
    {

        liste *nv = (liste*)malloc(sizeof(liste));
        if (nv == NULL)
        {
            printf("echec d'alocation \n");
            return NULL;
        }
        nv->cellule.Nom_produit = (char *)malloc(100 * sizeof(char));
        if (nv->cellule.Nom_produit == NULL)
        {
            printf("Échec d'allocation pour le nom du produit.\n");
            free(nv);
            return head;
        }
        printf("Nom de produit : \n");
        scanf(" %s", nv->cellule.Nom_produit);
        printf("Reference : \n");
        scanf(" %s", nv->cellule.Reference);
        printf("Montant : \n");
        scanf(" %f", &nv->cellule.Montant);
        printf("\n------la Date de Produit -------\n");
        printf("Entrez le jour : \n");
        scanf(" %s", nv->cellule.DateAchat.jour);
        printf("Entrez le mois : \n");
        scanf(" %s", nv->cellule.DateAchat.mois);
        printf("Entrez l'annee : \n");
        scanf(" %s", nv->cellule.DateAchat.annee);

        nv->next = NULL;
        if (head == NULL)
        {
            head = nv;
        }
        else
        {
            tmp->next = nv;
        }
        tmp = nv;
    }

    return head;
}

// list vide
int est_vide(liste *head)
{
    if (head == NULL)
        return 1;

    return 0;
}

// liste* affichage

void afficher_produit()
{
    liste *tmp = NULL;
    liste *head;
    if (tmp == NULL)
    {
        printf("La liste est vide.\n");
        return;
    }

    while (tmp != NULL)
    {

        printf("Nom du produit : %s\n", tmp->cellule.Nom_produit);
        printf("Référence : %s\n", tmp->cellule.Reference);
        printf("Montant : %.2f\n", tmp->cellule.Montant);
        printf("Date d'achat : %s/%s/%s\n", tmp->cellule.DateAchat.jour, tmp->cellule.DateAchat.mois, tmp->cellule.DateAchat.annee);
        printf("\n------------------------------Le produit suivant-----------------------------------\n");
        tmp = tmp->next;
    }
}

// creer

liste *creer_produit()
{
    liste *nv = (liste *)malloc(sizeof(liste));
    if (nv == NULL)
    {
        printf("echec d'allocation.\n");
        return NULL;
    }

    nv->cellule.Nom_produit = (char *)malloc(100 * sizeof(char));
    if (!nv->cellule.Nom_produit)
    {
        printf("echec d'allocation du nom.\n");
        free(nv);
        return NULL;
    }

    printf("Nom de produit : ");
    scanf(" %s", nv->cellule.Nom_produit);

    printf("Reference : ");
    scanf(" %s", nv->cellule.Reference);

    printf("Montant : ");
    scanf(" %f", &nv->cellule.Montant);

    printf("Jour : ");
    scanf(" %s", nv->cellule.DateAchat.jour);

    printf("Mois : ");
    scanf(" %s", nv->cellule.DateAchat.mois);

    printf("Annee : ");
    scanf(" %s", nv->cellule.DateAchat.annee);

    nv->next = NULL;
    return nv;
}

// liste ajouter au debutt

liste *ajouter_debut(liste *head)
{
    liste *nv = creer_produit();
    if (head == NULL)
        head = nv;

    nv->next = head;
    head = nv;
    return head;
}

// liste ajouter a la fin

liste *ajouter_fin(liste *head)
{
    liste *nv = creer_produit();

    if (head == NULL)
        head = nv;

    liste *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nv;
    return head;
}

// Je remarquer que l'ajouter a la fin prend plus de temps par rapport a l'ajouter au debut

// affichage avec des parametre

void afficher_produits(liste *head)
{
    if (head == NULL)
    {
        printf("La liste est vide.\n");
        return;
    }

    liste *tmp = head;
    int index = 1;

    while (tmp != NULL)
    {
        printf("\n--- Produit %d ---\n", index++);
        printf("Nom du produit : %s\n", tmp->cellule.Nom_produit);
        printf("Reference : %s\n", tmp->cellule.Reference);
        printf("Montant : %.2f\n", tmp->cellule.Montant);
        printf("Date d'achat : %s/%s/%s\n",
               tmp->cellule.DateAchat.jour,
               tmp->cellule.DateAchat.mois,
               tmp->cellule.DateAchat.annee);
        printf("-----------------------------------\n");
        tmp = tmp->next;
    }
}

// la longueur

int longueur_liste(liste *head)
{
    int cpt = 0;
    liste *tmp = head;

    while (tmp != NULL)
    {
        cpt++;
        tmp = tmp->next;
    }

    return cpt;
}

// void filtre de date

void filtrer_date(liste *head, date dt)
{
    liste *tmp = head;
    int trouve = 0;

    while (tmp != NULL)
    {
        if (
            strcmp(tmp->cellule.DateAchat.jour, dt.jour) == 0 &&
            strcmp(tmp->cellule.DateAchat.mois, dt.mois) == 0 &&
            strcmp(tmp->cellule.DateAchat.annee, dt.annee) == 0)
        {
            printf("Nom du produit : %s\n", tmp->cellule.Nom_produit);
            printf("Reference : %s\n", tmp->cellule.Reference);
            printf("Montant : %.2f\n", tmp->cellule.Montant);
            printf("Date d'achat : %s/%s/%s\n",
                   tmp->cellule.DateAchat.jour,
                   tmp->cellule.DateAchat.mois,
                   tmp->cellule.DateAchat.annee);
            printf("----------------------------------------\n");
            trouve = 1;
        }
        tmp = tmp->next;
    }

    if (!trouve)
    {
        printf("Aucun produit trouvé avec la date %s/%s/%s.\n", dt.jour, dt.mois, dt.annee);
    }
}

// supprimer debut

liste *supprimer_debut(liste *head)
{
    if (head == NULL)
    {
        printf("La liste est vide \n");
        return NULL;
    }
    liste *tmp = head;
    head = head->next;
    if (tmp->cellule.Nom_produit != NULL)
    {
        free(tmp->cellule.Nom_produit);
    }
    free(tmp);
    return head;
}

// supprimer fin

liste *supprimer_fin(liste *head)
{
    if (head == NULL)
    {
        printf("La liste est vide.\n");
        return NULL;
    }

    if (head->next == NULL)
    {
        if (head->cellule.Nom_produit != NULL)
            free(head->cellule.Nom_produit);
        free(head);
        return NULL;
    }

    liste *tmp = head;
    liste *prev = NULL;

    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp->cellule.Nom_produit != NULL)
        free(tmp->cellule.Nom_produit);
    free(tmp);

    prev->next = NULL;

    return head;
}

// rembourser
liste *rembourser(liste *head, char *refer)
{
    if (head == NULL)
    {
        printf("La liste est vide.\n");
        return NULL;
    }

    if (strcmp(head->cellule.Reference, refer) == 0)
    {
        return supprimer_debut(head);
    }

    liste *tmp = head;
    liste *prev = NULL;

    while (tmp != NULL && strcmp(tmp->cellule.Reference, refer) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        printf("Produit avec la référence %s non trouvé.\n", refer);
        return head;
    }

    if (tmp->next == NULL)
    {
        return supprimer_fin(head);
    }

    prev->next = tmp->next;
    if (tmp->cellule.Nom_produit != NULL)
        free(tmp->cellule.Nom_produit);
    free(tmp);

    return head;
}

// maiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiin

int main()
{
    liste *produits = NULL;
    int choix;
    char reference[100];
    date dt;

    do
    {
        printf("\n========= MENU PRODUITS =========\n");
        printf("1. Créer une liste de produits\n");
        printf("2. Afficher les produits\n");
        printf("3. Ajouter un produit au début\n");
        printf("4. Ajouter un produit à la fin\n");
        printf("5. Supprimer le premier produit\n");
        printf("6. Supprimer le dernier produit\n");
        printf("7. Rembourser (supprimer par référence)\n");
        printf("8. Filtrer par date\n");
        printf("9. Afficher la longueur de la liste\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            produits = creer_liste_produits();
            break;

        case 2:
            afficher_produits(produits);
            break;

        case 3:
            produits = ajouter_debut(produits);
            break;

        case 4:
            produits = ajouter_fin(produits);
            break;

        case 5:
            produits = supprimer_debut(produits);
            break;

        case 6:
            produits = supprimer_fin(produits);
            break;

        case 7:
            printf("Entrez la référence du produit à rembourser : ");
            scanf(" %s", reference);
            produits = rembourser(produits, reference);
            break;

        case 8:
            printf("Entrez la date à filtrer :\n");
            printf("Jour : ");
            scanf(" %s", dt.jour);
            printf("Mois : ");
            scanf(" %s", dt.mois);
            printf("Année : ");
            scanf(" %s", dt.annee);
            filtrer_date(produits, dt);
            break;

        case 9:
            printf("Nombre de produits dans la liste : %d\n", longueur_liste(produits));
            break;

        case 0:
            printf("Fin du programme.\n");
            break;

        default:
            printf("Choix invalide !\n");
        }
    } while (choix != 0);

    return 0;
}
