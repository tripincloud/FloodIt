#include <stdio.h>
#include "Entete_Fonctions.h"


void trouve_zone_V2(int **Matrice, int nbcase, int i, int j, int cl, int *Taille, ListeCase *ListeC){ 
  if (Matrice[i][j] == cl){  //Regarde si il doit etre dans la même zone que la case initiale
    if (est_la(ListeC,i,j) == 0){ //sous-fonction est_la permet comme elle indique si i j est dans ListeC (1:vrai 0:faux)
      *Taille += 1;
      ajoute_en_tete(ListeC,i,j);
    }
  }
  // on verifie que les côtés sont dans la grille est via la sous-fonction est_la si on ne l'a pas déjà visité
  if (j>0 && (Matrice[i][j-1] == cl) && !est_la(ListeC,i,j-1)){
    trouve_zone_V2(Matrice,nbcase,i,j-1,cl,Taille,ListeC); 
  }

  if (j<nbcase-1 && (Matrice[i][j+1] == cl) && !est_la(ListeC,i,j+1)){ 
    trouve_zone_V2(Matrice,nbcase,i,j+1,cl,Taille,ListeC);  
  }

  if (i>0 && (Matrice[i-1][j] == cl) && !est_la(ListeC,i-1,j)){
    trouve_zone_V2(Matrice,nbcase,i-1,j,cl,Taille,ListeC); 
  }
  
  if ((i<nbcase-1) && (Matrice[i+1][j] == cl) && !est_la(ListeC,i+1,j)){ 
    trouve_zone_V2(Matrice,nbcase,i+1,j,cl,Taille,ListeC);
  } 
}

int sequence_aleatoire_rec(int **Matrice, Grille *Grille, int Dimension, int nbcl, int aff){
  ListeCase Liste;
  init_liste(&Liste);
  int Compteur=0; //le nombre de cases qui ont été rajoutés
  int Taille=0;
  int comp=Matrice[0][0];

  while (fin(Matrice,Dimension) == 0){ //sous-fonction fin permet de savoir si toutes les cases sont de la même couleur (1:vrai 0:faux)
    trouve_zone_V2(Matrice,Dimension,0,0,Matrice[0][0],&Taille,&Liste);
    //On met a jour l'affichage et la matrice 
    while (Liste != NULL){
      Matrice[Liste->i][Liste->j] = comp;
      if(aff==1)
        Grille_attribue_couleur_case(Grille,Liste->i,Liste->j,comp);
      Liste = Liste->suiv;
    }
    //choisie de manière pseudo-aléatoire la couleur en dehors de celle de Matrice[0][0]
    do{
      comp = (int) rand()%(nbcl+1);
    }while(comp == Matrice[0][0]);

    if (aff==1){
      Grille_redessine_Grille();
    }

    detruit_liste(&Liste);
    Compteur++;
  }
  return Compteur;
}

int fin(int **Matrice, int Dimension){ 
  for (int i=0; i<Dimension; i++){
    for (int j=0; j<Dimension; j++){
      if (Matrice[i][j] != Matrice[0][0])
        return 0;
    }
  }
  return 1;
}



