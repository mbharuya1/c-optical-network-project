#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"


int main(void) {
    srand(time(NULL));
  
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    
    FILE * f1 = fopen("sortie_vitesse_liste.txt", "w");
    FILE * f2 = fopen("sortie_vitesse_hachage_arbre.txt", "w");
    Reseau * r = NULL;
    Chaines * chaines = NULL;
    
    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;
    int nbChaines = 500;
    
    for (nbChaines = 500 ; nbChaines <= 5000 ; nbChaines += 500) {
        printf("nbChaines = %d\n", nbChaines);
        chaines = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);
        
        // liste 
        fprintf(f1, "%d ", nbChaines);
        temps_initial = clock();
        r = reconstitueReseauListe(chaines);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(f1, "%f\n", temps_cpu);
        libereReseau(r);
        

        // table de hachage et arbre 
        fprintf(f2, "%d ", nbChaines);
        
        // temps de calcul pour la table de hachage
        // taille 500 */
        temps_initial = clock();
        r = reconstitueReseauHachage(chaines, 500);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps_cpu);
        libereReseau(r);
        
        /* taille 5000 */
        temps_initial = clock();
        r = reconstitueReseauHachage(chaines, 5000);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps_cpu);
        libereReseau(r);
        
        /* taille 50000 */
        temps_initial = clock();
        r = reconstitueReseauHachage(chaines, 50000);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f ", temps_cpu);
        libereReseau(r);

        /* temps de calcul pour l'arbre */
        temps_initial = clock();
        r = reconstitueReseauArbre(chaines);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
        fprintf(f2, "%f\n", temps_cpu);
        libereReseau(r);
        
        libererChaine(chaines);
    }
    
    
    fclose(f1);
    fclose(f2);


    return 0;
}