#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"

void couleur_noire(couleur *c) {
    c->rouge = 0;
    c->vert = 0;
    c->bleu = 0;
}

int egalite_couleur(couleur c1, couleur c2) {
    return(c1.rouge==c2.rouge && c1.vert==c2.vert && c1.bleu==c2.bleu);
}

pixel init_pixel() {
    pixel p;
    couleur_noire(&(p.c));
    p.op = 0;
    return p;
}

void print_pixel(pixel p) {
    printf("r = %d, v = %d, b = %d, op = %d\n",p.c.rouge,p.c.vert,p.c.bleu,p.op);
}

int egalite_pixel(pixel p1, pixel p2) {
    return(egalite_couleur(p1.c,p2.c) && p1.op==p2.op);
}