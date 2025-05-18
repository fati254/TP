#include<stdio.h>
#include<stdlib.h>
typedef struct Noeud {
    int valeur;
    struct Noeud*suivant;
}Noeud;
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
int main() {
    Noeud* pile = NULL;
    push(&pile, 10);
    push(&pile, 20);
    push(&pile, 30);
    afficher(pile);
    peek(pile);
    printf("Taille : %d\n", taille(pile));
    pop(&pile);
    pop(&pile);
    afficher(pile);
    return 0;
}
void Enfiler(int valeur) {
    Noeud* debut = NULL;
    Noeud* fin = NULL;
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    nouveau->valeur = valeur;
    nouveau->suivant = NULL;
    if (fin == NULL) {
        debut = fin = nouveau;
    } 
    else {
        fin->suivant = nouveau;
        fin = nouveau;
    }
}
void Defiler() {
    Noeud* debut = NULL;
    Noeud* fin = NULL;
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
void afficherFile(Noeud* top) {
    printf("Contenu de la file : ");
    while (top != NULL) {
        printf("%d ", top->valeur);
        top = top->suivant;
    }
    printf("\n");
}
void viderFile() {
    Noeud* debut = NULL;
    while (debut != NULL) {
        Defiler();
    }
}
int main() {
    Enfiler(10);
    Enfiler(20);
    Enfiler(30);
    afficherFile(debut);
    Defiler();
    afficherFile(debut);
    Enfiler(40);
    Enfiler(50);
    viderFile();
    afficherFile(debut);
    return 0;
}