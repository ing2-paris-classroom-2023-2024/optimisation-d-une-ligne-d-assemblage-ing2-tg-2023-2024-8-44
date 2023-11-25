//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "../src/fonction.c"
int main()
{
    printf("hello world");
    return 0;
}


void readExclusionConstraints(t_Exclusion *exclusionConstrainte, int *numConstrainte) {
    FILE *file = fopen("contraintes.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    *numConstrainte = 0;
    while (fscanf(file, "%d %d", &exclusionConstrainte[*numConstrainte].operation1,
                  &exclusionConstrainte[*numConstrainte].operation2) == 2)
    {
        (*numConstrainte)++;
    }

    fclose(file);

    int *tabPrecedence1, *tabPrecedence2;
    int *tabTempsCycle1, *tabTempsCycle2;
    int nbLignes = 0;
    char nomFichier[20];

    printf("Donnez le nom du fichier precedences:");
    scanf("%s", nomFichier);
    lecture(&tabPrecedence1, &tabPrecedence2, &nbLignes, nomFichier);
    for (int i=0; i<nbLignes; i++){            //vérifier les données
        printf("%d %d\n", tabPrecedence1[i], tabPrecedence2[i]);
    }
    printf("\nNombre de lignes: %d\n", nbLignes);
    nbLignes = 0;

    printf("Donnez le nom du fichier temps de cycle:");
    scanf("%s", nomFichier);
    lecture(&tabTempsCycle1, &tabTempsCycle2, &nbLignes, nomFichier);
    for (int i=0; i<nbLignes; i++){            //vérifier les données
        printf("%d %d\n", tabPrecedence1[i], tabPrecedence2[i]);
    }
    printf("\nNombre de lignes: %d\n", nbLignes);

    //libérer la memoire
    free(tabPrecedence1);
    free(tabPrecedence2);
}