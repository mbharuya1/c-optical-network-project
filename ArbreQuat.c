#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "Chaine.h"
#include "Reseau.h"


void insereVoisin(CellNoeud ** L, Noeud * n) {
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

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax) {
    if (!C || !xmin || !ymin || !xmax || !ymax) return ;

    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;

    // Initialiser les quatre valeurs 
    *xmin = cc -> points -> x;
    *ymin = cc -> points -> y;
    *xmax = cc -> points -> x;
    *ymax = cc -> points -> y;

    // Parcourir la liste pour touver les mins et les maxs 
    while (cc) {
        cp = cc -> points;
        while (cp) {
            if (cp -> x < (*xmin)) (*xmin) = cp -> x;
            if (cp -> y < (*ymin)) (*ymin) = cp -> y;
            if (cp -> x > (*xmax)) (*xmax) = cp -> x;
            if (cp -> y > (*ymax)) (*ymax) = cp -> y;
            cp = cp -> suiv;
        }
        cc = cc -> suiv;
    }
}



ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY) {
//Creation d'un arbre 

    ArbreQuat * aq = (ArbreQuat *)malloc(sizeof(ArbreQuat));
    if (!aq) {
        printf("Erreur d'allocation.\n");
        return NULL;
    }

    aq -> xc = xc;
    aq -> yc = yc;
    aq -> coteX = coteX;
    aq -> coteY = coteY;

    aq -> noeud = NULL;
    aq -> so = NULL;
    aq -> se = NULL;
    aq -> no = NULL;
    aq -> ne = NULL;

    return aq;
}



void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent) {
    if (!n || !parent) return ;

    //Cas arbre vide
    if ((*a) == NULL) {

        //Calculer la position du noeud dans l'arbre parent et creer une nouvelle cellule 
        double newCoteX = parent -> coteX * 1.0 / 2;
        double newCoteY = parent -> coteY * 1.0 / 2;
        double newXc, newYc;

        if (n -> x < parent -> xc) {
            newXc = parent -> xc - parent -> coteX * 1.0 / 4;
        } else {
            newXc = parent -> xc + parent -> coteX * 1.0 / 4;
        }
        if (n -> y < parent -> yc) {
            newYc = parent -> yc - parent -> coteY * 1.0 / 4;
        } else {
            newYc = parent -> yc + parent -> coteY * 1.0 / 4;
        }

        (*a) = creerArbreQuat(newXc, newYc, newCoteX, newCoteY);
        /* Ajouter le noeud dans la cellule */
        (*a) -> noeud = n;

        return ;
    }

    // Cas feuille 
    if ((*a) -> noeud != NULL) {
        Noeud * nAncien = (*a) -> noeud;

        //Calculer la position d'inserer le noeud 
        if (n -> x < (*a) -> xc && n -> y < (*a) -> yc) {
            insererNoeudArbre(n, &((*a) -> so), (*a));
        }
        else if (n -> x >= (*a) -> xc && n -> y < (*a) -> yc) {
            insererNoeudArbre(n, &((*a) -> se), (*a));
        }
        else if (n -> x < (*a) -> xc && n -> y >= (*a) -> yc) {
            insererNoeudArbre(n, &((*a) -> no), (*a));
        }
        else {
            insererNoeudArbre(n, &((*a) -> ne), (*a));
        }

        //Calculer la position d'inserer l'ancien noeud
        if (nAncien -> x < (*a) -> xc && nAncien -> y < (*a) -> yc) {
            insererNoeudArbre(nAncien, &((*a) -> so), (*a));
        }
        else if (nAncien -> x >= (*a) -> xc && nAncien -> y < (*a) -> yc) {
            insererNoeudArbre(nAncien, &((*a) -> se), (*a));
        }
        else if (nAncien -> x < (*a) -> xc && nAncien -> y >= (*a) -> yc) {
            insererNoeudArbre(nAncien, &((*a) -> no), (*a));
        }
        else {
            insererNoeudArbre(nAncien, &((*a) -> ne), (*a));
        }

        //Initialiser l'ancien noeud 
        (*a) -> noeud = NULL;
        return ;
    }

    //Cas noeud interne 
    if (n -> x < (*a) -> xc && n -> y < (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> so), (*a));
    }
    else if (n -> x >= (*a) -> xc && n -> y < (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> se), (*a));
    }
    else if (n -> x < (*a) -> xc && n -> y >= (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> no), (*a));
    }
    else {
        insererNoeudArbre(n, &((*a) -> ne), (*a));
    }
}



Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y) {
    ArbreQuat * arbre = *a;

    //Cas arbre vide 
    if (arbre == NULL) {
        // Creer un noeud 
        Noeud * n = (Noeud *)malloc(sizeof(Noeud));
        n -> num = (R -> nbNoeuds) + 1;
        n -> x = x;
        n -> y = y;
        n -> voisins = NULL;

        //L'inserer dans la liste 
        CellNoeud * cn = (CellNoeud *)malloc(sizeof(CellNoeud));
        cn -> nd = n;
        cn -> suiv = R -> noeuds;
        R -> noeuds = cn;
        R -> nbNoeuds++;

        //L'inserer dans l'arbreQuat 
        insererNoeudArbre(n, &(*a), parent);

        return n;
    }

    //Cas feuille
    if (arbre -> noeud != NULL) {
        if (arbre -> noeud -> x == x && arbre -> noeud -> y == y) {
            return arbre -> noeud;
        }

        //Creer un noeud nouveau
        Noeud * n = (Noeud *)malloc(sizeof(Noeud));
        n -> num = (R -> nbNoeuds) + 1;
        n -> x = x;
        n -> y = y;
        n -> voisins = NULL;

        // L'inserer dans la liste 
        CellNoeud * cn = (CellNoeud *)malloc(sizeof(CellNoeud));
        cn -> nd = n;
        cn -> suiv = R -> noeuds;
        R -> noeuds = cn;
        R -> nbNoeuds++;

        // L'inserer dans l'arbreQuat
        insererNoeudArbre(n, &(*a), parent);

        return n;
    }

    //Cas noeud interne 
    if (x < arbre -> xc && y < arbre -> yc) {
        return rechercheCreeNoeudArbre(R, &(arbre -> so), arbre, x, y);

    }
    else if (x >= arbre -> xc && y < arbre -> yc) {
        return rechercheCreeNoeudArbre(R, &(arbre -> se), arbre, x, y);

    }
    else if (x < arbre -> xc && y >= arbre -> yc) {
        return rechercheCreeNoeudArbre(R, &(arbre -> no), arbre, x, y);

    }
    else {
        return rechercheCreeNoeudArbre(R, &(arbre -> ne), arbre, x, y);
    }
}



Reseau* reconstitueReseauArbre(Chaines* C) {
    if (!C) return NULL;

    // Creer le reseau 
    Reseau * r = (Reseau *)malloc(sizeof(Reseau));
    r -> gamma = C -> gamma;
    r -> nbNoeuds = 0;
    r -> noeuds = NULL;
    r -> commodites = NULL;
    Noeud * nAjoute = NULL;
    Noeud * nPrec = NULL;

    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;

    // Creer la racine de l'arbre 
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    ArbreQuat * a = creerArbreQuat((xmin + xmax) * 1.0 / 2, (ymin + ymax) * 1.0 / 2, xmax - xmin, ymax - ymin);

    // Parcourir les chaines 
    while (cc) {

        //cas des extrimites de chaines: commodite
        CellCommodite * k = (CellCommodite*)malloc(sizeof(CellCommodite));
        cp = cc -> points;

        if ((cp -> x) < (a -> xc) && (cp -> y) < (a -> yc)) {
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> so), a, cp -> x, cp -> y);
        } else if ((cp -> x) >= (a -> xc) && (cp -> y) < (a -> yc)) {
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> se), a, cp -> x, cp -> y);
        } else if ((cp -> x) < (a -> xc) && (cp -> y) >= (a -> yc)) {
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> no), a, cp -> x, cp -> y);
        } else {
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> ne), a, cp -> x, cp -> y);
        }

        cp = cc -> points;
        //commodite extrA
        k -> extrA = nAjoute;
        cp = cp -> suiv;

        while (cp) {
            // Ajouter ce noeud dans la liste 
            nPrec = nAjoute;

            if (cp -> x < a -> xc && cp -> y < a -> yc) {
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> so), a, cp -> x, cp -> y);
            } else if (cp -> x >= a -> xc && cp -> y < a -> yc) {
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> se), a, cp -> x, cp -> y);
            } else if (cp -> x < a -> xc && cp -> y >= a -> yc) {
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> no), a, cp -> x, cp -> y);
            } else {
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> ne), a, cp -> x, cp -> y);
            }


            //Ajout les voisins 
            insereVoisin(&(nPrec -> voisins), nAjoute);
            insereVoisin(&(nAjoute -> voisins), nPrec);
            cp = cp -> suiv;

        }

        //commodite extrB
        k -> extrB = nAjoute;
        k -> suiv = r -> commodites;
        r -> commodites = k;

        cc = cc -> suiv;
    }

    libereArbreQuat(a);
    return r;
}


void libereArbreQuat(ArbreQuat * a) {
    if (a == NULL) return ;

    if (a -> noeud != NULL) {
        free(a);
        return ;
    }

    libereArbreQuat(a -> so);
    libereArbreQuat(a -> se);
    libereArbreQuat(a -> no);
    libereArbreQuat(a -> ne);
    free(a);
}