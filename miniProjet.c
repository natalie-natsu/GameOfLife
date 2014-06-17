#include <stdio.h>
#include <stdlib.h>
#include "miniProjet.h"




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                               FONCTIONS COMMUNES                                                                             //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






void dimensionnement(int*n, int*m) //Demande les nombre de ligne et de colonne à l'utilisateur pour son plateau de cellule.
{
	printf("Saisir les dimensions de votre tableau\n");
	do
	{
		printf("Lignes:");
		scanf("%d",n);
	}
	while(*n<1);
	do
	{
		printf("Colonnes:");
		scanf("%d",m);
	}
	while(*m<1);
}





void initialisation(int **tab, int n, int m) //Passe tout le tableau à 0, donc de cellules mortes, puis demande à l'utlisateur d'inscire les cellules qu'il veut.
{
	int i;
	int j;
	int nb_cellule=0;
	int c1;
	int c2;

	for(i=0;i<n;i++) //Parcours les lignes du tableau.
	{
		for(j=0;j<m;j++) //Parcours les colonnes de la ligne du tableau.
		{
			tab[i][j]=0; //Affecte la case à 0.
		}
	}
	while (nb_cellule<1)
	{
		printf("Saisir le nombre de cellule: "); //Demande la saisie du nombre de cellule et le répette si celui ci est inférieur à 1.
		scanf("%d",&nb_cellule);
	}
	for(i=0;i<nb_cellule;i++)
	{
		do
		{
			printf("Saisir les coordonees de la cellule %d: ",i+1); //Demande les coordonnées des cellules selon le nombre de cellule.
			scanf("%d%d",&c1,&c2);
		}
		while(c1<1 || c1>n || c2<1 || c2>m || tab[c1-1][c2-1]==1); //Les coordonnées ne peuvent pas être en dehors du plateau et ne peuvent pas être similaires pour plusierus cellules.
		tab[c1-1][c2-1]=1; //Place la cellule dans le tableau en prenant compte du 0 d'un tableau (c'est pourquoi c1-1 et c2-1).
	}
	printf("\n");
}





int nb_generation() //Demande à l'utlisateurs le nombre de génération qu'il souhaite avoir.
{
	int ng;

	do
	{
		printf("Saisir le nombre de generation:");
		scanf("%d",&ng);
	}
	while(ng<1); //Impossible d'avoir moins d'une génération.
	return ng;
}





void affiche(int**tab, int n, int m) //Parcours le tableau pour afficher les cellules ("." pour les mortes et "o" pour les vivantes).
{
	int i;
	int j;

	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(tab[i][j]==0)
				printf(". ");
			else
				printf("o ");
		}
		printf("\n");
	}
	printf("\n");
}





void affiche_fichier(int**tab, int n, int m, char*nom) //Affiche de tableau dans un fichier.txt nommé jeuDeLaVie.txt situé dans le même dossier que le projet.
{
	int i;
	int j;

	FILE* fichier=fopen("jeuDeLaVie.txt","a");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(tab[i][j]==0)
				fputs(". ",fichier);
			else
				fputs("o ",fichier);
		}
		fputs("\n",fichier);
	}
	fputs("\n",fichier);
	fclose(fichier);
}





void duplication(int**tab1, int**tab2, int n, int m) //Duplique le tableau afin de pouvoir modifier cette réplique pour les générations suivantes.
{
	int i;
	int j;

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			tab2[i][j]=tab1[i][j];
		}
	}
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                                      MOORE                                                                                   //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






void saisie_B_M(int B[9]) //L'utlisateur saisit ses règles de naissances pour les cas de 0 à 8 voisins.
{
	int i;
	for(i=0;i<9;i++)
	{
		do
		{
			printf("Une cellule morte ayant %d voisins sera t-elle morte ou vivante la generation    suivante ? (0 OU 1).",i);
			scanf("%d",&B[i]);
		}
		while(B[i]!=0 && B[i]!=1); //Les valeurs du tableau ne peuvent être que 0 ou 1.
	}
	printf("\n");
}





void saisie_S_M(int S[9]) //L'utlisateur saisit ses règles de survies pour les cas de 0 à 8 voisins.
{
	int i;

	for(i=0;i<9;i++)
	{
		do
		{
		printf("Une cellule vivante ayant %d voisins sera t-elle morte ou vivante la generation   suivante ? (0 OU 1).",i);
		scanf("%d",&S[i]);
		}
		while(S[i]!=0 && S[i]!=1); //Les valeurs du tableau ne peuvent être que 0 ou 1.
	}
	printf("\n");
}





int nb_voisins_M(int**tab, int i, int j, int n, int m) //Parcours les cases autour de la cellule afin de déterminer combien elle possède de cellules vivantes voisines.
{
	int nb_voisins=0;

	if (i-1>=0 && j-1>=0 && tab[i-1][j-1]==1) //Vérifie la case d'en haut à gauche tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (i-1>=0 && tab[i-1][j]==1) //Vérifie la case d'en haut tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins ++;
	if (i-1>=0 && j+1<m && tab[i-1][j+1]==1) //Vérifie la case d'en haut à droite tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (j-1>=0 && tab[i][j-1]==1) //Vérifie la case de gauche tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (j+1<m && tab[i][j+1]==1) //Vérifie la case de droite tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (i+1<n && j-1>=0 && tab[i+1][j-1]==1) //Vérifie la case d'en bas à gauche tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (i+1<n && tab[i+1][j]==1) //Vérifie la case d'en bas tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;
	if (i+1<n && j+1<m && tab[i+1][j+1]==1) //Vérifie la case d'en bas à droite tout en prenant soin de vérifier que la cellule ne soit pas sur le bord.
		nb_voisins++;

	return nb_voisins;
}






void generation_suivante_M(int**tab1, int**tab2, int n, int m, int B[9], int S[9]) //Calcule la génération suivante d'après les règles inscrites par l'utlisateur.
{
	int i;
	int j;

	for (i=0;i<n;i++) //Parcours tout le tableau pour chaque cellule.
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_M(tab1,i,j,n,m); //Détermine le nombre de voisins de la cellule.
			if (tab1[i][j]==1) //Si celle ci est vivante.
			{
				tab2[i][j]=S[nb_voisins]; //Applique les règles de survie selon le nombre de voisins calculé précédemment.
			}
			else //Si celle ci est morte.
			{
				tab2[i][j]=B[nb_voisins]; //Applique les règles de naissance selon le nombre de voisins calculé précédemment.
			}
		}
	}
}





void jeu_M(int**tab1, int n, int m, int B[9], int S[9], int ng) //Cette fonction jeu reprend plusieurs petites fonctions et nous affichera tous les tableaux en fonction de leurs générations.
{
	int i;
	int**tab2; //On déclare le tableau deux pour la duplication et la génération suivante.



	tab2=malloc(n*sizeof(int*)); //On définit sa taille dynamiquement correspondant à la taille du tableau initialisé.
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++) //Pour chaque génération le programme applique les fonctions décrites précemment.
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_M(tab1,tab2,n,m,B,S);
		duplication(tab2,tab1,n,m);
		affiche(tab1,n,m);
		affiche_fichier(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++) //On libère la mémoire.
	{
		free(tab2[i]);
	}
	free(tab2);
}





void jeu_fredkin_M(int**tab1, int n, int m,int ng) //De même que la fonction précédente mais avec des règles de naissance et survie préféfinis: celles de Fredkin.
{
	int i;
	int**tab2;



	tab2=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++)
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_F(tab1,tab2,n,m);
		duplication(tab2,tab1,n,m);
		affiche(tab1,n,m);
		affiche_fichier(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++)
	{
		free(tab2[i]);
	}
	free(tab2);
}





void generation_suivante_F(int**tab1, int**tab2, int n, int m)
{
	int i;
	int j;
	int B[9]={0,1,0,1,0,1,0,1,0}; //On remarque les tableaux déjà définis.
	int S[9]={0,1,0,1,0,1,0,1,0};

	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_M(tab1,i,j,n,m);
			if (tab1[i][j]==1)
			{
				tab2[i][j]=S[nb_voisins];
			}
			else
			{
				tab2[i][j]=B[nb_voisins];
			}
		}
	}
}





void jeu_conway(int**tab1, int n, int m,int ng) //De même que la fonction précédente mais avec des règles de naissance et survie préféfinis: celles de Conway.
{
	int i;
	int**tab2;



	tab2=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++)
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_C(tab1,tab2,n,m);
		duplication(tab2,tab1,n,m);
		affiche(tab1,n,m);
		affiche_fichier(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++)
	{
		free(tab2[i]);
	}
	free(tab2);
}






void generation_suivante_C(int**tab1, int**tab2, int n, int m)
{
	int i;
	int j;
	int B[9]={0,0,0,1,0,0,0,0,0}; //On remarque les tableaux déjà définis.
	int S[9]={0,0,1,1,0,0,0,0,0};

	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_M(tab1,i,j,n,m);
			if (tab1[i][j]==1)
			{
				tab2[i][j]=S[nb_voisins];
			}
			else
			{
				tab2[i][j]=B[nb_voisins];
			}
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






void saisie_B_N(int B_N[5]) //L'utlisateur saisit ses règles de naissances pour les cas de 0 à 4 voisins.
{
	int i;
	for(i=0;i<5;i++)
	{
		do
		{
			printf("Une cellule morte ayant %d voisins sera t-elle morte ou vivante la generation    suivante ? (0 OU 1).",i);
			scanf("%d",&B_N[i]);
		}
		while(B_N[i]!=0 && B_N[i]!=1);
	}
	printf("\n");
}





void saisie_S_N(int S_N[5]) //L'utlisateur saisit ses règles de survie pour les cas de 0 à 4 voisins.
{
	int i;

	for(i=0;i<5;i++)
	{
		do
		{
		printf("Une cellule vivante ayant %d voisins sera t-elle morte ou vivante la generation   suivante ? (0 OU 1).",i);
		scanf("%d",&S_N[i]);
		}
		while(S_N[i]!=0 && S_N[i]!=1);
	}
	printf("\n");
}





int nb_voisins_N(int**tab, int i, int j, int n, int m)
{
	int nb_voisins=0;

	if (i-1>=0 && tab[i-1][j]==1)//Regarde le voisin de gauche prenant en compte les bordure du tableau.
		nb_voisins ++;
	if (j-1>=0 && tab[i][j-1]==1)//Regarde le voisin du dessus prenant en compte les bordure du tableau.
		nb_voisins++;
	if (j+1<m && tab[i][j+1]==1)//Regarde le voisin de droite prenant en compte les bordure du tableau.
		nb_voisins++;
	if (i+1<n && tab[i+1][j]==1)//Regarde le voisins du bas prenant en compte les bordure du tableau.
		nb_voisins++;

	return nb_voisins;
}






void generation_suivante_N(int**tab1, int**tab2, int n, int m, int B_N[5], int S_N[5]) //Même principe que pour un voisinage de Moore mais en voisinage de Von Neumann.
{
	int i;
	int j;

	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_N(tab1,i,j,n,m);
			if (tab1[i][j]==1)
			{
				tab2[i][j]=S_N[nb_voisins];
			}
			else
			{
				tab2[i][j]=B_N[nb_voisins];
			}
		}
	}
}





void jeu_N(int**tab1, int n, int m, int B_N[5], int S_N[5], int ng) //Même principe que pour un voisinage de Moore mais en voisinage de Von Neumann.
{
	int i;
	int**tab2;



	tab2=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++)
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_N(tab1,tab2,n,m,B_N,S_N);
		duplication(tab2,tab1,n,m);
		affiche(tab1,n,m);
		affiche_fichier(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++)
	{
		free(tab2[i]);
	}
	free(tab2);
}




void generation_suivante_B13S13(int**tab1, int**tab2, int n, int m) //De même que la fonction generation_suivante_N mais avec des règles de naissance et survie préféfinis.
{
	int i;
	int j;
	int B_N[5]={0,1,0,1,0};
	int S_N[5]={0,1,0,1,0};

	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_N(tab1,i,j,n,m);
			if (tab1[i][j]==1)
			{
				tab2[i][j]=S_N[nb_voisins];
			}
			else
			{
				tab2[i][j]=B_N[nb_voisins];
			}
		}
	}
}





void jeu_B13S13_N(int**tab1, int n, int m, int ng) //Encore une fois, même principe que toutes les fonctions jeu, mais pour les règles B13/S13.
{
	int i;
	int**tab2;



	tab2=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++)
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_B13S13(tab1,tab2,n,m);
		duplication(tab2,tab1,n,m);
		affiche(tab1,n,m);
		affiche_fichier(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++)
	{
		free(tab2[i]);
	}
	free(tab2);
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                              //
//                                                                                                                                                              //
//                                                             AUTOMATES A TROIS ETATS                                                                          //
//                                                                                                                                                              //
//                                                                                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






void initialisation_3_etats(int **tab, int n, int m) //Cette fois ci, la fonction prendra en compte des cellules fantômes.
{
	int i;
	int j;
	int nb_cellule;
	int nb_cellule_f;
	int c1;
	int c2;

	for(i=0;i<n;i++) //Parcours les lignes du tableau.
	{
		for(j=0;j<m;j++) //Parcours les colonnes de la ligne du tableau.
		{
			tab[i][j]=0; //Affecte la case à 0.
		}
	}
	do
	{
		printf("Saisir le nombre de cellule vivante: "); //Demande la saisie du nombre de cellule vivante et le répette si celui ci est inférieur à 1.
		scanf("%d",&nb_cellule);
	}
	while (nb_cellule<1);
	do
	{
		printf("Saisir le nombre de cellule fantome: "); //Demande la saisie du nombre de cellule fantome et le répette si celui ci est inférieur à 1.
		scanf("%d",&nb_cellule_f);
	}
	while (nb_cellule_f<1);
	for(i=0;i<nb_cellule;i++)
	{
		do
		{
			printf("Saisir les coordonees de la cellule vivante %d: ",i+1); //Demande les coordonnées des cellules vivante selon le nombre de cellule.
			scanf("%d%d",&c1,&c2);
		}
		while(c1<1 || c1>n || c2<1 || c2>m || tab[c1-1][c2-1]==1); //Les coordonnées ne peuvent pas être en dehors du plateau et ne peuvent pas être similaires pour plusierus cellules.
		tab[c1-1][c2-1]=1; //Place la cellule dans le tableau en prenant compte du 0 d'un tableau (c'est pourquoi c1-1 et c2-1).
	}
	for(i=0;i<nb_cellule_f;i++)
	{
		do
		{
			printf("Saisir les coordonees de la cellule fantome %d: ",i+1); //Demande les coordonnées des cellules fantômes selon le nombre de cellule.
			scanf("%d%d",&c1,&c2);
		}
		while(c1<1 || c1>n || c2<1 || c2>m || tab[c1-1][c2-1]==1); //Les coordonnées ne peuvent pas être en dehors du plateau et ne peuvent pas être similaires pour plusierus cellules.
		tab[c1-1][c2-1]=2; //Place la cellule dans le tableau en prenant compte du 0 d'un tableau (c'est pourquoi c1-1 et c2-1).
	}
	printf("\n");
}




void affiche_fantome(int**tab, int n, int m) //Parcours le tableau pour afficher les cellules ("." pour les mortes et "o" pour les vivantes et "x" ppour les fantômes).
{
	int i;
	int j;

	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(tab[i][j]==0)
				printf(". ");
			if(tab[i][j]==1)
				printf("o ");
			if(tab[i][j]==2)
				printf("x ");
		}
		printf("\n");
	}
	printf("\n");
}




void affiche_fichier_fantome(int**tab, int n, int m, char*nom) //Affiche de tableau dans un fichier.txt nommé jeuDeLaVie.txt situé dans le même dossier que le projet.
{
	int i;
	int j;

	FILE* fichier=fopen("jeuDeLaVie.txt","a");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(tab[i][j]==0)
				fputs(". ",fichier);
			if(tab[i][j]==1)
				fputs("o ",fichier);
			if(tab[i][j]==2)
				fputs("x ",fichier);
		}
		fputs("\n",fichier);
	}
	fputs("\n",fichier);
	fclose(fichier);
}





void saisie_SF_M(int S[9]) //L'utlisateur saisit ses règles de survies pour les cas de 0 à 8 voisins.
{
	int i;

	for(i=0;i<9;i++)
	{
		do
		{
		printf("Une cellule vivante ayant %d voisins sera t-elle vivante ou fantome la generationsuivante ? (1 OU 2).",i);
		scanf("%d",&S[i]);
		}
		while(S[i]!=1 && S[i]!=2); //Les valeurs du tableau ne peuvent être que 1 ou 2.
	}
	printf("\n");
}





void generation_suivante_M_fantome(int**tab1, int**tab2, int n, int m, int B[9], int S[9]) //Calcule la génération suivante d'après les règles inscrites par l'utlisateur.
{
	int i;
	int j;

	for (i=0;i<n;i++) //Parcours tout le tableau pour chaque cellule.
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_M(tab1,i,j,n,m); //Détermine le nombre de voisins de la cellule.
			switch(tab1[i][j])
			{
				case 1: //Si celle ci est vivante.
					tab2[i][j]=S[nb_voisins]; //Applique les règles de survie selon le nombre de voisins calculé précédemment.
					break;
				case 0: //Si celle ci est morte.
					tab2[i][j]=B[nb_voisins]; //Applique les règles de naissance selon le nombre de voisins calculé précédemment.
					break;
				case 2: //Si celle ci est fantôme.
					tab2[i][j]=0; //Une cellule fantôme sera toujours morte à la génération suivante.
					break;
			}
		}
	}
}





void jeu_F(int**tab1, int n, int m, int B[9], int S[9], int ng) //Cette fonction jeu reprend plusieurs petites fonctions et nous affichera tous les tableaux en fonction de leurs générations.
{
	int i;
	int**tab2; //On déclare le tableau deux pour la duplication et la génération suivante.



	tab2=malloc(n*sizeof(int*)); //On définit sa taille dynamiquement correspondant à la taille du tableau initialisé.
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++) //Pour chaque génération le programme applique les fonctions décrites précemment.
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_M_fantome(tab1,tab2,n,m,B,S);
		duplication(tab2,tab1,n,m);
		affiche_fantome(tab1,n,m);
		affiche_fichier_fantome(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++) //On libère la mémoire.
	{
		free(tab2[i]);
	}
	free(tab2);
}





void generation_suivante_B2S(int**tab1, int**tab2, int n, int m) //Calcule la génération suivante d'après les règles B2/S.
{
	int i;
	int j;
	int B[9]={0,0,1,0,0,0,0,0,0}; //On remarque les tableaux déjà définis.
	int S[9]={2,2,2,2,2,2,2,2,2};

	for (i=0;i<n;i++) //Parcours tout le tableau pour chaque cellule.
	{
		for (j=0;j<m;j++)
		{
			int nb_voisins=nb_voisins_M(tab1,i,j,n,m); //Détermine le nombre de voisins de la cellule.
			switch(tab1[i][j])
			{
				case 1: //Si celle ci est vivante.
					tab2[i][j]=S[nb_voisins]; //Applique les règles de survie selon le nombre de voisins calculé précédemment.
					break;
				case 0: //Si celle ci est morte.
					tab2[i][j]=B[nb_voisins]; //Applique les règles de naissance selon le nombre de voisins calculé précédemment.
					break;
				case 2: //Si celle ci est fantôme.
					tab2[i][j]=0; //Une cellule fantôme sera toujours morte à la génération suivante.
					break;
			}
		}
	}
}





void jeu_B2S(int**tab1, int n, int m, int ng) //Cette fonction jeu reprend plusieurs petites fonctions et nous affichera tous les tableaux en fonction de leurs générations.
{
	int i;
	int**tab2; //On déclare le tableau deux pour la duplication et la génération suivante.



	tab2=malloc(n*sizeof(int*)); //On définit sa taille dynamiquement correspondant à la taille du tableau initialisé.
	for(i=0;i<n;i++)
	{
		tab2[i]=malloc(m*sizeof(int));
	}



	for(i=0;i<ng;i++) //Pour chaque génération le programme applique les fonctions décrites précemment.
	{
		duplication(tab1,tab2,n,m);
		generation_suivante_B2S(tab1,tab2,n,m);
		duplication(tab2,tab1,n,m);
		affiche_fantome(tab1,n,m);
		affiche_fichier_fantome(tab1,n,m,"jeuDeLaVie.txt");
	}



	for(i=0;i<n;i++) //On libère la mémoire.
	{
		free(tab2[i]);
	}
	free(tab2);
}




