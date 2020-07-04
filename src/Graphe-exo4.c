#include "Graphe-exo4.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"

void ajoute_liste_sommet(Sommet *som,Cellule_som **liste_cell_som){
  
  Cellule_som *aj = (Cellule_som *) malloc(sizeof(Cellule_som));
  aj->sommet = som;
  aj->suiv = *liste_cell_som;
  *liste_cell_som = aj;

}

void detruire_liste_somme(Cellule_som *liste_cell_som){
        Cellule_som * tmp;
        while(liste_cell_som != NULL){
            tmp = liste_cell_som;
            liste_cell_som = liste_cell_som->suiv;
            free(tmp);
        }
}

void ajoute_voisin(Sommet *s1, Sommet *s2){
    ajoute_liste_sommet(s1,&(s2->sommet_adj));
    ajoute_liste_sommet(s2,&(s1->sommet_adj));
}

int check_adjacent(Sommet *s1, Sommet *s2){
    Cellule_som *tmp = s1->sommet_adj;
    while (tmp != NULL){
        if (tmp->sommet == s2)
            return 1;
        tmp = tmp->suiv;
    }
    return 0;
}

Graphe_zone* creer_graphe_zone(int **Matrice, int dimension, int nbcl){
    Graphe_zone *graphe = (Graphe_zone *) malloc(sizeof(Graphe_zone)); //Allocation du graphe 
    graphe->nbsom = 0;
    graphe->som = NULL; //pour l'instant, la liste est vide
    graphe->Listezsg = NULL;
    graphe->nb_som_zsg = 0;
    graphe->nbcl = nbcl;

    graphe->Bordure = (Cellule_som **) malloc(sizeof(Cellule_som *)*nbcl);
    for (int i=0; i<nbcl; i++)
        graphe->Bordure[i] = NULL;
    
    graphe->tailleBordure = (int *) malloc(sizeof(int)*nbcl);
    for (int i=0; i<nbcl; i++)
        graphe->tailleBordure[i] = 0;
    
    Sommet ***mat = (Sommet ***) malloc(sizeof(Sommet **)*dimension);
    for (int i = 0; i<dimension; i++){
        mat[i] = (Sommet **) malloc(sizeof(Sommet *)*dimension); 
        for(int j = 0; j <dimension; j++){
            mat[i][j] = NULL; //il faut initialiser la matrice
        }
    }
    
    graphe->mat = mat;
    int Taille = 0;
    int k,l=0;
    ListeCase c;
    ListeCase c2;

    init_liste(&c2);
    init_liste(&c); 

    //réalisation de la pile 

    ajoute_en_tete(&c,0,0);// On empile 
    while (c != NULL){
        ListeCase p = c;
        while(p != NULL){
            p = p->suiv;
        }
        enleve_en_tete(&c,&k,&l);//On dépile

        Cellule_som *tmp = graphe->som;
        ListeCase tmp_cases = NULL ;
        if (graphe->mat[k][l] == NULL){ //case pour laquelle on n'a pas encore la zone
            trouve_zone_V2(Matrice,dimension,k,l,Matrice[k][l],&Taille,&c2);
            Sommet *som = (Sommet *) malloc(sizeof(Sommet));
            som->num = graphe->nbsom+1;
            som->cases = c2;
            som->cl = Matrice[k][l];
            som->nbcase_som = Taille;
            som->sommet_adj = NULL;
            ajoute_liste_sommet(som,&(graphe->som));
            graphe->nbsom +=1;
            while(c2 != NULL){
                graphe->mat[c2->i][c2->j]=som;

                //On récupere les variables
                int i = c2->i;
                int j = c2->j;

                //Nous vérifions sil voisins sont dans la grille et si ils n'ont pas déjà été inseré
                if (i>0 && graphe->mat[i-1][j]==NULL){
                ajoute_en_tete(&c,i-1,j);
                }
                if (j>0 && graphe->mat[i][j-1]==NULL){
                    ajoute_en_tete(&c,i,j-1);
                }
                if (i+1<dimension && graphe->mat[i+1][j]==NULL){
                    ajoute_en_tete(&c,i+1,j);
                }
                if (j+1<dimension && graphe->mat[i][j+1]==NULL){
                    ajoute_en_tete(&c,i,j+1);
                }

                        c2 = c2->suiv ;
            }
        }

        if (k>0 && graphe->mat[k-1][l]==NULL){
            ajoute_en_tete(&c,k-1,l);
        }
        if (l>0 && graphe->mat[k][l-1]==NULL){
            ajoute_en_tete(&c,k,l-1);
        }
        if (k+1<dimension && graphe->mat[k+1][l]==NULL){
            ajoute_en_tete(&c,k+1,l);
        }
        if (l+1<dimension && graphe->mat[k][l+1]==NULL){
            ajoute_en_tete(&c,k,l+1);
        }
        detruit_liste(&c2);    
    }

    //les adjacents de tous les sommets sont ajoutés sont ajoutés dans leurs liste_adjacents 

    for(int i = 0; i < dimension; i++){

        for(int j=0; j < dimension; j++){
            if (i>0 && graphe->mat[i-1][j] != graphe->mat[i][j] && !check_adjacent(graphe->mat[i][j],graphe->mat[i-1][j])){
                ajoute_voisin(graphe->mat[i][j],graphe->mat[i-1][j]);
            }
            if (j>0 && graphe->mat[i][j-1] != graphe->mat[i][j] && !check_adjacent(graphe->mat[i][j],graphe->mat[i][j-1])){
                ajoute_voisin(graphe->mat[i][j],graphe->mat[i][j-1]);
            }
            if (i+1<dimension && graphe->mat[i+1][j] != graphe->mat[i][j] && !check_adjacent(graphe->mat[i][j],graphe->mat[i+1][j])){
                ajoute_voisin(graphe->mat[i][j],graphe->mat[i+1][j]);
            }
            if (j+1<dimension && graphe->mat[i][j+1] != graphe->mat[i][j] && !check_adjacent(graphe->mat[i][j],graphe->mat[i][j+1])){
                ajoute_voisin(graphe->mat[i][j],graphe->mat[i][j+1]);
            }
        }
    }

    //Les marques sont alloué et initialisé à 2 
    graphe->marque = (int *) malloc(sizeof(int)*graphe->nbsom);
    for (int i=0; i<graphe->nbsom; i++)
       graphe->marque[i] = 2;

    return graphe;
}



void afficher_matrice(Graphe_zone * graphe, int dimension){
    for(int i = 0; i < dimension; i++)
    {
        printf("\n");
        for(int j=0; j < dimension; j++){
            if(graphe->mat[j][i] != NULL)
            {
                printf("%d ", (graphe->mat[j][i])->num);
            }
            else{
                printf("? ");
            }
        }
    }
    printf("\n");
}