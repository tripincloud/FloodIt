#include <stdlib.h>
#include <stdio.h>
#include "Liste_S_Zsg.h"
#include "Entete_Fonctions.h"


// les coordonnées sont j : ordonnee i : abscisse

void init_Zsg(S_Zsg *Zone, int Dimension, int nbcl){
  Zone->dim = Dimension;
  Zone->nbcl = nbcl;
  Zone->Lzsg = NULL;
  
  Zone->App = malloc(sizeof(int*)*Dimension);
  for (int i; i<Dimension; i++)
    Zone->App[i] = malloc(sizeof(int)*Dimension);
  for (int i=0;i<Dimension; i++){
    for (int j=0;j<Dimension; j++)
        Zone->App[i][j] = -2;
  }
  Zone->B = (ListeCase *) malloc(sizeof(ListeCase)*nbcl);
  for (int i; i<nbcl; i++)
    Zone->B[i] = NULL;
}

void ajoute_Zsg(S_Zsg *Zone, int i, int j){
  ListeCase new = (ListeCase) malloc(sizeof(ListeCase));
  new->i = i;
  new->j = j;
  new->suiv = Zone->Lzsg;
  Zone->Lzsg = new;
  Zone->App[i][j] = -1;
}

void ajoute_Bordure(S_Zsg *Zone, int i, int j, int Couleur){
  ListeCase new = (ListeCase) malloc(sizeof(ListeCase));
  new->i = i;
  new->j = j;
  new->suiv = Zone->B[Couleur];
  Zone->B[Couleur] = new;
  Zone->App[i][j] = Couleur;
}

int appartient_Zsg(S_Zsg *Zone, int i, int j){
  ListeCase tmp = Zone->Lzsg;
  while (tmp != NULL){
    if (tmp->i == i && tmp->j == j)
      return 1;
  }
  return 0;
}

int appartient_Bordure(S_Zsg *Zone, int i, int j, int Couleur){
  ListeCase tmp = Zone->B[Couleur];
  while (tmp != NULL){
    if (tmp->i == i && tmp->j == j)
      return 1;
  }
  return 0;
}

int affiche_Zsg(S_Zsg *Zone){
  ListeCase tmp = Zone->Lzsg;
  printf("Affiche Zsg");
  while(tmp != NULL){
    printf("i : %d\tj : %d\n",tmp->i,tmp->j);
    tmp = tmp->suiv;
  }
}

int affiche_Bordure(S_Zsg *Zone, int Couleur){
  printf("Couleur : %d\n\n",Couleur);
  ListeCase tmp = Zone->B[Couleur];
  while(tmp != NULL){
    printf("i : %d\tj : %d\n",tmp->i,tmp->j);
    tmp = tmp->suiv;
  }
}

void detruit_Zsg(S_Zsg *Zone, int Dimension){
  for (int i; i<Dimension; i++)
    free(Zone->App[i]);
  free(Zone->App);

  detruit_liste(Zone->B);
  detruit_liste(&(Zone->Lzsg));
}

int agrandit_Zsg(int **Matrice, S_Zsg *Zone, int Couleur, int k, int l){
  ListeCase c;
   init_liste(&c);
     //stocker les les valeurs du premier élement de la pile
   int nb_case=0; //nombre de cases qui a été ajouté à Zsg

   ajoute_en_tete(&c,k,l); //On empile le premier élement (celui en paramètre)
    
   while(c != NULL){
      int i = c->i;
      int j = c->j;
      enleve_en_tete(&c,&k,&l); //depile l'élément
     
      if (Zone->App[k][l] == -2)
      {
        if (Matrice[k][l] == Couleur){ //Si l'élément actuelle est de la bonne couleur on le rajoute a Zsg
            ajoute_Zsg(Zone,k,l);
            nb_case++;
        }
        else
        {
            ajoute_Bordure(Zone,k,l,Matrice[k][l]); //Sinon dans la Bordure
            
        }
      }
       
      if(Zone->App[k][l] == Couleur){
        ajoute_Zsg(Zone,k,l);
        nb_case++;
      }

    //On regarde si les côtés sont dans la grille, que leur couleur est la bonne et qu'il n'appartient pas dans la liste Zsg
    if(Matrice[i][j]==Couleur){
      if (i>0 && Zone->App[i-1][j] != -1){ 
          ajoute_en_tete(&c,i-1,j);
          
      }
      if (j>0 && Zone->App[i][j-1] != -1 ){
          ajoute_en_tete(&c,i,j-1);
      }
      if (i+1<Zone->dim && Zone->App[i+1][j] != -1){
          ajoute_en_tete(&c,i+1,j);
      }
      if (j+1<Zone->dim && Zone->App[i][j+1] != -1){
          ajoute_en_tete(&c,i,j+1);
      }
   }
  }

    return nb_case;
}

void sequence_aleatoire_rapide(int Dimension, int nbcl,int aff, int **Matrice, Grille *G, S_Zsg *Zone){

  agrandit_Zsg(Matrice,Zone,Matrice[0][0],0,0);
  //affiche_Zsg(Zone);
  
  ListeCase tmp,tmp2;
  init_liste(&tmp);
  init_liste(&tmp2);
  
  while(!fin(Matrice,Dimension)){
    do{
        nbcl = (int) rand()%(Zone->nbcl);
    }while(nbcl == Matrice[0][0]);
    tmp = Zone->Lzsg;
    //met à jour la matrice
    while(tmp != NULL){
      Matrice[tmp->i][tmp->j] = nbcl;
      if(aff==1)
        Grille_attribue_couleur_case(G,tmp->i,tmp->j,nbcl);
      tmp=tmp->suiv;
    }
    
    if (aff == 1) Grille_redessine_Grille();
    
    //la Zsg est aggrandi avec toutes les cases de la bordure de la couleur cl 
    tmp2 = Zone->B[nbcl];
    while(tmp2 != NULL){
      agrandit_Zsg(Matrice,Zone,nbcl,tmp2->i,tmp2->j);
      tmp2=tmp2->suiv;
    }
    detruit_liste(&(Zone->B[nbcl]));
    detruit_liste(&tmp);
    detruit_liste(&tmp2);
  }
}


