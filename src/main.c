#include <stdio.h>
#include <stdlib.h>
#include "../include/header.h"

int main(){
    int *tabPrecedence1=NULL, *tabPrecedence2=NULL;
    int *opSommets=NULL;
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
    printf("sommet max : %d\n", sommetMax);


    ///creer le graphe

    // Initialiser le graphe avec le nombre de sommets
    Graphe* graphe = creerGraphe(ordre+1);
    // Ajouter des arcs au graphe en fonction des tableaux de précédence
    for (int i=0; i<taille; i++){
        ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
    }


    /// AFFICHAGE /// Blinder l'affichage pour les sommets inexistants egalement et probleme avec le sommet 7
    affichageFichier(nbLignesPrecedence, nbLignesOperations, tempsCycle, ordre, taille, tabPrecedence1, tabPrecedence2, opSommets, opTemps, graphe);

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
    int tache_non_realisee = 1;
    while (tache_non_realisee){
        tache_non_realisee = 0;
        for (int i=0; i<sommetMax; i++){

            if (!taches[i].effectuee && taches[i].nb_predecesseurs == 0 && taches[i].existence == 1) {
                realiserTache(taches[i].id, taches, sommetMax);
                tache_non_realisee = 1;
                tempsTotal += taches[i].temps;
                if (tempsTotal > (float)tempsCycle){
                    tempsTotal = taches[i].temps;
                    station++;
                }
                printf("Tache %d | Temps %.2f | Station %d\n", taches[i].id, taches[i].temps, station);
                break;
            }
        }
    }



    //libérer la memoire
    free(tabPrecedence1);
    free(tabPrecedence2);
    free(opSommets);
    free(opTemps);
    free(sommets);
    free(graphe);

    return 0;
}
