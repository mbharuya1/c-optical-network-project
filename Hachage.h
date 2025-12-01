
#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"


typedef struct tableHachage{
  int tailleMax;
  CellNoeud** T;
} TableHachage ;

int clef (double x, double y);
int hachage( int taille, int clef);
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines* C, int M);
void insereVoisinT(CellNoeud ** L, Noeud * n);
void libereTableHachage(TableHachage * H);
#endif

