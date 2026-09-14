#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

void push(pile *p, calque e) {
    if (p->top < MAX) { 
        p->content[p->top] = e;
        p->top ++;
    }
}

calque pop(pile *p) {
    if (p->top<=0) printf("WARNING, la pile est vide");
    else {
        calque res = p->content[p->top -1];
        p->top --;
        return res;
    }
    return 0;
}

pile_pos *creer_pile_pos(int taille) {
    pile_pos *pile = malloc(sizeof(pile_pos));
    pile->data = malloc(taille * sizeof(pos));
    pile->top = -1;
    pile->size = taille;
    return pile;
}

int pile_pos_vide(pile_pos *pile) {
    return pile->top == -1;
}

int pile_pos_pleine(pile_pos *pile) {
    return pile->top == pile->size - 1;
}

void detruire_pile_pos(pile_pos *pile) {
    free(pile->data);
    free(pile);
}

void push_pos(pile_pos *pile, pos pos) {
    if (pile_pos_pleine(pile)) {
        int nouvelle_taille = pile->size * 2;
        pile->data = realloc(pile->data, nouvelle_taille * sizeof(pos));
        pile->size = nouvelle_taille;
    }
    pile->data[++pile->top] = pos;
}

pos pop_pos(pile_pos *pile) {
    if (pile_pos_vide(pile)) {
        fprintf(stderr, "Erreur : pile vide\n");
        exit(1);
    }
    return pile->data[pile->top--];
}
