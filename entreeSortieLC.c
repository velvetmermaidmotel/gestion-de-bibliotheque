#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

/* ***************** EXERCICE 1 Q 1.3 ***************** */

// La function permet de lire n lignes du fichier et les stocker dans une Biblio
Biblio* charger_n_entrees(char* nomfic, int n){
	    if (nomfic == NULL ){
	    	printf("Erreur : le ficher est NULL_n");
	    	return NULL;
	    }
	    FILE *fr = fopen(nomfic, "r");
	    if (fr == NULL) {
		printf("Erreur d'ouverture du fichier %s\n", nomfic);
		return NULL;
	    }
	    
	    Biblio* b = creer_biblio();
	    int cpt = 0;
	    char titre[250];
	    char auteur[250];
	    int num;
	    char buf[250];

	    while(cpt != n && fgets(buf, sizeof(buf), fr)){
		if(sscanf(buf, "%d %s %s", &num, titre, auteur) == 3){
		    inserer_en_tete(b, num, titre, auteur);
		    cpt++;
		}
	    }
	    
	    fclose(fr);
	    return b;
}

// La function permet de stocker une Bibliotheque dans un fichier au bon format
void enregistrer_biblio(Biblio *b, char* nomfic){
	if(b == NULL || b->L == NULL){
		printf("Erreur : la bibliotheque est vide.\n");
		return;
	}
	FILE *fw = fopen(nomfic, "w");
		if (fw == NULL) {
		printf("Erreur d'ouverture du fichier %s\n", nomfic);
		return;
	}
	Livre* tmp = b->L;
	while(tmp){
		fprintf(fw, "%d %s %s\n", tmp->num, tmp->titre, tmp->auteur);
		tmp = tmp->suiv;
	}

	fclose(fw);
	}

