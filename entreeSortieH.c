#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioH.h"

// Fonction pour charger n livres dans la table de hachage
BiblioH* charger_n_entreesH(char* file, int n){
	// Ouvrir le fichier
	FILE* f = fopen(file, "r");
	if(f == NULL){
		printf("Erreur: fichier %s non trouvé.\n", file);
		return NULL;
	}

    	// Création d'une biblio (table de hachage) 
    	int table_taill = n;
	BiblioH* biblio = creer_Biblio(table_taill);
	if(!biblio){
		fclose(f);
		return NULL;
	}

	int num;
	char titre[256], auteur[256];

    	// Lire du fichier
	for(int i = 0; i < n; i++){
		if(fscanf(f, "%d %255s %255s", &num, titre, auteur) == 3){
	    	inserer(biblio, num, titre, auteur);
		} else {
	   	 break;
		}
	}
	fclose(f);
	return biblio;
}

// Fonction permit d enregistrer les livres de une biblio (table de hachage)
void enregistrer_biblioH(BiblioH* b, char* nomfic){
	// Vérifier si la biblio 
	if (b == NULL) {
		printf("Erreur: La biblio est vide.\n");
		return;
	}

	// Ouverture du fichier en mode écriture
	FILE* fw = fopen(nomfic, "w");
	if(fw == NULL){
		printf("Erreur d'ouverture du fichier %s\n", nomfic);
		return;
	}

    	// Parcourir chaque case de la table de hachage
	for(int i = 0; i < b->m; i++){
		LivreH* livre = b->T[i];
		while(livre != NULL){
	   		 fprintf(fw, "%d %s %s\n", livre->num, livre->titre, livre->auteur);
	    		livre = livre->suivant;
			}
	}
	// Fermer le fichier après écrit
	fclose(fw);
}

