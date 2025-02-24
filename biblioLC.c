//Gul LAliko 21122992
//Guo Tongjing 


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biblioLC.h"


/* ***************** EXERCICE 1 ***************** */

//Creation d'un Livre

Livre* creer_livre(int num,char* titre,char* auteur){
	Livre * l = (Livre*)malloc(sizeof(Livre));
	if(!l){
		printf("Erreur: Allocation of memoire failed");
		return NULL;
		}
	l -> num = num;
	l -> titre = strdup(titre);
	l -> auteur = strdup(auteur);
	l -> suiv = NULL;
	return l;
}
//La Function realise une desallocation

void liberer_livre(Livre *l){
	Livre *temp;
	while(l){
		temp = l;
		free(l -> titre);
		free(l -> auteur);
		l = l -> suiv;
		free(temp);
	}
}

//La Function creer une Bibliotheque vide

Biblio * creer_biblio(){
	Biblio * b = malloc(sizeof(Biblio));
	if( b == NULL){
		printf("Erreur : Filed to allocate Memory");
		return NULL;
		}
	b -> L = NULL;
	return b;
}
	
//La Function liberer la memoire occupee par une Bibliotheque
		
void liberer_biblio(Biblio* b){
	liberer_livre(b->L);
	free(b);
	}
	
//La Function ajoute un livre a la bibliotheque	
		
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
	Livre *l = creer_livre(num,titre,auteur);
	l->suiv = b->L;
	b->L = l;
}

// Function afficher d'un livre

void afficher_livre(Livre *l){
	if(l != NULL){
		printf("Numéro : %d\n", l->num);
		printf("Titre : %s\n", l->titre);
		printf("Auteur : %s\n", l->auteur);
	} else {
		printf("Le livre n'a pas été trouvé.\n");
	}
}


// Function afficher une biblio

void afficher_biblio(Biblio* b){
	Livre* livre =b -> L;
	while(livre){
	afficher_livre(livre);
	livre = livre -> suiv;
	}
}

// Function recherche d'un ouverage par son numero

Livre *recherche_num(Biblio *b, int num){
	if (b == NULL || b->L == NULL){
		return NULL;
	}
	Livre* l = b->L;
	while(l){
		if(l->num == num){
	    		return l;
		}
		l = l->suiv;
	}
	return NULL;
}

// La function recherche d'un ourage par son titre

Livre *recherche_titre(Biblio *b, char *titre){
	Livre* l = b->L;
	while(l){
		if (strcmp(l->titre, titre) == 0) {
	   	 return l;
		}
		l = l->suiv;
	}
	return NULL;
}

//La Function recherche de tous les livre d'un meme auteur

Biblio *recherche_auteur(Biblio *b, char *auteur){
    if(!b || !b->L){  
	printf("Erreur: La biblio est vide.\n");
	return creer_biblio();  // Retourne biblio null
    }

    if(!auteur || strlen(auteur) == 0){
	printf("Erreur: Auteur invalide.\n");
	return creer_biblio();
    }

    Biblio* bibli = creer_biblio();
    Livre* l = b->L;
    int found = 0; 

    while(l){
	if(strcmp(l->auteur, auteur) == 0){
	    inserer_en_tete(bibli, l->num, l->titre, l->auteur);
	    found = 1;
	}
	l = l->suiv;
    }

    if(!found){
	printf("Aucun livre trouvé pour lauteur \"%s\".\n", auteur);
    }

    return bibli;
}


//LA function suprimer d'un ourage( apartir de numer,auteur,titre)
void suppression_ouvrage(Biblio *b, int num, char *titre, char *auteur){
    if(b == NULL || b->L == NULL){
        printf("Erreur: La bibliothèque est vide.\n");
        return;
    }

    Livre *l = b->L;
    Livre *prec = NULL;

    if(l->num == num && strcmp(l->auteur, auteur) == 0 && strcmp(l->titre, titre) == 0){
        b->L = l->suiv;  
        free(l->titre);  
        free(l->auteur);
        free(l);  
        return;
    }

    // Traverse reste de la liste
    while(l){
        if(l->num == num && strcmp(l->auteur, auteur) == 0 && strcmp(l->titre, titre) == 0){
            if (prec != NULL) {
                prec->suiv = l->suiv;
            }
            free(l->titre);  
            free(l->auteur);
            free(l);  
            return;
        }
        // livre suivante
        prec = l;
        l = l->suiv;
    }

    // si aucun livre trouve
    printf("Le livre n'a pas été trouvé.\n");
}

//Fusion de deux Bibliothequ
void fusion_bibli(Biblio *b1, Biblio *b2){
	Livre *l2 = b2->L;
	while(l2){
		inserer_en_tete(b1, l2->num, l2->titre, l2->auteur);
		l2 = l2->suiv;
	}
	free(b2);
}

//Recherche de tous les ouvrages avec Plusieurs Exemplaires.
Biblio* recherche_tous_ouvrages(Biblio* b){
	Biblio* bibli = creer_biblio();  // Creer une nouvel biblio
	Livre* l = b->L; 

	while(l){
		Livre* l2 = l->suiv;  
		int count = 1;  

		// Vérifier de fois ce livre vient
		while(l2){
            		if(strcmp(l->titre, l2->titre) == 0 && strcmp(l->auteur, l2->auteur) == 0){
            		count++;
           		}
            		l2 = l2->suiv;
        	}
		// Si un doublon existe, ajoute une fois 
		if(count > 1){
           		 if(!recherche_titre(bibli, l->titre)){  // Évite doublon
               			 inserer_en_tete(bibli, l->num, l->titre, l->auteur);
           		 	}	
       	 		 }
        l = l->suiv; 
        }
	return bibli;  
}



