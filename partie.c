#include <stdio.h>
#include <string.h>
#include "partie.h"

void initialiser_partie(Partie *p, int nombre_joueurs) {
    p->nb_joueurs = nombre_joueurs;
    p->joueur_actuel = 0;
    p->partie_finie = 0;

    initialiser_pioche(&p->pioche);
    creer_jeu_complet(&p->pioche);
    melanger_pioche(&p->pioche);

    initialiser_plateau(&p->plateau);

    printf("Partie initialisee avec %d joueurs\n", nombre_joueurs);
}

void distribuer_tuiles_debut(Partie *p) {
    int i, j;

    printf("\nDistribution des tuiles...\n");

    for (i = 0; i < p->nb_joueurs; i++) {
        for (j = 0; j < TUILES_DEBUT; j++) {
            Tuile *t = piocher_tuile(&p->pioche);
            if (t != NULL) {
                ajouter_tuile_joueur(&p->joueurs[i], t);
            }
        }
    }

    printf("Distribution terminée\n");
    printf("Tuiles restantes dans la pioche: %d\n", p->pioche.nb_tuiles_restantes);
}

void afficher_etat_partie(Partie *p) {
    printf("Tour du joueur: %s\n", p->joueurs[p->joueur_actuel].pseudo);
    printf("Pioche: %d tuiles restantes\n", p->pioche.nb_tuiles_restantes);

    printf("\nScores:\n");
    int i;
    for (i = 0; i < p->nb_joueurs; i++) {
        printf("  %s: %d points\n", p->joueurs[i].pseudo, p->joueurs[i].score);
    }

}

void passer_joueur_suivant(Partie *p) {
    p->joueur_actuel = (p->joueur_actuel + 1) % p->nb_joueurs;
}

int verifier_victoire(Partie *p) {
    int i;
    for (i = 0; i < p->nb_joueurs; i++) {
        if (p->joueurs[i].nb_tuiles == 0) {
            printf("\n %s a gagne! \n", p->joueurs[i].pseudo);
            return 1;
        }
    }

    return 0;
}

void jouer_tour(Partie *p) {
    Joueur *joueur_actif = &p->joueurs[p->joueur_actuel];
    int choix;
    printf("Tour de %s\n", joueur_actif->pseudo);
    afficher_chevalet(joueur_actif);
    afficher_plateau(&p->plateau);

    printf("\nQue voulez-vous faire ?\n");
    printf("1. Poser une combinaison\n");
    printf("2. Piocher et passer\n");
    printf("Choix: ");
    scanf("%d", &choix);

    if (choix == 1) {
        int nb_tuiles_combi;
        printf("Combien de tuiles dans votre combinaison ? ");
        scanf("%d", &nb_tuiles_combi);

        if (nb_tuiles_combi < 3 || nb_tuiles_combi > joueur_actif->nb_tuiles) {
            printf("Nombre invalide!\n");
            return;
        }
        Combinaison combi;
        initialiser_combinaison(&combi);

        int i;
        for (i = 0; i < nb_tuiles_combi; i++) {
            int index;
            printf("Numero de la tuile %d: ", i + 1);
            scanf("%d", &index);
            index--;

            if (index >= 0 && index < joueur_actif->nb_tuiles) {
                ajouter_tuile_combinaison(&combi, &joueur_actif->chevalet[index]);
            }
        }

        if (est_combinaison_valide(&combi)) {
            int points = calculer_points_combinaison(&combi);
            printf("Combinaison valide! (%d points)\n", points);

            if (joueur_actif->pose_30points == 0) {
                if (points >= 30) {
                    printf("Vous avez pose vos 30 points!\n");
                    joueur_actif->pose_30points = 1;
                } else {
                    printf("Il faut au moins 30 points pour commencer! (vous: %d)\n", points);
                    return;
                }
            }
            ajouter_combinaison_plateau(&p->plateau, &combi);
            for (i = nb_tuiles_combi - 1; i >= 0; i--) {
                int index;
                printf("Retirer tuile numero: ");
                scanf("%d", &index);
                index--;
                retirer_tuile_joueur(joueur_actif, index);
            }

        } else {
            printf("Combinaison invalide!\n");
        }

    } else if (choix == 2) {
        Tuile *t = piocher_tuile(&p->pioche);
        if (t != NULL) {
            ajouter_tuile_joueur(joueur_actif, t);
            printf("Tuile piochee: ");
            afficher_tuile(t);
            printf("\n");
        }
    }

    if (verifier_victoire(p)) {
        p->partie_finie = 1;

        int i;
        for (i = 0; i < p->nb_joueurs; i++) {
            if (p->joueurs[i].nb_tuiles == 0) {
                int j;
                for (j = 0; j < p->nb_joueurs; j++) {
                    if (i != j) {
                        int points_perdus = calculer_score_joueur(&p->joueurs[j]);
                        p->joueurs[i].score += points_perdus;
                        p->joueurs[j].score -= points_perdus;
                    }
                }
            }
        }
    }
}
