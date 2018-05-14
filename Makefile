all : Maingraph

Maingraph.o : Maingraph.c Grille.h ListeDC.h Graphe.h Circuit.h	Solution.h entree_sortie.h
	gcc -c Maingraph.c

Maingraph : Maingraph.o  Grille.o  ListeDC.o Graphe.o Circuit.o Solution.o entree_sortie.o
	gcc -gdbb -o Maingraph Maingraph.o  Grille.o  ListeDC.o Graphe.o Circuit.o	Solution.o	entree_sortie.o

clean :
	rm -f *.o Maingraph
