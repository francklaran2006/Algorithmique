/*
 * Fichier: regles.h
 * Description: Gestion des règles du jeu (combinaisons, validations)
 * Auteurs: [Votre Groupe]
 * Date: Décembre 2025
 */

#ifndef REGLES_H
#define REGLES_H

#include "tuiles.h"

#define MAX_TUILES_COMBINAISON 13

// Type de combinaison
typedef enum {
    SUITE = 0,    // exemple: 3-4-5 de même couleur
    SERIE = 1     // exemple: 7 de 3 couleurs différentes
} TypeCombinaison;

// Structure pour une combinaison de tuiles
typedef struct {
    Tuile tuiles[MAX_TUILES_COMBINAISON];
    int nb_tuiles;
    TypeCombinaison type;
} Combinaison;

// Structure pour le plateau de jeu
typedef struct {
    Combinaison combinaisons[50];  // maximum 50 combinaisons
    int nb_combinaisons;
} Plateau;

// Fonctions pour les combinaisons
void initialiser_combinaison(Combinaison *c);
void ajouter_tuile_combinaison(Combinaison *c, Tuile *t);
void afficher_combinaison(Combinaison *c);

// Fonctions de validation
int est_suite_valide(Combinaison *c);
int est_serie_valide(Combinaison *c);
int est_combinaison_valide(Combinaison *c);
int calculer_points_combinaison(Combinaison *c);

// Fonctions pour le plateau
void initialiser_plateau(Plateau *p);
void ajouter_combinaison_plateau(Plateau *p, Combinaison *c);
void afficher_plateau(Plateau *p);

#endif