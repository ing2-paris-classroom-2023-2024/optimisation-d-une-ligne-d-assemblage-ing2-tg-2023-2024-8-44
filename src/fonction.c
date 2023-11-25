//
// Created by mathe on 11/11/2023.
//
#include "../include/fonction.h"


void lecture(int **tabS1, int **tabS2, int *nbLignes, char *nomFichier){
    FILE *fichier = NULL;
    char ligne[10];
    int compteur=0;

    fichier = fopen(nomFichier,"r"); // ouverture du fichier
    if (fichier == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { //tant qu'on a des lignes on les additionne
        (*nbLignes)++;
    }

    // allocation dynamique
    *tabS1 = (int*)malloc((*nbLignes)*sizeof(int));
    *tabS2 = (int*)malloc((*nbLignes)*sizeof(int));

    // si problème avec les tableaux on sort du programme
    if (*tabS1 ==NULL || *tabS2==NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*tabS1);
        free(*tabS2);
        exit(1);
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL ){
        if (sscanf(ligne, "%d %d", &(*tabS1)[compteur], &(*tabS2)[compteur]) == 2){
            compteur++;
        }
    }

    fclose(fichier);
}