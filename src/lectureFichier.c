#include <stdio.h>
#include <stdlib.h>
#include "../include/header.h"


void lecture(int **arc1, int **arc2, int *nbLignesPrecedence, int *nbLignesOperations, int *tempsCycle, int **opSommets, float **opTemps) {
    FILE *fichier = NULL;
    char ligne[10];
    int compteur = 0;
    char nomFichier[50];

    /// PRECEDENCES ///
    fichier = fopen("../fileTexte/precedences.txt", "r"); // ouverture du fichier
    if (fichier == NULL) {
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { // tant qu'on a des lignes on les additionne
        (*nbLignesPrecedence)++;
    }

    // allocation dynamique
    *arc1 = (int*)malloc((*nbLignesPrecedence+1) * sizeof(int));
    *arc2 = (int*)malloc((*nbLignesPrecedence+1) * sizeof(int));

    // si problème avec les tableaux on sort du programme
    if (*arc1 == NULL || *arc2 == NULL) {
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*arc1);
        free(*arc2);
        exit(1);
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%d %d", &(*arc1)[compteur], &(*arc2)[compteur]) == 2) {
            compteur++;
        }
    }
    fclose(fichier);

    /// TEMPS CYCLE ///
    fichier = fopen("../fileTexte/temps_cycle.txt", "r"); // ouverture du fichier
    if (fichier == NULL) {
        printf("Erreur ouverture fichier");
        exit(1);
    }

    // Lire le temps de cycle depuis le fichier
    fscanf(fichier, "%d", tempsCycle); // Utilisez *tempsCycle pour accéder à la valeur pointée
    fclose(fichier);

    /// OPERATIONS ///
    compteur = 0;  // réinitialiser le compteur

//    printf("Donnez le nom du fichier operations:");
//    scanf("%s", nomFichier);
    fichier = fopen("../fileTexte/operations.txt", "r"); // ouverture du fichier
    if (fichier == NULL) {
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { // tant qu'on a des lignes on les additionne
        (*nbLignesOperations)++;
    }

    // allocation dynamique
    *opSommets = (int*)malloc((*nbLignesOperations+1) * sizeof(int));
    *opTemps = (float*)malloc((*nbLignesOperations+1) * sizeof(float)); // Correction ici

    // si problème avec les tableaux on sort du programme
    if (*opTemps == NULL || *opSommets == NULL) {
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*opTemps);
        free(*opSommets);
        exit(1);
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%d %f", &(*opSommets)[compteur], &(*opTemps)[compteur]) == 2) { // Correction ici
            compteur++;
        }
    }
    fclose(fichier);
}

void affichageFichier(int nbLignesPrecedence, int nbLignesOperations, int tempsCycle, int ordre, int taille, int *tabPrecedence1, int *tabPrecedence2, int *opSommets, float *opTemps, Graphe* graphe){
    printf("\nTableaux des precedences:\n");
    for (int i=0; i < nbLignesPrecedence; i++){
        printf("%d %d\n", tabPrecedence1[i], tabPrecedence2[i]);
    }

    printf("\nSommets et temps des operations:\n");
    for (int i=0; i < nbLignesOperations; i++){
        printf("Sommet: %d, Temps: %.2f\n", opSommets[i], opTemps[i]);
    }

    printf("\nInfos du graphe:\n");
    printf("Temps de cycle: %d\n", tempsCycle);
    printf("Ordre: %d\n", ordre-1);
    printf("Taille: %d\n", taille);

    // Afficher le graphe
    printf("\nGraphe oriente:\n");
    afficherGraphe(graphe);
}