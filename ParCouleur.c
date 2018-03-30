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
	int dist=abs(ppc->i-i)+abs(ppc->j-j);
	while(courante!=ldc->dernier){
		courante=courante->suiv;
		if (abs(courante->i-i)+abs(courante->j+j)<dist){
			ppc=courante;
			dist=abs(ppc->i-i)+abs(ppc->j-j);
		}
	}
	return ppc;
}

void algorithme_parcouleur(Grille *G, Solution *S){
	LDC *TC[G->nbcoul];
	int i,j;
	for(i=0;i<G->nbcoul;i++){
		LDCInitialise(TC[i]);
	}
	for (i=0;i<G->n;i++){
		for (j=0;j<G->m;j++){
			LDCInsererEnFin(TC[G->T[i][j].fond],i,j);
		}
	}
	while (G->cptr_noire<(G->n*G->m)){
		if(!RobotPortePiece(G)){
			RechercheCaseCirculaire_nn(G,G->ir,G->jr,&i,&j);
		}
		else{
			CelluleLDC *cel=LDCrechercherPlusProcheCase(TC[G->T[G->ir][G->jr].robot],G->ir,G->jr);
			i=cel->i;
			j=cel->j;
			LDCenleverCellule(TC[G->T[G->ir][G->jr].robot],cel);
		}
		printf("position du robot (%d,%d)\t",G->ir,G->jr);
		printf("couleur de la piece %d \n",G->T[G->ir][G->jr].robot);
		getchar();
		PlusCourtChemin(S,G->ir,G->jr,i,j);
		changement_case(G,i,j);
		swap_case(G);
	}
}