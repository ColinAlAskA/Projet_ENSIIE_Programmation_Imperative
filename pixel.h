#ifndef PIXEL_H
#define PIXEL_H

typedef unsigned int composante;
typedef composante opacite;

/* On définit le type "couleur" */
struct couleur {
    composante rouge;
    composante vert;
    composante bleu;
};
typedef struct couleur couleur;

/* @requires : c est un pointeur de couleur valide
@assigns : c
@ensures : Assigne 0 à chaque composante de c (couleur noire) */
void couleur_noire(couleur *c);

/* @requires : c1 et c2 sont deux couleurs valides
@assigns : rien
@ensures : Retourne 1 si chaque composante de c1 et c2 sont identiques */
int egalite_couleur(couleur c1, couleur c2);

/* On définit le type "pixel" */
struct pixel {
    couleur c;
    opacite op;
};
typedef struct pixel pixel;

/* @requires : rien
@assigns : rien
@ensures : retourne un pixel initilalisé à 0 pour chaque composante de couleur et 0 pour opacité */
pixel init_pixel();

/* @requires : p est un pixel valide
@assigns : rien
@ensures : affiche le pixel p */
void print_pixel(pixel p);          // [ Fonction de débogage ]

/* @requires : p1 et p2 sont des pixels valides
@assigns : rien
@ensures : Retourne 1 si égalité des couleurs et égalité des opacités */
int egalite_pixel(pixel p1, pixel p2);

/* On définit le type "calque" */
typedef pixel** calque;

#endif