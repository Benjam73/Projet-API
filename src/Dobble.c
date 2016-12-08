#include <stdio.h>
#include <stdlib.h>
#include "GestionGraphique.h"
#include <math.h>
#include <time.h>
#include "dobble.h"
#include <stdbool.h>
#include <unistd.h>

int TEMPS = 30;
int nb_ligne;
int nb_coll = 8;
int ligne_courante;
int icone_commun;
int mesIcone[1000][1000];
int Icone_commun;
int X_iconeCommun,Y_iconeCommun;
int Score = 100;

int TempsEcoule(){
	return TEMPS <= 0 ;
}

void LaSourisBouge( int x, int y)
{
	printf("la souris bouge, ses coordonnees sont: %d %d\r", x, y);
	fflush(stdout);
}

// UN CLICK: LE COMPTE A REBOURS EST LANCE
// UN DEUXIEME CLICK: LE COMPTE A REBOURS EST ARRETE
void UnBoutonEstClique(int x, int y)
{
	// VARIABLE PERMETTANT DE NE PAS RELANCER LE COMPTE-A-REBOURS AVANT DE L'AVOIR ARRETE
	static bool Lance = false;
	
	if (!Lance) {
		printf("je lance le compte a rebours\n");
		LanceCompteARebours();
		Lance = true;
	}
	
	printf(" coordonne X : %d ; coordonne Y : %d \n",X_iconeCommun,Y_iconeCommun);
	if((x<X_iconeCommun+45 && x>X_iconeCommun-45) && (y<Y_iconeCommun + 45 && y>Y_iconeCommun - 45)) {
		printf("bon clic \n");
		ligne_courante_random();
		BonneReponse();
	} else {
	 	printf("mauvais clic \n");
		MauvaiseReponse();
	}
	AfficheSceneComplete();
}


// PROCEDURE APPELLE CHAQUE SECONDE A PARTIR DU MOMENT OU LE COMPTE A REBOURS EST LANCE
void CompteARebours()
{
	 
	if(TEMPS > 0) {
		TEMPS=TEMPS -1 ;
	} else {
		ArreteCompteARebours(); 
	}
}

void ChangeCompteARebours(int n){
	TEMPS = TEMPS+n;
}

void AugmenterScore() {
	Score=Score + 10;
}

//Fonction qui prend un fichier.txt avec les lignes et qui renvoie les images correspondantes.
void Remplit_tableau(FILE* f){
	int numero_image;
	int i=0;
	int j;
	while(!feof(f)) {
		for(j=0;j!=nb_coll;j++){	
			fscanf(f,"%d",&numero_image);
			mesIcone[i][j]=numero_image;
		}	
		i++;
	}
	nb_ligne=i-1;
}

void incone_commun(){
	int i,j;	
	for (i=0;i!=nb_coll;i++) {
		for(j=0;j!=nb_coll;j++){
			if(mesIcone[ligne_courante][i] == mesIcone[ligne_courante+1][j]){
	  			Icone_commun=mesIcone[ligne_courante][i];
				
			}
		}
	}
}

Carte InitialiseCarte (PositionCarte PosCarte, int NumeroDIcone, double Rayon, double Angle, double Rotation, double Scale){
	Carte carte ;
	carte.PosCarte = PosCarte;
	carte.NumeroDIcone = NumeroDIcone;
	carte.Rayon = Rayon;
	carte.Angle = Angle;
	carte.Rotation = Rotation;
	carte.Scale = Scale;
	
	int CentreX, CentreY;
	if (carte.PosCarte == CarteDuHaut) {
		CentreX = 300;
		CentreY = 200;
	} else {
		CentreX = 300;
		CentreY = 520;
	}

	// ATTENTION AUX CONVERSIONS ENTRE FLOTTANTS DOUBLE PRECISION ET ENTIERS
	carte.Abscisse = carte.Rayon*cos(carte.Angle/360.*(2.*M_PI)) + CentreX;
	carte.Ordonnee = carte.Rayon*sin(carte.Angle/360.*(2.*M_PI)) + CentreY;

	return carte ;
}

// MISE A JOUR DE L'AFFICHAGE
// CETTE MISE A JOUR EST D'ABORD CALCULEE DANS UNE IMAGE D'ARRIERE PLAN
// AVANT D'ETRE ENSUITE PLACEE AU PREMIER PLAN DANS LE DERNIER APPEL (CELUI DE LA PROCEDURE MontreFenetre)
// CE PROCEDE CLASSIQUE EN GRAPHIQUE ASSURE QUE LES CHANGEMENTS APPARAISSENT INSTANTANEMENT A L OBSERVATEUR
// QUELLE QUE SOIT LA DUREE PRISE POUR CALCULER LA NOUVELLE IMAGE EN ARRIERE PLAN
void AfficheSceneComplete()
{
	char Message[100];

	// INITIALISE LE TITRE QUI SERA AFFICHE. UTILE POUR AFFICHER LE SCORE
	
	if (!TempsEcoule()){
		sprintf( Message, " Dobble    Score %d Temps : %i  ", Score, TEMPS);
	} 
	else{
		sprintf( Message, " Dobble    Score %d ", Score);
	}
	InitialiseTitre(Message);

	// EFFACE LA FENETRE
	EffaceFenetre();

	// AFFICHE LE TITRE (MESSAGE INITIALISEE PAR LA PROCEDURE InitialiseTexte APPELLEE PLUS HAUT
	AfficheTitre();
	
	// AFFICHE DES ICONES DANS LA CARTE DU HAUT, DISPOSEES REGULIEREMENT EN CERCLE	PositionCarte OuEstLaCarte = CarteDuHaut;
		
	int NumeroDIcone = mesIcone[ligne_courante][0];;
	double Rayon = 120.;
	double Angle = 0.;
	PositionCarte OuEstLaCarte = CarteDuHaut;
	Carte carte ; 
	int i;
	double Rotation = sin(Angle)*Angle+120.;
	double Taille = 0.8;
	incone_commun();	
	 for(i=1;i<nb_coll;i++){	
		Rotation = sin(Angle)*Angle+120.;
		carte = InitialiseCarte(OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
		AfficheIcone(carte);
		NumeroDIcone =mesIcone[ligne_courante][i];
		Angle += 360./7.; 
	}
	// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU HAUT
	carte.Rayon = 0. ;
	carte.Angle = 0. ;
	carte.Rotation = 0. ;
	carte.Scale = 0.8;
	carte.NumeroDIcone = NumeroDIcone;
	AfficheIcone(carte);
	NumeroDIcone =mesIcone[ligne_courante+1][0];
	printf("%d \r" ,NumeroDIcone);
	// AFFICHE DES ICONES DANS LA CARTE DU BAS, DISPOSEES REGULIEREMENT EN CERCLE
	OuEstLaCarte = CarteDuBas;
	for(i=1;i<nb_coll;i++){	
		Rotation = sin(Angle)*Angle+120.;
		carte = InitialiseCarte(OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
		AfficheIcone(carte);
		if(NumeroDIcone==Icone_commun) {
			X_iconeCommun = carte.Abscisse;
			Y_iconeCommun = carte.Ordonnee;
		}
		NumeroDIcone =mesIcone[ligne_courante+1][i];
		Angle += 360./7.; 
	}
	// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU BAS
	carte.Rayon = 0. ;
	carte.Angle = 0. ;
	carte.Rotation = 0. ;
	carte.Scale = 0.8;
	carte.NumeroDIcone = NumeroDIcone;
	AfficheIcone(carte);
	if(NumeroDIcone==Icone_commun) {
		X_iconeCommun = 300;
		Y_iconeCommun = 520;
	}
	// MET AU PREMIER PLAN LA FENETRE D ARRIERE PLAN QUI VIENT D ETRE MISE A JOUR
	MontreFenetre();
	
}

void ligne_courante_random(){
	ligne_courante=rand()%nb_ligne;

}

int main(int argc, char ** argv){
	FILE* fichier = NULL;
	fichier = fopen("../data/pg27.txt","r");
	Remplit_tableau(fichier);
	fclose(fichier);	
	srand(time(NULL));	
	ligne_courante_random();
	if (InitialiseGraphique() != 1) {
		printf("Echec de l initialisation de la librairie graphique\n");
		return -1;
	}

	if (ChargeImage("../data/Matrice8x10_Icones90x90.png") != 1) {
		printf("echec du chargement de l'image\n");
		return -1;
	}

	LisEtDispatchEvenement();

	ArreteGraphique();

	return 1;
}
