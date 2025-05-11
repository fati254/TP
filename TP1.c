#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    int valeur;
    struct noeud *next;
} noeud;

// Créer un nouveau noeud
noeud* creation(int _valeur) {
    noeud *nv = (noeud*)malloc(sizeof(noeud));
    if (nv == NULL) {
        printf("Échec d'allocation\n");
        return NULL;
    }
    nv->valeur = _valeur;
    nv->next = NULL;
    return nv;
}

// Ajouter au début
noeud* ajouterD(noeud *head, int _valeur) {
    noeud *nv = creation(_valeur);
    nv->next = head;
    return nv;
}

// Ajouter à la fin
noeud* ajouterF(noeud *head, int _valeur) {
    noeud *nv = creation(_valeur);
    if (head == NULL)
        return nv;

    noeud *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nv;
    return head;
}

// Taille de la liste
int taille(noeud *head) {
    int cpt = 0;
    noeud *tmp = head;
    while (tmp != NULL) {
        cpt++;
        tmp = tmp->next;
    }
    return cpt;
}

// Insertion à une position
noeud* insertionP(noeud *head, int pos, int _valeur) {
    if (pos < 0 || pos > taille(head)) {
        printf("Position invalide\n");
        return head;
    }

    if (pos == 0)
        return ajouterD(head, _valeur);

    noeud *nv = creation(_valeur);
    noeud *tmp = head;

    for (int i = 0; i < pos - 1; i++) {
        tmp = tmp->next;
    }

    nv->next = tmp->next;
    tmp->next = nv;
    return head;
}

// Recherche d'une valeur
noeud* rechercher(noeud *head, int _valeur) {
    noeud *tmp = head;
    while (tmp != NULL) {
        if (tmp->valeur == _valeur)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

// Supprimer au début
noeud* suppressionD(noeud *head) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }
    noeud *tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

// Supprimer à la fin
noeud* suppressionF(noeud *head) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    noeud *tmp = head;
    while (tmp->next->next != NULL)
        tmp = tmp->next;

    free(tmp->next);
    tmp->next = NULL;
    return head;
}

// Supprimer à une position
noeud* suppressionP(noeud *head, int pos) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }

    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide\n");
        return head;
    }

    if (pos == 0)
        return suppressionD(head);

    noeud *tmp = head;
    for (int i = 0; i < pos - 1; i++) {
        tmp = tmp->next;
    }

    noeud *supprimer = tmp->next;
    tmp->next = supprimer->next;
    free(supprimer);
    return head;
}

// Modifier au début
noeud* modifierD(noeud *head, int _valeur) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }
    head->valeur = _valeur;
    return head;
}

// Modifier à la fin
noeud* modifierF(noeud *head, int _valeur) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }

    noeud *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->valeur = _valeur;
    return head;
}

// Modifier à une position
noeud* modifierP(noeud *head, int pos, int _valeur) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return NULL;
    }

    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide\n");
        return head;
    }

    noeud *tmp = head;
    for (int i = 0; i < pos; i++) {
        tmp = tmp->next;
    }

    tmp->valeur = _valeur;
    return head;
}

// Affichage
void afficher(noeud *head) {
    if (head == NULL) {
        printf("La liste est vide\n");
        return;
    }

    noeud *tmp = head;
    printf("Liste : ");
    while (tmp != NULL) {
        printf("%d -> ", tmp->valeur);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

// Fonction principale
int main() {
    noeud *head = NULL;

    head = ajouterF(head, 20);
    head = ajouterF(head, 30);
    head = ajouterF(head, 40);
    afficher(head);

    head = insertionP(head, 1, 25);
    afficher(head);

    head = suppressionD(head);
    afficher(head);

    head = suppressionF(head);
    afficher(head);

    head = suppressionP(head, 1);
    afficher(head);

    head = modifierD(head, 99);
    afficher(head);

    head = ajouterF(head, 60);
    head = ajouterF(head, 70);
    afficher(head);

    head = modifierF(head, 100);
    afficher(head);

    head = modifierP(head, 1, 88);
    afficher(head);

    noeud *res = rechercher(head, 88);
    if (res != NULL)
        printf("Valeur 88 trouvée !\n");
    else
        printf("Valeur 88 non trouvée.\n");

    // Libérer toute la mémoire
    while (head != NULL)
        head = suppressionD(head);

    return 0;
}
