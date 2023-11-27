//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "src/fonction.h"


int main()
{
    char nomFichierExclusions[20];
    char nomFichierOperations[20];
    char nomFichierPrecedences[20];
    char nomFichierTempsCycle[20];

    t_operation *TabOp = NULL;
    t_InfoAllOp InfoTab;
    int tailleTabOp;
    int tempsDeCycle;


//    printf("Donnez le nom du fichier exclusions:");
//    scanf("%s", nomFichierExclusions);
//    printf("Donnez le nom du fichier precedences:");
//    scanf("%s", nomFichierPrecedences);
//    printf("Donnez le nom du fichier operations:");
//    scanf("%s", nomFichierOperations);
//    printf("Donnez le nom du fichier temps de cycle:");
//    scanf("%s", nomFichierTempsCycle);


    lecture(TabOp,&InfoTab, &tailleTabOp, &tempsDeCycle, "../fileTexte/exclusions.txt","../fileTexte/operations.txt","../fileTexte/precedences.txt","../fileTexte/temps_cycle.txt");
    return 0;
}