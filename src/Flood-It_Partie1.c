#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"
#include "Liste_S_Zsg.h"
#include "Graphe-exo4.h"

 
int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine, exo, aff;
  Grille *G;
  int i,j;
  int **M;
  ListeCase L;
  init_liste(&L);
  int taille=0;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 


  if(argc!=7){
    printf("usage: %s <dimension> <nb_de_couleurs> <niveau_difficulte> <graine> <exo:0-1-2> <aff 0/1>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);
  exo=atoi(argv[5]);
  aff=atoi(argv[6]);

  /* Allocation puis Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

  int cpt;

  if (aff==1){  /* Affichage de la grille */
    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    Grille_redessine_Grille();
    Grille_attente_touche();
  }

  temps_initial = clock ();

  if (exo==0){
     printf("%d essais", sequence_aleatoire_rec(M, G, dim, nbcl, aff)); 
  }

  else if (exo == 1){
    int valcl;
    do{
        int valcl = (int) rand()%(nbcl+1);
    }while(valcl == M[0][0]);

    cpt = sequence_aleatoire_rec(M,G,dim,valcl,aff);
  }

  else if (exo == 3){
    S_Zsg Z;
    init_Zsg(&Z, dim, nbcl);
    sequence_aleatoire_rapide(dim,nbcl,aff,M,G,&Z);
  }

  else if(exo == 4){
        
    Graphe_zone* graphe = creer_graphe_zone(M,dim,nbcl);
    afficher_matrice(graphe,dim);
    printf("%d\n",graphe->som->sommet->num);
  }

  else if(exo == 5){
    Graphe_zone* graphe = creer_graphe_zone(M, dim, nbcl);
    strat_exo5(aff,graphe,G);
  } 

  temps_final = clock ();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("%f\n",temps_cpu);
  if (exo == 1 && aff == 1)
  /* Desallocation de la matrice */
  for(i = 0; i< dim; i++) {
    if (M[i])
        free(M[i]);
  }
  if (M) free(M);

  
 
  if (aff==1){  /* Fermeture et désallocation de la grille */
    Grille_ferme_fenetre();

    Grille_free(&G);
  }

  return 0;


}
