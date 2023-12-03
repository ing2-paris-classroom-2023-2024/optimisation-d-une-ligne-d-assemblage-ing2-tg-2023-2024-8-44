#include <stdio.h>
#include <stdlib.h>

#define NBSTATIONS 10

typedef struct {
    int id;
    int *predecesseurs;
    int nb_predecesseurs;
    int effectuee;
    int existence;
    float temps;
} Tache;

typedef struct {
    int numero;
    float temps;
}Station;

void initialiserTaches(Tache taches[], int *tabSommets, int nbLignesOperations, float *tempsOP, int nbTACHES){
    for (int i=0; i<nbTACHES; i++) {
        taches[i].id = i+1;
        taches[i].predecesseurs = NULL;
        taches[i].nb_predecesseurs = 0;
        taches[i].effectuee = 0;
        taches[i].existence = 0;
    }

    // Mettre l'existence à 1 pour les sommets presents dans le tableau des sommets
    for (int i=0; i < nbLignesOperations; i++){
        for (int j=0; j < nbTACHES; j++){
            if (tabSommets[i] == taches[j].id){
                taches[j].existence = 1;
                taches[j].temps= tempsOP[i];
                break;  //sommet trouvé, on peut sortir de la boucle
            }
        }
    }
}


void ajouterDependance(int tache_ant, int tache_act, Tache taches[]){          /// ajouter une relation de dependance entre 2 taches
    Tache *tache = &taches[tache_act-1];
    tache->predecesseurs = realloc(tache->predecesseurs, (tache->nb_predecesseurs+1) * sizeof(int));
    tache->predecesseurs[tache->nb_predecesseurs++] = tache_ant;
}

void realiserTache(int tache_id, Tache taches[], int nbTACHES){          /// parfait rien a changer
    Tache *tache = &taches[tache_id-1];
    tache->effectuee = 1;


    for (int i=0; i < nbTACHES; i++){ // Parcourir toutes les tâches non encore réalisées
        if (!taches[i].effectuee){ // Si la tâche n'est pas encore réalisée
            for (int j=0; j < taches[i].nb_predecesseurs; j++){ // Parcourir les prédécesseurs de la tâche en cours

                if (taches[i].predecesseurs[j] == tache_id){ // Supprimer la tâche réalisée de la liste des prédécesseurs des autres taches
                    for (int k=j; k < taches[i].nb_predecesseurs - 1; k++) {
                        taches[i].predecesseurs[k] = taches[i].predecesseurs[k + 1];
                    }
                    taches[i].nb_predecesseurs--;
                    break;
                }
            }
        }
    }
}

//premiere version
void PrecedenceEtTempsSuitee(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int taille, int tempsCycle){
    float tempsTotal = 0;
    int station = 1;

    //initialiser les tâches et ajoutez des dépendances
    initialiserTaches(taches,opSommets,nbLignesOperations, opTemps, sommetMax);
    for (int i=0; i<taille; i++){
        ajouterDependance(tabPrecedence1[i], tabPrecedence2[i], taches);
    }

    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w"); // ouverture du fichier

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
                fprintf(fichier,"Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n", taches[i].id, taches[i].temps, station, tempsTotal);
                //sauvegarder dans un fichier
                break;
            }
        }
    }
    fclose(fichier);
}

void initialiserStation(Station *station, int numero, float temps){
    station->numero = numero;
    station->temps = temps;
}

void PrecedenceEtTempsOpti(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int taille, int tempsCycle){
    Station *stations = (Station *)malloc(NBSTATIONS * sizeof(Station));

    for (int i=0; i < NBSTATIONS; i++){
        initialiserStation(&stations[i], i+1, 0);
    }

    // initialiser les tâches et ajoutez les dépendances
    initialiserTaches(taches,opSommets,nbLignesOperations, opTemps, sommetMax);
    for (int i=0; i<taille; i++){
        ajouterDependance(tabPrecedence1[i], tabPrecedence2[i], taches);
    }

    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w"); // ouverture du fichier de sauvegarde

    // Réalisez toutes les tâches
    int tache_non_realisee = 1;         //on peut encore optimiser ceci pour ajouter une tache a la station 1 car il reste de la place pour certaines op
    printf("\n\n///////////////////////////////////////////////\n");
    printf("///////// ATTRIBUTIONS DES STATIONS ///////////\n");
    printf("///////////////////////////////////////////////\n");

    while (tache_non_realisee){
        tache_non_realisee = 0;
        for (int i=0; i<sommetMax; i++){

            if (!taches[i].effectuee && taches[i].nb_predecesseurs == 0 && taches[i].existence == 1){
                realiserTache(taches[i].id, taches, sommetMax);
                tache_non_realisee = 1;
                for (int j=0; j < NBSTATIONS; j++) {
                    if (stations[j].temps + taches[i].temps <= (float)tempsCycle){
                        stations[j].temps += taches[i].temps;
                        printf("Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n", taches[i].id, taches[i].temps, stations[j].numero, stations[j].temps);
                        fprintf(fichier, "Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n",
                                taches[i].id, taches[i].temps, stations[j].numero, stations[j].temps);
                        break;
                    }
                }
                break;
            }
        }
    }
    fclose(fichier);
}



void PrecedenceCycleContrainte(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int *tabExclusion1, int *tabExclusion2, int taille, int tempsCycle){
    Station *stations = (Station *)malloc(NBSTATIONS * sizeof(Station));
    for (int i=0; i < NBSTATIONS; i++) {
        initialiserStation(&stations[i], i+1, 0);
        printf("Station %d:\n", stations[i].numero);
    }


    // initialiser les tâches et ajoutez des dépendances
    initialiserTaches(taches,opSommets,nbLignesOperations, opTemps, sommetMax);
    for (int i=0; i<taille; i++){
        ajouterDependance(tabPrecedence1[i], tabPrecedence2[i], taches);
    }

    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w"); // ouverture du fichier

    // Réaliser toutes les tâches
    int tache_non_realisee = 1;
    while (tache_non_realisee){
        tache_non_realisee = 0;
        for (int i=0; i<sommetMax; i++){ // parcourir les taches

            if (!taches[i].effectuee && taches[i].nb_predecesseurs == 0 && taches[i].existence == 1) {
                realiserTache(taches[i].id, taches, sommetMax);
                tache_non_realisee = 1;
                for (int j=0; j < NBSTATIONS; j++) { // parcourir les stations

                    if (stations[j].temps + taches[i].temps <= (float) tempsCycle) { //verification si on peut ajouter la tache a la station
                        stations[j].temps += taches[i].temps;
                        printf("Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n",
                               taches[i].id, taches[i].temps, stations[j].numero, stations[j].temps);
                        fprintf(fichier, "Tache %d | Temps de l'operation %.2f | Station %d | Temps de cycle %.2f\n",
                                taches[i].id, taches[i].temps, stations[j].numero, stations[j].temps);
                        break;
                    }
                }
                break;
            }
        }
    }

}
