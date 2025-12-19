

#include <stdio.h>
#include <stdlib.h>
#include "tuiles.h"
#include "regles.h"
#include "joueur.h"
#include "partie.h"

int main() {

    int nb_joueurs;
    printf("Combien de joueurs (2-4) ? ");
    scanf("%d", &nb_joueurs);
    if (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("Erreur: il faut entre 2 et 4 joueurs\n");
        return 1;
    }

    Partie partie;
    initialiser_partie(&partie, nb_joueurs);

    int i;
    for (i = 0; i < nb_joueurs; i++) {
        char nom[50];
        printf("Nom du joueur %d: ", i + 1);
        scanf("%s", nom);
        initialiser_joueur(&partie.joueurs[i], nom);
    }

    distribuer_tuiles_debut(&partie);

    while (partie.partie_finie == 0) {
        afficher_etat_partie(&partie);
        jouer_tour(&partie);
        if (partie.partie_finie == 0) {
            passer_joueur_suivant(&partie);
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
            getchar();
        }
    }


    printf("\nScores finaux:\n");
    for (i = 0; i < nb_joueurs; i++) {
        printf("  %s: %d points", partie.joueurs[i].pseudo, partie.joueurs[i].score);
        if (partie.joueurs[i].nb_tuiles == 0) {
            printf(" (GAGNANT!)");
        }
        printf("\n");
    }

    printf("\nMerci d'avoir joue!\n");

    return 0;
}
