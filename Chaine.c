#include "Chaine.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "SVGwriter.h"
#include <math.h>


Chaines* lectureChaine(FILE * f){
  //Crée une Chaine en lisant dans un fichier f

  char buf[6000];

  //Variables declarees pour la lecture de la structure Chaines
  double x, y;
  int nbPoints;
  int num;
  int gamma, nbChaines;

  //Création l'ensemble de chaînes
  Chaines *C = (Chaines *) malloc(sizeof(Chaines));
  if(!C){ 
    printf("Erreur lors de l'allocation Chaines.\n");
    return NULL;
  }
  fgets(buf, 5000, f);
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "NbChain: %d", &nbChaines);

  fgets(buf, 5000, f);
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "Gamma: %d", &gamma);

  C -> nbChaines = nbChaines;
  C -> gamma = gamma;
  C -> chaines = NULL;

  //Boucle pour lecture de chaines
  for(int i = 0; i < C -> nbChaines; i++){

    //Suite de la ligne qui n'a pas encore ete lu
    char points[6000];

    //Création de liste chainee de chaines
    CellChaine* cc = (CellChaine*)malloc(sizeof(CellChaine));
    if(!cc){ //Test malloc
      printf("Erreur lors de l'allocation CellChaine.\n");
      libererChaine(C);
      return NULL;
    }

    //Nous lisons les deux premiers variables
    fgets(buf, 6000, f);
    buf[strlen(buf) - 1] = '\0';
    sscanf(buf, "%d %d %[^\n]\n", &num, &nbPoints, points);

    cc -> numero = num;
    cc -> points = NULL;

    //lecture de points
    for(int j = 0; j < nbPoints ; j++){
      sscanf(points, "%lf %lf %[^\n]\n", &x, &y, points);

      //Création de points
      CellPoint* cp = (CellPoint*)malloc(sizeof(CellPoint));
      if(!cp){ //Test malloc
        printf("Erreur lors de l'allocation CellPoint.\n");
        libererCellChaine(cc);
        libererChaine(C);
        return NULL;
      }
      cp -> x = x;
      cp -> y = y;

      //Insertion dans la liste de points
      cp -> suiv = cc -> points;
      cc -> points = cp;
    }

    //Insertion dans la liste des chaines
    cc -> suiv = C -> chaines;
    C -> chaines = cc;
  }
    return C;
}

void ecrireChaine( Chaines *C, FILE *f){
//Ecriture d'une chaine c dans un fichier f

    if(f==NULL){
        printf("Probleme d'ouverture");
        exit(1);
    }

    if (C!=NULL){
        //Ecriture des premières informations
        fprintf(f, "NbChain: %d \nGamma: %d\n",C->nbChaines, C->gamma );
        CellChaine* tmp= C->chaines;
        
        //Parcourt des chaines
        while(tmp){
            fprintf(f, "%d " , tmp->numero);
            int i=0;
            CellPoint *tmp1= tmp->points;

            //Compte le nombre de points
            while(tmp1){
                i++;
                tmp1=tmp1->suiv;
            }  
            fprintf(f, "%d " , i);   
            CellPoint *tmp2= tmp->points;

            //Parcourts des points
            while( tmp2){
                
                fprintf(f, "%.2f %.2f ",tmp2->x, tmp2->y );
                tmp2=tmp2->suiv;
            }
            fprintf(f,"\n");
            tmp=tmp->suiv;
        }
    }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


double longueurChaine(CellChaine *c){
//Longueurs d'une chaines c

    double res=0.0;
    CellPoint* pt=c->points;
    CellPoint* pt2;
    while(pt){
        pt2=pt->suiv;
        while(pt2){
            double x = (pt2->x-pt->x)*(pt2->x-pt->x);
            double y = (pt2->y-pt->y)*(pt2->y-pt->y);
            res+=sqrt(x+y);
            pt2=pt2->suiv;
        }
        pt=pt->suiv;
    }
    return res;
}

double longueurTotale(Chaines *C){
//Longueurs physique totale des chaines de c

    CellChaine* c = C->chaines;
    double res=0.0;
    while(c){
        //Sommes de la longueurs des différentes chaines
        res+=longueurChaine(c);
        c=c->suiv;
    }
    return res;
}

int comptePointsTotal(Chaines *C){
//Nombre total d'occurrences de points 

    int res=0;
    CellChaine* c = C->chaines;
    while(c){
        CellPoint* p=c->points;
        while(p){
            res++;
            p=p->suiv;
        }
        c=c->suiv;
    }
    return res;

}

void libererCellChaine(CellChaine * cc){
//Liberation d'une CellChaine

  if(!cc){
    return;
  }

  CellPoint * cpCour = cc -> points;
  CellPoint * cpPrec;

  while(cpCour){
    cpPrec = cpCour;
    cpCour = cpCour -> suiv;
    free(cpPrec);
  }

  free(cc);
  return;
}

void libererChaine(Chaines* C){
//Liberation d'une chaine

  if(!C){
    return;
  }
  CellChaine * ccCour = C -> chaines;
  CellChaine * ccPrec;

  while(ccCour){
    ccPrec = ccCour;
    ccCour = ccCour -> suiv;
    libererCellChaine(ccPrec);
  }

  free(C);
  return;
}


//EXercice 6
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax) {
//Genere aleatoirement une chaine 

    //Declarer et initialiser les chaines 
    Chaines * cs = (Chaines *)malloc(sizeof(Chaines));
    cs -> gamma = 0;
    cs -> nbChaines = nbChaines;
    cs -> chaines = NULL;

    CellChaine * cc = NULL;
    CellPoint * cp = NULL;

    //Creer chaque chaine avec les valeurs aleatoires
    for (int i = 0 ; i < nbChaines ; i++) {
        cc = (CellChaine *)malloc(sizeof(CellChaine));
        cc -> numero = i;
        cc -> points = NULL;
        cc -> suiv = cs -> chaines;
        cs -> chaines = cc;

        // Creer aleatoirement les points dans la chaine 
        for (int j = 0 ; j < nbPointsChaine ; j++) {
            cp = (CellPoint *)malloc(sizeof(CellPoint));
            cp -> x = rand() % xmax;
            cp -> y = rand() % ymax;
            cp -> suiv = cc -> points;
            cc -> points = cp;
        }
    }
    return cs;
}