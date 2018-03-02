#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"


//Insertion en fin de liste chainee de la sequence de caractere correspond au plus court chemin 
//dans la grille allant de la case (i,j) a la case (k,l)
void PlusCourtChemin(Solution *S, int i,int j, int k, int l);

//Savoir si le fond d'une case et la piece qu'elle porte sont de meme couleur
int CaseEstNoire(Grille *G,int i,int j);

//Savoir si le robot porte une piece
int RobotPortePiece(Grille *G);

//Savoir si la piece est noire
int PieceEstNoire(Grille *G, int i, int j);

//Savoir de quelle couleur est la piece portee par le robot
int RobotCouleurPiece(Grille *G);

//Retourne la case (k,l) de couleur c la plus proche de (i,j) au sens de l'algorithme "au plus proche"
void RechercheCaseNaif_c(Grille *G,int c, int i, int j, int *k, int *l);

//Retourne la case (k,l) de couleur NOIRE la plus proche de (i,j) au sens de l'algorithme "au plus proche"
void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

//Version naive de l'algorithme au plus proche, ecrit sur disque la Solution
void algorithme_naif(Grille *G, Solution *S);

//Calcule la distance entre deux cases referencees par leurs coordonnees entieres//
int distance(int i, int j, int k, int l);