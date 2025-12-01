#include "Chaine.h"
#include <stdlib.h>
#include <stdio.h>
#include "SVGwriter.h"



int main(){

    FILE *f= fopen("00014_burma.cha", "r");
    FILE *g= fopen("test.txt", "w");

    //lecture
    Chaines* test= lectureChaine(f);
    
    //ecriture
    ecrireChaine( test,g);
    afficheChainesSVG(test,"graphe");//A ouvrir le html avec navigateur

    //printf("%d\n",comptePointsTotal(test));

    //printf("%f\n",longueurChaine(test->chaines));

    //printf("%f\n",longueurTotale(test));

    fclose(f);
    fclose(g);
    return 0;
}
