#ifndef BIBLIOH_H
#define BIBLIOH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure for a book in the hash table
typedef struct livreh {
	int num;            
	char *titre;       
	char *auteur;      
	struct livreh *suivant; 
} LivreH;

// Structure pout hasg table
typedef struct {
	int nE; 
	int m;     
	LivreH **T;    
} BiblioH;

// Function declarations
	int fonctionClef(char* auteur);
	LivreH* creer_LivreH(int num, char* titre, char* auteur);
	void liberer_LivreH(LivreH* l);
	BiblioH* creer_Biblio(int m);
	void liberer_BiblioH(BiblioH* b);
	int fonctionHachage(int cle, int m);
	void inserer(BiblioH* b, int num, char* titre, char* auteur);
	LivreH* rechercher_auteurH(BiblioH* b, char* auteur);
	BiblioH* charger_n_entreesH(char* ficher, int n);
	void afficher_biblioH(BiblioH* biblio);
	LivreH* recherche_titreH(BiblioH* b, char* titre);
	LivreH* recherche_numH(BiblioH* b, int num);

#endif // BIBLIOH_H

