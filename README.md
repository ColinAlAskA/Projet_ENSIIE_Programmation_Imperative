# Interpréteur graphique PPM

Projet de programmation en C réalisé en première année à l'ENSIIE.

## Description

L'objectif du projet est de concevoir et d'implémenter un interpréteur pour un langage graphique textuel. Le programme lit un fichier d'instructions, interprète les déplacements et les opérations graphiques, puis génère une image au format matriciel PPM.

La machine interprétée gère notamment :

- les déplacements d'un curseur sur une image carrée ;
- le mélange de doses de couleurs et d'opacités ;
- les calques superposés ;
- le remplissage de zones ;
- les rotations et les retours aux bords de l'image.

Le résultat obtenu est fonctionnel et produit des rendus très proches des résultats attendus. Une légère différence de couleur peut toutefois apparaître sur certains cas.

## Architecture

Le projet est organisé autour de plusieurs modules C :

- `projet.c` : point d'entrée du programme, lecture du fichier source et écriture de l'image PPM ;
- `machine.c` / `machine.h` : machine à états, position et direction du curseur, interprétation des instructions ;
- `pixel.c` / `pixel.h` : représentation et manipulation des pixels et des couleurs ;
- `couleur.c` / `couleur.h` : listes chaînées de couleurs et calcul de leur moyenne ;
- `opacite.c` / `opacite.h` : listes chaînées d'opacités et calcul de leur moyenne ;
- `pile.c` / `pile.h` : pile de calques et pile de positions utilisée notamment pour le remplissage ;
- `Makefile` : compilation et nettoyage des fichiers générés.

## Prérequis

- un compilateur C compatible avec GCC ;
- `make` ;
- un logiciel capable d'ouvrir les images PPM pour visualiser les résultats.

## Compilation

Depuis la racine du projet :

```sh
make
```

L'exécutable `projet_ppm` est alors généré.

Pour supprimer les fichiers objets produits pendant la compilation :

```sh
make clean
```

## Utilisation

Le fichier d'entrée doit contenir les instructions du langage graphique. Sa première ligne indique la taille de l'image carrée.

```sh
./projet_ppm <fichier_entree.ipi> <fichier_sortie.ppm>
```

Exemple :

```sh
./projet_ppm exemples_ipi_2022/simple.ipi resultat.ppm
```

Les fichiers d'exemples se trouvent dans `exemples_ipi_2022/`. Des images de référence sont également disponibles dans `images/`.

Le programme accepte aussi un seul fichier d'entrée et écrit alors l'image PPM sur la sortie standard :

```sh
./projet_ppm exemples_ipi_2022/simple.ipi > resultat.ppm
```

## Format de sortie

Les images générées utilisent le format PPM binaire `P6`, avec une valeur maximale de composante de couleur égale à `255`.

## Organisation du depot

```text
.
├── *.c, *.h             Sources du projet
├── Makefile             Compilation
├── exemples_ipi_2022/   Fichiers d'entrée et résultats de référence
├── images/              Images de référence
├── test1.ppm            Image de test
└── Coerchon_Colin_Rapport.pdf
```

Les fichiers générés par la compilation, les exécutables, les archives et les réglages locaux de VS Code sont ignorés par Git. Voir `.gitignore`.

## Contexte pedagogique

Ce projet a été réalisé dans le cadre du cours de programmation de première année à l'ENSIIE. Il met en pratique la programmation en C, la gestion dynamique de la mémoire, les listes chaînées, les piles et la décomposition d'un programme en modules.

## Auteur

Colin Coerchon - ENSIIE, première année
