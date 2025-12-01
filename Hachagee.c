#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

#include <math.h>
#include <stdlib.h>
#include "Hachage.h"

void insereVoisinT(CellNoeud ** L, Noeud * n) {
//inserer un voisin

    CellNoeud * voisin = (*L);
    
   
    while ((voisin != NULL) && (voisin -> nd != n)) voisin = voisin -> suiv;
    
   
    if (!voisin) {
        voisin = (CellNoeud *)malloc(sizeof(CellNoeud));
        voisin -> nd = n;
        voisin -> suiv = (*L);
        (*L) = voisin;
    }
}


double Clef(double x, double y){
    return y + (x + y) * (x + y + 1) * 1.0 / 2;
}



int Hachage(double k, int m) {
  double A = (sqrt(5) - 1) / 2;
  return ((int)(m * (k * A - ((long int)(k * A)))));
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){

    double clf = Clef(x,y);
    int index = Hachage(clf, H -> tailleMax);
    CellNoeud * CNoeudH = (H -> T)[index];
    Noeud * NoeudH = NULL;

    //Nous comparons les coordonnes de NoeudH dans la liste CNoeudH avec x et y passés en paramètres
    while(CNoeudH != NULL){
        NoeudH = CNoeudH -> nd;

        if((NoeudH -> x) == x && (NoeudH -> y) == y) 
          return NoeudH;//si present deja 
        CNoeudH = CNoeudH -> suiv;
    }

    //si pas present ajout dans la table de hachage et dans la liste
    Noeud * NoeudNouv = (Noeud *)malloc(sizeof(Noeud));
    NoeudNouv -> num = ((R -> nbNoeuds) + 1);
    NoeudNouv -> x = x;
    NoeudNouv -> y = y;
    NoeudNouv -> voisins = NULL;

    // L'ajouter dans la liste 
    CellNoeud * CNouvL = (CellNoeud*)malloc(sizeof(CellNoeud));
    CNouvL -> nd = NoeudNouv;
    CNouvL -> suiv = R -> noeuds;
    R -> noeuds = CNouvL;
    R -> nbNoeuds++;

    // L'ajouter dans la table de hachage 
    CellNoeud * CNouvH = (CellNoeud*)malloc(sizeof(CellNoeud));
    CNouvH -> nd = NoeudNouv;
    CNouvH -> suiv = (H -> T)[index];
    (H -> T)[index] = CNouvH;

    return NoeudNouv;
    
}


Reseau* reconstitueReseauHachage(Chaines *C, int M){
    if(!C) return NULL;

    // Declarer et initialiser la table hachage et le reseau 
    TableHachage * H = (TableHachage *)malloc(sizeof(TableHachage));

    H -> tailleMax = M;
    H -> T = (CellNoeud**)malloc(M * sizeof(CellNoeud*));

    for (int i = 0 ; i < M ; i++) (H -> T[i]) = NULL;
    
    Reseau * r = (Reseau *)malloc(sizeof(Reseau));
    r -> gamma = C -> gamma;
    r -> nbNoeuds = 0;
    r -> noeuds = NULL;
    r -> commodites = NULL;
    
    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;

    while(cc){
        // Nous traitons d'abord le cas des extrimites de chaines (commodite)
        CellCommodite * k = (CellCommodite*)malloc(sizeof(CellCommodite));
        cp = cc -> points;
        Noeud * noeudAjouter = rechercheCreeNoeudHachage(r, H, cp -> x, cp -> y);
        Noeud * noeudPrec = NULL;
        //commodite extrA
        k -> extrA = noeudAjouter;
        cp = cp -> suiv;
        
        while(cp){
            // Nous gardons à chaque fois, le dernier noeudAjouter pour déterminer les voisins. 
            noeudPrec = noeudAjouter;
            noeudAjouter = rechercheCreeNoeudHachage(r, H, cp -> x, cp -> y);
            
            insereVoisinT(&(noeudPrec -> voisins), noeudAjouter);
            insereVoisinT(&(noeudAjouter -> voisins), noeudPrec);
            
            cp = cp -> suiv;
        }
        //commodite extrB
        k -> extrB = noeudAjouter;
        k -> suiv = r -> commodites;
        r -> commodites = k;
        
        cc = cc -> suiv;
    }
    
    libereTableHachage(H);
    return r;
}

void libereTableHachage(TableHachage * H) {
    if (!H) return ;
    
    CellNoeud * cnCour = NULL;
    CellNoeud * cnPrec = NULL;
    for (int i = 0 ; i < H -> tailleMax ; i++) {
        cnPrec = NULL;
        cnCour = (H -> T)[i];
        while (cnCour) {
            cnPrec = cnCour;
            cnCour = cnCour -> suiv;
            free(cnPrec);
        }
    }
    free(H -> T);
    free(H);
}