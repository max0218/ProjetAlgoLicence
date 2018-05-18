#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "Circulaire.h"
#include "Moins_de_pas.h"


//Grille une case par couleur

void moins_de_pas(Solution *S, Grille *H){
	int k,l;

	while (G->cptr_noire<(G->n*G->m)){
		//cas où le robot ne porte pas de pièce : on se rend sur la case non noire la plus proche et on ramasse la piece
		if(!RobotPortePiece(G)){ 
			RechercheCaseCirculaire_nn(G,G->ir,G->jr,&k,&l);
			PlusCourtChemin(S,G->ir,G->jr,k,l);
			changement_case(G,k,l);
			swap_case(G);
		}

		//cas où le robot porte une pièce : on recherche la case de meme couleur, et on se deplace d'une case dans sa direction. Si la case n'est pas noire, on echange ls pieces
		else{
			RechercheCaseCirculaire_c(G,G->T[G->ir][G->jr].robot,G->ir,G->jr,&k,&l);
			if (k<G->ir){
				G->ir--;
				Ajout_Action(S,'L');
			}
			else if (k>G->ir){
				G->ir++;
				Ajout_Action(S,'R');
			}
			else if (l<G->jr){
				G->jr--;
				Ajout_Action(S,'U');
			}
			else{
				G->jr++;
				Ajout_Action(S,'D');
			}
			if (!CaseEstNoire){
				swap_case(G);
				Ajout_Action(S,'S');
			}
		}
	}
}
