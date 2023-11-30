#include "../include/header.h"

// Fonction pour initialiser un graphe avec un nombre donné de sommets
Graphe* creerGraphe(int nbSommets) {
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe->nbSommets = nbSommets;
    graphe->listeAdjacence = (Arc**)malloc(nbSommets * sizeof(Arc*));

    for (int i = 0; i < nbSommets; i++){
        graphe->listeAdjacence[i] = NULL;
    }

    return graphe;
}

// Fonction pour ajouter un arc au graphe (sommets précédents vers sommet suivant)
void ajouterArc(Graphe* graphe, int source, int destination) {
    Arc* nouvelArc = (Arc*)malloc(sizeof(Arc));
    nouvelArc->sommetDestination = destination;
    nouvelArc->suivant = graphe->listeAdjacence[source];
    graphe->listeAdjacence[source] = nouvelArc;
}

// Fonction pour afficher le graphe
void afficherGraphe(Graphe* graphe) {
    for (int i=1; i < graphe->nbSommets; i++){
        Arc* arcCourant = graphe->listeAdjacence[i];
        printf("Sommets suivants pour le sommet %d:\n", i);
        while (arcCourant != NULL) {
            printf("  -> Sommet: %d\n", arcCourant->sommetDestination);
            arcCourant = arcCourant->suivant;
        }
        printf("\n");
    }
}
