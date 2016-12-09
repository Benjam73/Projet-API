#ifndef _DOBBLE_
#define _DOBBLE_

void AfficheSceneComplete();
void LaSourisBouge(int x, int y);
void UnBoutonEstClique(int x, int y);
void CompteARebours();
void AugmenterScore();
void Remplit_tableau(FILE* f);
void incone_commun();
int TempsEcoule();
void Afficher_HuitCartes();
void Afficher_CinqCartes();
void Afficher_TroisCartes();
void ChangeCompteARebours(int n);
void ligne_courante_random();
void permutation();
Carte InitialiseCarte (PositionCarte PosCarte, int NumeroDIcone, double Rayon, double Angle, double Rotation, double Scale);

#endif
