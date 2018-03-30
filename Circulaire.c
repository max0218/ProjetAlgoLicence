#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "Grille.h"
#include "Solution.h"
#include "Naif.h"
#include "Circulaire.h"


void test_circulaire(int i,int j,int L){
	int k=i-L;
	int lg =j;
	int ld=j;
	while(k<=i){
		printf("(%d,%d)\t",k,lg);
		printf("(%d,%d)\n",k,ld);
		k++;
		lg--;
		ld++;
	}
	k=i+1;
	lg=j-L+1;
	ld=j+L-1;
	while(k<=i+L){
		printf("(%d,%d)\t",k,lg);
		printf("(%d,%d)\n",k,ld);
		k++;
		lg++;
		ld--;
	}
}
void RechercheCaseCirculaire_c(Grille *G,int c,int i, int j, int *k, int *l){
	int rayon;
	for(rayon=1 ; rayon<=(G->n+G->m) ; rayon++){

		int line=i-rayon;
		int lg=j;
		int ld=j;

		//On cherche circulairement dans les cases au dessus et au niveau de notre robot
		while(line<=i){
			//A gauche
			if ((line>=0)	&&	(line<G->m)	&&	(lg>=0)	&&	(lg<G->n)	&&	
				(c==G->T[line][lg].fond)	&&	(G->T[line][lg].piece!=G->T[line][lg].fond)){
				*k=line;
				*l=lg;
				return;
			}
			//A droite
			if ((line>=0)	&&	(line<G->m)	&&	(ld>=0)	&&	(ld<G->n)	&&	
				(c==G->T[line][ld].fond)	&&	(G->T[line][ld].piece!=G->T[line][ld].fond)){
				*k=line;
				*l=ld;
				return;
			}
			line++;
			lg--;
			ld++;
		}

		line=i+1;
		lg=j-rayon+1;
		ld=j+rayon-1;

		//On recherche circulairement dans les casses en dessous de notre robot
		while(line<=i+rayon) {
			//A gauche
			if ((line>=0)	&&	(line<G->m)	&&	(lg>=0)	&&	(lg<G->n)	&&	
				(c==G->T[line][lg].fond)	&&	(G->T[line][lg].piece!=G->T[line][lg].fond)){
				*k=line;
				*l=lg;
				return;
			}
			//A droite
			if ((line>=0)	&&	(line<G->m)	&&	(ld>=0)	&&	(ld<G->n)	&&	
				(c==G->T[line][ld].fond)	&&	(G->T[line][ld].piece!=G->T[line][ld].fond)){
				*k=line;
				*l=ld;
				return;
			}
			line++;
			lg++;
			ld--;
		}

	}
	
}

void RechercheCaseCirculaire_nn(Grille *G,int i,int j, int *k, int *l){
	int rayon;
	for(rayon=0 ; rayon<=(G->n+G->m) ; rayon++){

		int line=i-rayon;
		int lg=j;
		int ld=j;

		//On cherche circulairement dans les cases au dessus et au niveau de notre robot
		while(line<=i){
			//A gauche
			if ((line>=0)	&&	(line<G->m)	&&	(lg>=0)	&&	(lg<G->n)	&&
				(G->T[line][lg].piece>=0)	&&	(G->T[line][lg].piece!=G->T[line][lg].fond)){
				*k=line;
				*l=lg;
				return;
			}
			//A droite
			if ((line>=0)	&&	(line<G->m)	&&	(ld>=0)	&&	(ld<G->n)	&&	
				(G->T[line][ld].piece>=0)	&&	(G->T[line][ld].piece!=G->T[line][ld].fond)){
				*k=line;
				*l=ld;
				return;
			}
			line++;
			lg--;
			ld++;
		}

		line=i+1;
		lg=j-rayon+1;
		ld=j+rayon-1;

		//On recherche circulairement dans les casses en dessous de notre robot
		while(line<=i+rayon) {
			//A gauche
			if ((line>=0)	&&	(line<G->m)	&&	(lg>=0)	&&	(lg<G->n)	&&
				(G->T[line][lg].piece>=0)	&&	(G->T[line][lg].piece!=G->T[line][lg].fond)){
				*k=line;
				*l=lg;
				return;
			}
			//A droite
			if ((line>=0)	&&	(line<G->m)	&&	(ld>=0)	&&	(ld<G->n)	&&	
				(G->T[line][ld].piece>=0)	&&	(G->T[line][ld].piece!=G->T[line][ld].fond)){
				*k=line;
				*l=ld;
				return;
			}
			line++;
			lg++;
			ld--;
		}

	}

}

void algorithme_circulaire(Grille *G, Solution *S){
	int k,l;

	
	while (G->cptr_noire<(G->n*G->m)){
		
		if(!RobotPortePiece(G)){
			RechercheCaseCirculaire_nn(G,G->ir,G->jr,&k,&l);
		}
		else{
			RechercheCaseCirculaire_c(G,G->T[G->ir][G->jr].robot,G->ir,G->jr,&k,&l);
		}
		//printf("position du robot (%d,%d)\t",G->ir,G->jr);
		//printf("couleur de la piece %d \n",G->T[G->ir][G->jr].robot);
		//getchar();
		PlusCourtChemin(S,G->ir,G->jr,k,l);
		changement_case(G,k,l);
		swap_case(G);
	}
}