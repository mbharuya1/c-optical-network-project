#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"
#include "Struct_File.h"


typedef struct {
    int u, v; /* Numeros des sommets extremite */
} Arete;

typedef struct cellule_arete {
    Arete *a; /* pointeur sur l’arete */
    struct cellule_arete *suiv;
} Cellule_arete;

typedef struct {
    int num; /* Numero du sommet (le meme que dans T_som) */
    double x, y;
    Cellule_arete *L_voisin; /* Liste chainee des voisins */
} Sommet;

typedef struct {
    int e1, e2; /* Les deux extremites de la commodite */
} Commod;

typedef struct {
    int nbsom; /* Nombre de sommets */
    Sommet **T_som; /* Tableau de pointeurs sur sommets */
    int gamma;
    int nbcommod; /* Nombre de commodites */
    Commod *T_commod; /* Tableau des commodites */
} Graphe;

//Structure définissant une liste d'entier
typedef struct entier{
  int n;
  struct entier *suiv;
} Entier;

typedef Entier * ListeEntier;

void ajoute_en_tete(ListeEntier* L, int n){
  Entier* nvsom=(Entier*) malloc(sizeof(Entier));
  nvsom->n=n;
  nvsom->suiv=*L;
  *L=nvsom;
}

Graphe* creerGraphe(Reseau* r);
Noeud* RechercheNoeudIndice(CellNoeud* n, int i);
void AjouteVoisin(Sommet* s, int numv);
int reorganiseReseau(Reseau * r);
void libereMatrice(int ** matrice, int taille);
void libereGraphe(Graphe * g);
int plusPetitNombreAretes(Graphe* g, int u, int v);
void ajoute_en_tete(ListeEntier* L, int n);
void desalloue(ListeEntier *L);
#endif
