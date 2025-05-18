#include<stdio.h>
#include<stdlib.h>
typedef struct Etudiant{
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant*suivant;
    struct Etudiant*precedent;
}Etudiant;
Etudiant*cree_etudiant(){
    Etudiant*NV= (Etudiant*)malloc(sizeof(Etudiant));
    if(NV==NULL){
        printf("erreur d'allocation");
    }
    printf("Entrez ID de l'etudiant:");
    scanf("%d",&NV->id);
    printf("Entrez le nom de l'etudiant");
    scanf("%s",&NV->nom);
    printf("Entrez la moyenne de l'etudiant");
    scanf("%f",&NV->moyenne);
    NV->suivant=NULL;
    NV->precedent=NULL;
    return NV;
}
int longueur(Etudiant*tete){
    int cmpt=0;
    while(tete != NULL){
        cmpt++;
        tete=tete->suivant;
    }
    return cmpt;
}
Etudiant* ajouter_position(Etudiant* tete, Etudiant* NV, int pos){
    if(pos<1){
        printf("Position invalide");
        return tete;
    }
    if(pos==1){
        NV->suivant=tete;
        if(tete!=NULL){
            tete->precedent=NV;
        }
        return NV;
    }
    Etudiant* tmp=tete;
    int i=1;
    while(tmp!=NULL && i<pos-1){
        tmp=tmp->suivant;
        i++;
    }
    if(tmp==NULL){
        printf("Position en dehors de la liste");
        return tete;
    }
    NV->suivant=tmp->suivant;
    NV->precedent=tmp;
    if(tmp->suivant!=NULL){
        tmp->suivant->precedent=NV;
    }
    tmp->suivant=NV;
    return tete;
}
Etudiant* supprimer_position(Etudiant*tete,int pos){
    if(pos<1){
        printf("Position invalide");
        return tete;
    }
    Etudiant* tmp=tete;
    int i=1;
    while(tmp!=NULL && i<pos){
        tmp=tmp->suivant;
        i++;
    }
    if(tmp==NULL){
        printf("Position en dehors de la liste");
        return tete;
    }
    if(tmp->precedent!=NULL){
        tmp->precedent->suivant=tmp->suivant;
    }
    else{
        tete=tmp->suivant;
    }
    if(tmp->suivant !=NULL){
        tmp->suivant->precedent=tmp->precedent;
    }
    free(tmp);
    return tete;
}
void afficher_liste(Etudiant*tete){
    Etudiant* tmp=tete;
    while(tmp!=NULL){
        printf("ID:%d, Nom:%s, Moyenne:%f",tmp->ID, tmp->nom, tmp->moyenne);
        tmp=tmp->suivant;
    }
}
Etudiant* derniere_cellule(Etudiant*tete){
    Etudiant*tmp=tete;
    while(tmp!= NULL && tmp->suivant!=NULL){
        tmp=tmp->suivant;
    }
    return tmp;
}
void afficher_liste_inverse(Etudiant*dernier){
    Etudiant*tmp=dernier;
    while(tmp!=NULL){
       printf("ID:%d, Nom:%s, Moyenne:%f",tmp->ID, tmp->nom, tmp->moyenne);
       tmp=tmp->precedent;  
    }
}
int chercher_etudiant(Etudiant*tete, int id){
    Etudiant* tmp= tete;
    while(tmp!=NULL){
        if(tmp->id=id){
            return 1;
        }
        tmp=tmp->suivant;
    }
    return 0;
}
int main(){
    Etudiant*tete= NULL;
    int choix,pos,id;
    do{
        printf("Menu de gestion des etudiants:");
        printf("1.Ajouter un etudiant");
        printf("2.Afficher la liste des etudiants");
        printf("3.Ajouter un etudiant a une position donnee");
        printf("4.Supprimer un etudiant a une position donnee");
        printf("5.Rechercher un etudiant par ID");
        printf("6.Afficher la liste des etudiants en sens inverse");
        printf("7.Separer les etudiants par moyenne");
        printf("8.Quitter");
        printf("Choix:");
        scanf("%d",&choix);
        switch (choix) {
            case 1: {
                Etudiant* etudiant= cree_etudiant();
                tete=ajouter_position(tete, etudiant,1);
                break;
            }
            case 2: 
                afficher_liste(tete);
                break;
            case 3: {
                printf("Entrez la position a laquelle ajouter l'etudiant: ");
                scanf("%d",&pos);
                Etudiant* etudiant= cree_etudiant();
                tete=ajouter_position(tete,etudiant,pos);
                break;
            }
            case 4: {
                printf("Entrez la position laquelle supprimer l'etudiant");
                scanf("%d",&pos);
                tete=supprimer_position(tete,pos);
                break;
            }
            case 5:{
                printf("Entrez ID de l'etudiant a rechercher");
                scanf("%d",&id);
                if(chercher_etudiant(tete,id)){
                    printf("L'etudiant avec ID %d a ete trouve.",id);
                }
                else{
                    printf("L'etudiant avec ID %d n'a pas trouve.",id);
                }
                break;
            }
            case 6: {
                Etudiant* dernier= derniere_cellule(tete);
                afficher_liste_inverse(dernier);
                break;
            }
            case 7:
                printf("Au revoir");
                break;
            default:
                printf("Choix invalide");
        }
    }while(choix != 7)
    return 0;
}