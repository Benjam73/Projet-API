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
void ChangeCompteARebours(int n);
void ligne_courante_random();

Carte InitialiseCarte (PositionCarte PosCarte, int NumeroDIcone, double Rayon, double Angle, double Rotation, double Scale);

#endif
