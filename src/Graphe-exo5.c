#include <stdio.h>
#include "Graphe-exo4.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"
#include "Liste_case.h"

void maj_bordure(Graphe_zone *graphe , int cl){
    Cellule_som *tmp_g = graphe->Bordure[cl];

    while(tmp_g != NULL){//les sommets contenu dans la bordure de la couleur en parametre sont parcourus 
        graphe->marque[tmp_g->sommet->num-1] = 0;//ils sont ajoutés dans la Zsg
        ajoute_liste_sommet(tmp_g->sommet,&(graphe->Listezsg));
        graphe->nb_som_zsg += 1;
        
        tmp_g = tmp_g->suiv;
    }
    graphe->Bordure[cl] = NULL;//La liste des sommets de la bordure sont détruit 
    graphe->tailleBordure[cl] = 0;

    //Les adjacents des sommets de la bordure deviennent les adjacents de la Zsg 

    Cellule_som * tmp_Lzsg = graphe->Listezsg;
    Cellule_som *tmp_adj;

    //On parcours les sommets de la Zsg 
    while(tmp_Lzsg != NULL){
        tmp_adj = tmp_Lzsg->sommet->sommet_adj;
        //On parcours les sommets adjacents à ce sommet 
        while(tmp_adj != NULL){
            if (!check_in(tmp_adj->sommet,&(graphe->Listezsg)) && !check_in(tmp_adj->sommet,&(graphe->Bordure[tmp_adj->sommet->cl]))){//On vérifie si le sommet n'est pas deja dans la Zsg 
                graphe->marque[tmp_adj->sommet->num-1] = 1;
                ajoute_liste_sommet(tmp_adj->sommet,&(graphe->Bordure[tmp_adj->sommet->cl]));
                graphe->tailleBordure[tmp_adj->sommet->cl]++;
            }
            tmp_adj = tmp_adj->suiv;
        }

        tmp_Lzsg = tmp_Lzsg->suiv;
    }
}


void strat_exo5(int aff, Graphe_zone *graphe, Grille *Grille){
    Cellule_som *tmp_g = graphe->som;
    Cellule_som *tmp_adj;

    //La première Zsg et sa bordure sont initialiser
    while(tmp_g != NULL){ 
        if(tmp_g->sommet->num == 1){ //cherche le sommet 1 qui est censé contenir la case ayant l'indice (0,0) , la Zsg 
            graphe->marque[tmp_g->sommet->num-1] = 0;
            ajoute_liste_sommet(tmp_g->sommet,&(graphe->Listezsg));//le sommet est ajouté à la liste Zsg 
            graphe->nb_som_zsg += 1;
            tmp_adj = tmp_g->sommet->sommet_adj; 

            while(tmp_adj != NULL){ //On parcourt les adjacents dans la liste adjacent du sommet de la Zsg (La bordure)
                //
                graphe->marque[tmp_adj->sommet->num-1] = 1;
                ajoute_liste_sommet(tmp_adj->sommet,&(graphe->Bordure[tmp_adj->sommet->cl]));
                graphe->tailleBordure[tmp_adj->sommet->cl]++;
                tmp_adj = tmp_adj->suiv;
            }
        }
        tmp_g = tmp_g->suiv;
    }
    int cl = -1;//Stock la couleur étant la plus présente dans la bordure 

    while(!fin5(graphe)){ //Vérifie la fin du jeu 
        for (int i=0; i<graphe->nbcl; i++){
            if (cl < graphe->tailleBordure[i])
                cl = i;
        }
        maj_bordure(graphe,cl);

        aff_grille(graphe,cl,Grille);
        cl = -1;
    }
}

void aff_grille(Graphe_zone *graphe , int cl, Grille *Grille){
    Cellule_som * tmp_zsg = graphe->Listezsg;
    ListeCase tmp_case;
    init_liste(&tmp_case);

    while(tmp_zsg != NULL){
        tmp_case = tmp_zsg->sommet->cases;
        while(tmp_case != NULL){
            Grille_attribue_couleur_case(Grille,tmp_case->i,tmp_case->j,cl);
            tmp_case = tmp_case->suiv;
        }
        detruit_liste(&tmp_case);
        tmp_zsg = tmp_zsg->suiv;
    }

    Grille_redessine_Grille();
}

int fin5(Graphe_zone *graphe){
    for (int i=0; i<graphe->nbcl; i++){
        if (graphe->tailleBordure[i] != 0)
            return 0;
    }

    return 1; 
}

int check_in(Sommet *sommet,Cellule_som **list){
    Cellule_som *tmp_list = *list;

    while(tmp_list != NULL){
        if (sommet->num == tmp_list->sommet->num)
            return 1;
        tmp_list = tmp_list->suiv;
    }

    return 0;
}