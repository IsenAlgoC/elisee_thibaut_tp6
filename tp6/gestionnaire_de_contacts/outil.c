#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom :  THIBAUT                       Prénom :  ELisée                */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx = rep->nb_elts; //on se situe dans le tableau
	if (rep->nb_elts < MAX_ENREG)
	{

		rep->tab[idx] = enr;//on place l'enregistrement dans le tableau d'enregistrements du repertoire
		affichage_enreg(enr);//on dit à l'utilisateur qu'il a ajouté qqn

		rep->nb_elts++;
		modif = true;
		rep->est_trie = false;//l'élement étant ajouté à la fin, le tableau n'est plus trié
	}
	else {
		return(ERROR);
	}


#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {//si il y a des éléments
		for (int i = 0; i < rep->nb_elts; i++) {
			if (est_sup(GetElementAt(rep->liste, i)->pers, enr) == false) {//si l'élement i de la liste n'est pas alphabétiquement avant celui qu'on ajoute
				InsertElementAt(rep->liste, i, enr);//on l'insère au rang i
			}
		}
	}


#endif

#endif


	return(OK);
} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */

		for (int i = indice; i < rep->nb_elts; i++) {//on décale tous les éléments après d'un rang en avant
			rep->tab[i] = rep->tab[i + 1];//ce qui va supprimer l'élement voulu, sans créer de blanc
		}



		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf_s("\n\nContact :  %s, %s                 %s\n", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */

  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	printf_s("| %s %s| %s %s| %s\n",enr.nom,"  ",enr.prenom,"  ",enr.tel);

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{	//si enr1>enr2, on renvoie true
	// code à compléter ici

	/*char NOM1 = toupper(enr1.nom);
	char PRENOM1 = toupper(enr1.prenom);
	char NOM2 = toupper(enr2.nom);
	char PRENOM2 = toupper(enr2.prenom);*/

	if (_strcmpi(enr1.nom, enr2.nom) > 0) {//si le nom de enr1 est avant alphabétiquement le nom de enr2
		return true;
	}
	else if (_strcmpi(enr1.nom, enr2.nom) == 0) {//si les noms sont identiques, on compare les prénoms de la meme facon
		if (_strcmpi(enr1.prenom, enr2.prenom) > 0) {
			return true;
		}
	}
	
	return false;

}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	
	if (rep->est_trie == false) {//on ne trie que si le rep n'est pas trié
		Enregistrement e1;//c'est une variable qui permettra d'intervetir deux à deux des élements
		for (int j = 0; j < rep->nb_elts - 1; j++) {//on utilise ici un tri à bulles
			for (int i = 0; i < rep->nb_elts - 1; i++) {
				if (est_sup(rep->tab[i], rep->tab[1 + i])) {
					e1 = rep->tab[i];
					rep->tab[i] = rep->tab[1 + i];
					rep->tab[1 + i] = e1;
				}

			}
		}
	}
	rep->est_trie = true;

	//for (int i = 0; i < rep->nb_elts; i++) {//cette partie affiche
	//	printf_s("\n\n %s, %s                 %s\n",rep->tab[i].nom, rep->tab[i].prenom, rep->tab[i].tel);
	//}


#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;

	ind_fin = rep->nb_elts - 1; // indice de fin à ne pas dépasser
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	while ((i <= ind_fin) && (!trouve))
	{

		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);



		if (strcmp(tmp_nom, tmp_nom2) == 0)
			trouve = true;
		else
			i++;
	}

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	if (s == NULL) {//si le mot est vide on ne s'embete pas
		return;
	}

	char* pDest = s;//on assigne à notre variable locale la valeur de l'argument

	while (*s) {//on le fait tant qu'il y a des caractères
		if (*s >= 48 && *s <= 57) //si on est compris entre le 0 et le 9 d'ascii
			*pDest++ = *s; //on recopie le caractère
		s++;//puis on passe au caractère suivant
	}
	*pDest = '\0';//on termine notre mot
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	errno_t err;
	err = fopen_s(&fic_rep, "rep.txt", "w+");
	if (err == 0 && fic_rep!=NULL)//pour ouvrir le fichier .txt en sécurité, sans message d'erreur
	{
		for (int i = 0; i < rep->nb_elts; i++) {//on recopie les infos des gens au fur et à mesure
			fprintf(fic_rep, "%s;%s;%s\n", rep->tab[i].nom, rep->tab[i].prenom, rep->tab[i].tel);
		}
		int numclosed = _fcloseall();//on ferme le document texte
	}
	else
	{
		printf("The file 'data2' was not opened\n");
	}
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
						
														
														
														
														
														
														
	// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */