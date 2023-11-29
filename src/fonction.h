//
// Created by mathe on 11/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

typedef struct {
    double tempsOperation;
    int *exclusion;
    int *precedence;
} t_operation;

typedef struct arc_s {
    struct arc_s *next;
    struct sommet_s *sommet;
    struct sommet_s *origin;
} arc_t;

typedef struct sommet_s {
    int id;
    int deg;
    short couleur;
    int pred;
    int dist;
    arc_t *arc;
} sommet_t;

typedef struct graphe_s {
    int taille;
    int ordre;
    sommet_t **sommets;
} graphe_t;


typedef struct ope_s
{
    int id;
    double time;
} ope_t;

typedef struct maillon_s
{
    ope_t *ope;
    struct maillon_s *next;
} maillon_t;

typedef struct workStation_s
{
    maillon_t *ope;
    double time;
} workStation_t;

typedef struct assemblyLine_s
{
    ope_t **ope;
    workStation_t **workStation;
    graphe_t *graph;
    bool **unassociable;
    double cycleTime;
    int nbOpe;
} assemblyLine_t;

typedef struct
{
    int **matriceExclusion;
    int **matricePrecedence;
}t_InfoAllOp;



void lecture(t_operation *TabOp,t_InfoAllOp *Tab1,int *tailleTab, int *tempsDeCyle, char *nomFichierExclusions,char *nomFichierOperations,char *nomFichierPrecedence,char *nomFichierTempsDeCycle);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
