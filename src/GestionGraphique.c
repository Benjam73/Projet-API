#include "GestionGraphique.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

#include "dobble.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static SDL_Texture *textureImage = NULL;
static SDL_Texture *textureTexte = NULL;
static int tw, th;

static TTF_Font *police = NULL;
SDL_Surface *image = NULL;
static bool DemandeArretCompteARebours = false;
static bool CompteAReboursLance = false;

// PROCEDURE LISANT UNE IMAGE STOCKEE SUR LE DISQUE
// CETTE PROCEDURE EST UTILISEE DANS LE PROGRAMME PRINCIPALE Dobble.c POUR LIRE L IMAGE CONTENANT TOUTES LES ICONES
// L IMAGE EST TRANSFORMEE EN UNE STRUCTURE DE DONNEE ACCESSIBLE VIA LA VARIABLE textureImage
// CETTE VARIABLE textureImage EST DEFINIE GLOBALEMENT AU PROGRAMME ET SERT DANS LA PROCEDURE
// AFFICHANT UNE ICONE DEFINIE PLUS BAS (procedure AfficheIcone)
int ChargeImage(const char *NomDuFichier)
{
	
	
	printf("chargement de l image %s\n", NomDuFichier);
	image = IMG_Load(NomDuFichier);
	if (image == NULL) {
		printf("Echec du chargement de l'image %s\n", NomDuFichier);
		return -1;
	}
	textureImage = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface( image);

	return 1;
}

// DESSINE DANS L IMAGE textureTexte UN MESSAGE AVEC UNE POLICE DE CARACTERE
int InitialiseTitre(const char *Message)
{
	SDL_Surface *texte = NULL;

	if (textureTexte != NULL) {
		SDL_DestroyTexture(textureTexte);
	}
	SDL_Color couleurNoire={0,0,0}, couleurBlanche={255,255,255};

	texte = TTF_RenderText_Shaded(police, Message, couleurNoire, couleurBlanche);
	tw = texte->w;
	th = texte->h;
	if (texte == NULL) {
		printf("echec de la creation de la surface texte\n");
		return -1;
	}
	textureTexte = SDL_CreateTextureFromSurface(renderer, texte);
	if (textureTexte == NULL) {
		printf("echec de la creation de la texture texte\n");
		return -1;
	}
	SDL_FreeSurface( texte);

	return 1;
}

// PROCEDURE QUI EST APPELLEE REGULIEREMENT PAR LA LIBRAIRIE SDL, ET QUI SERT A PILOTER LE COMPTE A REBOURS DANS CETTE APPLICATION
Uint32 MonTimer(Uint32 IntervalleDAvant, void *Param)
{
	// APPEL DE LA PROCEDURE CompteARebours SPECIFIEE DANS Dobble.h ET IMPLEMENTEE DANS Dobble.c
	CompteARebours();

	// SI L'ARRET DU COMPTE A REBOURS A ETE DEMANDE, ALORS RETOURNE UNE VALEUR DE 0 SINON RETOURNE LA MEME VALEUR IntervalleAvant
	if (DemandeArretCompteARebours) {
		CompteAReboursLance = false;
		DemandeArretCompteARebours = false;
		return(0);
	} else {
		return (IntervalleDAvant);
	}
}

// INITIALISATION DE L'APPEL REGULIER DE LA FONCTION MonTimer DEFINIE CI-DESSUS
void LanceCompteARebours()
{
	if (CompteAReboursLance) {
		printf("vous ne pouvez pas lancer un compte-a-rebours sans avoir arrete celui en cours\n");
	}
	CompteAReboursLance = true;
	Uint32 UneSecondeEnMilliseconde = 1000;
	SDL_TimerID MonTimerId = SDL_AddTimer( UneSecondeEnMilliseconde, MonTimer, NULL);
}

//  AU PROCHAIN APPEL DE LA FONCTION MonTimer, LE TIMER SERA STOPPE
void ArreteCompteARebours()
{
	DemandeArretCompteARebours = true;
}

// FONCTION INITIALISANT LES LIBRAIRIES GRAPHIQUES SDL2, SDL2_image, SDL2_ttf 
int InitialiseGraphique()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("Dobble - Benjamin, Enzo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 700, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
		printf("echec de l initialisation de SDL_image: %s\n", IMG_GetError() );
		return -1;
        }

	if(TTF_Init() == -1)
	{
		printf("Erreur d'initialisation de TTF_Init: %s\n", TTF_GetError());
		return -1;
	}


	int TaillePoliceCaractere = 30;
	police = TTF_OpenFont("../data/FONTS/Chalkduster.ttf", TaillePoliceCaractere);

	if (police == NULL) {
		printf("echec du chargement de la police de caracteres\n");
		return -1;
	}

	// INITIALISATION DU GENERATEUR DE NOMBRE ALEATOIRE
	srand48(SDL_GetTicks());

	return 1;
}

// EFFACE LA FENETRE. NECESSAIRE AVANT DE REDESSINER
void EffaceFenetre()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
}

void AfficheTitre()
{
	const SDL_Rect OuEstLeTexte = {0, 0, tw, th};	
	SDL_RenderCopy(renderer, textureTexte, NULL, &OuEstLeTexte);
}

void Attends(unsigned long int Duree)
{
	SDL_Delay( Duree);
}

// UNE FOIS LA FENETRE DESSINEE EN ARRIER PLAN, LA PRESENTER AU PREMIER PLAN
void MontreFenetre()
{
	SDL_RenderPresent(renderer);
}

void PositionIconeDansImage(Carte carte, int *PosX, int *PosY)
{
	// Ici vous devrez calculer la position de l'icone #NumeroIcone dans l'image
  	*PosX = 90*(carte.NumeroDIcone)% 900;//juste pour ce fichier
	*PosY = (carte.NumeroDIcone/10)*90;
}

// AFFICHE UNE ICONE SOIT DANS UNE DES DEUX CARTES (CarteDuHaut OU CarteDuBas)
// LA PLACE DE L'ICONE EST CODEE EN COORDONNEES POLAIRES AUTOUR DU CENTRE DE LA CARTE
// Rayon EST LA DISTANCE AU CENTRE DE LA CARTE
// Angle EST L'ANGLE EN DEGRES, DANS LE SENS HORAIRE ET EN PARTANT DE LA DROITE.
//   Angle = 0 => L ICONE EST A DROITE DU CENTRE
//   Angle = 90 => L ICONE EST EN DESSOUS DU CENTRE
// Rotation EST UN ANGLE EN DEGRES PERMETTANT DE TOURNER L ICONE AUTOUR DE SON CENTRE
// Scale EST UN REEL PERMETTANT DE MODIFIER LA TAILLE DE L ICONE. Scale = 1 => TAILLE ORIGINALE (90) CONSERVEE
void AfficheIcone(Carte carte)
{
	int CentreX, CentreY;

	if (carte.PosCarte == CarteDuHaut) {
		CentreX = 300;
		CentreY = 200;
	} else {
		CentreX = 300;
		CentreY = 520;
	}

	// ATTENTION AUX CONVERSIONS ENTRE FLOTTANTS DOUBLE PRECISION ET ENTIERS
	int DestX = carte.Rayon*cos(carte.Angle/360.*(2.*M_PI)) + (CentreX-carte.Scale*90./2.);
	int DestY = carte.Rayon*sin(carte.Angle/360.*(2.*M_PI)) + (CentreY-carte.Scale*90./2.);
	int OrigX, OrigY;

	// RECUPERATION DE LA POSITION DE L ICONE NumeroIcone DANS L IMAGE CONTENANT TOUTES LES ICONES
	PositionIconeDansImage(carte, &OrigX, &OrigY);

	// SDL_Rect UnRectangle = {OrigineX, OrigineY, TailleX, TailleY}

	SDL_Rect srcrect = {OrigX, OrigY, 90,90}; // DANS L IMAGE EN ENTREE

	SDL_Rect dstrect = {DestX, DestY, 90*carte.Scale, 90*carte.Scale}; // DANS LA FENETRE EN SORTIE (ATTENTION: CONVERSION IMPLICITE ENTRE FLOTTANT ET ENTIER)

	SDL_RenderCopyEx(renderer, textureImage, &srcrect, &dstrect, carte.Rotation, NULL, SDL_FLIP_NONE);
}

void LaPartieEstQuittee (){
	printf("Au revoir \n");
	AfficherScore();
}

void BonneReponse(){
	printf("Bonne réponse\n");
	ChangeCompteARebours(3);
	AugmenterScore();	
}

void MauvaiseReponse(){
	printf("Mauvaise réponse\n");
	ChangeCompteARebours(-3);
}


// ATTENDS QU'UN EVENEMENT UTILISATEUR SOIT EMIS, PUIS REAGIT A CETTE EVENEMENT
void LisEtDispatchEvenement()
{
	Uint8 Pixels[4];
	int quit = 0;
	SDL_Event Evenement;
	SDL_Rect VoisinageSouris;

	while (!quit)
	{
		if (TempsEcoule()){
			LaPartieEstQuittee();
			quit = 1;
		}
		if(SDL_PollEvent(&Evenement)){
			switch (Evenement.type){
				case SDL_MOUSEMOTION:
					LaSourisBouge( Evenement.motion.x, Evenement.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					UnBoutonEstClique(Evenement.motion.x, Evenement.motion.y);
					break;
				case SDL_WINDOWEVENT:
					AfficheSceneComplete();
					break;
				case SDL_QUIT:
					LaPartieEstQuittee();
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (Evenement.key.keysym.sym){
						case SDLK_q:
							LaPartieEstQuittee();
							quit = 1;
							break;
						case SDLK_j:
							BonneReponse();
							break;
						case SDLK_f:
							MauvaiseReponse();
							break;
					}
			}
		}
		else{
			AfficheSceneComplete();
		}
	}
}



// LIBERE TOUTES LES RESOURCES GRAPHIQUES ALLOUEES PRECEDEMENT PUIS STOPPE LES LIBRAIRIES GRAPHIQUES
int ArreteGraphique()
{

	TTF_CloseFont(police); 
	TTF_Quit();
	IMG_Quit();

	SDL_DestroyTexture(textureImage);
	SDL_DestroyTexture(textureTexte);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); 

	SDL_Quit();

	return 0;
}
