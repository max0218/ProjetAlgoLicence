#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include"Grille.h"

typedef struct cell_circuit{
LDC L;
int jmin , jmax;
struct cell_circuit *suiv;
} Cell_circuit;


typedef struct{
int nb_circuit;
Cell_circuit *premier;
Cell_circuit *dernier;
} Lcircuit;


//Initialise un Cell_circuit
Cell_circuit* CC_Init(int jmin,int jmax);

//Initialise un LCircuit
Lcircuit* Lcircuit_Init();

//Insertion en queue dans un Lcircuit
Insertion_en_queue_Lcircuit(Lcircuit *LC,Cell_circuit* cc);

//Liberation memoire cell_circuit
void Cell_circuit_free(Lcircuit * circuit, Cell_circuit * c);

//Liberation memoire cell
void Cell_free(Cell_circuit * c);

//Permet d'afficher un ensemble de circuits couvrant les sommets non-noirs de H
void Graphe_Rech_Circuit(Graphe *H);

//Retourne une liste de circuits de H couvrant les sommets non-noirs
void Graphe_Rech_Circuit_v2(Graphe *H, Lcircuit *LC);

//Liste de circuit LC triée et contient les valeurs jmin et jmax
void CalculJminJmax(Lcircuit *LC);

//Insere L,R,S dans une solution S (en tete si S est NULL sinon apres le pointeur c d'une case de S),
//retourne le pointeur de la cellule créée et update Tref
Cell_char* Ajout_action_apres_c(Solution* S,Cell_char* c,int j, char a,Cell_char** Tref);

//Insere le chemin de R ou L dans la solution S entre la case j et l, retourne un pointeur sur la dernière cellule ajoutée
Cell_char* pluscourtchemin_apres_c(Solution *S,Cell_char* c, int j,int l,Cell_char** Tref);

//Insere une sequence de déplacements L,R,S du robot dans S correspondant au circuit c
void Ajout_circuit_dans_solution(LDC* L,Solution* S,Cell_char* c,Cell_char** Tref,int* Jdroite);

//algorithme de Daniel Graf
void algorithme_circuit_CasLigne1x1(Grille *G,Solution *S);

#endif