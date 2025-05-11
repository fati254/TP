#include<stdio.h>
#include<stdlib.h>
typedef struct noeud {
    int valeur ;
    struct noeud *next;
    struct noeud *prev; 
}noeud;

//creation 
noeud* cree(int _valeur){
    noeud *nv = (noeud*)malloc(sizeof(noeud));
    if(nv == NULL){
        printf("echec d'allocatiion");
        return NULL ;
    }
    nv->valeur = _valeur;
    nv->next = NULL ; 
    nv->prev = NULL ; 
    return nv; 
}
//affichage 
void affiche( noeud *head ){
    noeud *tmp = head ; 
    while(tmp != NULL ){
        printf(" %d \t ",tmp->valeur);
        tmp = tmp->next ; 
    }
    printf("\n");
}

//afficher inverse 
void afficheInverse( noeud *head){
    noeud *tmp = head;
    while(tmp->next != NULL)
    tmp = tmp->next ; 
  while(tmp->prev != NULL){
    printf("%d  \t",tmp->valeur);
    tmp= tmp->prev ;
  }
  printf("\n");
}

//Partiiiiiiiiiiiiiie 2 : 

// ajouter debut 
noeud* ajouterD(noeud *head , int _valeur){
    noeud *nv = cree(_valeur);
    if(head == NULL){
        printf("La liste est vide\n");
        return NULL ; 
    }
    nv->next = head;
    head->prev = nv ; 
    head = nv ; 
    return head;
}

//ajouter fin 

noeud* ajouterF(noeud *head , int _valeur){
    noeud *nv = cree(_valeur);
    if(head == NULL){
        printf("La liste est vide\n");
        return NULL ; 
    }
    noeud *tmp = head; 
    while(tmp->next != NULL )
    tmp = tmp->next ; 
    tmp->next = nv ; 
    nv->prev = tmp ; 
    return head ; 
}

//taille 

int taille(noeud *head){
    noeud *tmp = head ; 
    int cpt=0; 
    while(tmp!= NULL){
        cpt++ ; 
        tmp=tmp->next ; 
    }
    return cpt ; 
}

//insertion a pos
noeud* insertion(noeud *head , int pos , int _valeur ){
    noeud *nv = cree(_valeur);
    if(head == NULL){
        printf("La liste est vide\n");
        return NULL ; 
    }
    else if(pos == 0){
        head = ajouterD(head , _valeur );
    }
    else if( pos < 0 || pos > taille(head)+1 ){
        printf("La position invalide \n");
    }
    else{
        int i ; 
        noeud *tmp=head; 
        for(int i=0 ; i<pos ; i++)
           tmp=tmp->next; 
        nv->next = tmp->next ; 
        nv->prev = tmp ; 
        tmp->next->prev = nv ;
        tmp->next = nv ;  
    }
    return head;
}

//rechercher 

int rechercher(noeud *head , int _valeur ){
    noeud *tmp = head ; 
    int trouve = 0 ; 
    while(tmp != NULL ){
        if(tmp->valeur == _valeur ){
            trouve = 1 ; 
            break ; 
        }
      tmp = tmp->next ; 
    }
  return trouve ; 
}

//suppression debut 

noeud *suppressionD(noeud *head){
    if(head == NULL ){
      printf("La liste est vide \n");
    }
    else{
        noeud *tmp = head ; 
        head = head->next ; 
        head->prev = NULL ; 
        free(tmp);
        return head ; 
    }

}

//suppression fin 

noeud *suppressionF(noeud *head){
    if(head == NULL ){
        printf("La liste est vide \n");
      }
    else if(head->next == NULL ){
        free(head);
        head = NULL ; 
    }
    else{
        noeud *tmp = head; 
        while(tmp->next != NULL )
        tmp=tmp->next ; 
      tmp->prev->next = NULL ; 
      free(tmp);
    }
  return head ; 
}

//suppression a pos 

noeud *suppressionP(noeud *head , int pos){
    if(head == NULL ){
        printf("La liste est vide \n");
      }
    else if( pos == 0 ){
        head = suppressionD(head);
    }
    else if( pos < 0 || pos > taille(head)+1 ) {
        printf("La position Invalide \n");
    }
    else{
        noeud *tmp = head ; 
       for(int i =0 ; i<pos ; i++)
       tmp = tmp->next ; 
       if(tmp->prev != NULL )
      tmp->prev->next = tmp->next ; 
       if(tmp->next != NULL)
      tmp->next->prev= tmp->prev ;
      free(tmp);
    }
    return head ; 
}

//modifier debut 

noeud* modifierD(noeud *head, int _valeur) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    printf("Ancienne valeur : %d\n", head->valeur);
    head->valeur = _valeur;
    printf("Nouvelle valeur : %d\n", head->valeur);

    return head;
}

//modifier fin 

noeud* modifierF(noeud *head, int _valeur) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    noeud* tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next; 
    }
    printf("->Ancienne valeur du dernier noeuud : %d\n", tmp->valeur);
    tmp->valeur = _valeur;
    printf("->Nouvelle valeur : %d\n", tmp->valeur);

    return head;
}

//modifier val a une position 

noeud* modifierP(noeud * head , int pos , int _valeur ){
    if(head == NULL ){
        printf("La liste est vide \n");
        return NULL ; 
    }
    if(pos == 0){
        head = modifierD(head , _valeur );
    }
    else if( pos < 0 || pos > taille(head)+1 ){
        printf("La position Invalide \n");
    }
    else{
        noeud *tmp = head ; 
        for(int i=0 ; i<pos ; i++)
          tmp = tmp->next ; 
        printf("->Ancienne valeur est : %d \n",tmp->valeur);
        tmp->valeur = _valeur ; 
        printf("->Nouvelle valeur : %d\n", tmp->valeur);
    }
  return head ; 
}

//tri en ordre croissant 

noeud* tri(noeud *head) {

    if (head == NULL || head->next == NULL) {
        return head; 
    }
    int per;
    noeud* tmp;
    do {
        per = 0;
        tmp = head;

        while (tmp->next != NULL) {
            if (tmp->valeur > tmp->next->valeur) {
                
                int temp = tmp->valeur;
                tmp->valeur = tmp->next->valeur;
                tmp->next->valeur = temp;
                per = 1;
            }
            tmp = tmp->next;
        }
    } while (per);

    return head;
}

//main 
int main() {
    noeud* head = NULL;

    head = cree(10);
    head = ajouterF(head, 20);
    head = ajouterF(head, 30);
    head = ajouterF(head, 40);

    printf("Liste initiale :\n");
    affiche(head);

    head = ajouterD(head, 5);
    printf("\nApres ajout au début (5) :\n");
    affiche(head);

    head = ajouterF(head, 50);
    printf("\nApres ajout a la fin (50) :\n");
    affiche(head);

    head = insertion(head, 2, 15);
    printf("\nApres insertion a la position 2 (15) :\n");
    affiche(head);

    head = modifierD(head, 1);
    printf("\nApres modification du debut (valeur = 1) :\n");
    affiche(head);

    head = modifierF(head, 99);
    printf("\nApres modification de la fin (valeur = 99) :\n");
    affiche(head);

    head = modifierP(head, 3, 25);
    printf("\nApres modification a la position 3 (valeur = 25) :\n");
    affiche(head);

    head = suppressionD(head);
    printf("\nApres suppression du debut :\n");
    affiche(head);

    head = suppressionF(head);
    printf("\nApres suppression de la fin :\n");
    affiche(head);

    head = suppressionP(head, 2);
    printf("\nApres suppression a la position 2 :\n");
    affiche(head);

    head = tri(head);
    printf("\nApres tri en ordre croissant :\n");
    affiche(head);

    printf("\nAffichage inverse :\n");
    afficheInverse(head);

    return 0;
}