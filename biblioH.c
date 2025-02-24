#include "biblioH.h"
#include <math.h>

/* ***************** EXERCICE 2 ***************** */ 

// Q 2.2: Fonction pour calculer la clé d'un auteur
int fonctionClef(char* aut){
	int cle = 0;
	while(*aut){
		cle += (int)(*aut);
		aut++;
	}
	return cle;
}

// Q 2.3 : Fonction pour créer un livre
LivreH* creer_LivreH(int num, char* titre, char* aut){
	LivreH* livre = (LivreH*)malloc(sizeof(LivreH));
	if (!livre) {
		printf("Erreur: Allocation mémoire échouée\n");
		return NULL;
	}
	livre->num = num;
	livre->titre = strdup(titre);
	livre->auteur = strdup(aut);
	livre->suivant = NULL;
	return livre;
}

// Fonction pour libérer un livre
void liberer_LivreH(LivreH* l){
	if (l != NULL) {
		free(l->titre);
		free(l->auteur);
		free(l);
	}
}

// Fonction: créer une bibliothèque avec une table de hachage
BiblioH* creer_Biblio(int m){
	BiblioH* biblio = (BiblioH*)malloc(sizeof(BiblioH));
	if (!biblio) {
		printf("Erreur: Allocation mémoire échouée\n");
		return NULL;
	}
	biblio->m = m;
	biblio->nE = 0;
	biblio->T = (LivreH**)malloc(sizeof(LivreH*) * m);

	if(!biblio->T){
		printf("Erreur: Allocation mémoire échouée\n");
		free(biblio);
		return NULL;
	}

	// Initialisation de la table
	for(int i = 0; i < m; i++){
		biblio->T[i] = NULL;
	}

	return biblio;
}


// Fonction: afficher biblio
void afficher_biblioH(BiblioH* biblio){
    if (biblio == NULL) {
        printf("La bibliothèque est vide.\n");
        return;
    }

    // Iterate parcour hasg table
    for(int i = 0; i < biblio->m; i++){
        LivreH* current = biblio->T[i];  
        if (current != NULL) {
            printf("Bucket %d:\n", i); 
            while (current != NULL) {
                printf("Numéro: %d, Titre: %s, Auteur: %s\n", 
                        current->num, current->titre, current->auteur);
                current = current->suivant;  
            }
        }
    }
}

// Fonction: libérer la mémoire d'une biblio
void liberer_BiblioH(BiblioH* b){
    if (!b) return;
    
    for(int i = 0; i < b->m; i++){
        LivreH* livre = b->T[i];
        while (livre != NULL) {
            LivreH* tmp = livre;
            livre = livre->suivant;
            liberer_LivreH(tmp);
        }
    }
    free(b->T);
    free(b);
}

// Q 2.4: Fonction de hachage pour la clé
int fonctionHachage(int cle, int m){
	const double A = (sqrt(5) - 1) / 2; 
	double y = cle * A - (int)(cle * A);
	return (int)(m * y);
}

// Q 2.5 : Fonction pour insérer un livre dans la biblio
void inserer(BiblioH* b, int num, char* titre, char* auteur){
	if (!b) return;

	int clef = fonctionClef(auteur); 
	int i = fonctionHachage(clef, b->m); 

	LivreH* l = creer_LivreH(num, titre, auteur);
	if (!l) return;

	l->suivant = b->T[i];  
	b->T[i] = l; 

	b->nE++;
}
// Fonction: rechercher un livre dans la biblio par number
LivreH* recherche_numH(BiblioH* b, int num){
	if(!b) return NULL;
	int i = fonctionHachage(num, b->m);  
	LivreH* livre = b->T[i];
	while(livre != NULL){
		if(livre->num == num){  
			return livre;
		}
		livre = livre->suivant;
	}

	return NULL;  
	}
// Fonction: rechercher un livre dans la biblio par titre
LivreH* recherche_titreH(BiblioH* b, char* titre){
	if(!b){
		return NULL;
	}
	for(int i = 0; i < b->m; i++){
		LivreH* l = b->T[i];
		while(l != NULL){
	    		if(strcmp(l->titre, titre) == 0){  
				return l; 
	    		}
	   		l = l->suivant;
	   	}
	}
	return NULL;
}

// Fonction: rechercher un livre dans la biblio par auteur
LivreH* rechercher_auteurH(BiblioH* b, char* auteur){
    if (!b) return NULL;

    int clef = fonctionClef(auteur);
    int i = fonctionHachage(clef, b->m);
    LivreH* livre = b->T[i];
    LivreH* res = NULL;
    LivreH* last = NULL;

    while(livre != NULL){
        if (strcmp(livre->auteur, auteur) == 0) {
            if (res == NULL) {
                res = livre;
            } else {
                last->suivant = livre;
            }
            last = livre;
        }
        livre = livre->suivant;
    }
    return res; 
}

