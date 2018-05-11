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

//Recherche d'un circuit à partir d'un sommet 
Cell_circuit* Sommet_Rech_Circuit(Graphe* H,Sommet* somm){

	Sommet* psom=sommet;
	Cell_circuit* c;

	while(psom->visit!=0){
		LDCInsererEnFin(c->L,psom->i,psom->j);
		psom->visit=0;

		psom=psom->Lsucc->succ;
	}
	LDCafficher(c->L);
	printf("Fin du circuit \n");
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