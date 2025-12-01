#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <stdio.h> 


Noeud* rechercheCreeNoeudListe(Reseau* R, double x, double y){
//Retourne ou cree un noeud de coordonée (x,y) si pas présent dans R

    CellNoeud* cell=R->noeuds;

    //Nous regardons si le noeud existe
    while(cell){
        double x1=cell->nd->x;
        double y1=cell->nd->y;
        if(x1==x && y1==y){
            //Si il existe alors il est retourné
            return cell->nd;
        }
        cell=cell->suiv;
    }
    
    //Sinon nous le créons et l'ajoutons dans R
    CellNoeud* c = (CellNoeud*)malloc(sizeof(CellNoeud));
    if( c==NULL){
        printf("Probleme d'allocation 1\n");
        exit(1);
    }
    c->nd=(Noeud*)malloc(sizeof(Noeud));
    if( c->nd==NULL){
        printf("Prbleme d'allocation 2\n");
        exit(1);
    }
    R->nbNoeuds+=1;
    c->nd->num=R->nbNoeuds;
    c->nd->x=x;
    c->nd->y=y;
    c->nd->voisins=NULL;
    c->suiv=R->noeuds;
    R->noeuds=c;

    return c->nd;

}

void ajoutVNoeuds( Reseau* r, Noeud* n, double x, double y){
//Ajout d'un noeud dans les voisins de n 

    CellNoeud* voisin = n->voisins;
    while (voisin) {
        if (voisin->nd->x == x && voisin->nd->y == y) {
            return; // Le voisin existe déjà, pas besoin de l'ajouter
        }
        voisin = voisin->suiv;
    }

    //Sinon nous l'ajoutons dans les voisins et le reseau
    CellNoeud* new=malloc(sizeof(CellNoeud));
   
    if( new==NULL){
        printf("Probleme d'allocation pour la liste\n");
        exit(1);
    }

    new->nd=rechercheCreeNoeudListe(r, x,y);
    new->suiv=n->voisins;
    n->voisins=new;
}

CellCommodite* ajouteCommodites( CellCommodite* c, Noeud* A, Noeud* B){
// Ajout d'une commodité dans un reseau

    CellCommodite* cell=c;
    while(cell){
        if ((cell->extrA==A) && (cell->extrB==B)){
            return c; //si present pas la peine de le créer
        
        }
        cell=cell->suiv;
    }
 
    //sinon nous le créons la commodité
    CellCommodite* newC= malloc(sizeof(CellCommodite));
    if( newC==NULL){
        printf("Probleme d'allocation pour la commodite\n");
        exit(1);
    }
 
    newC->extrA=A;
    newC->extrB=B;
    newC->suiv=c;
    return newC;

}


Reseau* reconstitueReseauListe(Chaines *C){

    //creation du reseau 
    Reseau* R=(Reseau*)malloc(sizeof(Reseau));
    if(R==NULL){
        printf("Probleme memoire pour reseau\n");
        exit(1);
    }
    R->gamma=C->gamma;
    R->nbNoeuds=0;
    R->noeuds = NULL;
    R->commodites = NULL;

    //creation du noeud lors de la recherche
    Noeud* n;
    CellChaine* c= C->chaines;
    CellPoint* p;
    CellPoint* pprec;
    CellPoint* pproch;
    CellPoint* first;

    while(c){
        first=c->points;
        pprec=NULL;
        p=c->points;
        pproch= p->suiv;

        while (p){
            //ajout d'un noeud, ou recherche du noeud si deja present  
            n=rechercheCreeNoeudListe( R, p->x, p->y);

            //ajout du voisin de deriere
            if(pprec!=NULL){
               ajoutVNoeuds(R, n, pprec->x, pprec->y );
            }

            //ajout du voisin de devant 
            if(pproch!=NULL){
                ajoutVNoeuds(R, n, pproch->x, pproch->y);
            }
            
            pprec=p;
            p=p->suiv;
            if(p!=NULL)
                pproch=p->suiv;
            else 
                pproch=NULL;
        }
        //ajout des commodites
        CellCommodite* tmp= ajouteCommodites(R->commodites, rechercheCreeNoeudListe(R, first->x, first->y), rechercheCreeNoeudListe(R, pprec->x, pprec->y));
        R->commodites=tmp;
        c=c->suiv;  
    }

    return R;
}

int nbCommodites( Reseau* R){
//compte le nombre de commodités d'un reseau
    int nb=0;
    CellCommodite *c=R->commodites;
    while(c){
        nb++;
        c=c->suiv;
    }
    return nb;
}

int nbLiaisons(Reseau *R){
//compte le nombre de liaison d'un reseau 
    int nb=0;
    CellNoeud *noeud=R->noeuds;
    CellNoeud* voisin;
    while(noeud){

        voisin=noeud->nd->voisins;

        while(voisin){
            nb++;
            voisin=voisin->suiv;
        }
        
        noeud=noeud->suiv;
    }

    nb=nb/2;
    return nb;
}

Paire* AjoutePaire( Paire* l, int x, int y){

   Paire* new =malloc(sizeof(Paire));
   if(new==NULL){
        printf("probleme d'allocation\n");
        exit(1);
   }
   new->n1=x; 
   new->n2=y;
   new->suiv=l;
   return new;
}

int RechercheV(Paire* l, int x, int y){

    Paire* tmp=l;
    while(tmp){
        if( tmp->n1==x && tmp->n2==y || tmp->n1==y && tmp->n2==x )
            return 0;
        tmp=tmp->suiv;
    }
    return 1;
}

void ecrireReseau( Reseau *R, FILE *f){

    if(f==NULL){
        printf("Probleme d'ouverture");
        exit(1);
    }

    if (R!=NULL){ 
        fprintf(f, "NbNoeuds: %d \nNbLiaisons: %d \nNbCommodites: %d \nGamma: %d\n",R->nbNoeuds, nbLiaisons(R), nbCommodites(R), R->gamma );
        fprintf(f,"\n");

        //ecriture des noeuds
        CellNoeud* Cnoeud=R->noeuds;
        Noeud* tmp;

        while (Cnoeud){
            tmp=Cnoeud->nd;
            fprintf(f, "v %d %f %f \n", tmp->num, tmp->x, tmp->y );
            Cnoeud=Cnoeud->suiv;
        }
        fprintf(f,"\n");
        
        //ecriture des liaisons
        Paire* listep= NULL;
        Paire* tmp2;

        CellNoeud* Cnoeud2 = R->noeuds;
        while (Cnoeud2) {
            Noeud* noeud2 = Cnoeud2->nd;
            CellNoeud* voisin2 = noeud2->voisins;

            while (voisin2) {
                
                if( RechercheV(listep, noeud2->num, voisin2->nd->num ) ==1  ){
                    fprintf(f, "l %d %d \n", noeud2->num, voisin2->nd->num);
                    tmp2=AjoutePaire( listep, noeud2->num, voisin2->nd->num);
                    listep=tmp2;
                }
                voisin2 = voisin2->suiv;

            }
            Cnoeud2 = Cnoeud2->suiv;
        }
        fprintf(f,"\n");

        //ecriture des commodites
        CellCommodite* Ccom=R->commodites;
        while(Ccom){
            fprintf(f, "k %d %d  \n", Ccom->extrA->num, Ccom->extrB->num);
            Ccom=Ccom->suiv;
        }
    }

}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

void libereReseau(Reseau * R) {
//Liberation d'un reseau 

    if (!R) return ;
    
    // Liberer les commodites
    CellCommodite * commoCour = NULL;
    CellCommodite * commoSuiv = R -> commodites;
    
    while (commoSuiv) {
        commoCour = commoSuiv;
        commoSuiv = commoSuiv -> suiv;
        free(commoCour);
    }
    
    //Liberer les cellNoeuds et les noeuds 
    CellNoeud * cnCour = NULL;
    CellNoeud * cnSuiv = R -> noeuds;
    CellNoeud * voisinCour = NULL;
    CellNoeud * voisinSuiv = NULL;
    
    while (cnSuiv) {
        cnCour = cnSuiv;
        cnSuiv = cnSuiv -> suiv;

        // Liberer tous les voisins du noeud 
        voisinSuiv = cnCour -> nd -> voisins;
        while (voisinSuiv) {
            voisinCour = voisinSuiv;
            voisinSuiv = voisinSuiv -> suiv;
            free(voisinCour);
        }
            
        //Liberer ce noeud 
        free(cnCour -> nd);
        
        // Liberer ce CellNoeud 
        free(cnCour);
    }

    free(R);
}