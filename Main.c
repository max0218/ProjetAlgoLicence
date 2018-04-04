#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "Grille.h"
#include "Solution.h"
#include "entree_sortie.h"
#include "API_AffGrille.h"
#include "Naif.h"
#include "Circulaire.h"

int main(int argc,char**argv){
  
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i,j;

  if(argc!=5){
    printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine >\n",argv[0]);
    return 1;
  }

  G.m=atoi(argv[1]);
  G.n=atoi(argv[2]);
  
  if (G.m>G.n){
    printf("Il doit y avoir plus de colonnes que de lignes.\n");
    exit(1);
  }
  G.nbcoul=atoi(argv[3]);
  if (G.nbcoul>G.m*G.n){
    printf("Il ne doit pas y avoir plus de couleurs que de cases.\n");
    exit(1);
  }
  
  graine=atoi(argv[4]);


  /* Generation de l'instance */

  Grille_allocation(&G);
  
  Gene_Grille(&G,graine);

  Solution_init(&S);

    /* Affichage de la grille */

  AffGrille_init(&G, 600, &AG);

  AffGrille_ouvre_fenetre(&AG);

  for (i=0;i<G.m;i++)
    for (j=0;j<G.n;j++){
          AffGrille_redessine_case(&AG,&G,i,j);
    }

  AffGrille_reaffiche_Grille();


  int ch;
  printf("Choisissez quel algorithme utiliser pour résoudre la grille\n");
  printf("1 : algorithme_naif\n");
  printf("2 : algorithme_circulaire\n");
  printf("3 : algorithme_ParCouleur\n");
  printf("4 : algorithme par AVL\n");
  scanf(" %d",&ch);

  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu;
  temps_initial=clock();

  switch(ch){
    case 1:
     // Resolution de la grille par l'algorithme naif, ecriture sur la solution
      algorithme_naif(&G,&S);
      break;
    case 2:
      //Resolution de la grille par l'algorithme circulaire, ecriture sur la solution
      algorithme_circulaire(&G,&S);
      break;
    case 3:
      //Resolution de la grille par l'algorithme ParCouleur, ecriture
      algorithme_parcouleur(&G,&S);
      break;
    case 4:
      //Resolution de la grille par l'algorithme AVL, ecriture
      algorithme_parcouleur(&G,&S);
      break;
}

  temps_final=clock();
  temps_cpu=((double) (temps_final - temps_initial))/CLOCKS_PER_SEC;

  Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  printf("\nVous avez gagne en %d pas\n",S.cptr_pas);
  printf("\nEcriture de la solution sur disque\n\n");


	Affiche(&S);
 	printf("TAILLE : %d,TEMPS : %f \n", G.n*G.m,temps_cpu);
	return 0;
}