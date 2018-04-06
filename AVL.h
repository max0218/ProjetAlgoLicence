#include <stdio.h>
#include<stdlib.h>

#include "Grille.h"
#include "Solution.h"
#include "Naif.h"
#include "Circulaire.h"
#include "ParCouleur.h"

typedef struct s_avltree{
	int c;
	int hauteur; //Hauteur de l'arbre

	struct s_avltree* fd;
	struct s_avltree* fg;
}AVL;


//Retourne la hauteur d'un noeud
int AVL_hauteur(AVL *r);

//Retourne le maximum entre deux int
int maxHauteur(int a,int b);

//Met à jour la hauteur d'un noeud
void majHauteur(AVL *r);

// Effectue une rotation droite de l'arbre
void rotationDroite(AVL *r);

//Effectue une rotation gauche de l'arbre
void rotationGauche(AVL *r);

//Creation d'un noeud
AVL* creationNoeud(int contenu,AVL* fd,AVL* fg);

//Equilibre un AVL
AVL * Equilibre(AVL *r);

//Ajout d'une valeur dans l'AVL
AVL * Ajout(int contenu, AVL *r);

//Cherche un entier dans l'AVL et le supprime s'il existe
AVL * Suppression(int contenu,AVL *r);

//Affiche l'AVL dans l'ordre croissant
void Affichageprefixe(AVL *r);

//Initialise une matrice d'AVL de taille nb_couleurs * nb_lignes
AVL*** InitialisationMatrice(Grille *G);

// Trouve tous les j tels que la case (i,j) contient la couleur c, et stock dans un AVL
AVL* ConstructionAVL(Grille* G,int c,int i);

//Construit la matrice M[c][i] tq les cases (i,j) contiennent la couleur c 
AVL *** ConstructionMatrice(Grille * G);

//Retourne la case la plus proche d'une case (k,l) pour une certaine couleur, sur une ligne
int j_plus_proche(Grille * G,AVL *r, int j );

//Recherche la case la plus proche de (i,j) de couleur c dans la matrice d'AVL
void case_plus_proche_c(Grille *G,AVL ***M,int c,int i,int j,int *k,int *l);

//Resoud la grille avec l'algorithme par AVL
void algorithme_AVL(Grille *G,Solution *S);
