#ifndef MACHINE_H
#define MACHINE_H

#include "pixel.h"
#include "couleur.h"
#include "opacite.h"
#include "pile.h"

/* @requires : taille est un entier strictement positif
@assigns : rien
@ensures : Retourne un calque de taille (taille * taille) en allouant la mémoire nécessaire */
calque create_calque(int taille);

/* @requires : img est un calque valide, taille est un entier strictement positif
@assigns : img
@ensures : Libère le mémoire précedemment allouée pour le calque img */
void liberer_calque(calque img, int taille);

/* @requires : taille est un entier strictement positif
@assigns : rien
@ensures : Retourne un calque initialisé de taille (taille*taille) avec pour chacun de ses pixels :
0 pour chaque composante de couleur et 0 pour opacité*/
calque init_calque(int taille);

/* On définit le type machine [ TRES UTILE POUR LA SUITE ]*/
struct machine {
    int pos_courante[2];
    int pos_marquee[2];
    char* dir_curseur;
    list_c seau_couleur;
    list_op seau_opacite;
    pile pile_calque;
};
typedef struct machine machine;

/* @requires : taille est un entier strictement positif
@assigns : rien
@ensures : Retourne une machine initialisée comme décrit dans l'énoncé :
- les positions courante et marquée sont toutes les deux en (0,0) ;
- la direction est Est ;
- les seaux de couleurs et d'opacités sont vides tous les deux ;
- la pile contient un seul calque ; chaque pixel de ce calque est formé de la couleur (0,0,0) et de l'opacité 0.*/
machine init_machine(int taille);

#endif