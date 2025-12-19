

#ifndef JOUEUR_H
#define JOUEUR_H
#include "tuiles.h"



// Structure joueur
typedef struct {
    char pseudo[50];
    Tuile chevalet[106];
    int nb_tuiles;
    int score;
    int pose_30points;  // 1 s'il a déjà posé 30 points au début, sino 0
} Joueur;


void initialiser_joueur(Joueur *j, char *nom);
void ajouter_tuile_joueur(Joueur *j, Tuile *t);
void afficher_chevalet(Joueur *j);
void retirer_tuile_joueur(Joueur *j, int index);
int calculer_score_joueur(Joueur *j);

#endif
