#ifndef _GESTION_GRAPHIQUE_
#define _GESTION_GRAPHIQUE_

typedef enum{ CarteDuHaut, CarteDuBas} PositionCarte;

typedef struct Carte Carte ; 
struct Carte{
	PositionCarte PosCarte ;
	int NumeroDIcone ;
	double Rayon ;
	double Angle ; 
	double Rotation ; 
	double Scale ;
	double Ordonnee ;
	double Abscisse ;
};

// LIS UNE IMAGE SUR LE DISQUE DUR QUI CONTIENT TOUTES LES ICONES
int ChargeImage(const char *NomDuFichier);


// PAUSE PENDANT UNE DUREE INDIQUEE EN MILLISECONDES
void Attends(unsigned long int Duree);

// DESSINE DANS UNE IMAGE UN MESSAGE AVEC UNE POLICE DE CARACTERE
int InitialiseTitre(const char *Message);

// AFFICHE L IMAGE DU MESSAGE PRODUIT PAR InitialiseTexte DANS LA FENETRE
void AfficheTitre();

// EFFACE LA FENETRE, NECESSAIRE AVANT DE REDESSINER
void EffaceFenetre();

// UNE FOIS LA FENETRE DESSINEE EN ARRIERE PLAN, LA PRESENTER AU PREMIER PLAN
void MontreFenetre();

// AFFICHE UNE ICONE SOIT DANS UNE DES DEUX CARTES (CarteDuHaut OU CarteDuBas)
// LA PLACE DE L'ICONE EST CODEE EN COORDONNEES POLAIRES AUTOUR DU CENTRE DE LA CARTE
// Rayon EST LA DISTANCE AU CENTRE DE LA CARTE
// Angle EST L'ANGLE EN DEGRES, DANS LE SENS HORAIRE ET EN PARTANT DE LA DROITE.
//   Angle = 0 => L ICONE EST A DROITE DU CENTRE
//   Angle = 90 => L ICONE EST EN DESSOUS DU CENTRE
// Rotation EST UN ANGLE EN DEGRES PERMETTANT DE TOURNER L ICONE AUTOUR DE SON CENTRE
// Scale EST UN REEL PERMETTANT DE MODIFIER LA TAILLE DE L ICONE. Scale = 1 => TAILLE ORIGINALE (90) CONSERVEE
void AfficheIcone( PositionCarte NumeroDeCarte, int NumeroDIcone, double Rayon, double Angle, double Rotation, double Scale);

void Hit_box(PositionCarte NumeroDeCarte, double Rayon, double Angle, double Scale);

// ATTENDS QU'UN EVENEMENT UTILISATEUR SOIT EMIS, PUIS REAGIT A CETTE EVENEMENT
void LisEtDispatchEvenement();

// LANCEMENT DE L'APPEL REGULIER A LA FONCTION CompteARebours
void LanceCompteARebours();
// ARRET DE L APPEL REGULIER A LA FONCTION CompteARebours LORS DU PROCHAIN APPEL A CETTE FONCTION
void ArreteCompteARebours();

// FONCTION INITIALISANT LES LIBRAIRIES GRAPHIQUES SDL2, SDL2_image, SDL2_ttf 
int InitialiseGraphique();

// LIBERE TOUTES LES RESOURCES GRAPHIQUES ALLOUEES PRECEDEMENT PUIS STOPPE LES LIBRAIRIES GRAPHIQUES
int ArreteGraphique();

#endif
