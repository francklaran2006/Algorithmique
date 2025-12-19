#include <stdio.h>
#include "regles.h"

// Fonction pour initialiser une combinaison vide
void initialiser_combinaison(Combinaison *c) {
    c->nb_tuiles = 0;
    c->type = SUITE;
}

// Fonction pour ajouter une tuile à une combinaison
void ajouter_tuile_combinaison(Combinaison *c, Tuile *t) {
    if (c->nb_tuiles < MAX_TUILES_COMBINAISON) {
        copier_tuile(&c->tuiles[c->nb_tuiles], t);
        c->nb_tuiles++;
    } else {
        printf("Erreur: combinaison pleine\n");
    }
}

// Fonction pour afficher une combinaison
void afficher_combinaison(Combinaison *c) {
    int i;
    for (i = 0; i < c->nb_tuiles; i++) {
        afficher_tuile(&c->tuiles[i]);
        printf(" ");
    }
}

// Fonction pour vérifier si c'est une suite valide
// Une suite = 3 tuiles ou plus de même couleur et valeurs consécutives
int est_suite_valide(Combinaison *c) {
    if (c->nb_tuiles < 3) {
        return 0;
    }

    // On récupère la couleur de référence
    char couleur_ref = 'X';
    int i;
    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker == 0) {
            couleur_ref = c->tuiles[i].couleur;
            break;
        }
    }

    // Vérifier que toutes les tuiles ont la même couleur
    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker == 0) {
            if (c->tuiles[i].couleur != couleur_ref) {
                return 0;
            }
        }
    }

    // vérifier que les valeurs sont différentes

    int j;
    for (i = 0; i < c->nb_tuiles - 1; i++) {
        for (j = i + 1; j < c->nb_tuiles; j++) {
            if (c->tuiles[i].est_joker == 0 && c->tuiles[j].est_joker == 0) {
                if (c->tuiles[i].valeur == c->tuiles[j].valeur) {
                    return 0;
                }
            }
        }
    }

    return 1;  // c'est bon
}

// Fonction pour vérifier si c'est une série valide
// Une série = 3 ou 4 tuiles de même valeur mais couleurs différentes
int est_serie_valide(Combinaison *c) {
    // Il faut 3 ou 4 tuiles
    if (c->nb_tuiles < 3 || c->nb_tuiles > 4) {
        return 0;
    }

    // On récupère la valeur de référence
    int valeur_ref = -1;
    int i;
    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker == 0) {
            valeur_ref = c->tuiles[i].valeur;
            break;
        }
    }

    // Vérifier que toutes les tuiles ont la même valeur
    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker == 0) {
            if (c->tuiles[i].valeur != valeur_ref) {
                return 0;
            }
        }
    }

    // Vérifier que les couleurs sont différentes
    int couleurs_utilisees[4] = {0, 0, 0, 0};  // J, R, N, B
    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker == 0) {
            int index = -1;
            if (c->tuiles[i].couleur == 'J') index = 0;
            else if (c->tuiles[i].couleur == 'R') index = 1;
            else if (c->tuiles[i].couleur == 'N') index = 2;
            else if (c->tuiles[i].couleur == 'B') index = 3;

            if (couleurs_utilisees[index] == 1) {
                return 0;
            }
            couleurs_utilisees[index] = 1;
        }
    }

    return 1;
}

// Fonction pour vérifier si une combinaison est valide
int est_combinaison_valide(Combinaison *c) {
    // On teste si c'est une suite ou une série
    if (est_suite_valide(c)) {
        c->type = SUITE;
        return 1;
    }

    if (est_serie_valide(c)) {
        c->type = SERIE;
        return 1;
    }

    return 0;
}

// Fonction pour calculer les points d'une combinaison
int calculer_points_combinaison(Combinaison *c) {
    int total = 0;
    int i;

    for (i = 0; i < c->nb_tuiles; i++) {
        if (c->tuiles[i].est_joker) {
            // Pour le prototype on compte le joker comme 0
            // normalement il prend la valeur qu'il remplace
            total += 0;
        } else {
            total += c->tuiles[i].valeur;
        }
    }

    return total;
}

// Fonction pour initialiser le plateau
void initialiser_plateau(Plateau *p) {
    p->nb_combinaisons = 0;
}

// Fonction pour ajouter une combinaison au plateau
void ajouter_combinaison_plateau(Plateau *p, Combinaison *c) {
    if (p->nb_combinaisons < 50) {
        // On copie toute la combinaison
        p->combinaisons[p->nb_combinaisons] = *c;
        p->nb_combinaisons++;
        printf("Combinaison ajoutee au plateau\n");
    }
}

// Fonction pour afficher le plateau
void afficher_plateau(Plateau *p) {
    if (p->nb_combinaisons == 0) {
        printf("(vide)\n");
    } else {
        int i;
        for (i = 0; i < p->nb_combinaisons; i++) {
            printf("Comb %d: ", i + 1);
            afficher_combinaison(&p->combinaisons[i]);
            printf("\n");
        }
    }

}
