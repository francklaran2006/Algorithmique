/*
 * Fichier: tuiles.c
 * Description: Implémentation des fonctions pour les tuiles
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tuiles.h"

// Fonction pour créer une tuile avec les paramètres donnés
void creer_tuile(Tuile *t, int val, char coul, int identifiant) {
    t->valeur = val;
    t->couleur = coul;
    t->id = identifiant;
    
    // Si la valeur est 0, c'est un joker
    if (val == 0) {
        t->est_joker = 1;
    } else {
        t->est_joker = 0;
    }
}

// Fonction pour copier une tuile dans une autre
void copier_tuile(Tuile *destination, Tuile *source) {
    destination->valeur = source->valeur;
    destination->couleur = source->couleur;
    destination->est_joker = source->est_joker;
    destination->id = source->id;
}

// Fonction pour afficher une tuile dans le terminal
void afficher_tuile(Tuile *t) {
    if (t->est_joker == 1) {
        printf("[JOKER]");
    } else {
        printf("[%2d%c]", t->valeur, t->couleur);
    }
}

// Fonction pour initialiser une pioche vide
void initialiser_pioche(Pioche *p) {
    p->nb_tuiles_restantes = 0;
    
    // On met toutes les tuiles à zéro au début
    int i;
    for (i = 0; i < NB_TUILES_TOTAL; i++) {
        creer_tuile(&p->tuiles[i], 0, 'X', i);
    }
}

// Fonction pour créer un jeu complet de Rummikub
// Il y a 104 tuiles normales (2 exemplaires de chaque) + 2 jokers
void creer_jeu_complet(Pioche *p) {
    int compteur = 0;  // pour compter les tuiles créées
    char couleurs[4] = {'J', 'R', 'N', 'B'};  // les 4 couleurs
    
    // On fait 2 exemplaires de chaque tuile
    int exemplaire;
    for (exemplaire = 0; exemplaire < 2; exemplaire++) {
        // Pour chaque couleur
        int c;
        for (c = 0; c < 4; c++) {
            // Pour chaque valeur de 1 à 13
            int v;
            for (v = 1; v <= 13; v++) {
                creer_tuile(&p->tuiles[compteur], v, couleurs[c], compteur);
                compteur++;
            }
        }
    }
    
    // On ajoute les 2 jokers à la fin
    creer_tuile(&p->tuiles[compteur], 0, 'X', compteur);
    compteur++;
    creer_tuile(&p->tuiles[compteur], 0, 'X', compteur);
    compteur++;
    
    p->nb_tuiles_restantes = compteur;  // Devrait être 106
    
    printf("Jeu cree: %d tuiles\n", p->nb_tuiles_restantes);
}

// Fonction pour échanger deux tuiles (utile pour le mélange)
void echanger_deux_tuiles(Tuile *t1, Tuile *t2) {
    Tuile temp;
    copier_tuile(&temp, t1);
    copier_tuile(t1, t2);
    copier_tuile(t2, &temp);
}

// Fonction pour mélanger la pioche (algorithme de Fisher-Yates)
void melanger_pioche(Pioche *p) {
    // On initialise le générateur de nombres aléatoires
    srand(time(NULL));
    
    // On mélange en partant de la fin
    int i;
    for (i = p->nb_tuiles_restantes - 1; i > 0; i--) {
        // On choisit un index aléatoire entre 0 et i
        int j = rand() % (i + 1);
        
        // On échange les tuiles
        echanger_deux_tuiles(&p->tuiles[i], &p->tuiles[j]);
    }
    
    printf("Pioche melangee\n");
}

// Fonction pour piocher une tuile de la pioche
Tuile* piocher_tuile(Pioche *p) {
    // Si il n'y a plus de tuiles
    if (p->nb_tuiles_restantes <= 0) {
        printf("La pioche est vide!\n");
        return NULL;
    }
    
    // On prend la dernière tuile (c'est plus simple)
    p->nb_tuiles_restantes--;
    
    // On retourne un pointeur vers cette tuile
    return &p->tuiles[p->nb_tuiles_restantes];
}