#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"

list_c cons_c(list_c l, couleur e) {
    list_c ll = malloc(sizeof(struct maillon_c));
    ll -> val = e;
    ll -> next = l;
    return ll;
}

void add_c(list_c *l, couleur e) {
    *l = cons_c(*l, e);
}

void print_list_c(list_c l) {
    while (l!=NULL) {
        printf("-> [r : %d, v : %d, b : %d]", l->val.rouge, l->val.vert, l->val.bleu);
        l = l->next;
    }
    printf("-> []\n");
}

couleur moyenne_c(list_c l) {
    couleur res;
    couleur_noire(&res);
    int nb = 0;
    //printf("m.sceau_couleur = ");
    //print_list_c(l);
    while (l!=NULL) {
        couleur c = l->val;
        res.bleu += c.bleu;
        res.rouge += c.rouge;
        res.vert += c.vert;
        nb ++;
        l=l->next;
    }
    if (nb>=1) {
        res.bleu = res.bleu / nb;
        res.rouge = res.rouge / nb;
        res.vert = res.vert / nb;
    }
    return res;
}