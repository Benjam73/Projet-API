#include <stdio.h>
#include <stdlib.h>
#include "GestionGraphique.h"
#include <math.h>
#include "dobble.h"
#include <stdbool.h>
#include <unistd.h>

int TEMPS = 30;
int nb_ligne;
int nb_coll = 8;
int mesIcone[1000][1000];

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
	//if((x<PosX+45 && x>PosX-45) && (y<PosY+45 && y>PosY-45)) {
	//	printf("bon clic \n");
	//} else {
	  //	printf("mauvais clic \n");
	//}
	printf("un bouton de souris est presse\n");
	if (!Lance) {
		printf("je lance le compte a rebours\n");
		LanceCompteARebours();
		Lance = true;
	} else {
		printf("j arrete le compte a rebours\n");
		Lance = false;
		ArreteCompteARebours();
	}
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

//Fonction qui prend un fichier.txt avec les lignes et qui renvoie les images correspondantes.
void Remplit_tableau(FILE* f){
	char numero_image;
	int i=0;
	int j;
	fscanf(f,"%c",&numero_image);	
	while(!feof(f)) {
		for(j=0;j!=nb_coll;j++){
			mesIcone[i][j]=numero_image;
			fscanf(f,"%c",&numero_image);
		}
	i++;
	}
	nb_ligne=i;
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
	carte.Abscisse = carte.Rayon*cos(carte.Angle/360.*(2.*M_PI)) + (CentreX-carte.Scale*90./2.);
	carte.Ordonnee = carte.Rayon*sin(carte.Angle/360.*(2.*M_PI)) + (CentreY-carte.Scale*90./2.);

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
		sprintf( Message, " Dobble,Benjamin Enzo   Score %d Temps : %i  ", 100, TEMPS);
	} 
	else{
		sprintf( Message, " Dobble,Benjamin Enzo   Score %d ", 100);
	}
	InitialiseTitre(Message);

	// EFFACE LA FENETRE
	EffaceFenetre();

	// AFFICHE LE TITRE (MESSAGE INITIALISEE PAR LA PROCEDURE InitialiseTexte APPELLEE PLUS HAUT
	AfficheTitre();
	
	// AFFICHE DES ICONES DANS LA CARTE DU HAUT, DISPOSEES REGULIEREMENT EN CERCLE	PositionCarte OuEstLaCarte = CarteDuHaut;
		
	int NumeroDIcone = 0;
	double Rayon = 120.;
	
	PositionCarte OuEstLaCarte = CarteDuHaut;
	Carte carte ; 
		
	for (double Angle = 0.; Angle < 360.; Angle += 360./7.) {
		double Rotation = sin(Angle)*Angle+120.;
		double Taille = 1.;
		double Scale = 1;
		carte = InitialiseCarte(OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Scale);
		AfficheIcone(carte);
		NumeroDIcone++;
		//NumeroDIcone = Lis_ligne(fichier);
	}
	// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU HAUT
	carte.Rayon = 0. ;
	carte.Angle = 0. ;
	carte.Rotation = 0. ;
	carte.Scale = 1.0;
	AfficheIcone(carte);
	//NumeroDIcone = Lis_ligne(fichier);
	// AFFICHE DES ICONES DANS LA CARTE DU BAS, DISPOSEES REGULIEREMENT EN CERCLE
	OuEstLaCarte = CarteDuBas;
	NumeroDIcone = 0 ;
	for (double Angle = 0.; Angle < 360.; Angle += 360./7.) {
		double Rotation = sin(Angle)*Angle+70.;
		double Taille = 1.;
		double Scale = 1;
		carte = InitialiseCarte(OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Scale);
		AfficheIcone(carte);
		//NumeroDIcone = Lis_ligne(fichier);
		NumeroDIcone++;
	}
	// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU BAS
	carte.Rayon = 0. ;
	carte.Angle = 0. ;
	carte.Rotation = 0. ;
	carte.Scale = 1.0;
	AfficheIcone(carte);

	// MET AU PREMIER PLAN LA FENETRE D ARRIERE PLAN QUI VIENT D ETRE MISE A JOUR
	MontreFenetre();
	
}

int main(int argc, char ** argv){
	FILE* fichier = NULL;
	fichier = fopen("../data/pg27.txt","r");
	Remplit_tableau(fichier);
	fclose(fichier);	

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
