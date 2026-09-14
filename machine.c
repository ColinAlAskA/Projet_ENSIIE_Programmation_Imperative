#include<stdio.h>
#include<stdlib.h>

#include "machine.h"

calque create_calque(int taille) {
    calque img = malloc(taille*sizeof(pixel *));
    for(int i = 0; i < taille; i++)
        img[i] = malloc(taille*sizeof(pixel));
    return img;
};

void liberer_calque(calque img, int taille) {
    for (int i=0; i<taille; i++) {
        free(img[i]);
    }
    free(img);
}

calque init_calque(int taille) {
    calque img = create_calque(taille);
    for(int i = 0 ; i<taille; i++) {
        for(int j = 0; j<taille; j++) {
            img[i][j] = init_pixel();
        }
    }
    return img;
}

machine init_machine(int taille) {
    machine m;
    m.pos_courante[0] = 0;
    m.pos_courante[1] = 0;
    m.pos_marquee[0] = 0;
    m.pos_marquee[1] = 0;
    m.dir_curseur = malloc(sizeof(char*));
    m.dir_curseur = "Est";
    m.seau_couleur = NULL;
    m.seau_opacite = NULL;
    pile p;
    p.content[0] = init_calque(taille); p.top = 1;   // p.top = 0 si la pile est vide
    m.pile_calque = p;
    return m;
}