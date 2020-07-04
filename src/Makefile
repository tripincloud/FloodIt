all: Flood-It_Partie1

Liste_S_Zsg.o: Liste_S_Zsg.c Liste_S_Zsg.h
	gcc -g -c Liste_S_Zsg.c `sdl-config --cflags`

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -g -c API_Gene_instance.c `sdl-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -g -c API_Grille.c `sdl-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -g -c Liste_case.c `sdl-config --cflags`

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -g -c Fonctions_exo1.c `sdl-config --cflags`

Fonctions_exo2.o: Fonctions_exo2.c Entete_Fonctions.h Liste_case.h
	gcc -g -c Fonctions_exo2.c `sdl-config --cflags`

 Graphe-exo4.o: Graphe-exo4.c Graphe-exo4.h	Entete_Fonctions.h Liste_case.h
	gcc -g -c Graphe-exo4.c `sdl-config --cflags`

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc -g -c Flood-It_Partie1.c `sdl-config --cflags`

Graphe-exo5.o: Graphe-exo5.c Graphe-exo4.h
	gcc -g -c Graphe-exo5.c `sdl-config --cflags`

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille.o API_Gene_instance.o Fonctions_exo1.o Liste_S_Zsg.o Fonctions_exo2.o Graphe-exo4.o Graphe-exo5.o
	gcc -g -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o Liste_S_Zsg.o Fonctions_exo2.o Graphe-exo4.o Graphe-exo5.o `sdl-config --libs` 

clean:
	rm -f *.o Flood-It_Partie1


