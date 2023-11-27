//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "../src/fonction.h"
#define MAX_OPERATIONS 35
#define MAX_STATIONS 10


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
//int Respect_contrainte(int stationAssignment[MAX_OPERATIONS], t_Exclusion constraint) {
//    return (stationAssignment[constraint.operation1 - 1] != stationAssignment[constraint.operation2 - 1]);
//}
//
//void assignStations(int stationAssignment[MAX_OPERATIONS], int numStations, t_Exclusion *exclusionConstraints, int numConstraints) {
//    for (int i = 0; i < MAX_OPERATIONS; i++) {
//        stationAssignment[i] = 0; // INITIALISER TOUTES LES STATIONS A 0
//    }
//
//    for (int i = 0; i < numConstraints; i++) {
//        if (Respect_contrainte(stationAssignment, exclusionConstraints[i])) {
//            // ASSIGNER LES DIFFERENTES OPERATIONS AUX STATIONS
//            stationAssignment[exclusionConstraints[i].operation1 - 1] = 1;
//            stationAssignment[exclusionConstraints[i].operation2 - 1] = 2;
//        }
//    }
//}
//
//void printStationAssignment(int stationAssignment[MAX_OPERATIONS]) {
//    printf("Répartition des opérations sur les stations de travail :\n");
//    for (int i = 0; i < MAX_OPERATIONS; i++) {
//        printf("Opération %d -> Station %d\n", i + 1, stationAssignment[i]);
//    }
//}