//
// Created by simon on 30/11/2023.
//
#include <stdio.h>
#include "header.h"
#include "fonction.h"
#include "string.h"
void afficher_menu() {
    printf("Menu Principal de Gestion de la Ligne d'Assemblage\n");
    printf("1. Afficher exclusion tout seul\n");
    printf("2. Afficher les contraintes d'exclusion et temps de cycle\n");
    printf("3. Afficher le graphe de precedence\n");
    printf("4. Afficher les contraintes de precedence et de temps de cycle V1\n");
    printf("5. Afficher les contraintes de precedence et de temps de cycle V2\n");
    printf("6. Afficher les contraintes de precedence, exclusion et de temps de cycle\n");
    printf("7. Quitter\n");
}


void Menu(){
    int choix;

    do {
        afficher_menu();
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int **MatriceExclusion = NULL;
                int *tabPrecedence1 = NULL, *tabPrecedence2 = NULL;
                int *opSommets = NULL;
                t_OpTempsDeCyle *Opstruct = NULL;
                float *opTemps = NULL;
                int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations = 0;
                int *sommets = NULL;

                lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations, &tempsCycle,
                        &opSommets, &opTemps);

                // Allouer dynamiquement de la mémoire pour le tableau sommets
                sommets = (int *) malloc(nbLignesPrecedence * 2 * sizeof(int));
                if (sommets == NULL) {
                    printf("Erreur d'allocation mémoire pour le tab sommets.\n");
                    // Quitter le programme avec un code d'erreur
                }


                ///GRAPHE ///
                //récuperer l'odre et la taille du grahpe
                int ordre = nbLignesOperations;
                int taille = nbLignesPrecedence;
                int sommetMax = opSommets[nbLignesOperations - 1];

                Opstruct = malloc(sizeof(t_OpTempsDeCyle) * ordre);

                lectureTempsDeCycleOp(Opstruct);


                ///creer le graphe

                // Initialiser le graphe avec le nombre de sommets
                Graphe *graphe = creerGraphe(sommetMax + 1);
                // Ajouter des arcs au graphe en fonction des tableaux de précédence
                for (int i = 0; i < taille; i++) {
                    ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
                }



                ///Gérer les exclusions Tout seul///
                //Lire le fichier exclusion:

                MatriceExclusion = lectureExclusion(sommetMax, "../fileTexte/exclusions.txt", opSommets, ordre);

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
                        //printf("Opération %d -> Station %d\n", i, stations[i].id);
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
                printf("\nCompteur Station 2: %.2f\n\n", counterStation2);

                // Charger les données depuis les fichiers
                break;
            }
            case 2: {
                int **MatriceExclusion = NULL;


                int *tabPrecedence1 = NULL, *tabPrecedence2 = NULL;
                int *opSommets = NULL;
                t_OpTempsDeCyle *Opstruct = NULL;
                float *opTemps = NULL;
                int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations = 0;
                int *sommets = NULL;

                lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations,
                        &tempsCycle, &opSommets, &opTemps);

                // Allouer dynamiquement de la mémoire pour le tableau sommets
                sommets = (int *) malloc(nbLignesPrecedence * 2 * sizeof(int));
                if (sommets == NULL) {
                    printf("Erreur d'allocation mémoire pour le tab sommets.\n");
                    // Quitter le programme avec un code d'erreur
                }


                ///GRAPHE ///
                //récuperer l'odre et la taille du grahpe
                int ordre = nbLignesOperations;
                int taille = nbLignesPrecedence;
                int sommetMax = opSommets[nbLignesOperations - 1];

                Opstruct = malloc(sizeof(t_OpTempsDeCyle) * ordre);

                lectureTempsDeCycleOp(Opstruct);


                ///creer le graphe

                // Initialiser le graphe avec le nombre de sommets
                Graphe *graphe = creerGraphe(sommetMax + 1);
                // Ajouter des arcs au graphe en fonction des tableaux de précédence
                for (int i = 0; i < taille; i++) {
                    ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
                }



                ///Gérer les exclusions Tout seul///
                //Lire le fichier exclusion:

                MatriceExclusion = lectureExclusion(sommetMax, "../fileTexte/exclusions.txt", opSommets,
                                                    ordre);

                t_stations stations[sommetMax + 1];

                for (int i = 1; i <= sommetMax; i++) {
                    stations[i].id = 1;
                    stations[i].tempsDeCycle = 0;
                    stations[i].nbOp = 0;
                    stations[i].Op = NULL;
                }
                // Afficher la répartition finale des opérations sur les stations


                int nbStation = 0;

                Stack *AllStation;
                AllStation = malloc(sizeof(Stack));
                realloc(AllStation, sizeof(Stack));
                parcourirTempsDeCycleAvecExclusion(MatriceExclusion, sommetMax, Opstruct, ordre, AllStation,
                                                   (float) tempsCycle, &nbStation);
                // Afficher la répartition finale des opérations sur les stations
                printf("\n\n\n");
                for (int i = 0; i <= nbStation; i++) {
                    printf("station : %d\n", i + 1);
                    display(&AllStation[i], NULL);
                    printf("\n");
                }
                printf("\n\n\n");

                //libérer la memoire
                free(MatriceExclusion);
                free(AllStation);
                free(tabPrecedence1);
                free(tabPrecedence2);
                free(opSommets);
                free(opTemps);
                free(sommets);
                break;
            }
            case 3: {
                // Afficher les contraintes de précédence et temps de cycle
                int *tabPrecedence1 = NULL, *tabPrecedence2 = NULL, *tabExclusions1 = NULL, *tabExclusions2 = NULL;
                int *opSommets = NULL;
                float *opTemps = NULL;
                int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations = 0, nbLignesExclusions = 0;
                int *sommets = NULL;

                /// LECTURE FICHIER ///
                lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations,
                        &tempsCycle, &opSommets, &opTemps);


                ///DONNEES GRAPHE ///
                int ordre = nbLignesOperations;
                int taille = nbLignesPrecedence;
                int sommetMax = opSommets[nbLignesOperations - 1];


                /// creer le graphe ///
                Graphe *graphe = creerGraphe(sommetMax + 1);
                for (int i = 0; i < taille; i++) { // Ajouter des arcs au graphe
                    ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
                }

                printf("Affichage du graphe.\n");
                affichageFichier(nbLignesPrecedence, nbLignesOperations, tempsCycle, ordre, taille,
                                 tabPrecedence1, tabPrecedence2, opSommets, opTemps, graphe, sommetMax);
                break;
            }
            case 4: {
                // Afficher les contraintes de précédence et temps de cycle
                int *tabPrecedence1 = NULL, *tabPrecedence2 = NULL, *tabExclusions1 = NULL, *tabExclusions2 = NULL;
                int *opSommets = NULL;
                float *opTemps = NULL;
                int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations = 0, nbLignesExclusions = 0;
                int *sommets = NULL;

                /// LECTURE FICHIER ///
                lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations,
                        &tempsCycle, &opSommets, &opTemps);


                ///DONNEES GRAPHE ///
                int ordre = nbLignesOperations;
                int taille = nbLignesPrecedence;
                int sommetMax = opSommets[nbLignesOperations - 1];


                /// creer le graphe ///
                Graphe *graphe = creerGraphe(sommetMax + 1);
                for (int i = 0; i < taille; i++) { // Ajouter des arcs au graphe
                    ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
                }



                /// TACHES ///
                Tache taches[sommetMax];
                printf("Precedence et temps de cycle V1.\n");
                PrecedenceEtTempsSuitee(taches, opSommets, nbLignesOperations, opTemps, sommetMax,
                                        tabPrecedence1, tabPrecedence2, taille, tempsCycle);

                /// MEMOIRE ///
                //libérer la memoire
                free(tabPrecedence1);
                free(tabPrecedence2);
                free(opSommets);
                free(opTemps);
                free(sommets);
                free(graphe);
                printf("\n");
                break;
            }

            case 5: {

                // Afficher les contraintes de précédence et temps de cycle
                int *tabPrecedence1 = NULL, *tabPrecedence2 = NULL, *tabExclusions1 = NULL, *tabExclusions2 = NULL;
                int *opSommets = NULL;
                float *opTemps = NULL;
                int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations = 0, nbLignesExclusions = 0;
                int *sommets = NULL;

                /// LECTURE FICHIER ///
                lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations,
                        &tempsCycle, &opSommets, &opTemps);


                ///DONNEES GRAPHE ///
                int ordre = nbLignesOperations;
                int taille = nbLignesPrecedence;
                int sommetMax = opSommets[nbLignesOperations - 1];


                /// creer le graphe ///
                Graphe *graphe = creerGraphe(sommetMax + 1);
                for (int i = 0; i < taille; i++) { // Ajouter des arcs au graphe
                    ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
                }



                /// TACHES ///
                Tache taches[sommetMax];
                //PrecedenceEtTempsSuitee(taches, opSommets, nbLignesOperations, opTemps, sommetMax, tabPrecedence1, tabPrecedence2, taille, tempsCycle);

                //V2:
                PrecedenceEtTempsOpti(taches, opSommets, nbLignesOperations, opTemps, sommetMax,
                                      tabPrecedence1, tabPrecedence2, taille, tempsCycle);

                /// MULTI CONTRAINTE ///
                //PrecedenceCycleContrainte(taches, opSommets, nbLignesOperations, opTemps, sommetMax, tabPrecedence1, tabPrecedence2, tabExclusions1, tabExclusions2, taille, tempsCycle);


                /// MEMOIRE ///
                //libérer la memoire
                free(tabPrecedence1);
                free(tabPrecedence2);
                free(opSommets);
                free(opTemps);
                free(sommets);
                free(graphe);
                printf("\n");
                break;
            }
            case 6: {
                precedenceEtExclusionEtTempsDeCycle();
                printf("\n");
                break;
            }
            case 7: {
                printf("Quitter\n");
                break;
            }
            default: {
                printf("Choix invalide. Veuillez réessayer.\n");
            }
        }
    }while (choix != 7);
}