#include <stdio.h>
#include<stdlib.h>

typedef struct celluleLDC{

	int i,j;

	struct celluleLDC* prec /*pointeur sur l'element precedend de la liste*/

	struct celluleLDC* suiv; /*pointeur sur l'element suivant de la liste*/
} CelluleLDC;




typedef struct {

	CelluleLDC* premier; /*Pointeur sur element en tete*/

	CelluleLDC* dernier; /*Pointeur sur element en fin*/

} LDC;



CelluleLDC* creerCellule(int i, int j;){
	//qui alloue et retourne une cellule
	CelluleLDC* cel=(CelluleLDC*)malloc(sizeof(CelluleLDC));

	cel.i=i;

	cel.j=j;

	return cel;

}

void LDCInitialise(LDC *ldc);	//qui initialise une liste

int LDCVide(LDC* ldc);	//qui teste si la liste est vide

void LDCInsererEnFin(LDC* ldc, int i, int j);	//qui insere une nouvelle cellule en fin

void LDCenleverCellule(LCD* ldc, CelluleLDC* cel);	//qui supprime une cellule a partir d un pointeur sur la cellule

void LDCafficher(LDC* ldc);	// un affichage en cas de besoin pour debugage

void LDCdesalloue(LDC *ldc);	// qui desalloue toute la liste (si elle n'est pas vide a la fin)

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j);	//recherche dans une liste LDC la premirer case la plus proche de (i,j)

void algorithme_parcouleur(Grille *G, Solution *S);
