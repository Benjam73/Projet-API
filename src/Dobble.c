#include <stdio.h>
#include <stdlib.h>
#include "GestionGraphique.h"
#include <math.h>
#include "dobble.h"
#include <stdbool.h>
<<<<<<< HEAD
#include <unistd.h>

int TEMPS = 30;
=======
>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e


void LaSourisBouge( int x, int y)
{
	printf("la souris bouge, ses coordonnees sont: %d %d\r", x, y);
	fflush(stdout);
}

// UN CLICK: LE COMPTE A REBOURS EST LANCE
// UN DEUXIEME CLICK: LE COMPTE A REBOURS EST ARRETE
void UnBoutonEstClique()
{
	// VARIABLE PERMETTANT DE NE PAS RELANCER LE COMPTE-A-REBOURS AVANT DE L'AVOIR ARRETE
	static bool Lance = false;

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
<<<<<<< HEAD
	if(TEMPS > 0) {
		printf("\n click \n");
		TEMPS=TEMPS -1 ;
		AfficheSceneComplete();
	} else {
		ArreteCompteARebours(); 
	}

	
=======
	printf("\nclick\n");
>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e
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
<<<<<<< HEAD
	if(TEMPS != 0) {
		sprintf( Message, "Dobble projet   Score %d ,   Temps : %i  ", 100, TEMPS);
	} else {
		sprintf( Message, "Dobble projet   Score %d ,   Temps ecoule  ", 100);
	}
	InitialiseTitre(Message);
=======
	sprintf( Message, "Dobble, hein voila    Score %d", 100);
	InitialiseTitre(Message);

>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e
// EFFACE LA FENETRE
	EffaceFenetre();

// AFFICHE LE TITRE (MESSAGE INITIALISEE PAR LA PROCEDURE InitialiseTexte APPELLEE PLUS HAUT
	AfficheTitre();
<<<<<<< HEAD
	
=======

>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e
// AFFICHE DES ICONES DANS LA CARTE DU HAUT, DISPOSEES REGULIEREMENT EN CERCLE
	PositionCarte OuEstLaCarte = CarteDuHaut;
	int NumeroDIcone = 1;
	double Rayon = 120.;

	for (double Angle = 0.; Angle < 360.; Angle += 360./7.) {
		double Rotation = sin(Angle)*Angle+120.;
<<<<<<< HEAD
		double Taille = 0.8;
		AfficheIcone( OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
	}
// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU HAUT
	AfficheIcone( OuEstLaCarte, NumeroDIcone, 0., 0., 0., 0.8);
=======
		double Taille = 1.;
		AfficheIcone( OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
	}
// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU HAUT
	AfficheIcone( OuEstLaCarte, NumeroDIcone, 0., 0., 0., 1.0);
>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e

// AFFICHE DES ICONES DANS LA CARTE DU BAS, DISPOSEES REGULIEREMENT EN CERCLE
	OuEstLaCarte = CarteDuBas;
	for (double Angle = 0.; Angle < 360.; Angle += 360./7.) {
		double Rotation = sin(Angle)*Angle+70.;
<<<<<<< HEAD
		double Taille = 0.8;
		AfficheIcone( OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
	}
// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU BAS
	AfficheIcone( OuEstLaCarte, NumeroDIcone, 0., 0., 0., 0.8);
=======
		double Taille = 1.;
		AfficheIcone( OuEstLaCarte, NumeroDIcone, Rayon, Angle, Rotation, Taille);
	}
// AFFICHE UNE ICONE AU CENTRE DE LA CARTE DU BAS
	AfficheIcone( OuEstLaCarte, NumeroDIcone, 0., 0., 0., 1.0);
>>>>>>> 72dffba199016cc5347b788a2f3e2653e29cca8e

// MET AU PREMIER PLAN LA FENETRE D ARRIERE PLAN QUI VIENT D ETRE MISE A JOUR
	MontreFenetre();
}

int main(int argc, char ** argv)
{
	if (InitialiseGraphique() != 1) {
		printf("Echec de l initialisation de la librairie graphique\n");
		return -1;
	}

	if (ChargeImage("../data/Matrice3x3_Icones90x90.png") != 1) {
		printf("echec du chargement de l'image\n");
		return -1;
	}

	LisEtDispatchEvenement();

	ArreteGraphique();

	return 1;
}
