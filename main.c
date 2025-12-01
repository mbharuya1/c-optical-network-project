#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"


int main() {

    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;


    //lecture des instances
    FILE * f1 = fopen("00014_burma.cha", "r");
    FILE * f2 = fopen("05000_USA-road-d-NY.cha", "r");
    FILE * f3 = fopen("07397_pla.cha", "r");
    
    Chaines * c1 = lectureChaine(f1);
    
    Chaines * c2 = lectureChaine(f2);

    Chaines * c3 = lectureChaine(f3);

    
    //ecriture du temps 
    FILE * L = fopen("vitesseL.txt", "w");
    FILE * H = fopen("vitesseH.txt", "w");
    FILE * A = fopen("vitesseA.txt", "w");
    Reseau * r = NULL;

    //Liste
    fprintf(L, "Liste:\n ");
    fprintf(L, " C1        C2      C3\n");

    //C1
    temps_initial = clock();
    r = reconstitueReseauListe(c1); 
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    fprintf(L, "%f   ", temps_cpu);
    libereReseau(r);


    //C2
    temps_initial = clock();
    r = reconstitueReseauListe(c2);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(L, "%f  ", temps_cpu);
    libereReseau(r);

    //C3
    temps_initial = clock();
    r = reconstitueReseauListe(c3);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(L, "%f  \n", temps_cpu);
    libereReseau(r);


    //Table de Hachage 
    fprintf(H, "Table de hachage:\n ");
    fprintf(H, " C1        C2      C3\n");

    // M = 100 
    fprintf(H, "taille=150\n");
    //C1
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 100);
    
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);

    //C2
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 100);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C3
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 100);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      \n", temps_cpu);
    libereReseau(r);

    // M = 200 

    fprintf(H, "taille 200\n");
    //C1
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 200);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);

    //C2
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 200);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C3
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 200);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      \n", temps_cpu);
    libereReseau(r);
    
    //M = 300 
    fprintf(H, "taille=300\n");


    //C1
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 300);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C2
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 300);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f ", temps_cpu);
    libereReseau(r);
    
    //C3
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 300);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f    \n", temps_cpu);
    libereReseau(r);

    // M = 400 
    fprintf(H, "taille=400\n");
    //C1
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 400);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C2
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 400);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C3
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 400);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      \n", temps_cpu);
    libereReseau(r);

    //M = 500 
    fprintf(H, "taille=500\n");
    //C1 
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C2
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      ", temps_cpu);
    libereReseau(r);
    
    //C3
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(H, "%f      \n", temps_cpu);
    libereReseau(r);

 
    //Arbre
    fprintf(A, "Arbre :\n ");
    fprintf(A, " C1        C2      C3\n");

    //C1
    temps_initial = clock();
    r = reconstitueReseauArbre(c1);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(A, "%f      ", temps_cpu);
    libereReseau(r);

    
    //C2
    temps_initial = clock();
    r = reconstitueReseauArbre(c2);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(A, "%f      ", temps_cpu);
    libereReseau(r);
   
    //C3
    temps_initial = clock();
    r = reconstitueReseauArbre(c3);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(A, "%f      \n", temps_cpu);
    libereReseau(r);
    
    
    fclose(L);
    fclose(H);
    fclose(A);
    
    libererChaine(c1);
    libererChaine(c2);
    libererChaine(c3);

    fclose(f1);
    fclose(f2);
    fclose(f3);
         
return 0;
}