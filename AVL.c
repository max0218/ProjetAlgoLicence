#include <stdio.h>
#include <stdlib.h>

#include "Grille.h"
#include "Solution.h"
#include "Naif.h"
#include "Circulaire.h"
#include "AVL.h"

//Retourne la hauteur d'un noeud
int AVL_hauteur(AVL *r){
	if(r==NULL){
		return -1;
	}
	return r->hauteur;
}

//Retourne le maximum entre deux int
int maxHauteur(int a,int b){
	if(a>b){
		return a;
	}
	return b;
}
//Met à jour la hauteur d'un noeud
void majHauteur(AVL *r){
	if(r!=NULL){
		r->hauteur=1+maxHauteur(AVL_hauteur(r->fg),AVL_hauteur(r->fd));
	}
}

// Effectue une rotation droite de l'arbre
void rotationDroite(AVL *r){
	AVL *new=r;
	AVL *fg=r->fg;
	AVL *fd=r->fd;

	r->fg=fg->fd;
	fg->fd=r;
	r=fg;
	majHauteur(r->fd);
	majHauteur(r);
}

//Effectue une rotation gauche de l'arbre
void rotationGauche(AVL *r){
	AVL *new=r;
	AVL *fg=r->fg;
	AVL *fd=r->fd;

	r->fd=fd->fg;
	fd->fg=r;
	r=fd;

	majHauteur(r->fg);
	majHauteur(r);
}

//Creation d'un noeud
AVL* creationNoeud(int contenu,AVL* fd,AVL* fg){
	AVL *new=(AVL *)malloc(sizeof(AVL));
	new->c=contenu;
	new->hauteur=1+maxHauteur(fg->hauteur,fd->hauteur);

	new->fd=fd;
	new->fg=fg;
	return new;
}


//Equilibre un AVL
AVL * Equilibre(AVL *r){
	AVL *fg=r->fg;
	AVL *fd=r->fd;
	if(abs((fg->hauteur)-(fd->hauteur))<2){ // Aucune reorganisation necessaire
		return r;
	}
	if((fg->hauteur)-(fd->hauteur)==2){
		if(fg->fg->hauteur < fg->fd->hauteur){
			rotationGauche(fg);
		}
		rotationDroite(r);
		return r;
	}
	if((fg->hauteur)-(fd->hauteur)==-2){
		if( fd->fd->hauteur < fd->fg->hauteur){
			rotationDroite(fd);
		}
		rotationGauche(r);
		return r;
	}
	return r;

}
// Ajout d'une valeur dans l'avl
AVL * Ajout(int contenu, AVL *r){
	if (r==NULL){ // Premier elem de l'AVL
		return creationNoeud(contenu,NULL,NULL);
	}

	if(contenu < r->c){ // Dans Ag
		if(r->fg==NULL){ //Nouveau fils gauche
			AVL *new=creationNoeud(contenu,NULL,NULL);
			r->fg=new;
		} else {
			r->fg=Ajout(contenu,r->fg);
		}

	} else { // Dans Ad
		if (r->fd==NULL){ //Nouveau fils droit
			AVL *new=creationNoeud(contenu,NULL,NULL);
			r->fd=new;
		} else {
			r->fd=Ajout(contenu,r->fd);
		}
	}

	majHauteur(r);
	r=Equilibre(r);
	return r;

}

//Cherche un entier dans l'AVL et le supprime s'il existe
AVL * Suppression(int contenu,AVL *r){
	if(contenu==r->c){
		
		return r;
	}
	if(r->fd==NULL&&r->fg==NULL){
		printf("Cet element n'existe pas dans l'ABR-AVL");
		return NULL;
	}
	if(contenu<r->c){
		Suppression(contenu,r->fg);

	} else {
		Suppression(contenu,r->fd);
	}

}