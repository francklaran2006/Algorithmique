/*
 * Fichier: tuiles.h
 * Description: Gestion des tuiles et de la pioche pour le jeu Rummikub
 * Auteurs: [Votre Groupe]
 * Date: Décembre 2025
 */

#ifndef TUILES_H
#define TUILES_H

// Constantes pour les tuiles
#define NB_TUILES_TOTAL 106
#define NB_COULEURS 4
#define NB_VALEURS 13

// Structure pour représenter une tuile
typedef struct {
    int valeur;         // de 1 à 13, ou 0 pour un joker
    char couleur;       // 'J' pour jaune, 'R' pour rouge, 'N' pour noir, 'B' pour bleu
    int est_joker;      // 1 si c'est un joker, 0 sinon
    int id;             // identifiant unique de 0 à 105
} Tuile;

// Structure pour la pioche
typedef struct {
    Tuile tuiles[NB_TUILES_TOTAL];
    int nb_tuiles_restantes;
} Pioche;

// Fonctions pour gérer les tuiles
void creer_tuile(Tuile *t, int val, char coul, int identifiant);
void copier_tuile(Tuile *destination, Tuile *source);
void afficher_tuile(Tuile *t);

// Fonctions pour gérer la pioche
void initialiser_pioche(Pioche *p);
void creer_jeu_complet(Pioche *p);
void melanger_pioche(Pioche *p);
Tuile* piocher_tuile(Pioche *p);

// Fonction utilitaire
void echanger_deux_tuiles(Tuile *t1, Tuile *t2);

#endif