#ifndef _DOBBLE_
#define _DOBBLE_

void AfficheSceneComplete();
void LaSourisBouge(int x, int y);
void UnBoutonEstClique(int x, int y);
void CompteARebours();
void Remplit_tableau(FILE* f);

int TempsEcoule();
void ChangeCompteARebours(int n);

#endif
