#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"
#include "Reseau.h"
#include "Struct_File.h"

Noeud* RechercheNoeudIndice(CellNoeud* n, int i){

    CellNoeud* cn = n;
    while(cn){ 
        if (cn->nd->num==i){
            return cn->nd;
        }
        cn=cn->suiv;
    }

    return NULL;

}

void AjouteVoisin(Sommet* s, int numv){
    
    Cellule_arete* ca = (Cellule_arete*)malloc(sizeof(Cellule_arete));

    if (ca==NULL){
        exit(1);
    }

    ca->a = (Arete*)malloc(sizeof(Arete));

    if (ca->a==NULL){
        exit(1);
    }

    ca->a->u=s->num;
    ca->a->v = numv;

    ca->suiv=s->L_voisin;
    s->L_voisin=ca;

}


Graphe* creerGraphe(Reseau* r) {
    Graphe* gr = malloc(sizeof(Graphe));
    // Vérification de l'allocation
    if (gr == NULL) {
        exit(1);
    }

    int nbsom = r->nbNoeuds;
    gr->gamma = r->gamma;
    gr->nbcommod = nbCommodites(r);

    // Allocation du tableau de pointeurs sur sommets
    gr->T_som = (Sommet**)malloc(sizeof(Sommet*) * nbsom);
    // Vérification de l'allocation
    if (gr->T_som == NULL) {
        exit(1);
    }

    // Initialisation des valeurs du tableau
    CellNoeud* n = r->noeuds;
    int i = 0;

    while (i < nbsom) {
        gr->T_som[i] = (Sommet*)malloc(sizeof(Sommet));
        // Vérification de l'allocation
        if (gr->T_som[i] == NULL) {
            exit(1);
        }

        Noeud* noeud = RechercheNoeudIndice(n, i);
        // Vérification de la recherche du noeud
        if (noeud == NULL) {
            i++;
            continue;
        }
        gr->T_som[i]->num = noeud->num;
        gr->T_som[i]->x = noeud->x;
        gr->T_som[i]->y = noeud->y;
        gr->T_som[i]->L_voisin = NULL;

        // Ajout des voisins
        CellNoeud* v = noeud->voisins;
        while (v) {
            AjouteVoisin(gr->T_som[i], v->nd->num);
            v = v->suiv;
        }

        i++;
    }

    // Commodites
    gr->T_commod = (Commod*)malloc(sizeof(Commod) * gr->nbcommod);
    // Vérification de l'allocation
    if (gr->T_commod == NULL) {
        exit(1);
    }

    CellCommodite* c = r->commodites;
    int j = 0;
    while (c && j < gr->nbcommod) {
        gr->T_commod[j].e1 = c->extrA->num;
        gr->T_commod[j].e2 = c->extrB->num;
        c = c->suiv;
        j++;
    }

    return gr;
}


//Question 2

int plusPetitNombreAretes(Graphe* g, int u, int v){

    //On initialise le file

    S_file* file = malloc(sizeof(S_file));
    if(file==NULL){
        exit(1);
    }
    Init_file(file);


    //Tableau des sommets visite

    int* visite=malloc(g->nbsom*sizeof(int));

    //Si probleme d'allocation
    if(visite==NULL){
        free(file);
        exit(1);
    }


    //On initialise le tableau des sommets visites
    for (int i=0; i<g->nbsom; i++){
        visite[i]=0;
    }

    enfile(file, u);
    visite[u]=1; //On le marque comme visite

    //On initialise le compteur de distance


    while(!estFileVide(file)){
        int sommet_courant=defile(file);

        if (sommet_courant==v){
            free(visite);
            return visite[v];
        }

        Cellule_arete* voisin = g->T_som[sommet_courant]->L_voisin;

        while(voisin){
            int voisin_num=0;

            if(sommet_courant==v){
                voisin_num = voisin->a->u;
            } else {
                voisin_num = voisin->a->v;
            }
            if (visite[voisin_num]!=0){
                visite[voisin_num]=visite[u]+1; //On le marque comme visite
                enfile(file,voisin_num);
            }
            voisin=voisin->suiv;
        }
    }

    //Liberation de la memoire
    free(visite); 
    free(file);
    return -1; //Si on a pas atteint le sommet

}


//Question 3
ListeEntier * plusCourteChaineUV(Graphe* g, int u, int v){
    
    ListeEntier * res = (ListeEntier *)malloc(sizeof(ListeEntier));
    *res=NULL;

    //On initialise le file
    S_file* file = malloc(sizeof(S_file));
    if(file==NULL){
        exit(1);
    }
    Init_file(file);

    //Allocation
    int* visite=malloc(g->nbsom*sizeof(int));
    int* prec=malloc(g->nbsom*sizeof(int));

    //Si probleme d'allocation
    if(visite==NULL || prec==NULL){
        free(file);
        exit(1);
    }

    //On initialise le tableau des sommets visites
    //et le tableau prec qui sert a retourner le chemin entre u et v et remplir notre liste d'entiers
    for (int i=0; i<g->nbsom; i++){
        visite[i]=0;
        prec[i]= -1;
    }

    enfile(file,u);

    while(!estFileVide(file)){
        int sommet_courant = defile(file); 
        Cellule_arete* voisin = g->T_som[sommet_courant] -> L_voisin;

        while(voisin){
            int voisin_num = 0;

            //On choisit le bon arete entre u et v selon le sommet courant
            if(sommet_courant==v){
                voisin_num = voisin->a->u;
            } else {
                voisin_num = voisin->a->v;
            }
            //Verification si le voisin a déjà été visité et n'est pas le sommet de départ
            if(visite[voisin_num] == 0 && voisin_num != u){
                visite[voisin_num] = visite[sommet_courant] + 1;
                enfile(file,voisin_num);

                // Mise à jour du tableau prec pour stocker le père du voisin
                if(prec[v] == -1){ 
                    prec[v] = sommet_courant; //On enregistre le sommet courant comme pere
                }

                if(voisin_num == v){
                    int tmp = v;
                    
                    // Reconstruction de la chaîne du sommet v au sommet u en remontant les pères
                    while(prec[tmp] != -1){
                        ajoute_en_tete(res, tmp);
                        tmp = prec[tmp];
                    }

                    // Ajout du sommet de départ u à la tête de la liste
                    ajoute_en_tete(res,tmp);

                    while (!estFileVide(file)) {
                        defile(file);
                    }
                    free(file);

                    return res; //Renvoie la liste contenant la chaîne de sommets trouvee
                }
            }
            voisin = voisin->suiv;
        }

    }
    //Liberation de la memoire
    free(visite);
    free(prec);
    free(file);
    return NULL;
}

int reorganiseReseau(Reseau * r){

    Graphe * g = creerGraphe(r);

    //Initialisation de la matrice
    int ** matrice = (int **)malloc(((g -> nbsom) + 1) * sizeof(int*));
    if(matrice == NULL){
        libereGraphe(g);
        exit(1);
    }

    for (int i = 0; i < (g -> nbsom) + 1; i++){
        matrice[i] = (int *)malloc(((g -> nbsom) + 1) * sizeof(int));

        if(matrice[i] == NULL){
            for(int j = 0; j < i; i++){
                free(matrice[j]);
            }
            libereGraphe(g);
            free(matrice);
            exit(1);
        }
    }

    for(int i = 0; i < (g -> nbsom) + 1; i++){
        for(int j = 0; j < (g -> nbsom) + 1; j++){
            matrice[i][j] = 0;
        }
    }


    //Parcours de la table de commodites
    Commod * tabC = g -> T_commod;
    Commod k;
    for(int j = 0; j < g -> nbcommod; j++){
        k = tabC[j];

        ListeEntier * LEtemp = plusCourteChaineUV(g, k.e1, k.e2);
        ListeEntier parcours = *LEtemp;
        //Ajout des aretes dans la matrice
        while(parcours -> suiv != NULL){
            matrice[parcours->n][parcours->suiv->n]++;
            parcours = parcours -> suiv;
        }
        desalloue(LEtemp);
        free(LEtemp);
    }

    //Compte les aretes
    int aretes = 0;
    for (int m = 0; m < (g -> nbsom) + 1; m++){
        for(int n = m; n < (g -> nbsom) + 1; n++){
            aretes = matrice[m][n] + matrice[n][m];
            if(aretes > g -> gamma){
                libereMatrice(matrice, (g -> nbsom) + 1);
                libereGraphe(g);
                return 0;
            }
        }
    }

    libereMatrice(matrice, (g -> nbsom) + 1);
    libereGraphe(g);
    return 1;
}


void libereMatrice(int ** matrice, int taille){
    for(int i = 0; i < taille; i++){
        free(matrice[i]);
    }
    free(matrice);
}

void libereGraphe(Graphe * g){
    Sommet * s = NULL;
    Cellule_arete * caCurr = NULL;
    Cellule_arete * caPrec = NULL;

    //Liberation des sommets et des aretes
    for (int i = 1 ; i < g -> nbsom + 1 ; i++) {
        s = g -> T_som[i];
        caCurr = s -> L_voisin;

        while (caCurr) {
            //On libere l'arete si on la rencontre la premiere fois
            if (s -> num == (caCurr -> a -> u)) {
                free(caCurr -> a);
            }
            caPrec = caCurr;
            caCurr = caCurr -> suiv;
            free(caPrec);
        }

        free(s);
    }
    //Liberation de memoire
    free(g -> T_som);
    free(g -> T_commod);
    free(g);
}

void desalloue(ListeEntier *L){
  Entier *cour,*prec;
  cour=*L;
  while(cour!=NULL){
    prec=cour;
    cour=cour->suiv;
    free(prec);
  }
  *L=NULL;
}