#ifndef __ENTETE_FONCTIONS__
#define __ENTETE_FONCTIONS__

#include "API_Grille.h"
#include "Liste_case.h"

/* Retourne dans L la liste des cases de meme couleur que la case i,j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int nbcase,int i, int j, int *taille, ListeCase *L);

/* Algorithme tirant au sort une couleur: il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/* Permet de savoir si toutes les cases de la matrice M sont de la même couleur (1:vrai 0:faux) */
int fin(int **M, int dim);

/* meme principe que trouve_zone_rec sans récursion */
void trouve_zone_V2(int **M, int nbcase, int i, int j, int cl , int *taille, ListeCase *L);

/* meme principe que sequence_aleatoire_rec sans recursion */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __ENTETE_FONCTIONS__ */
