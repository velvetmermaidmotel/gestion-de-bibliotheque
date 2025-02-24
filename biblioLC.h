#ifndef biblioLC_H
#define biblioLC_H
#include <stdio.h>

typedef struct livre {
	 int num ;
	 char * titre ;
	 char * auteur ;
	 struct livre * suiv ;
	 } Livre ;

 typedef struct { 
	 Livre * L ; 
	 } Biblio ;
//functions decleartions	 
	Livre* creer_LivreH(int num,char* titre,char* auteur);
	void liberer_livre(Livre* l);
	Biblio* creer_biblio();
	void liberer_biblio(Biblio* b);
	void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);
	void afficher_livre(Livre* l);
	void afficher_biblio(Biblio* b);
	Livre * recherche_num(Biblio *b, int num);
	Livre * recherche_titre(Biblio* b, char* t);
	void suppression_ouvrage(Biblio *b, int num, char* auteur, char* titre);
	void fusion(Biblio* b1, Biblio* b2);
	Livre* recherche(Biblio* b);
	Biblio* recherche_tous_ouvrages(Biblio *b);
	Biblio* recherche_auteur(Biblio *b, char *auteur);
	

#endif
