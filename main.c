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

	int **tab; //Tout premier tableau de cellules configur� par l'utilisateur qui sera dynamiquement alou�.
	int n; //Nombre de ligne de "tab".
	int m; //Nombre de colonne de "tab.
	int B[9]; //R�gles de naissance selon le voisinage de Moore.
	int S[9]; //R�gles de survie selon le voisinage de Moore.
	int B_N[5]; //R�gles de naissance selon le voisinage de Von Neumann.
	int S_N[5]; //R�gles de survie selon le voisinage de Von Neumann.
	int i; //Variable d�clar�e pour les boucles.
	int ng; //Nombre de g�n�ration entr� par l'utilisateur par la fonction "nb_generation()".
	int rules; //Variable permettant � l'utilisateur de choisirs les r�gles (Conway, Fredkin ou �crire ses propres r�gles...).
	int neighborhood; //Variable indiquant quel type de voisineage l'utilisateur choisi.
	int state; //Variable indiquant si l'utilisateur choisit un automate � deux ou trois �tats.




	printf("                      /////////////////////////////////\n");
	printf("                      //                             //\n");
	printf("                      //        Jeu de la vie        //\n");
	printf("                      //                             //\n");
	printf("                      /////////////////////////////////\n\n\n\n");




    dimensionnement(&n,&m); //Cette fonction demande � l'utlisateur le nombre de ligne et de colonnes afin de d�finir le tableau.
    tab=malloc(n*sizeof(int*)); //On alloue dynamiquement le tableau d'apr�s les valeurs de la fonction "dimensionnement".
	for(i=0;i<n;i++)
	{
		tab[i]=malloc(m*sizeof(int));
	}



	do
	{
    printf("\n[1]Voisinage de Moore     [2]Voisinage de Von Neumann  "); //On veux d�finir quel principe de voisinage utiliser, Moore ou bien Von Neumann.
    scanf("%d",&neighborhood);
	}
	while(neighborhood<1 && neighborhood>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.



	if(neighborhood==1)
	{
		do
		{
			printf("\n[1]Automates a 2 etats     [2]Automates a 3 etats  "); //On veux d�finir si l'on prend en compte les cellules fant�mes ou non.
			scanf("%d",&state);
		}
		while(state<1 && state>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.
		printf("\n\n");
		if(state==1)
		{
			initialisation(tab,n,m); //Cette fonction initialise tout le tableau � 0 puis demande le nombre et les coordonn�es des cellules vivantes afin de les placer dans le tableau.
			affiche(tab,n,m); //Cette fonction affiche le tableau de cellules.
			affiche_fichier(tab,n,m,"jeuDeLaVie.txt"); //De m�me que "affiche" mais cette fois ci dans un fichier .txt
		}
		else
		{
			initialisation_3_etats(tab,n,m);// De m�me mais pour des cellules � trois �tats.
			affiche_fantome(tab,n,m); //Cette fonction affiche le tableau de cellules.
			affiche_fichier_fantome(tab,n,m,"jeuDeLaVie.txt"); //De m�me que "affiche" mais cette fois ci dans un fichier .txt
		}
	}
	else
	{
		printf("\n");
		initialisation(tab,n,m); //Cette fonction initialise tout le tableau � 0 puis demande le nombre et les coordonn�es des cellules vivantes afin de les placer dans le tableau.
		affiche(tab,n,m); //Cette fonction affiche le tableau de cellules.
		affiche_fichier(tab,n,m,"jeuDeLaVie.txt"); //De m�me que "affiche" mais cette fois ci dans un fichier .txt
	}



    ng=nb_generation(); //On d�finie la variable ng d'apr�s la fonction "nb_generation".




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                                     MOORE                                                                                    //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	if(neighborhood==1)//Si l'utlisateur a d�cid� de prendre un voisinage de Moore.
	{
		if(state==1)
		{
			do
			{
				printf("[1]Automate de Conway  [2] Automate de Fredkin  [3]Definir les regles du jeu "); //On propose � l'utilisateur des r�gles de naissances et survies d�j� pr�d�finis, mais aussi de d�finir ses propres r�gles.
				scanf("%d",&rules);
			}
			while(rules<1 && rules>3);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

			switch(rules) //Realise les diff�rente r�gles par rapport au choix pr�c�dent.
			{
				case 1: jeu_conway(tab,n,m,ng);//Voir les d�tails dans "miniProjet.c
						break;
				case 2: jeu_fredkin_M(tab,n,m,ng);//Voir les d�tails dans "miniProjet.c"
						break;
				case 3:
				{
					saisie_B_M(B); //Demande � l'utilisateur ses r�gles de naissance.
					saisie_S_M(S); //Demande � l'utilisateur ses r�gles de survie.
					jeu_M(tab,n,m,B,S,ng);//Voir les d�tails dans "miniProjet.c"
				}
					break;
			}
		}
		else
		{
			do
			{
				printf("[1]Automate B2S  [2]Definir les regles du jeu "); //On propose � l'utilisateur des r�gles de naissances et survies d�j� pr�d�finis, mais aussi de d�finir ses propres r�gles.
				scanf("%d",&rules);
			}
			while(rules<1 && rules>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

			switch(rules) //Realise les diff�rente r�gles par rapport au choix pr�c�dent.
			{
				case 1: jeu_B2S(tab,n,m,ng);//Voir les d�tails dans "miniProjet.c"
						break;
				case 2:
				{
					saisie_B_M(B); //Demande � l'utilisateur ses r�gles de naissance.
					saisie_SF_M(S); //Demande � l'utilisateur ses r�gles de survie.
					jeu_F(tab,n,m,B,S,ng);//Voir les d�tails dans "miniProjet.c"
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






	else //Si l'utlisateur a d�cid� de prendre un voisinage de Von Neumann.
	{
		do
		{
			printf("[1]Automate B13/S13  [2]Definir les regles du jeu "); //On propose � l'utilisateur des r�gles de naissances et survies d�j� pr�d�finis, mais aussi de d�finir ses propres r�gles.
			scanf("%d",&rules);
		}
		while(rules<1 && rules>2);//Repose la question tant que l'utilisateur n'entre pas une valeur juste.

		switch(rules) //Realise les diff�rente r�gles par rapport au choix pr�c�dent.
		{
			case 1: jeu_B13S13_N(tab,n,m,ng);//Voir les d�tails dans "miniProjet.c"
					break;
			case 2:
			{
				saisie_B_N(B_N); //Demande � l'utilisateur ses r�gles de naissance.
				saisie_S_N(S_N); //Demande � l'utilisateur ses r�gles de survie.
				jeu_N(tab,n,m,B_N,S_N,ng);//Voir les d�tails dans "miniProjet.c"
			}
				break;
		}
	}
	for(i=0;i<n;i++) //Lib�re la m�moire alou�e.
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
