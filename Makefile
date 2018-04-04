all: Game_SortingRobot Checker_SortingRobot Main

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c

API_AffGrille.o: API_AffGrille.c API_AffGrille.h Grille.h
	gcc -c API_AffGrille.c

Game_SortingRobot.o: Game_SortingRobot.c Grille.h API_AffGrille.h Solution.h 
	gcc -c Game_SortingRobot.c 

Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Game_SortingRobot Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

Checker_SortingRobot.o: Checker_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Checker_SortingRobot.c

Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

Naif.o : Naif.c Naif.h Grille.h  Solution.h 
	gcc -c Naif.c

Circulaire.o : Circulaire.c Circulaire.h Grille.h Solution.h
	gcc -c Circulaire.c

ParCouleur.o : ParCouleur.c ParCouleur.h Grille.h Solution.h
	gcc -c ParCouleur.c

AVL.o : AVL.c AVL.h Grille.h Solution.h
	gcc -c AVL.c

Main.o : Main.c Naif.h Circulaire.h ParCouleur.h AVL.h Grille.h API_AffGrille.h Solution.h
	gcc -c Main.c

Main : Main.o  Naif.o Circulaire.o ParCouleur.o AVL.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Main Main.o Naif.o Circulaire.o ParCouleur.o AVL.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

clean:
	rm -f *.o Game_SortingRobot Checker_SortingRobot Main *.sol

cleansol: 
	rm -f *.sol