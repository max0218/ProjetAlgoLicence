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
int AVL_hauteur(AVL r);

//Retourne le maximum entre deux int
int maxHauteur(int a,int b);

//Met à jour la hauteur d'un noeud
void majHauteur(AVL r);

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

