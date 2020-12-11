#pragma once
#include <stdbool.h>
#include "liste.h"


// #define VERSION 3.0
// #define SQUELET


#define IMPL_TAB  // si défini, on compile pour une implémentation tableau du répertoire
#define IMPL_LIST // si défini, on compile pour un implémentation Liste Chaînée du répertoire

#ifdef IMPL_LIST
#undef IMPL_TAB
#endif

#define MAX_ENREG 1000  /* nbre max d'enregistrements */
#define MAX_SAISIE 1024 /* longueur max pour la saisie d'une chaîne
ATTENTION, il faut que MAX_SAISIE > MAX_NOM et
MAX_SAISIE > MAX_TEL */

#define OK    1
#define ERROR 0

#define SEPARATEUR ';'
#define LIGNES_PAR_PAGE 5
#define MAX_NOM_FICHIER 80


/**********************************************************************/
/*** Déclarations des types                                         ***/
/***                                                                ***/
/**********************************************************************/



/* Repertoire : structure qui contient :                         */
/* le nombre de contacts                                         */
/* le tableau de contacts,                                       */
/* est_trie : qui vaut VRAI si le tableau est trié et FAUX sinon */
typedef struct rept
{
	int nb_elts;
#ifdef IMPL_TAB
	Enregistrement* tab;
#else
#ifdef IMPL_LIST
	LinkedList* liste;
#endif
#endif
	bool est_trie;
} Repertoire;

// initialise le répertoire passé en paramètre et fait appel à charger() pour charger le fichier de contacts
int init_rep(Repertoire* rep);

// lit les lignes dans le fichier de contacts et les analyse avec la fonction lire_champ_suivant()
int charger(Repertoire* rep, char nom_fichier[]);

// Affiche le menu utilisateur principal
void afficher_menu_principal();

void option_ajouter(Repertoire* rep); // Traitement de l'option ajout d'un contact depuis le menu principal

// Ajout d'un contact dans le répertoire stocké en mémoire
int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr);

// Suppression d'un contact, utilisé notamment par traiter_recherche() afin de supprimer un contact recherché et trouvé
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice);


// Suppression d'un contact pour implémentation avec une liste chaînée
int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem);

void trier(Repertoire* rep); // tri du répertoire en mémoire

int saisie_chaine(unsigned char c[], int max);  // entree d'une chaine de caractères quelconque au clavier, un nom par exemple
int saisie_enreg(Enregistrement* enr); // fait appel à saisie_chaine pour l'entree d'un nouveau contact
void affichage_enreg(Enregistrement enr); // affiche un seul enregistrement sur une ligne
void affichage_enreg_frmt(Enregistrement enr); // affiche un seul enregistrement avec des largeurs de colonnes fixes
void affichage_repertoire(Repertoire* rep); // affichage de tout le répertoire en paginant les lignes à la façon de la commande 'MORE'
bool est_sup(Enregistrement enr1, Enregistrement enr2); // test si un contact se trouve après dans l'ordre alphabétique par rapport à un autre contact
void trier(Repertoire* rep);  // tri des contacts du répertoire en mémoire

void compact(char* s); // suppression de tous les caratères non numériques dans une chaine (0..9) afin de faciliter la recherche par no de tel par ex.
int lire_champ_suivant(char* ligne, int* idx, char* champ, int taille_champ, char separateur); // analyse d'une ligne lue dans le fichier et stockée dans le buffer 'ligne' 

void option_rechercher(Repertoire* rep); //traitement de l'option de recherche du menu principal
void afficher_menu_recherche();  //affiche un menu afin de proposer une recherche par nom ou par no tel ou, d'abandonner la recherche
int rechercher_nom(Repertoire* rep, char nom[], int ind); // recherche l'existance d'un contact et renvoie l'indice de sa position si trouvé ou -1 sinon
int rechercher_tel(Repertoire* rep, char tel[], int ind); // recherche l'existance d'un contact par no tel et renvoie l'indice de sa position si trouvé ou -1 sinon
bool traiter_recherche(Repertoire* rep, int pos); // menu qui propose de supprimer le contact trouvé, de poursuivre la recherche ou de s'arreter 

int saisir_chemin(char* message, char* buffer); // demande de saisie au clavier d'un chemin pour un fichier de sauvegarde, fait appel à saisie_chaine()
int sauvegarder(Repertoire* rep, char nom_fichier[]); // sauvegarde tout le répertoire en mémoire vers un fichier en remplaçant l'ancien fichier



