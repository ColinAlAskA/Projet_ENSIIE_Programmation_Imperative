#ifndef PILE_H
#define PILE_H

#define MAX 10      // Une pile de calque ne peut prendre que 10 calques d'après l'énoncé.

#include "pixel.h"

/* On définit le type "pile" (pile de calque)*/
struct pile {
    calque content[MAX];
    int top;
};
typedef struct pile pile;

/* @requires : p est un pointeur de pile valide, e est un calque valide
@assigns : p
@ensures : Ajoute le calque e à la pile p */
void push(pile *p, calque e);

/* @requires : p est un pointeur de pile valide
@assigns : p
@ensures : Retire et retourne le calque e situé au sommet de la pile p */
calque pop(pile *p);



/* La suite est utile uniquement pour la version évoluée de la fonction remplissage ('fill') */

/* On définit le type "pos" */
struct pos {
    int x;
    int y;
};
typedef struct pos pos;

/* On définit le type pile_pos (pile de positions de type "pos") : c'est une pile dynamique */
struct pile_pos {
    pos *data;
    int top;
    int size;
};
typedef struct pile_pos pile_pos;

/* @requires : taille est un entier strictement positif
@assigns : rien
@ensures : Retourne un pointeur de pile de positions de taille initiale "taille" */
pile_pos *creer_pile_pos(int taille);

/* @requires : pile est un pointeur de pile valide
@assigns : rien
@ensures : Retourne 1 si la pile est vide (pile->top == -1) */
int pile_pos_vide(pile_pos *pile);

/* @requires : pile est un pointeur de pile valide
@assigns : rien
@ensures : Retourne 1 si la pile est pleine (pile->top == pile->size -1) */
int pile_pos_pleine(pile_pos *pile);

/* @requires : pile est un pointeur de pile valide
@assigns : pile
@ensures : libère la mémoire allouée pour la pile */
void detruire_pile_pos(pile_pos *pile);

/* @requires : pile est un pointeur de pile valide, pos est une position valide
@assigns : pile
@ensures : Ajoute la position pos à la pile */
void push_pos(pile_pos *pile, pos pos);

/* @requires : pile est un pointeur de pile valide
@assigns : pile
@ensures : Retire et retourne la position située au sommet de la pile */
pos pop_pos(pile_pos *pile);

#endif