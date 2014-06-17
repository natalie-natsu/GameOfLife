# ifndef miniProjet_H_INCLUDED
# define miniProjet_H_INCLUDED

void dimensionnement(int*n, int*m);
void initialisation(int**tab, int n, int m);
int nb_generation();
void affiche(int**tab, int n, int m);
void affiche_fichier(int**tab, int n, int m, char*nom);
void saisie_B_M(int B[9]);
void saisie_S_M(int S[9]);
int nb_voisins_M(int**tab, int i, int j, int n, int m);
void duplication(int**tab1, int**tab2, int n, int m);
void generation_suivante_M(int**tab1, int**tab2, int n, int m, int B[9], int S[9]);
void jeu_M(int**tab1, int n, int m, int B[9], int S[9], int ng);
void jeu_conway(int**tab1, int n, int m,int ng);
void jeu_fredkin_M(int**tab1, int n, int m,int ng);
void generation_suivante_C(int**tab1, int**tab2, int n, int m);
void generation_suivante_F(int**tab1, int**tab2, int n, int m);
void saisie_B_N(int B_N[5]);
void saisie_S_N(int S_N[5]);
int nb_voisins_N(int**tab, int i, int j, int n, int m);
void generation_suivante_N(int**tab1, int**tab2, int n, int m, int B_N[5], int S_N[5]);
void jeu_N(int**tab1, int n, int m, int B_N[5], int S_N[5], int ng);
void generation_suivante_B13S13(int**tab1, int**tab2, int n, int m);
void jeu_B13S13_N(int**tab1, int n, int m, int ng);
void initialisation_3_etats(int **tab, int n, int m);
void affiche_fantome(int**tab, int n, int m);
void affiche_fichier_fantome(int**tab, int n, int m, char*nom);
void generation_suivante_M_fantome(int**tab1, int**tab2, int n, int m, int B[9], int S[9]);
void jeu_F(int**tab1, int n, int m, int B[9], int S[9], int ng);
void saisie_SF_M(int S[9]);
void generation_suivante_B2S(int**tab1, int**tab2, int n, int m);
void jeu_B2S(int**tab1, int n, int m, int ng);

# endif
