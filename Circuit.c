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
Insertion_en_queue_Lcircuit(Lcircuit *LC,Cell_circuit* cc){

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
//Recherche d'un circuit à partir d'un sommet 
Cell_circuit* Sommet_Rech_Circuit(Graphe* H,Sommet* somm){

	Sommet* psom=somm;
	Cell_circuit* c=CC_Init(psom->j,0);	//Initialisation d'une liste chainée de circuit, jmin est le j du premier sommet(donc le plus à gauche)
	int jmax=0;

	while(psom->visit!=0){
		LDCInsererEnFin(c->L,psom->i,psom->j);
		psom->visit=0;

		if(psom->j>jmax){
			jmax=psom->j;	// Indice jmax de la case la plus à droite de ce circuit
		}

		psom=psom->Lsucc->succ;
	}
	c->jmax=jmax;
	LDCafficher(c->L);
	printf("Fin du circuit \n");

	return c;
}

//Permet d'afficher un ensemble de circuits couvrant les sommets non-noirs de H
void Graphe_Rech_Circuit(Graphe *H){
	int i,j;
	//Sommet *scour;
	//Arc *acour;
	//On pourrait réduire le nombre d'itérations 
	for(i=0;i<H->n;i++){
		
		for(j=0;j<H->m;j++){

			if(H->Tsom[i][j]->visit==-1){
			
				Sommet_Rech_Circuit(H,H->TSom[i][j]); // Affiche un circuit 

			}
		}
	}
}


//Retourne une liste de circuits de H couvrant les sommets non-noirs
void Graphe_Rech_Circuit_v2(Graphe *H, Lcircuit *LC){

	for(i=0;i<H->n;i++){
		
		for(j=0;j<H->m;j++){

			if(H->Tsom[i][j]->visit==-1){

				cell_circuit *cc=CC_init(0,0);		//Initialisation d'une liste chainée de circuit

				cc=Sommet_Rech_Circuit(H,H->Tsom[i][j]);	//Un circuit de sommets non-noirs

				Insertion_en_queue_Lcircuit(LC,cc); //Insertion du circuit dans une liste
			}
		}
	}
}

//Liste de circuit LC triée et contient les valeurs jmin et jmax
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

}

//Insere le chemin de R ou L dans la solution S entre la case j et l, retourne un pointeur sur la dernière cellule ajoutée
Cell_char* pluscourtchemin_apres_c(Solution *S,Cell_char* c, int j,int l,Cell_char** Tref){

}

//Insere une sequence de déplacements L,R,S du robot dans S correspondant au circuit c
void Ajout_circuit_dans_solution(LDC* L,Solution* S,Cell_char* c,Cell_char** Tref,int* Jdroite){

}

//algorithme de Daniel Graf
void algorithme_circuit_CasLigne1x1(Grille *G,Solution *S){

}
