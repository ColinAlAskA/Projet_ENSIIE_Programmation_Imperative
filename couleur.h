#ifndef COULEUR_H
#define COULEUR_H
#include "pixel.h"

/* On définit le type "list_c" (liste de couleurs) */
typedef struct maillon_c* list_c;
struct maillon_c {
    couleur val;
    list_c next;
};

/* @requires : l est une liste de couleurs valide, e est une couleur valide
@assigns : rien
@ensures : Retourne la liste l dans laquelle on a rajouté la couleur e */
list_c cons_c(list_c l, couleur e);

/* @requires : l est un pointeur de liste de couleurs valide, e est une couleur valide
@assigns : l
@ensures : Ajoute à la liste l la couleur e */
void add_c(list_c *l, couleur e);

/* @requires : l est une liste de couleurs valide
@assigns : rien
@ensures : Affiche la liste l */
void print_list_c(list_c l);        // [ Fonction de débogage ]

/* @requires : l est une liste de couleurs valide
@assigns : rien
@ensures : Retourne la moyenne (composante par composante) des couleurs contenues dans l */
couleur moyenne_c(list_c l);

#endif