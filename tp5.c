#include <stdio.h>
#include <stdlib.h>


typedef struct Noeud {
    int valeur;
    struct Noeud* suivant;
} Noeud;

void push(Noeud** top, int valeur) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    nouveau->valeur = valeur;
    nouveau->suivant = *top;
    *top = nouveau;
}

void pop(Noeud** top) {
    if (*top == NULL) {
        printf("Pile vide.\n");
        return;
    }
    Noeud* temp = *top;
    *top = (*top)->suivant;
    free(temp);
}

void peek(Noeud* top) {
    if (top == NULL) {
        printf("Pile vide.\n");
    } else {
        printf("Sommet de la pile : %d\n", top->valeur);
    }
}

void afficher(Noeud* top) {
    printf("Contenu de la pile : ");
    while (top != NULL) {
        printf("%d ", top->valeur);
        top = top->suivant;
    }
    printf("\n");
}

int taille(Noeud* top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->suivant;
    }
    return count;
}


Noeud* debut = NULL;
Noeud* fin = NULL;

void Enfiler(int valeur) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    nouveau->valeur = valeur;
    nouveau->suivant = NULL;
    if (fin == NULL) {
        debut = fin = nouveau;
    } else {
        fin->suivant = nouveau;
        fin = nouveau;
    }
}

void Defiler() {
    if (debut == NULL) {
        printf("File vide.\n");
        return;
    }
    Noeud* temp = debut;
    debut = debut->suivant;
    if (debut == NULL)
        fin = NULL;
    free(temp);
}

void afficherFile() {
    Noeud
