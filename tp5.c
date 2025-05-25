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
    printf("File : ");
    Noeud* temp = debut;
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->suivant;
    }
    printf("\n");
}

void viderFile() {
    while (debut != NULL) {
        Defiler();
    }
}
