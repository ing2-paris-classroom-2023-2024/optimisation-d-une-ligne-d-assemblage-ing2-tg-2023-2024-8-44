#include <stdio.h>
#include <stdlib.h>
#include "../include/header.h"


// pour enlever le defin et avoir un truc modulable, on doit recup le numero de sommet de la derniere ligne du fichier operations.txt

void initialiserTaches(Tache taches[], const int *tabSommets, int nbLignesOperations, const float *tempsOP, int nbTACHES){
    for (int i = 0; i < nbTACHES; i++) {
        taches[i].id = i + 1;
        taches[i].predecesseurs = NULL;
        taches[i].nb_predecesseurs = 0;
        taches[i].effectuee = 0;
        taches[i].existence = 0;
    }

    // Mettre l'existence à 1 pour les sommets dans le tableau          /// faire alloc dynamique
    for (int i = 0; i < nbLignesOperations; i++) {                                      /// 35 = nombrede taches = ??? peutetre nbLignesOperations donc si probleme voir pourimplementerlavariable
        for (int j = 0; j < nbTACHES; j++) {
            if (tabSommets[i] == taches[j].id) {
                taches[j].existence = 1;
                taches[j].temps= tempsOP[i];
                break;  // On a trouvé le sommet, on peut sortir de la boucle interne
            }
        }
    }
    //verif existence
    //for (int i = 0; i < nbTACHES; i++) {
    //    printf("Tache %d : existence = %d\n", taches[i].id, taches[i].existence);
    //}
}


void ajouterDependance(int tache_ant, int tache_act, Tache taches[]) {          /// parfait rien a changer
    Tache *tache = &taches[tache_act - 1];
    tache->predecesseurs = realloc(tache->predecesseurs, (tache->nb_predecesseurs + 1) * sizeof(int));
    tache->predecesseurs[tache->nb_predecesseurs++] = tache_ant;
}

void realiserTache(int tache_id, Tache taches[], int nbTACHES) {          /// parfait rien a changer
    Tache *tache = &taches[tache_id - 1];
    tache->effectuee = 1;

    // Parcourir toutes les tâches non encore réalisées
    for (int i = 0; i < nbTACHES; i++) {
        if (!taches[i].effectuee) {
            // Parcourir les prédécesseurs de la tâche en cours
            for (int j = 0; j < taches[i].nb_predecesseurs; j++) {
                // Supprimer la tâche réalisée de la liste des prédécesseurs
                if (taches[i].predecesseurs[j] == tache_id) {
                    for (int k = j; k < taches[i].nb_predecesseurs - 1; k++) {
                        taches[i].predecesseurs[k] = taches[i].predecesseurs[k + 1];
                    }
                    taches[i].nb_predecesseurs--;
                    break;  // On a trouvé et supprimé la tâche, on peut sortir de la boucle
                }
            }
        }
    }
}

