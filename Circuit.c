#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Graphe.h"
#include "ListeDC.h"
#include "Circuit.h"


//Permet d'afficher un ensemble de circuits couvrant les sommets non-noirs de H
void Graphe_Rech_Circuit(Graphe *H){
	int i,j;
	Sommet *scour;
	Arc *acour;
	for(i=0;i<H->n;i++){
		
		for(j=0;j<H->m;j++){

			if(H->Tsom[i][j]->visit==-1){

				printf("\n(%d,%d) ",i,j);
				H->Tsom[i][j]->visit=0;
				scour=H->Tsom[i][j];
				do{
					acour=scour->Lsucc;
					while((acour!=NULL)&&(acour->succ!=H->Tsom[i][j])&&(acour->succ->visit != -1)){
						acour=acour->suiv;
					}
					if(acour!=NULL){
						scour=acour->succ;
						scour->visit=0;
						printf("(%d,%d) ",scour->i,scour->j);
					}
				}while (scour!=H->Tsom[i][j]);
				printf("\n");
			}
		}
	}
}


//Retourne une liste de circuits de H couvrant les sommets non-noirs
void Graphe_Rech_Circuit_v2(Graphe *H, Lcircuit *LC){

}