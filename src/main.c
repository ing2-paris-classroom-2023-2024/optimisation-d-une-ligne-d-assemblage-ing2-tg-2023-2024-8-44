#include <stdio.h>
#include <stdlib.h>
#include "../include/header.h"
#include "../include/fonction.h"
#include "string.h"

int main(){
    int **MatriceExclusion = NULL;


    int *tabPrecedence1=NULL, *tabPrecedence2=NULL;
    int *opSommets=NULL;
    t_OpTempsDeCyle * Opstruct = NULL;
    float *opTemps=NULL;
    int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations=0;
    int *sommets = NULL;

    lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations, &tempsCycle, &opSommets, &opTemps);



    // Allouer dynamiquement de la mémoire pour le tableau sommets
    sommets = (int *)malloc(nbLignesPrecedence * 2 * sizeof(int));
    if (sommets == NULL){
        printf("Erreur d'allocation mémoire pour le tab sommets.\n");
        return 1; // Quitter le programme avec un code d'erreur
    }


    ///GRAPHE ///
    //récuperer l'odre et la taille du grahpe
    int ordre = nbLignesOperations;
    int taille = nbLignesPrecedence;
    int sommetMax = opSommets[nbLignesOperations-1];

    Opstruct = malloc(sizeof (t_OpTempsDeCyle)*ordre);

    lectureTempsDeCycleOp(Opstruct);


    ///creer le graphe

    // Initialiser le graphe avec le nombre de sommets
    Graphe* graphe = creerGraphe(sommetMax+1);
    // Ajouter des arcs au graphe en fonction des tableaux de précédence
    for (int i=0; i<taille; i++){
        ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
    }


    /// AFFICHAGE /// Blinder l'affichage pour les sommets inexistants egalement et probleme avec le sommet 7
    affichageFichier(nbLignesPrecedence, nbLignesOperations, tempsCycle, ordre, taille, tabPrecedence1, tabPrecedence2, opSommets, opTemps, graphe, sommetMax);

    printf("TAB SOMMET : \n");
    for (int i=0; i<nbLignesOperations; i++){
        printf("%d ", opSommets[i]);
    }
    printf("\n");


    /// TACHES ///
    Tache taches[sommetMax];
    float tempsTotal = 0;
    int station = 1;

    // Initialisez les tâches et ajoutez des dépendances
    initialiserTaches(taches,opSommets,nbLignesOperations, opTemps, sommetMax);
    for (int i=0; i<taille; i++){
        ajouterDependance(tabPrecedence1[i], tabPrecedence2[i], taches);
    }

    // Réalisez toutes les tâches
    int tache_non_realisee = 1;         //on peut encore optimiser ceci pour ajouter une tache a la station 1 car il reste de la place pour certaines op
    printf("\n\n///////////////////////////////////////////////\n");
    printf("///////// ATTRIBUTIONS DES STATIONS ///////////\n");
    printf("///////////////////////////////////////////////\n");
    printf("\n STATION 1\n\n");

    while (tache_non_realisee){
        tache_non_realisee = 0;
        for (int i=0; i<sommetMax; i++){

            if (!taches[i].effectuee && taches[i].nb_predecesseurs == 0 && taches[i].existence == 1) {
                realiserTache(taches[i].id, taches, sommetMax);
                tache_non_realisee = 1;
                tempsTotal += taches[i].temps;
                if (tempsTotal > (float)tempsCycle){ // creation nouvelle station
                    tempsTotal = taches[i].temps;
                    station++;
                    printf("\n STATION %d\n\n",station);
                }
                printf("Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n", taches[i].id, taches[i].temps, station, tempsTotal);
                break;
            }
        }
    }



    ///Gérer les exclusions Tout seul///
    //Lire le fichier exclusion:

    MatriceExclusion = lectureExclusion(sommetMax,"../fileTexte/exclusions.txt",opSommets,ordre);

    printf("%d\n", checkIfExclusion(1,4,MatriceExclusion));
    // Initialiser les stations à -1, indiquant qu'aucune station n'est attribuée


    t_stations stations[sommetMax + 1];

    for (int i = 1; i <= sommetMax; i++) {
        stations[i].id = 1;
        stations[i].tempsDeCycle = 0;
        stations[i].nbOp = 0;
        stations[i].Op = NULL;
    }
    parcourirExclusion(MatriceExclusion, sommetMax, stations, Opstruct, ordre);
    // Afficher la répartition finale des opérations sur les stations
    printf("\nRépartition finale des opérations sur les stations :\n");
    char *operationsByStation1[sommetMax + 1];
    char *operationsByStation2[sommetMax + 1];
    for (int i = 1; i <= sommetMax; i++) {
        operationsByStation1[i] = malloc(256 * sizeof(char));
        operationsByStation2[i] = malloc(256 * sizeof(char));
        // Assurez-vous de gérer les erreurs d'allocation comme cela a été fait dans votre code précédent
    }
    // Initialisation des compteurs pour chaque station
    float counterStation1 = 0;
    float counterStation2 = 0;
    // Initialisation des tableaux de chaînes de caractères
    for (int i = 1; i <= sommetMax; i++) {
        operationsByStation1[i][0] = '\0';
        operationsByStation2[i][0] = '\0';
    }
    for (int i = 1; i <= sommetMax; i++) {
        if (stations[i].id != -1) {
            printf("Opération %d -> Station %d\n", i, stations[i].id);
            char temp[50];
            snprintf(temp, sizeof(temp), " %d  ", i);
            if (stations[i].id == 1) {
                strcat(operationsByStation1[stations[i].id], temp);
                counterStation1 += GetTempsDeCycleToOp(Opstruct, i, ordre);

            } else if (stations[i].id == 2) {
                strcat(operationsByStation2[stations[i].id], temp);
                counterStation2 += GetTempsDeCycleToOp(Opstruct, i, ordre);
            }
        }
    }

    printf("\nAffichage des opérations par station :\n");

    printf("Station %d :\n", stations[1].id);
    printf("%s\n", operationsByStation1[stations[1].id]);
    printf("\nCompteur Station 1: %.2f\n", counterStation1);
    printf("\nStation %d :\n", stations[4].id);
    printf("%s\n", operationsByStation2[stations[4].id]);
    printf("\nCompteur Station 2: %.2f\n", counterStation2);



    int nbStation=0;

    Stack * AllStation;
    AllStation = malloc(sizeof (Stack));
    realloc(AllStation,sizeof (Stack));
    parcourirTempsDeCycleAvecExclusion(MatriceExclusion, sommetMax,stations,Opstruct,ordre,AllStation,tempsCycle,&nbStation);
    // Afficher la répartition finale des opérations sur les stations

    printf("\n\n///////////////////////////////////////////////\n");
    printf("///////// ATTRIBUTIONS DES STATIONS ///////////\n");
    printf("///////////////////////////////////////////////\n");

    for (int i = 0; i <= nbStation; i++) {
        printf("station : %d\n",i+1);
        display(&AllStation[i]);
    }

    // Libérer la mémoire allouée
    for (int i = 0; i <= sommetMax; i++) {
        free(MatriceExclusion[i]);
    }
    free(MatriceExclusion);

    //libérer la memoire
    free(tabPrecedence1);
    free(tabPrecedence2);
    free(opSommets);
    free(opTemps);
    free(sommets);
    free(graphe);

    return 0;
}
