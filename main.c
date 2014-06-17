#include <stdio.h>
#include <stdlib.h>
#include "miniProjet.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                     Le Jeu De La Vie - SUPINFO Mini Projet - Nicolas ROUVIERE - 158390                                                       //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{

	int **tab; //Tout premier tableau de cellules configuré par l'utilisateur qui sera dynamiquement aloué.
	int n; //Nombre de ligne de "tab".
	int m; //Nombre de colonne de "tab.
	int B[9]; //Règles de naissance selon le voisinage de Moore.
	int S[9]; //Règles de survie selon le voisinage de Moore.
	int B_N[5]; //Règles de naissance selon le voisinage de Von Neumann.
	int S_N[5]; //Règles de survie selon le voisinage de Von Neumann.
	int i; //Variable déclarée pour les boucles.
	int ng; //Nombre de génération entré par l'utilisateur par la fonction "nb_generation()".
	int rules; //Variable permettant à l'utilisateur de choisirs les règles (Conway, Fredkin ou écrire ses propres règles...).
	int neighborhood; //Variable indiquant quel type de voisineage l'utilisateur choisi.
	int state; //Variable indiquant si l'utilisateur choisit un automate à deux ou trois états.




	printf("                      /////////////////////////////////\n");
	printf("                      //                             //\n");
	printf("                      //        Jeu de la vie        //\n");
	printf("                      //                             //\n");
	printf("                      /////////////////////////////////\n\n\n\n");




    dimensionnement(&n,&m); //Cette fonction demande à l'utlisateur le nombre de ligne et de colonnes afin de définir le tableau.
    tab=malloc(n*sizeof(int*)); //On alloue dynamiquement le tableau d'après les valeurs de la fonction "dimensionnement".
	for(i=0;i<n;i++)
	{
		tab[i]=malloc(m*sizeof(int));
	}



	do
	{
    printf("\n[1]Voisinage de Moore     [2]Voisinage de Von Neumann  "); //On veux définir quel principe de voisinage utiliser, Moore ou bien Von Neumann.
    scanf("%d",&neighborhood);
	}
	while(neighborhood<1 && neighborhood>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.



	if(neighborhood==1)
	{
		do
		{
			printf("\n[1]Automates a 2 etats     [2]Automates a 3 etats  "); //On veux définir si l'on prend en compte les cellules fantômes ou non.
			scanf("%d",&state);
		}
		while(state<1 && state>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.
		printf("\n\n");
		if(state==1)
		{
			initialisation(tab,n,m); //Cette fonction initialise tout le tableau à 0 puis demande le nombre et les coordonnées des cellules vivantes afin de les placer dans le tableau.
			affiche(tab,n,m); //Cette fonction affiche le tableau de cellules.
			affiche_fichier(tab,n,m,"jeuDeLaVie.txt"); //De même que "affiche" mais cette fois ci dans un fichier .txt
		}
		else
		{
			initialisation_3_etats(tab,n,m);// De même mais pour des cellules à trois états.
			affiche_fantome(tab,n,m); //Cette fonction affiche le tableau de cellules.
			affiche_fichier_fantome(tab,n,m,"jeuDeLaVie.txt"); //De même que "affiche" mais cette fois ci dans un fichier .txt
		}
	}
	else
	{
		printf("\n");
		initialisation(tab,n,m); //Cette fonction initialise tout le tableau à 0 puis demande le nombre et les coordonnées des cellules vivantes afin de les placer dans le tableau.
		affiche(tab,n,m); //Cette fonction affiche le tableau de cellules.
		affiche_fichier(tab,n,m,"jeuDeLaVie.txt"); //De même que "affiche" mais cette fois ci dans un fichier .txt
	}



    ng=nb_generation(); //On définie la variable ng d'après la fonction "nb_generation".




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                                     MOORE                                                                                    //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	if(neighborhood==1)//Si l'utlisateur a décidé de prendre un voisinage de Moore.
	{
		if(state==1)
		{
			do
			{
				printf("[1]Automate de Conway  [2] Automate de Fredkin  [3]Definir les regles du jeu "); //On propose à l'utilisateur des règles de naissances et survies déjà prédéfinis, mais aussi de définir ses propres règles.
				scanf("%d",&rules);
			}
			while(rules<1 && rules>3);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

			switch(rules) //Realise les différente règles par rapport au choix précédent.
			{
				case 1: jeu_conway(tab,n,m,ng);//Voir les détails dans "miniProjet.c
						break;
				case 2: jeu_fredkin_M(tab,n,m,ng);//Voir les détails dans "miniProjet.c"
						break;
				case 3:
				{
					saisie_B_M(B); //Demande à l'utilisateur ses règles de naissance.
					saisie_S_M(S); //Demande à l'utilisateur ses règles de survie.
					jeu_M(tab,n,m,B,S,ng);//Voir les détails dans "miniProjet.c"
				}
					break;
			}
		}
		else
		{
			do
			{
				printf("[1]Automate B2S  [2]Definir les regles du jeu "); //On propose à l'utilisateur des règles de naissances et survies déjà prédéfinis, mais aussi de définir ses propres règles.
				scanf("%d",&rules);
			}
			while(rules<1 && rules>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

			switch(rules) //Realise les différente règles par rapport au choix précédent.
			{
				case 1: jeu_B2S(tab,n,m,ng);//Voir les détails dans "miniProjet.c"
						break;
				case 2:
				{
					saisie_B_M(B); //Demande à l'utilisateur ses règles de naissance.
					saisie_SF_M(S); //Demande à l'utilisateur ses règles de survie.
					jeu_F(tab,n,m,B,S,ng);//Voir les détails dans "miniProjet.c"
				}
					break;
			}
		}
	}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                                   VON NEUMANN                                                                                //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	else //Si l'utlisateur a décidé de prendre un voisinage de Von Neumann.
	{
		do
		{
			printf("[1]Automate B13/S13  [2]Definir les regles du jeu "); //On propose à l'utilisateur des règles de naissances et survies déjà prédéfinis, mais aussi de définir ses propres règles.
			scanf("%d",&rules);
		}
		while(rules<1 && rules>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

		switch(rules) //Realise les différente règles par rapport au choix précédent.
		{
			case 1: jeu_B13S13_N(tab,n,m,ng);//Voir les détails dans "miniProjet.c"
					break;
			case 2:
			{
				saisie_B_N(B_N); //Demande à l'utilisateur ses règles de naissance.
				saisie_S_N(S_N); //Demande à l'utilisateur ses règles de survie.
				jeu_N(tab,n,m,B_N,S_N,ng);//Voir les détails dans "miniProjet.c"
			}
				break;
		}
	}
	for(i=0;i<n;i++) //Libère la mémoire alouée.
	{
		free(tab[i]);
	}
	free(tab);



	printf("\n\n\n                      /////////////////////////////////\n");
	printf("                      //                             //\n");
	printf("                      //      THANKS FOR PLAYING     //\n");
	printf("                      //                             //\n");
	printf("                      /////////////////////////////////\n\n\n\n");


    return 0;
}
