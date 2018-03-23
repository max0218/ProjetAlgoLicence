#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "Grille.h"
#include "Solution.h"
#include "Naif.h"


//Insertion en fin de liste chainee de la sequence de caractere correspond au plus court chemin 
//dans la grille allant de la case (i,j) a la case (k,l)
void PlusCourtChemin(Solution *S, int i,int j, int k, int l){
	if (S==NULL){
		Solution_init(S);
	}

	while((i!=k)||(j!=l)){
		if(i<k){
			Ajout_action(S,'D');
			i++;
		}else if(i>k){
			Ajout_action(S,'U');
			i--;
		}
		if(j<l){
			Ajout_action(S,'R');
			j++;
		}else if(j>l){
			Ajout_action(S,'L');
			j--;
		}
	}
	Ajout_action(S,'S');
}

int distance(int i, int j, int k, int l){
	return abs(i-k)+abs(j-l);
}

int CaseEstNoire(Grille *G,int i,int j){
	return (G->T[i][j].fond)==(G->T[i][j].piece);
}

int PieceEstNoire(Grille *G, int i, int j){
	return G->T[i][j].piece>=0;
}

int RobotPortePiece(Grille *G){
	return (G->T[G->ir][G->jr].robot)>=0;
}

int RobotCouleurPiece(Grille *G){
	assert(RobotPortePiece(G));
	return G->T[G->ir][G->jr].robot;
	
}

//Retourne la case (k,l) de couleur c la plus proche de (i,j) au sens de l'algorithme "au plus proche"
void RechercheCaseNaif_c(Grille *G,int c, int i, int j, int *k, int *l){
	int line,col;
	int bdist=G->m+G->n;
	for(line=0;line<G->m;line++){
		for(col=0;col<G->n;col++){
			if ((c==G->T[line][col].fond)&&(G->T[line][col].piece!=G->T[line][col].fond)){
				if (bdist>distance(i,j,line,col)){
					*k=line;
					*l=col;
					bdist=distance(i,j,line,col);
				}
			}
		}
	}
}

//Retourne la case (k,l) de couleur NOIRE la plus proche de (i,j) au sens de l'algorithme "au plus proche"
void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
	int line,col;
	int bdist=G->m+G->n+1;
	for(line=0;line<G->m;line++){
		for(col=0;col<G->n;col++){
			if ((G->T[line][col].piece>=0)&&(G->T[line][col].piece!=G->T[line][col].fond)){
				if (bdist>distance(i,j,line,col)){
					*k=line;
					*l=col;
					bdist=distance(i,j,line,col);
				}
			}
		}
	}
}


void algorithme_naif(Grille *G,Solution *S){
	int k,l;

	
	while (G->cptr_noire<(G->n*G->m)){
		
		if(!RobotPortePiece(G)){
			RechercheCaseNaif_nn(G,G->ir,G->jr,&k,&l);
		}
		else{
			RechercheCaseNaif_c(G,G->T[G->ir][G->jr].robot,G->ir,G->jr,&k,&l);
		}

		PlusCourtChemin(S,G->ir,G->jr,k,l);
		changement_case(G,k,l);
		swap_case(G);
	}
}
