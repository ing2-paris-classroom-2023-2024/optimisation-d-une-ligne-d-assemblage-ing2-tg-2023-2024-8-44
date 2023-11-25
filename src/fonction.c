//
// Created by mathe on 11/11/2023.
//
#include "../include/fonction.h"


//void readExclusionConstraints(t_Exclusion *exclusionConstrainte, int *numConstrainte) {
//    FILE *file = fopen("contraintes.txt", "r");
//    if (file == NULL) {
//        perror("Erreur lors de l'ouverture du fichier");
//        exit(EXIT_FAILURE);
//    }
//    *numConstrainte = 0;
//    while (fscanf(file, "%d %d", &exclusionConstrainte[*numConstrainte].operation1,
//                  &exclusionConstrainte[*numConstrainte].operation2) == 2)
//    {
//        (*numConstrainte)++;
//    }
//
//    fclose(file);
//}