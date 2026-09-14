#ifndef OPACITE_H
#define OPACITE_H
#include "pixel.h"

/* On définit le type "list_op"s (liste d'opacités) */
typedef struct maillon_op* list_op;
struct maillon_op {
    opacite val;
    list_op next;
};

/* @requires : l est une liste d'opacités valide, e est une opacité valide
@assigns : rien
@ensures : Retourne la liste l dans laquelle on a rajouté l'opacité e */
list_op cons_op(list_op l, opacite e);

/* @requires : l est un pointeur de liste d'opacités valide, e est une opacité valide
@assigns : l
@ensures : Ajoute à la liste l l'opacité e */
void add_op(list_op *l, opacite e);

/* @requires : l est une liste d'opacités valide
@assigns : rien
@ensures : Affiche la liste l */
void print_list_op(list_op l);       // [ Fonction de débogage ]

/* @requires : l est une liste d'opacités valide
@assigns : rien
@ensures : Retourne la moyenne des opacités contenues dans l */
opacite moyenne_op(list_op l);

#endif