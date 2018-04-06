#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "AVL.h"

int main(){

	AVL *racine=Ajout(5,racine);
	Ajout(4,racine);
	Ajout(6,racine);

	Affichageprefixe(racine);


return 0;
}