#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


#include "Grille.h"
#include "Graphe.h"
#include "ListeDC.h"
#include "Circuit.h"
#include "Solution.h"


int main(int argc,char**argv){

  Graphe H; 
  Grille G;
  Solution S;
  int graine;
  int i,j;

  if(argc!=5){
    printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine>\n",argv[0]);
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


  /* G�n�ration du graphe et Affichage*/

	Graphe_init(&H, G.m,G.n);
	Graphe_creation(&G, &H);
	Graphe_affiche(&H);

	//Création de la liste de circuits
	Lcircuit* LC=Lcircuit_Init();

	//Recherche des circuits dans le graphe
	Graphe_Rech_Circuit_v2(&H,LC);

	//Initialisation de la solution
	Solution_init(&S);


  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu;
  temps_initial=clock();

  //algortithme de Daniel Graf
  algorithme_circuit_CasLigne1x1(&G,&S,LC);


  temps_final=clock();
  temps_cpu=((double) (temps_final - temps_initial))/CLOCKS_PER_SEC;

  Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  printf("\nVous avez gagne en %d pas\n",S.cptr_pas);
  printf("\nEcriture de la solution sur disque\n\n");


	Affiche(&S);
 	printf("TAILLE : %d,TEMPS : %f \n", G.n*G.m,temps_cpu);
	return 0;
   
return 0;
}