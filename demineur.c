#include <stdio.h> /* librairie standard */
#include <stdlib.h> /* librairie stdlib, pour la fonction srand */
#include <time.h> /* librairie time, pour les nombre random */
#define NB_LIGNE 10 /*nombre de ligne de la matrice*/
#define NB_COLONNE 10 /*nombre de colonne de la matrice*/
#define NB_BOMBES 10/*nombre de bombes*/
#define TRUE 1
#define FALSE 0

 

 void facile(int A[NB_LIGNE][NB_COLONNE]){ /*Déclare une matrice nulle puis la remplie aléatoirement de 10 -1*/
int i,j;
srand(time(NULL)); /*Initialise la fonction srand sur le temps actuel*/
    for(int ligne=0; ligne < NB_LIGNE; ligne++){/*A =np.zeros([10,10])*/
        for(int col=0; col < NB_COLONNE; col++){
            A[ligne][col] = 0;
        }
    }
for(int bombe = 0; bombe < NB_BOMBES; bombe++){
i = (rand()%(9-0)+1)+0; /*(rand()%(MAX-MIN)+1)+MIN retourne un nombre aléatoire entre 0 et 9*/
j = (rand()%(9-0)+1)+0;
while(A[i][j] == -1){
i = (rand()%(9-0)+1)+0;
j = (rand()%(9-0)+1)+0; 
}
A[i][j] = -1;
}
return ; 
 }

void initialisationA(int A[NB_LIGNE][NB_COLONNE]){ /*"i" correspond aux lignes (horizontal) et "j" correspond aux colonnes (vertical)*/
facile(A);
for(int i=0; i< 10; i++){
for(int j=0; j< 10; j++){
if(A[i][j] == -1){
if(i>0 && j>0){
if(A[i-1][j-1] != -1) A[i-1][j-1] += 1;
}
if(i>0){
if(A[i-1][j] != -1) A[i-1][j] += 1;
}
if(j>0){
if(A[i][j-1] != -1) A[i][j-1] += 1;
}
if(i<9 && j<9){
if(A[i+1][j+1] != -1) A[i+1][j+1] +=1;
}
if(i<9){
if(A[i+1][j] != -1) A[i+1][j] += 1;
}
if(j<9){
if(A[i][j+1] != -1) A[i][j+1] += 1;
}
if(i<9 && j>0){
if(A[i+1][j-1] != -1) A[i+1][j-1] += 1;
}
if(i>0 && j<9){
if(A[i-1][j+1] != -1) A[i-1][j+1] += 1;
}
}
}
}
return ;
}

void initialisationB(char B[NB_LIGNE][NB_COLONNE]){ /*initialisation de la variable globale B*/
for(int i=0; i< NB_LIGNE; i++){
for(int j=0; j< NB_COLONNE; j++){
B[i][j] = '~';
}
}
return ;
}

void decouvrir(int i, int j, int A[NB_LIGNE][NB_COLONNE], char B[NB_LIGNE][NB_COLONNE]){ /*Découvre une case à l'emplacement (i,j)*/
if(A[i][j] != 0 && A[i][j] != -1)
B[i][j] = 'O';/*Le '0' a une valeur ASCII de 48. Nous devons donc ajouter sa valeur à la valeur entière pour le convertir en le caractère désiré*/ 
else if(A[i][j] == 0 && B[i][j] != 'O'){
B[i][j] = 'O';
if(i>0) decouvrir(i-1,j,A,B);
if(j>0) decouvrir(i,j-1,A,B);
if(i<9) decouvrir(i+1,j,A,B);
if(j<9) decouvrir(i,j+1,A,B);
}
    else {}
return ;
}

int placerMarqueur(int i, int j, int nbMarqueursBombes, char B[NB_LIGNE][NB_COLONNE]){
if(B[i][j] != 'O' && B[i][j] != 'X'){
B[i][j] = 'X';
nbMarqueursBombes -= 1;
}
return nbMarqueursBombes;
}

int gagne(int nbMarqueursBombes, char B[NB_LIGNE][NB_COLONNE]){
int somme = 0;
if(nbMarqueursBombes == 0){
for(int i=0; i< NB_LIGNE; i++){
for(int j=0; j< NB_COLONNE; j++){
if(B[i][j] != 'X') somme += 1;
} 
}
}
if(somme == 90) return TRUE;
else 
return FALSE;
}
void afficheB(char mat[NB_LIGNE][NB_COLONNE]){
printf("   ");
for(int i=0;i<NB_COLONNE;i++){
printf(" %d " ,i);
}
printf("\n");
    for(int ligne = 0; ligne < NB_LIGNE; ligne++){
        for(int col = 0; col < NB_COLONNE; col++){
            if(col == 0) printf("%d |",ligne);
            printf(" %c ",mat[ligne][col]);
            if(col == 9) printf("|\n"); /*passage à la ligne*/
        }
    }
    return ;
}

void Jeu(int A[NB_LIGNE][NB_COLONNE], char B[NB_LIGNE][NB_COLONNE]){/*Jeu entier*/
int nbMarqueursBombes = 10;
int choix,i,j;
    char *res = "";
while(gagne(nbMarqueursBombes, B) == FALSE){
afficheB(B);
printf("Il reste %d bombes à placer.\n", nbMarqueursBombes);
printf("Voulez-vous :\n 1.Découvrir une case\n 2.Placer un Marqueur de Bombe\n");
scanf("%d", &choix);

        printf("Choisissez vos coordonnées : \ni= ");
        scanf("%d",&i);
        printf("j= ");
        scanf("%d",&j);
if(choix == 1){
decouvrir(i,j,A,B);
if(A[i][j] == -1){
                printf("Vous avez perdu.");
                return ;
            }
}
if(choix == 2)
nbMarqueursBombes = placerMarqueur(i,j,nbMarqueursBombes,B);
}
printf("Vous avez gagné !");
    return ;
}



int main(){ /* fonction principale */
int A[NB_LIGNE][NB_COLONNE];
char B[NB_LIGNE][NB_COLONNE];
int l;
int c;
initialisationA(A);
initialisationB(B);
Jeu(A,B);
return 0;
}