#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Graphe.h"
#include "ListeDC.h"
#include "Circuit.h"


//Initialise un Cell_circuit
Cell_circuit* CC_Init(int jmin,int jmax){

	Cell_circuit *cc=malloc(sizeof(Cell_circuit));

	cc->L.premier=NULL;
	cc->L.dernier=NULL;

	cc->jmin=jmin;
	cc->jmax=jmax;

	cc->suiv=NULL;

	return cc;
}

//Initialise un LCircuit
Lcircuit* Lcircuit_Init(){

	Lcircuit* LC=malloc(sizeof(Lcircuit));

	LC->nb_circuit=0;
	LC->premier=NULL;
	LC->dernier=NULL;

	return LC;
}

//Insertion en queue dans un Lcircuit
void Insertion_en_queue_Lcircuit(Lcircuit *LC,Cell_circuit* cc){

	if(LC->premier==NULL){
		LC->premier=cc;
		LC->dernier=cc;
	}else{
		LC->dernier->suiv=cc;
		LC->dernier=cc;
		cc->suiv=NULL;
	}
	LC->nb_circuit++;
}

//Liberation memoire cell_circuit
/*
void Cell_circuit_free(Lcircuit * circuit, Cell_circuit * c){

	Cell_circuit * precC=c->prec;
	Cell_circuit * suivC=c->suiv;

	if (precC==NULL) 
	    circuit->premier=suivC;
	else 
	    precC->suiv=suivC;
	if (suivC==NULL) 
	    circuit->dernier=precC;
	else 
		suivC->prec=precC;
	Cell_free(c);
}

//Liberation memoire cell
void Cell_free(Cell_circuit * c){
	LDCdesalloue(c->L);
	free(c);
}
*/
//Recherche d'un circuit à partir d'un sommet et màj jmin et jmax
Cell_circuit* Sommet_Rech_Circuit(Graphe* H,Sommet* somm){

	if(somm->visit==0){	// Si ce sommet est déjà visité
		return NULL;
	}

	Sommet* psom=somm;
	Cell_circuit* c=CC_Init(psom->j,0);	//Initialisation d'une liste chainée de circuit, jmin est le j du premier sommet(donc le plus à gauche)
	int jmax=0;

	while(psom->visit	==	-1){
		LDCInsererEnFin(&(c->L),psom->i,psom->j);
		psom->visit=0;

		if(psom->j>jmax){
			jmax=psom->j;	// Indice jmax de la case la plus à droite de ce circuit
		}

		psom=psom->Lsucc->succ;
	}
	c->jmax=jmax;
	LDCafficher(&(c->L));
	printf("Fin du circuit \n");

	return c;
}

//Permet d'afficher un ensemble de circuits couvrant les sommets non-noirs de H
void Graphe_Rech_Circuit(Graphe *H){
	int i,j;

	for(i=0;i<H->m;i++){
		
		for(j=0;j<H->n;j++){

			if(H->Tsom[i][j]->visit==-1){
			
				Sommet_Rech_Circuit(H,H->Tsom[i][j]); // Affiche un circuit 

			}
		}
	}
}


//Retourne une liste de circuits de H couvrant les sommets non-noirs
void Graphe_Rech_Circuit_v2(Graphe *H, Lcircuit *LC){
	int i,j;
	for(i=0	;	i<H->m	;	i++){
		//printf("début itération i=%d \n",i);
		for(j=0	;	j<H->n	;	j++){
			//printf("début itération j=%d \n",j);
			if(H->Tsom[i][j]->Lsucc==NULL){
				H->Tsom[i][j]->visit=-2;
			}
			//printf("Valeur de visit : %d\n",H->Tsom[i][j]->visit);
			if(H->Tsom[i][j]->visit==-1){
				
				//printf("Avant la recherche du circuit\n");
				Cell_circuit* cc = Sommet_Rech_Circuit(H,H->Tsom[i][j]);	//Un circuit de sommets non-noirs
				//printf("Avant l'insertion\n");
				Insertion_en_queue_Lcircuit(LC,cc); //Insertion du circuit dans une liste
				//printf("Insertion circuit dans liste\n");
			}
			//printf("fin itération j=%d \n",j);
		}
		//printf("fin itération i=%d\n",i);
	}
}

//Liste de circuit LC triée et contient les valeurs jmin et jmax
//Tout est fait dans la fonction Sommet_rech_circuit
void CalculJminJmax(Lcircuit *LC){

	if(LC==NULL){
		printf("Calcul de Jmin et Jmax impossible : Liste de circuit NULL");
	}

	Cell_circuit* pcc=LC->premier;
	//On parcourt la liste de circuits
	while(pcc!=LC->dernier){

	}
}

//Insere L,R,S dans une solution S (en tete si S est NULL sinon apres le pointeur c d'une case de S),
//retourne le pointeur de la cellule créée et update Tref
Cell_char* Ajout_action_apres_c(Solution* S,Cell_char* c,int j, char a,Cell_char** Tref){

	if(c==NULL){	//Insertion en tête de liste S
		Ajout_action(S,a);
	}else{ //Insertion après le pointeur c d'une case de S

	}
}

//Insere le chemin de R ou L dans la solution S entre la case j et l, retourne un pointeur sur la dernière cellule ajoutée
Cell_char* pluscourtchemin_apres_c(Solution *S,Cell_char* c, int j,int l,Cell_char** Tref){

}

//Insere une sequence de déplacements L,R,S du robot dans S correspondant au circuit c
void Ajout_circuit_dans_solution(LDC* L,Solution* S,Cell_char* c,Cell_char** Tref,int* Jdroite){

}

//algorithme de Daniel Graf
void algorithme_circuit_CasLigne1x1(Grille *G,Solution *S,Lcircuit* LC){

	int i;
	//Tref contient NULL si la case i n'a pas été rencontrée par le robot
	Cell_char* Tref[G->n];
	for(i=0;i<G->n;i++){
		Tref[i]=NULL;
	}

	int Jdroite=0;	//Indice de la case la plus à droite visitée par le robot

	Cell_circuit* cc=LC->premier;
	int Drapeau=0;
	do{
		if(Tref[cc->jmin]==NULL){
			Drapeau=1;
			
		}

		if(Drapeau==1){
			Drapeau=0;

		}
		cc=cc->suiv;
	}while(cc!=LC->dernier);	
}
