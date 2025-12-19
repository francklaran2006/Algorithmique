

#include <stdio.h>
#include <string.h>
#include "joueur.h"

void initialiser_joueur(Joueur *j, char *nom) {
    strcpy(j->pseudo, nom);


    j->nb_tuiles = 0;
    j->score = 0;
    j->pose_30points = 0;

    printf("Joueur %s initialisé\n", j->pseudo);
}

void ajouter_tuile_joueur(Joueur *j, Tuile *t) {
    if (j->nb_tuiles < 106) {
        copier_tuile(&j->chevalet[j->nb_tuiles], t);
        j->nb_tuiles++;
    } else {
        printf("Erreur: chevalet plein pour %s\n", j->pseudo);
    }
}

void afficher_chevalet(Joueur *j) {
    printf("\nChevalet de %s (%d tuiles):\n", j->pseudo, j->nb_tuiles);

    if (j->nb_tuiles == 0) {
        printf("(vide)\n");
    } else {
        int i;
        for (i = 0; i < j->nb_tuiles; i++) {
            printf("%d: ", i + 1);
            afficher_tuile(&j->chevalet[i]);
            printf("  ");

            if ((i + 1) % 7 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
}

void retirer_tuile_joueur(Joueur *j, int index) {
    if (index < 0 || index >= j->nb_tuiles) {
        printf("Erreur: index invalide\n");
        return;
    }

    int i;
    for (i = index; i < j->nb_tuiles - 1; i++) {
        copier_tuile(&j->chevalet[i], &j->chevalet[i + 1]);
    }

    j->nb_tuiles--;
}

int calculer_score_joueur(Joueur *j) {
    int total = 0;
    int i;

    for (i = 0; i < j->nb_tuiles; i++) {
        if (j->chevalet[i].est_joker) {
            total += 30;
        } else {
            total += j->chevalet[i].valeur;
        }
    }

    return total;
}
