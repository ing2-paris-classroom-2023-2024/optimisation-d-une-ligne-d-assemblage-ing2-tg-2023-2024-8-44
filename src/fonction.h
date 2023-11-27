//
// Created by mathe on 11/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H

#include "stdlib.h"
#include "stdio.h"
typedef struct {
    double tempsOperation;
    int *exclusion;
    int *precedence;
} t_operation;

typedef struct
{
    int **matriceExclusion;
    int **matricePrecedence;
}t_InfoAllOp;



void lecture(t_operation *TabOp,t_InfoAllOp *Tab1,int *tailleTab, int *tempsDeCyle, char *nomFichierExclusions,char *nomFichierOperations,char *nomFichierPrecedence,char *nomFichierTempsDeCycle);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_8_44_FONCTION_H
