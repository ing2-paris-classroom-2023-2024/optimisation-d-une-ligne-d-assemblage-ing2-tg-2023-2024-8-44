//
// Created by mathe on 11/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "header.h"

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

typedef struct s_station
{
    int id;
    int tempsDeCycle;
    char * Op;
    int nbOp;
}t_stations;



int **lectureExclusion(int tailleMatriceExclusion, char *nomFichierExclusions, int *tabOpExisant, int ordre);
bool checkIfExclusion(int op1, int op2,int **MatriceExlcusion);
void parcourirExclusionToutSeul(int **MatriceExlcusion,int tailleMatriceExclusion, t_stations *stations,int *tabOpExistant, int ordre);
void parcourirTempsDeCycleAvecExclusion(int **MatriceExlcusion,int tailleMatriceExclusion,t_stations *stations, t_OpTempsDeCyle *OpStruct, int ordre);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
