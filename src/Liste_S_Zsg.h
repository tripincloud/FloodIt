#ifndef __LISTE_S_ZSG__
#define __LISTE_S_ZSG__

#include "Liste_case.h"
#include "Entete_Fonctions.h"

typedef struct{
    int dim;
    int nbcl;

    ListeCase Lzsg;
    ListeCase *B;
    int **App;
} S_Zsg;


void init_Zsg(S_Zsg *Z, int dim, int nbcl);

void ajoute_Zsg(S_Zsg *Z, int i, int j);

void ajoute_Bordure(S_Zsg *Z, int i, int j, int cl);

int appartient_Zsg(S_Zsg *Z, int i, int j);

int appartient_Bordure(S_Zsg *Z, int i, int j, int cl);

int affiche_Zsg(S_Zsg *Z);

int affiche_Bordure(S_Zsg *Z, int cl);

void detruit_Zsg(S_Zsg *Z, int dim);

int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

int fin2(S_Zsg *Z, int dim);

void sequence_aleatoire_rapide(int dim, int nbcl,int aff, int **M, Grille *G, S_Zsg *Z);

#endif