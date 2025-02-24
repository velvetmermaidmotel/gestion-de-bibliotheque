#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

//#define USE_HASH_TABLE  // Commente pour utliser liste chainees option

#define NB_TESTS 10000 
#ifdef USE_HASH_TABLE
#include "biblioH.h"
#include "entreeSortieH.h"
#else
#include "biblioLC.h"
#include "entreeSortieLC.h"
#endif

//Q 1.7 :Fonction void menu() permettant d'afficher les actions possibles sur la biblio
void menu() {
	printf("\n=== MENU ===\n");
	printf("0 - Quitter\n");
	printf("1 - Afficher bibliothèque\n");
	printf("2 - Ajouter un livre\n");
	printf("3 - Rechercher un livre par numéro\n");
	printf("4 - Rechercher un livre par titre\n");
	printf("5 - Recherche de tous les livres de meme auteur\n");
	printf("6 - Rechercher tous les livres\n");
	printf("7 - Supprimer un ouvrage\n");
	printf("8 - Rechercher tous les ouvrages avec plusieurs exemplaires\n");
	printf("9 - Comparison_Test\n");
}

// Exercice 3 – Implementtation de Comparaison des deux structures
void comparer_recherche(char* fichier, int max_taille, int type, char* v){
	FILE *f = fopen("comparison_recherche.txt", "w");
	if(!f){
		perror("Erreur: Impossible d'ouvrir le fichier.\n");
		return;
	}

	for(int n = 1000; n <= max_taille; n *= 2){  
		printf("Test avec n = %d...\n", n);
		clock_t debut, fin;
		double temps_liste = 0, temps_hachage = 0;

		#ifdef USE_HASH_TABLE
		
		BiblioH *b_hachage = charger_n_entreesH(fichier, n);
		for(int i = 0; i < NB_TESTS; i++){
	   		debut = clock();
	    		switch(type){
				case 1: rechercher_auteurH(b_hachage, v); break;
				case 2: recherche_titreH(b_hachage, v); break;
				case 3: recherche_numH(b_hachage, atoi(v)); break;
				case 4: recherche_tous_ouvragesH(b_hachage); break;
	    		}
	    		fin = clock();
	   		temps_hachage += (double)(fin - debut)/CLOCKS_PER_SEC;
	   		printf("Temps enregistré: %f\n", temps_hachage);
		}
		liberer_BiblioH(b_hachage);

		#else
		
		Biblio *b_liste = charger_n_entrees(fichier, n);
		for(int i = 0; i < NB_TESTS; i++){
	    		debut = clock();
	    		switch (type) {
				case 1: recherche_auteur(b_liste, v); break;
				case 2: recherche_titre(b_liste, v); break;
				case 3: recherche_num(b_liste, atoi(v)); break;
				case 4: recherche_tous_ouvrages(b_liste); break;
	    	    }
		    fin = clock();
		    temps_liste += (double)(fin - debut)/CLOCKS_PER_SEC;
		}
		liberer_biblio(b_liste);
		#endif

		fprintf(f, "%d %f %f\n", n, temps_liste /NB_TESTS, temps_hachage/NB_TESTS);
	}
	fclose(f);
	printf("Résultats enregistrés dans comparison_recherche.txt\n");
	}

// Q 1.8 :MAIN 
       
int main(int argc, char** argv){
	if (argc < 3) {
	printf("Usage: %s <fichier> <nbr lignes>\n", argv[0]);
	return 1;
}

#ifdef USE_HASH_TABLE
                   /* ********** VERSION HASHAGE ********** */
    
        // Créer bibliO de taille de table de hachage
	BiblioH* b = charger_n_entreesH(argv[1], atoi(argv[2]));
	if(b == NULL){
		printf("Erreur du chargement de la biblio.\n");
	return 1;
        }
	int rep, num;
	char titre[256], auteur[256];

     do {
        menu();
        printf("Choisisse un option : ");
        scanf("%d", &rep);
        getchar();  // clean buffer

        switch(rep){
            case 0:
                printf("Fin du programme.\n");
                break;
            case 1:
                printf("Affichage de la biblio :\n");
                afficher_biblioH(b); 
                break;

            case 2:
                printf("Ajout d'un ouvrage\n");
                printf("Numero : ");
                scanf("%d", &num);
                getchar();

                printf("Titre : ");
                fgets(titre, sizeof(titre), stdin);
                titre[strcspn(titre, "\n")] = '\0';

                printf("Auteur : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = '\0';

                inserer(b, num, titre, auteur);
                printf("Ajout reussi !\n");
                break;
	    case 3:
		printf("Entrez le numero du livre : ");
		if(scanf("%d", &num) == 1){
			LivreH* l = recherche_numH(b, num); 
			if(l){
		    	printf("Livre trouve: Numero: %d, Titre: %s, Auteur: %s\n", l->num, l->titre, l->auteur);
			} else {
		    		printf("Livre non trouve.\n");
			}
		} else {
			printf("Erreur de format.\n");
			while(getchar() != '\n'); 
		}
		break;
	    case 4:
		printf("Entrez le titre du livre : ");
		fgets(titre, sizeof(titre), stdin);
		titre[strcspn(titre, "\n")] = '\0'; 

		LivreH* lr = recherche_titreH(b, titre);
		if(lr){
			printf("Livre trouve: Numero: %d, Titre: %s, Auteur: %s\n", lr->num, lr->titre, lr->auteur);
		} else {
			printf("Livre non trouve.\n");
		}
		break;

            case 5:
                printf("Entrez le nom de l'auteur : ");
                fgets(auteur, sizeof(auteur), stdin);
                auteur[strcspn(auteur, "\n")] = '\0';

                LivreH* livre = rechercher_auteurH(b, auteur);
                if(livre){
                    printf("Livre trouvé : Num %d, Titre: %s, Auteur: %s\n", 
                           livre->num, livre->titre, livre->auteur);
                } else {
                    printf("Aucun livre trouve pour cet auteur.\n");
                }
		break;
	  case 10:
		printf("Choisisse le type de recherche pour comparer :\n");
		printf("1 - Recherche par auteur\n");
		printf("2 - Recherche par titre\n");
		printf("3 - Recherche par numéro\n");
		printf("4 - Recherche des ouvrages en plusieurs exemplairs\n");
		int choix;
		scanf("%d", &choix);
		getchar();

		char valeur[256] = "";
		if(choix >= 1 && choix <= 3){
			printf("Entre la valeur de recherche : ");
			fgets(valeur, sizeof(valeur), stdin);
			valeur[strcspn(valeur, "\n")] = '\0';
		}
		comparer_recherche(argv[1], atoi(argv[2]), choix, valeur);
		printf("Comparaison termine !\n");
		break;

            default:
                printf("Choix invalide.\n");
             }
    } while(rep != 0);
    liberer_BiblioH(b);  

#else

                          /* *********version Liste Chainees******** */

	if(argc < 3){
		printf("Usage: %s <ficher> <nbr linges>\n", argv[0]);
		return 1;
	}
	Biblio* b = charger_n_entrees(argv[1], atoi(argv[2]));
	if(b == NULL){
		printf("Erreur:Ne peut pas charger la biblio depuis le fichier %s\n", argv[1]);
		return 1;
	}
	enregistrer_biblio(b, "File.txt");

	int rep;
	int num;
	char titre[256];
	char auteur[256];

    do {
        menu();
        printf("Choisisse une option : ");
        if(scanf("%d", &rep) != 1){
            printf("Entre invalide.Entrer un valid nbr.\n");
            while (getchar() != '\n'); 
            continue;
        }
        switch(rep){
        case 0:
            printf("Quitter le programme.\n");
            break;

        case 1:
            printf("Affichage de la biblio :\n");
            afficher_biblio(b);
            printf("Bibliotheque est Affiché.\n");
            break;

        case 2:
            printf("Ajout d'un ouvrage\n");
            printf("Numero : ");
            if(scanf("%d", &num) != 1){
                printf("Erreur : Entrer un nbr valide.\n");
                while (getchar() != '\n');
                continue;
            }
            while(getchar() != '\n'); 
            
            printf("Titre : ");
            fgets(titre, sizeof(titre), stdin);
            titre[strcspn(titre, "\n")] = '\0'; 
            
            printf("Auteur : ");
            fgets(auteur, sizeof(auteur), stdin);
            auteur[strcspn(auteur, "\n")] = '\0';

            if(strlen(titre) == 0 || strlen(auteur) == 0){
                printf("Erreur : not valid titte/auteur\n");
                continue;
            }

            inserer_en_tete(b, num, titre, auteur);
            printf("Ajout réussi !\n");
            printf("l'Ouvrage bien Ajouté.\n");
            break;

        case 3:
            printf("Entrez le numéro du livre : ");
            if(scanf("%d", &num) == 1){
                Livre* l = recherche_num(b, num);
                if(l){
                    afficher_livre(l);
                } else {
                    printf("Livre non trouvé.\n");
                }
            } else {
                printf("Erreur de format.\n");
                while (getchar() != '\n');
            }
            break;

        case 4:
            printf("Entrez le titre du livre  : ");
            while(getchar() != '\n'); 
            fgets(titre, sizeof(titre), stdin);
            titre[strcspn(titre, "\n")] = '\0';
            Livre* l = recherche_titre(b, titre);
            if(l){
            	afficher_livre(l);
            } else {
            	printf("Livre not Trouve.\n");
            }
            break;
	case 5:
	    printf("Entrez le nom de l'auteur : ");
	    while(getchar() != '\n');
	    fgets(auteur, sizeof(auteur), stdin);
	    auteur[strcspn(auteur, "\n")] = '\0'; 

	    Biblio* bib = recherche_auteur(b, auteur); 
	    
	    if(bib && bib->L){
		afficher_biblio(bib);
	    } else {
		printf("Aucun livre trouvé pour cet auteur.\n");
	    }
	    liberer_biblio(bib);
	    break;


        case 6:
            printf("Recherche de tous les livres :\n");
            afficher_biblio(b);
            printf("Biblio Affiché.\n");
            break;

        case 7:
            printf("Suppression d'un ouvrage\n");
            printf("Numero : ");
            if (scanf("%d", &num) != 1) {
                printf("Erreur de format.\n");
                while (getchar() != '\n');
                continue;
            }
            while(getchar() != '\n'); 

            printf("Auteur : ");
            fgets(auteur, sizeof(auteur), stdin);
            auteur[strcspn(auteur, "\n")] = '\0';

            printf("Titre : ");
            fgets(titre, sizeof(titre), stdin);
            titre[strcspn(titre, "\n")] = '\0';

            suppression_ouvrage(b, num, auteur, titre);
            printf("Ouvrage supprimé.\n");
            break;

        case 8:
            printf("Recherche Ourages de PLusieur Exemplaires :\n");
            Biblio* res = recherche_tous_ouvrages(b);
            if(res->L == NULL){
            	printf("Aucun ourage avec plusier exemplaires trouve\n");
            	}
            else{
            	printf("Ourgars trouves avec plusier exemples: \n");
            	afficher_biblio(res);
            	printf("Liste des Exemplaires de Ouvrages Envoyé.\n");
            }
            liberer_biblio(res); 
            break;
	case 9:
		printf("Recherche à comparer :\n");
		printf("1 - Recherche par auteur\n");
		printf("2 - Recherche par titre\n");
		printf("3 - Recherche par numéro\n");
		printf("4 - Recherche des ouvrages en plusieurs exemplaires\n");
		scanf("%d", &rep);
		getchar();

		char v[256] = "";
		if(rep >= 1 && rep <= 3){
			printf("Entrez la valeur de recherche : ");
			fgets(v, sizeof(v), stdin);
			v[strcspn(v, "\n")] = '\0';
		}
		printf("Test de performance en cours...\n");
		comparer_recherche(argv[1], atoi(argv[2]), rep, v);
		printf("Comparaison termine !\n");
		break;



        default:
            printf("Option inconnue,Reessayer.\n");
        }

    } while(rep != 0);

    printf("Merci, et au revoir.\n");
    liberer_biblio(b);
#endif
    return 0;
}

