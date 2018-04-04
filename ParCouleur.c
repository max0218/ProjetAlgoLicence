#include <stdio.h>
#include <stdlib.h>

#include "ParCouleur.h"
#include "Grille.h"
#include "Solution.h"
#include "Naif.h"
#include "Circulaire.h"

CelluleLDC* creerCellule(int i, int j){
	//qui alloue et retourne une cellule
	CelluleLDC* cel=(CelluleLDC*)malloc(sizeof(CelluleLDC));

	cel->i=i;

	cel->j=j;

	return cel;

}

void LDCInitialise(LDC *ldc){	//qui initialise une liste
	ldc->premier=NULL;
	ldc->dernier=NULL;
}
 

int LDCVide(LDC* ldc){	//qui teste si la liste est vide
	return (ldc->premier==NULL);
}

void LDCInsererEnFin(LDC* ldc, int i, int j){	//qui insere une nouvelle cellule en fin
	CelluleLDC* cel=creerCellule(i,j);
	if (LDCVide(ldc)){
		ldc->premier=cel;
		ldc->dernier=cel;
	}
	else{
		ldc->dernier->suiv=cel;
		cel->prec=ldc->dernier;
		ldc->dernier=cel;
	}
}

void LDCenleverCellule(LDC* ldc, CelluleLDC* cel){	//qui supprime une cellule a partir d un pointeur sur la cellule
	if (ldc->premier==cel){
		if (ldc->dernier==cel)
			free(cel);
		else{
			ldc->premier=cel->suiv;
			free(cel);
		}
	}
	else{
		if (ldc->dernier==cel){
			ldc->dernier=cel->prec;
			free(cel);
		}
		else{

			cel->suiv->prec=cel->prec;
			cel->prec->suiv=cel->suiv;
			free(cel);
		}
	}
}

void LDCafficher(LDC* ldc){	// un affichage en cas de besoin pour debugage
	CelluleLDC* cel=ldc->premier;
	while(cel!=NULL){
		printf("(%d,%d)\n",cel->i,cel->j);
		cel=cel->suiv;
	}
	printf("Fin de la liste\n");
}

void LDCdesalloue(LDC *ldc){	// qui desalloue toute la liste (si elle n'est pas vide a la fin)
	CelluleLDC* cel=ldc->premier;
	while (cel!=ldc->dernier){
		cel=cel->suiv;
		free(cel->prec);
	}
	free(cel);
}

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j){	//recherche dans une liste LDC la premirer case la plus proche de (i,j)
	CelluleLDC* courante=ldc->premier;
	CelluleLDC* ppc=courante;
	// on calcule la distance enttre la cellule ppc et notre robot
	int dist=distance(ppc->i,ppc->j,i,j);

	while(courante!=ldc->dernier){
		courante=courante->suiv;
		// Si la distance entre cette nouvelle case et notre robot est plus faible, on la garde
		if (distance(courante->i,courante->j,i,j)<dist){
			ppc=courante;
			//MàJ distance avec la nouvelle case
			dist=distance(ppc->i,ppc->j,i,j);
		}
	}
	return ppc;
}


void algorithme_parcouleur(Grille *G, Solution *S){

	LDC** TC=malloc(sizeof(LDC)*G->nbcoul);
	int i,j;

	// Initialisation du tableau de couleurs
	for (i = 0; i < G->nbcoul; i++)
	{
		LDC * ldc = malloc(sizeof(LDC));

		LDCInitialise(ldc);
		TC[i] = ldc;

	}

	//Insertion de toutes les cases de la grille en fonction de leur couleur
	for (i=0;i<G->m;i++){

		for (j=0;j<G->n;j++){

			LDCInsererEnFin((TC[G->T[i][j].fond]),i,j);
		}
	}


	while (G->cptr_noire<(G->n*G->m)){
		if(!RobotPortePiece(G)){
			RechercheCaseCirculaire_nn(G,G->ir,G->jr,&i,&j);
		}else{
			int couleurdurobot=G->T[G->ir][G->jr].robot;
			//On recherche la case la plus proche pour une couleur donnee
			CelluleLDC *cel=LDCrechercherPlusProcheCase((TC[couleurdurobot]),G->ir,G->jr);
			i=cel->i;
			j=cel->j;
			LDCenleverCellule((TC[couleurdurobot]),cel);
		}
		//printf("position du robot (%d,%d)\t",G->ir,G->jr);
		//printf("couleur de la piece %d \n",G->T[G->ir][G->jr].robot);
		//getchar();
		PlusCourtChemin(S,G->ir,G->jr,i,j);
		changement_case(G,i,j);
		swap_case(G);
	}
}