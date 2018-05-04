all : Maingraph

Maingraph.o : Maingraph.c Grille.h ListeDC.h Graphe.h Circuit.h
	gcc -c Maingraph.c

Maingraph : Maingraph.o  Grille.o  ListeDC.o Graphe.o Circuit.o
	gcc -gdbb -o Maingraph Maingraph.o  Grille.o  ListeDC.o Graphe.o Circuit.o

clean :
	rm -f *.o Maingraph
