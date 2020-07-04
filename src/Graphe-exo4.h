#include <stdio.h>
#include <stdlib.h>

#include "Liste_case.h"
#include "Entete_Fonctions.h"

typedef struct sommet Sommet;

typedef struct cellule_som{
    Sommet * sommet;
    struct cellule_som * suiv;
} Cellule_som;

struct sommet{
    int num;
    int cl;
    ListeCase cases;
    int nbcase_som;

    

    Cellule_som * sommet_adj;
};

typedef struct graphe_zone{
    int nbsom;
    int nbcl;
    Cellule_som * som;
    int *marque;
    Sommet ***mat;

    Cellule_som **Bordure;
    int *tailleBordure;

    Cellule_som *Listezsg;
    int nb_som_zsg;  

    
}Graphe_zone;

Graphe_zone *creer_graphe_zone(int **Matrice, int dim, int nbcl);
void afficher_matrice(Graphe_zone * graphe, int dim);
void ajoute_liste_sommet(Sommet *som,Cellule_som **liste_cell_som);
void detruire_liste_sommet(Cellule_som *liste_cell_som);

void strat_exo5(int aff, Graphe_zone *graphe, Grille *G);
void aff_grille(Graphe_zone *graphe , int cl, Grille *G);
int fin5(Graphe_zone *graphe);
int check_in(Sommet *sommet,Cellule_som **list);