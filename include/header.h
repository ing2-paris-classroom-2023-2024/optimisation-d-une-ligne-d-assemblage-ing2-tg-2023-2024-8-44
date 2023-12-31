//
// Created by mathe on 30/11/2023.
//

#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Structure d'un arc du graphe
typedef struct Arc {
    int sommetDestination;
    struct Arc* suivant;
} Arc;

// Structure du graphe
typedef struct Graphe {
    int nbSommets;
    Arc** listeAdjacence;
} Graphe;

typedef struct
{
    int idOp;
    float tempsDeCycle;
}t_OpTempsDeCyle;

typedef struct s_stations
{
    int id;
    int nbOp;
    int attribue;
    char * Op;
    float tempsDeCycle;
}t_stations;

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



///Partie Graphe///

Graphe* creerGraphe(int nbSommets);
void ajouterArc(Graphe* graphe, int source, int destination);
void afficherGraphe(Graphe* graphe, const int *tabSommets, int sommetMax);

///Partie Lecture de fichier///
void lecture(int **arc1, int **arc2, int *nbLignesPrecedence, int *nbLignesOperations, int *tempsCycle, int **opSommets, float **opTemps);
void lectureTempsDeCycleOp(t_OpTempsDeCyle * Opstruct);
void affichageFichier(int nbLignesPrecedence, int nbLignesOperations, int tempsCycle, int ordre, int taille, int *tabPrecedence1, int *tabPrecedence2, int *opSommets, float *opTemps, Graphe* graphe, int sommetMax);
///Partie precedence et temps de cycle///
void ajouterDependance(int tache_ant, int tache_act, Tache taches[]);
void realiserTache(int tache_id, Tache taches[], int nbTACHES);
void initialiserTaches(Tache taches[], int *tabSommets, int nbLignesOperations, float *tempsOP, int nbTACHES);
void PrecedenceEtTempsOpti(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int taille, int tempsCycle);
int * PrecedenceEtTempsPourExclusion(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int taille, int tempsCycle);
void PrecedenceEtTempsSuitee(Tache taches[], int *opSommets, int nbLignesOperations, float *opTemps, int sommetMax, int *tabPrecedence1, int *tabPrecedence2, int taille, int tempsCycle);
bool checkIfTabEmpty(const int *tab,int taille);

///Gestion de menu///
void Menu();

///Reunion des codes///
void precedenceEtExclusionEtTempsDeCycle();

#endif //PROJECT_HEADER_H
