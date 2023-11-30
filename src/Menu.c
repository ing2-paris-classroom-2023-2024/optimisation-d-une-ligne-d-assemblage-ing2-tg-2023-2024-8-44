//
// Created by simon on 30/11/2023.
//
#include <stdio.h>

void afficher_menu() {
    printf("Menu Principal de Gestion de la Ligne d'Assemblage\n");
    printf("1. Charger les donnees des fichiers\n");
    printf("2. Afficher les contraintes d'exclusion\n");
    printf("3. Afficher les contraintes de precedence et de temps de cycle \n");
    printf("4. Heuristique\n");
    printf("5. Quitter\n");
}

int main() {
    int choix;

    do {
        afficher_menu();
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                // Charger les données depuis les fichiers
                break;
            case 2:
                // Afficher les contraintes d'exclusion
                break;
            case 3:
                // Afficher les contraintes de précédence et temps de cycle
                break;
            case 4:
                //Heuristique
                break;
            case 5:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 5);

    return 0;
}
