#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "Grille.h"
#include "Solution.h"
#include "Naif.h"

void test_circulaire(int i,int j,int L);

//Retourne la case (k,l) de couleur c la plus proche de (i,j) par l'algorithme circulaire
void RechercheCaseCirculaire_c(Grille *G,int c,int i, int j, int *k, int *l);

//Retourne la case (k,l) de couleur NOIRE la plus proche de (i,j) au sens de l'algorithme circulaire
void RechercheCaseCirculaire_nn(Grille *G,int i,int j, int *k, int *l);

//Version de l'algorithme circulaire
void algorithme_circulaire(Grille *G, Solution *S);