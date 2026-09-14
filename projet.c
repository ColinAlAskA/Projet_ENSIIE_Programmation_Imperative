#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // Utile pour la fonction strcmp
#include <stdbool.h>    // Utile pour construire un tableau de booléen dans la fonction remplissage ("fill")
#include <math.h>

#include "machine.h"

/* @requires : sceau_c et sceau_op sont respectivement des sceaux de couleurs et d'opacités valides
@assigns : rien
@ensures : Le calcul du pixel courant en fonction du contenu du sceau de couleur et du sceau d'opacité */
pixel pixel_courant(list_c sceau_c, list_op sceau_op) {
    opacite op_courante = moyenne_op(sceau_op);         // cf. couleur.h
    couleur c_courante = moyenne_c(sceau_c);            // cf. opacite.h
    c_courante.bleu *= op_courante/255;
    c_courante.rouge *= op_courante/255;
    c_courante.vert *= op_courante/255;

    pixel p;
    p.c = c_courante;
    p.op = op_courante;
    return p;
}

/* @requires : pos est un tableau d'entiers à 2 entrées, taille est un entier strictement positif
@assigns : pos
@ensures : Avance la position du curseur d'un pas dans la direction courante ; si le bord de l'image est atteint, on repasse de l'autre coté.*/
void deplacement_curseur(int pos[2], char* dir, int taille) {
    if (!( strcmp(dir,"Nord") || strcmp(dir,"Sud") || strcmp(dir,"Est") || strcmp(dir,"Ouest") ))
        printf("La direction n'existe pas\n");
    else {
        switch (dir[0])
        {
        case 'N':
            if (pos[0]!=0) (pos[0])--;
            else pos[0] = taille-1;
            break;
        case 'S':
            if (pos[0]<taille-1) (pos[0])++;
            else pos[0] = 0;
            break;
        case 'E':
            if (pos[1]<taille-1) (pos[1])++;
            else pos[1] = 0;
            break;
        case 'O':
            if (pos[1]!=0) (pos[1])--;
            else pos[1] = taille-1;
            break;
        default:
            printf("La direction n'existe pas\n");
            break;
        }
    }
}


/* @requires : direction est un pointeur de chaine de caractères valide, sens vaut soit 'h' soit 'a'
@assigns : direction
@ensures : Tourne la direction courante ("direction") dans le sens horaire ('h') ou dans le sens anti-horaire ('a') */
void tourner_dir(char** direction, char sens) {
    char* dir = *direction;
    if (!( strcmp(dir,"Nord") || strcmp(dir,"Sud") || strcmp(dir,"Est") || strcmp(dir,"Ouest") ))
        printf("La direction n'existe pas\n");
    else {
        if (sens=='h') {    // sens = 'h' : On tourne dans le sens horaire
            switch (dir[0])
            {
            case 'N':
                dir = "Est";
                break;
            case 'S':
                dir = "Ouest";
                break;
            case 'E':
                dir = "Sud";
                break;
            case 'O':
                dir = "Nord";
                break;
            default:
                printf("La direction n'existe pas\n");
                break;
            }
        }
        else {               // sens = 'a' : On tourne dans le sens anti-horaire (trigonométrique)
            switch (dir[0])
            {
            case 'N':
                dir = "Ouest";
                break;
            case 'S':
                dir = "Est";
                break;
            case 'E':
                dir = "Nord";
                break;
            case 'O':
                dir = "Sud";
                break;
            default:
                printf("La direction n'existe pas\n");
                break;
            }
        }
    }
    *direction = dir;       // Ligne de code CRUCIALE : elle permet de modifier la valeur de la variable à laquelle pointe "direction"
}


/* @requires : pos1 et pos2 sont des tableaux d'entiers à 2 entrées, p_courant est un pixel valide, img est un calque valide
@assigns : img
@ensures : Trace une ligne sur img entre la position du curseur ("pos0") et la position marquée ("pos1") */
void tracer_ligne(int pos0[2], int pos1[2], pixel p_courant, calque img) {
    int delta_x = pos1[0] - pos0[0];
    int delta_y = pos1[1] - pos0[1];
    int d, s, x, y;
    if (abs(delta_x)>abs(delta_y)) d=abs(delta_x);
    else d=abs(delta_y);
    if (delta_x*delta_y > 0) s=0;   // "delta_x*delta_y>0" verifie bien la condition "non nuls et de meme signe"
    else s=1;

    x = pos0[0]*d + (d-s)/2;
    y = pos0[1]*d + (d-s)/2;

    for (int i=0; i<d; i++) {
        img[x/d][y/d]=p_courant;
        x+=delta_x;
        y+=delta_y;
    }
    img[pos1[0]][pos1[1]]=p_courant;
}


/* Methode naïve en récursive */

/* @requires : x et y sont des entiers tels que 0 <= x,y < taille, ancien et nouveau sont de pixels valides,
img est un calque valide, taille est un entier strictement positif
@assigns : img
@ensures : Remplit la zone de même couleur (couleur de "ancien") autour du curseur ((x,y)),
en la remplaçant par la couleur courante (couleur de "nouveau") */

// void remplissage(int x, int y, pixel ancien, pixel nouveau, calque img, int taille) {
//     int test = 1;
//     while (test) {
//         if (!egalite_pixel(img[x][y],ancien)) test = 0;
//         else {
//             img[x][y] = nouveau;
//             if (x>0) remplissage(x-1,y,ancien,nouveau,img,taille);
//             if (y>0) remplissage(x,y-1,ancien,nouveau,img,taille);
//             if (x<taille-1) remplissage(x+1,y,ancien,nouveau,img,taille);
//             if (y<taille-1) remplissage(x,y+1,ancien,nouveau,img,taille);
//         }
//     }
// }


/* Methode avec une pile explicite de positions */

/* @requires : x et y sont des entiers tels que 0 <= x,y < taille, ancien et nouveau sont de pixels valides,
img est un calque valide, taille est un entier strictement positif
@assigns : img
@ensures : Remplit la zone de même couleur (couleur de "ancien") autour du curseur ((x,y)),
en la remplaçant par la couleur courante (couleur de "nouveau") */
void remplissage(int x, int y, pixel ancien, pixel nouveau, calque img, int taille) {
    // On utilise un tableau de booléens pour repérer sur l'image les endroits déjà parcourus dans la boucle
    bool traites[taille][taille];
    memset(traites, false, taille * taille * sizeof(bool));     // On initialise le tableau sur false pour chaque pixel avec "memset"
    pile_pos *p = creer_pile_pos(taille * taille);              // cf. pile.h
    push_pos(p, (pos){x, y});

    while (!pile_pos_vide(p)) {
        pos n = pop_pos(p);
        if (traites[n.x][n.y]) continue;    // Si la case a déjà était traitée, on "continue" : on interrompt l'exécution de l'itération en cours de la boucle while
        traites[n.x][n.y] = true;           // Si jamais parcourue, la case prend alors la valeur "true" dans le tableau
        img[n.x][n.y] = nouveau;
        pos voisins[4] = {{n.x - 1, n.y}, {n.x + 1, n.y}, {n.x, n.y - 1}, {n.x, n.y + 1}};
        for (int i = 0; i < 4; i++) {
            int x = voisins[i].x;
            int y = voisins[i].y;
            if (x >= 0 && x < taille && y >= 0 && y < taille && !traites[x][y] && egalite_pixel(img[x][y], ancien)) {
                // On empile les voisins de la case s'ils sont de même couleur, s'ils n'ont pas déjà été traitées et s'ils restent dans les dimensions de l'image
                push_pos(p, voisins[i]);
            }
        }
    }
    detruire_pile_pos(p);       // Une fois utilsée, on libère la mémoire allouée
}

/* @requires : p est un pointeur de pile valide, taille est un entier strictement positif
@assigns : p
@ensures : Fusionne les deux calques les plus hauts dans la pile, il y aura donc un calque de moins dans la pile ;
s'il n'y a qu'un seul calque, ne fait rien. */
void fusion(pile *p, int taille) {
  if (p->top > 1) {
    calque c0 = pop(p);
    calque c1 = pop(p);
    for(int i = 0 ; i < taille; i++) {
      for(int j = 0; j < taille; j++) {
        pixel p0 = c0[i][j];
        pixel p1 = c1[i][j];
        composante r = p0.c.rouge + (p1.c.rouge * (255 - p0.op)/255);
        composante v = p0.c.vert + (p1.c.vert * (255 - p0.op)/255);
        composante b = p0.c.bleu + (p1.c.bleu * (255 - p0.op)/255);
        couleur c = {r, v, b};
        opacite op = p0.op + p1.op * (255 - p0.op)/255;
        c0[i][j].c = c;
        c0[i][j].op = op;
      }
    }
    push(p, c0);                    // Une fois fusionné, on remet le calque obtenue dans la pile
    liberer_calque(c1, taille);     // Une fois utilsé, on libère la mémoire allouée
  }
}

/* @requires : p est un pointeur de pile valide, taille est un entier strictement positif
@assigns : p
@ensures : Découpe le calque situé juste en dessous du sommet de la pile en utilisant comme masque les opacités de celui au sommet ;
 retire celui au sommet ; s'il n'y a qu'un seul calque, ne fait rien.*/
void decoupe(pile *p, int taille) {
    if (p->top > 1) {
        calque c0 = pop(p);
        calque c1 = pop(p);
        for(int i = 0 ; i<taille; i++) {
            for(int j = 0; j<taille; j++) {
                pixel p0 = c0[i][j];
                pixel p1 = c1[i][j];
                composante r = (p1.c.rouge * p0.op) /255;
                composante v = (p1.c.vert * p0.op) /255;
                composante b = (p1.c.bleu * p0.op) /255;
                couleur c = {r,v,b};
                opacite op = (p1.op * p0.op) /255;
                c0[i][j].c = c;
                c0[i][j].op = op;
            }
        }
        push(p,c0);                     // Une fois decoupé, on remet le calque obtenue dans la pile
        liberer_calque(c1,taille);      // Une fois utilsé, on libère la mémoire allouée
    }
}

/* @requires : m est un pointeur de machine valide, taille est un entier strictement positif
@assigns : m
@ensures : Modifie les différents paramètres (son état) de la machine m en fonction des ordres dictés par le caractère s */
void modif_etat(machine *m, char s, int taille) {
    switch (s)
    {
    case 'n': ;     // ";" pour eviter l'erreur "a label can only be part of a statement and a declaration is not a statement"
        couleur c;
        couleur_noire(&c);
        add_c(&(m->seau_couleur),c);
        break;
    case 'r':
        c.rouge = 255;
        c.vert = 0;
        c.bleu = 0;
        add_c(&(m->seau_couleur),c);
        break;
    case 'g':
        c.rouge = 0;
        c.vert = 255;
        c.bleu = 0;
        add_c(&(m->seau_couleur),c);
        break;
    case 'b':
        c.rouge = 0;
        c.vert = 0;
        c.bleu = 255;
        add_c(&(m->seau_couleur),c);
        break;
    case 'y':
        c.rouge = 255;
        c.vert = 255;
        c.bleu = 0;
        add_c(&(m->seau_couleur),c);
        break;
    case 'm':
        c.rouge = 255;
        c.vert = 0;
        c.bleu = 255;
        add_c(&(m->seau_couleur),c);
        break;
    case 'c':
        c.rouge = 0;
        c.vert = 255;
        c.bleu = 255;
        add_c(&(m->seau_couleur),c);
        break;
    case 'w':
        c.rouge = 255;
        c.vert = 255;
        c.bleu = 255;
        add_c(&(m->seau_couleur),c);
        break;
    case 't':
        add_op(&(m->seau_opacite),0);
        break;
    case 'o':
        add_op(&(m->seau_opacite),255);
        break;
    case 'i':
        m->seau_couleur = NULL;
        m->seau_opacite = NULL;
        break;
    case 'v':
        deplacement_curseur(m->pos_courante,m->dir_curseur,taille);
        break;
    case 'h':
        tourner_dir(&(m->dir_curseur),'h');
        break;
    case 'a':
        tourner_dir(&(m->dir_curseur),'a');
        break;
    case 'p':
        m->pos_marquee[0] = m->pos_courante[0];
        m->pos_marquee[1] = m->pos_courante[1];
        break;
    case 'l': ;     // idem que 'n'
        pixel p_courant = pixel_courant(m->seau_couleur,m->seau_opacite);
        pile p = m->pile_calque;
        tracer_ligne(m->pos_courante,m->pos_marquee,p_courant,p.content[p.top -1]);
        break;
    case 'f': ;     // idem que 'n'
        int x = m->pos_courante[0];
        int y = m->pos_courante[1];
        p = m->pile_calque;
        calque img = p.content[p.top -1];
        pixel ancien = img[x][y];
        pixel nouveau = pixel_courant(m->seau_couleur,m->seau_opacite);
        if (!egalite_pixel(img[x][y],nouveau))
            remplissage(x,y,ancien,nouveau,img,taille);
        break;
    case 's':
        push(&(m->pile_calque),init_calque(taille));
        break;
    case 'e':
        fusion(&(m->pile_calque),taille);
        break;
    case 'j':
        decoupe(&(m->pile_calque),taille);
        break;

    default:    // Le caractère s est dans ce cas ignoré.
        //printf("le caractere %c est ignoré\n",s);
        break;
    }
}

int main(int argc, char* argv[]) {

    int taille;
    char buf[256];

    if (argc == 1) {    // Cas : 0 argument

        fgets(buf,256,stdin);                                       // On récupère la première ligne de l'entrée standard (stdin) dans le buffer
        sscanf(buf,"%d",&taille);                                   // On récupère l'entier écrit dans le buffer pour que "taille" pointe vers lui

        machine m = init_machine(taille);                           // On initialise la machine (cf. machine.h)
        
        char c;
        while((c = getc(stdin)) != EOF) {                           // Le GROS du programme, on parcourt l'ensemble des caractères du stdin et on modifie à chaque itération la machine m
            modif_etat(&m,c,taille);
        }

        calque image_finale = pop(&(m.pile_calque));                // On récupère l'image finale (qui correspond au sommet de la pile de calque)
        
        fprintf (stdout, "P6\n%d %d\n255\n",taille,taille);         // Pour écrire l'en-tête du fichier PPM dans la sortie standard (stdout)

        for (int i = 0; i < taille; i++) {                          // On écrit dans stdout compasante par composante de chaque pixel grâce à fwrite
            for (int j = 0; j < taille; j++) {
                fwrite(&image_finale[i][j].c.rouge, 1, 1, stdout);
                fwrite(&image_finale[i][j].c.vert, 1, 1, stdout);
                fwrite(&image_finale[i][j].c.bleu, 1, 1, stdout);
            }
        }
        liberer_calque(image_finale,taille);                        // On libère la mémoire précedemment allouée pour l'image finale
    }

    if (argc == 2) {    // Cas : 1 argument

        FILE *f1 = fopen(argv[1], "r");                             // On ouvre le fichier placé en premier arguement en lecture seule
        if(f1==NULL){
            fprintf(stderr,"can't open the source file\n");
            exit(1);
        }

        fgets(buf,256,f1);                                          // On récupère la première ligne du fichier f1 dans le buffer
        sscanf(buf,"%d",&taille);                                   // On récupère l'entier écrit dans le buffer pour que "taille" pointe vers lui

        machine m = init_machine(taille);                           // On initialise la machine (cf. machine.h)
        
        char c;
        while((c = getc(f1)) != EOF) {                              // Le GROS du programme, on parcourt l'ensemble des caractères de f1 et on modifie à chaque itération la machine m
            modif_etat(&m,c,taille);
        }

        calque image_finale = pop(&(m.pile_calque));                // On récupère l'image finale (qui correspond au sommet de la pile de calque)
        
        fprintf(stdout, "P6\n%d %d\n255\n",taille,taille);          // Pour écrire l'en-tête du fichier PPM dans la sortie standard (stdout)

        for (int i = 0; i < taille; i++) {                          // On écrit dans stdout compasante par composante de chaque pixel grâce à fwrite
            for (int j = 0; j < taille; j++) {
                fwrite(&image_finale[i][j].c.rouge, 1, 1, stdout);
                fwrite(&image_finale[i][j].c.vert, 1, 1, stdout);
                fwrite(&image_finale[i][j].c.bleu, 1, 1, stdout);
            }
        }
        liberer_calque(image_finale,taille);                        // On libère la mémoire précedemment allouée pour l'image finale

        // Fermeture du fichier f1
        fclose(f1);
    }

    if (argc >= 3) {    // Cas : 2 arguments et plus

        if (argc > 3) { // Petit avertissement si 3 arguments et plus
            fprintf(stderr, "Attention, l'exécutable %s prend au maximum 2 arguments. Les autres seront ignorés.", argv[0]);
        }

        FILE *f1 = fopen(argv[1], "r");                             // On ouvre le fichier placé en premier argument en lecture seule
        if(f1==NULL){
            fprintf(stderr,"can't open the source file\n");
            exit(1);
        }

        fgets(buf,256,f1);                                          // On récupère la première ligne du fichier f1 dans le buffer
        sscanf(buf,"%d",&taille);                                   // On récupère l'entier écrit dans le buffer pour que "taille" pointe vers lui

        machine m = init_machine(taille);                           // On initialise la machine (cf. machine.h)

        char c;
        while((c = getc(f1)) != EOF) {                              // Le GROS du programme, on parcourt l'ensemble des caractères de f1 et on modifie à chaque itération la machine m
            modif_etat(&m,c,taille);
        }

        calque image_finale = pop(&(m.pile_calque));                // On récupère l'image finale (qui correspond au sommet de la pile de calque)

        FILE *f2 = fopen(argv[2], "wb");                            // On ouvre le fichier placé en premier argument en écriture binaire
        if(f2==NULL) {
            fprintf(stderr,"Cannot open output file\n");
            fclose(f1);
            return 1;
        }
        
        fprintf (f2, "P6\n%d %d\n255\n",taille,taille);             // Pour écrire l'en-tête du fichier PPM dans le fichier f2

        for (int i = 0; i < taille; i++) {                          // On écrit dans f2 compasante par composante de chaque pixel grâce à fwrite
            for (int j = 0; j < taille; j++) {
                fwrite(&image_finale[i][j].c.rouge, 1, 1, f2);
                fwrite(&image_finale[i][j].c.vert, 1, 1, f2);
                fwrite(&image_finale[i][j].c.bleu, 1, 1, f2);
            }
        }
        liberer_calque(image_finale,taille);                        // On libère la mémoire précedemment allouée pour l'image finale

        // Fermeture des fichiers
        fclose(f1);
        fclose(f2);
    }

    return 0;
}