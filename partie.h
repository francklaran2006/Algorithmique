/*
 * Fichier: partie.h
 * Description: Gestion d'une partie complète de Rummikub
 * Auteurs: [Votre Groupe]
 * Date: Décembre 2025
 */

#ifndef PARTIE_H
#define PARTIE_H

#include "tuiles.h"
#include "joueur.h"
#include "regles.h"

#define MAX_JOUEURS 4
#define TUILES_DEBUT 14  // chaque joueur commence avec 14 tuiles

// Structure pour une partie
typedef struct {
    Joueur joueurs[MAX_JOUEURS];
    int nb_joueurs;
    Pioche pioche;
    Plateau plateau;
    int joueur_actuel;  // l'index du joueur qui joue (0, 1, 2 ou 3)
    int partie_finie;   // 1 si la partie est terminée, 0 sinon
} Partie;

// Fonctions pour la partie
void initialiser_partie(Partie *p, int nombre_joueurs);
void distribuer_tuiles_debut(Partie *p);
void jouer_tour(Partie *p);
void afficher_etat_partie(Partie *p);

// Fonction pour passer au joueur suivant
void passer_joueur_suivant(Partie *p);

// Fonction pour vérifier si la partie est finie
int verifier_victoire(Partie *p);

#endif