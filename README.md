Projet de programmation impérative réalisé en première année à l'ENSIIE.
Note finale : **17/20**

## Description

L'objectif du projet est de concevoir et d'implémenter un interpréteur pour un langage graphique textuel. Le programme lit un fichier d'instructions, interprète les déplacements et les opérations graphiques, puis génère une image au format matriciel PPM.

La machine interprétée gère notamment :

- les déplacements d'un curseur sur une image carrée ;
- le mélange de doses de couleurs et d'opacités ;
- les calques superposés ;
- le remplissage de zones ;
- les rotations et les retours aux bords de l'image.

Le résultat obtenu est fonctionnel et produit des rendus très proches des résultats attendus. Il y a juste une très légère différence de couleur qui peut arriver sur certaines images. Je n'ai malheureusement pas réussi à corriger cela avant le rendu du projet.

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
- un logiciel capable d'ouvrir les images PPM pour visualiser les résultats.

## Compilation

Depuis la racine du projet :

```sh
make
```

L'exécutable `projet_ppm` est alors généré.

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

Les images générées utilisent le format PPM binaire `P6`.

Un exemple : 

<img width="600" height="600" alt="best" src="https://github.com/user-attachments/assets/c3b12c70-521d-43db-bddc-f5288535f255" />

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

## Auteur

Colin Coërchon - ENSIIE, première année
