#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include "SVGwriter.h"

/* Q 2.3 */
int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Nombre de parametres incorrect\n");
        printf("1 : liste ; 2 : table hachage ; 3 : arbre\n");
        return 1;
    }

    FILE * f = fopen(argv[1], "r");
    FILE* g;
    Chaines * c = lectureChaine(f);
    int choix= atoi(argv[2]);
    Reseau * r = NULL;

    /* 1 liste chainee, 2 table hachage et 3 arbre quaternaire*/
    switch (choix) {
        case 1:
            g = fopen("reseauListe.txt", "w");
            r = reconstitueReseauListe(c);
            afficheReseauSVG(r, "reseauListe");
            ecrireReseau(r, g);
            libereReseau(r);
            
    
            break;

        case 2:
            g = fopen("reseauHachage.txt", "w");
            r = reconstitueReseauHachage(c, comptePointsTotal(c));
            afficheReseauSVG(r, "reseauHachage");
            ecrireReseau(r, g);
            libereReseau(r);
        
            break;
            
        case 3:
            g = fopen("reseauArbre.txt", "w");
            r = reconstitueReseauArbre(c);
            afficheReseauSVG(r, "reseauArbre");
            ecrireReseau(r, g);
            libereReseau(r);
            break;
    }

    libererChaine(c);
    fclose(f);
    fclose(g);

    return 0;
}
