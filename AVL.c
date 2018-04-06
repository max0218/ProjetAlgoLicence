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

	//Nouvelle racine si besoin
	AVL *res=r;
	if(r==NULL){	
		printf("Cet element n'existe pas dans l'ABR-AVL");
		return NULL;
	}
	if(contenu==r->c){
		//ICI on voudrait supprimer le noeud avant de le return
		if(r->fd==NULL){
			r=r->fg;
			return r;
		}

		res=r->fd;
		while(res->fd!=NULL){
			res=res->fg;
		}
		r->c=res->c;
		free(res);	
	}
	if(r->fd==NULL&&r->fg==NULL){
		printf("Cet element n'existe pas dans l'ABR-AVL");
		return NULL;
	}
	if(contenu < r->c){
		r->fg=Suppression(contenu,r->fg);
	} else if(contenu > r->c) {
		r->fd=Suppression(contenu,r->fd);
	}
}
void Affichageprefixe(AVL *r){
	if(r==NULL){
		return;
	}
	Affichageprefixe(r->fg);
	printf("%d\t",r->c);
	Affichageprefixe(r->fd);
}
//Initialise une matrice d'AVL de taille nb_couleurs * nb_lignes
AVL*** InitialisationMatrice(Grille *G){

  int k,j,i;
  
  int nb_couleurs = G->nbcoul;
  int nb_lignes = G->m ;

  AVL*** matrice=(AVL***)malloc(nb_couleurs*sizeof(AVL**));


  for(i=0 ; i<nb_lignes ; i++){
    (matrice)[i]=(AVL**)malloc (sizeof(AVL*));
  }
 
    
  return matrice;
}

// Trouve tous les j tels que la case (i,j) contient la couleur c, et stock dans un AVL
AVL* ConstructionAVL(Grille* G,int c,int i){
  AVL * res = NULL;
  int j;

    for(j=0 ; j < G->n ; j++){

      if(G->T[i][j].piece == c){
			Ajout(j,res);
      }

  	}	   
  return res;
}

//Construit la matrice M[c][i] tq les cases (i,j) contiennent la couleur c 
AVL *** ConstructionMatrice(Grille * G){
  
  int nb_couleurs = G->nbcoul; 
  int nb_lignes = G->m ;

  int k,l;
  
  AVL *** M =InitialisationMatrice(G);

  for(k=0;k<nb_couleurs;k++){ 	//Pour chaque couleur que la grille possede

    for(l=0;l<nb_lignes ; l++){	//On parcourt les lignes de la Grille

      M[k][l]=ConstructionAVL(G,k,l);
      // M[k][l] contiendra toutes les cases de couleur k à la ligne l, dans un AVL 
    }
  }
  
  
  return M;
}


//Retourne la case la plus proche d'une case (k,l) pour une certaine couleur, sur une ligne
int j_plus_proche(Grille * G,AVL *r, int j ){
	
  
  int distance = abs( j - r->c);
  int minJ=G->n;
  int min=0;

  if(!r)return minJ;
  
  if(abs(distance) < min){
      min = abs(j-r->c);
      minJ = r->c;
  }

  if(r->c == j){
      return j;
  }

  if(r->c < j){
    j_plus_proche(G,r->fd,j);
  }
  if(r->c > j){
    j_plus_proche(G,r->fg,j);
  }

  return;

}

//Recherche la case la plus proche de (i,j) de couleur c dans la matrice d'AVL
void case_plus_proche_c(Grille *G,AVL ***M,int c,int i,int j,int *k,int *l){
	int cpt;
	int dist_min=G->n+G->m;

	for (cpt=0;cpt < (G->m)/2; cpt++){


	}
}


void algorithme_AVL(Grille *G, Solution *S){
  
  AVL *** M =InitialisationMatrice(G);

  int i,j;
  int k = 0;
  int l = 0;


  while (G->cptr_noire<(G->n*G->m)){
		if(!RobotPortePiece(G)){
			RechercheCaseCirculaire_nn(G,G->ir,G->jr,&i,&j);
		}else{
			int couleurdurobot=G->T[G->ir][G->jr].robot;
			//On recherche la case la plus proche pour une couleur donnee

			//case_plus_proche_c(M,c,i,j,k,l);

		}
		//printf("position du robot (%d,%d)\t",G->ir,G->jr);
		//printf("couleur de la piece %d \n",G->T[G->ir][G->jr].robot);
		//getchar();
		PlusCourtChemin(S,G->ir,G->jr,i,j); // A DECONNECTER POUR TESTER DE GRANDES GRILLES
		changement_case(G,i,j);
		swap_case(G);
	}

}