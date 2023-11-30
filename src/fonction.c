//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "limits.h"
#include "../include/fonction.h"
#define MAX_OPERATIONS 35
#define MAX_STATIONS 10


//void readExclusionConstraints(t_Exclusion *exclusionConstrainte, int *numConstrainte) {
//    FILE *file = fopen("contraintes.txt", "r");
//    if (file == NULL) {
//        perror("Erreur lors de l'ouverture du fichier");
//        exit(EXIT_FAILURE);
//    }
//    *numConstrainte = 0;
//    while (fscanf(file, "%d %d", &exclusionConstrainte[*numConstrainte].operation1,
//                  &exclusionConstrainte[*numConstrainte].operation2) == 2)
//    {
//        (*numConstrainte)++;
//    }
//
//    fclose(file);
//}
//int Respect_contrainte(int stationAssignment[MAX_OPERATIONS], t_Exclusion constraint) {
//    return (stationAssignment[constraint.operation1 - 1] != stationAssignment[constraint.operation2 - 1]);
//}
//
//void assignStations(int stationAssignment[MAX_OPERATIONS], int numStations, t_Exclusion *exclusionConstraints, int numConstraints) {
//    for (int i = 0; i < MAX_OPERATIONS; i++) {
//        stationAssignment[i] = 0; // INITIALISER TOUTES LES STATIONS A 0
//    }
//
//    for (int i = 0; i < numConstraints; i++) {
//        if (Respect_contrainte(stationAssignment, exclusionConstraints[i])) {
//            // ASSIGNER LES DIFFERENTES OPERATIONS AUX STATIONS
//            stationAssignment[exclusionConstraints[i].operation1 - 1] = 1;
//            stationAssignment[exclusionConstraints[i].operation2 - 1] = 2;
//        }
//    }
//}
//
//void printStationAssignment(int stationAssignment[MAX_OPERATIONS]) {
//    printf("Répartition des opérations sur les stations de travail :\n");
//    for (int i = 0; i < MAX_OPERATIONS; i++) {
//        printf("Opération %d -> Station %d\n", i + 1, stationAssignment[i]);
//    }
//}

void lectureMatheo(t_operation *TabOp,t_InfoAllOp *InfoTab,int *tailleTab, int *tempsDeCyle, char *nomFichierExclusions,char *nomFichierOperations,char *nomFichierPrecedence,char *nomFichierTempsDeCycle)
{
    FILE *fichierOperation = NULL;
    FILE *fichierExclusions = NULL;
    FILE *fichierPrecedences = NULL;
    FILE *fichierTempsDeCyle = NULL;
    char ligne[10];
    int compteur=0;
    int nbLignesLecture = 0;
    int valeurTmp,valeurTmp2;
    double valeurLectureDouble;


    fichierOperation = fopen(nomFichierOperations,"r"); // ouverture du fichier operation
    if (fichierOperation == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne,INT_MAX,fichierOperation)!=NULL) { //tant qu'on a des lignes on les additionne
        nbLignesLecture++;
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichierOperation, 0, SEEK_SET);

    //allocation dynamique pour gérer la structure TabOp
    TabOp = malloc(sizeof(t_operation)*nbLignesLecture);

    //garder la taille du tableau de TabOp
    *tailleTab=nbLignesLecture;

    printf("%d\n",*tailleTab);

    //s'il y a un problème avec les tableaux, on sort du programme
    if (TabOp ==NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichierOperation);
        free(TabOp);
        exit(1);
    }


    // vérifier si la ligne n'est pas vide et si elle contient bien 1 entier et un double
    while (fgets(ligne,nbLignesLecture,fichierOperation) != NULL){
        sscanf(ligne, "%d %lf",&valeurTmp, &valeurLectureDouble);
        TabOp[valeurTmp-1].tempsOperation=valeurLectureDouble;
        printf("%d %lf\n",valeurTmp,TabOp[valeurTmp-1].tempsOperation);
    }

    fclose(fichierOperation);
    nbLignesLecture = 0;

    fichierExclusions = fopen(nomFichierExclusions,"r"); // ouverture du fichier
    if (fichierExclusions == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    InfoTab->matriceExclusion = malloc(sizeof (int*)*(*tailleTab));
    if (InfoTab->matriceExclusion == NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichierExclusions);
        free(InfoTab);
        exit(1);
    }
    for (int i=0;i<(*tailleTab);i++)
    {
        InfoTab->matriceExclusion[i] = malloc(sizeof (int)*(*tailleTab));
        if (InfoTab->matriceExclusion[i] ==NULL){
            printf("Erreur d'allocation de mémoire");
            fclose(fichierExclusions);
            free(InfoTab);
            exit(1);
        }
    }

    for(int i=0;i<(*tailleTab);i++)
    {
        for(int j=0;j<(*tailleTab);j++)
        {
            InfoTab->matriceExclusion[i][j]=0;
        }
    }
    while (fgets(ligne,INT_MAX,fichierExclusions)!=NULL) { //tant qu'on a des lignes on les additionne
        nbLignesLecture++;
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichierExclusions, 0, SEEK_SET);

    while (fgets(ligne,nbLignesLecture,fichierExclusions) != NULL){
        sscanf(ligne, "%d %d",&valeurTmp,&valeurTmp2);
        InfoTab->matriceExclusion[valeurTmp-1][valeurTmp2-1]=1;
        printf("%d %d\n",valeurTmp,valeurTmp2);
    }

    for(int i=0;i<(*tailleTab);i++)
    {
        for(int j=0;j<(*tailleTab);j++)
        {
            printf("%d ",InfoTab->matriceExclusion[i][j]);
        }
        printf("\n");
    }

    fclose(fichierExclusions);
    nbLignesLecture = 0;

    fichierPrecedences = fopen(nomFichierPrecedence,"r"); // ouverture du fichier
    if (fichierPrecedences == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    InfoTab->matricePrecedence = malloc(sizeof (int*)*(*tailleTab));
    if (InfoTab->matricePrecedence == NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichierPrecedences);
        free(InfoTab);
        exit(1);
    }
    for (int i=0;i<(*tailleTab);i++)
    {
        InfoTab->matricePrecedence[i] = malloc(sizeof (int)*(*tailleTab));
        if (InfoTab->matricePrecedence[i] ==NULL){
            printf("Erreur d'allocation de mémoire");
            fclose(fichierPrecedences);
            free(InfoTab);
            exit(1);
        }
    }

    for(int i=0;i<(*tailleTab);i++)
    {
        for(int j=0;j<(*tailleTab);j++)
        {
            InfoTab->matricePrecedence[i][j]=0;
        }
    }
    while (fgets(ligne,INT_MAX,fichierPrecedences)!=NULL) { //tant qu'on a des lignes on les additionne
        nbLignesLecture++;
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichierPrecedences, 0, SEEK_SET);

    while (fgets(ligne,nbLignesLecture,fichierPrecedences) != NULL){
        sscanf(ligne, "%d %d",&valeurTmp,&valeurTmp2);
        InfoTab->matricePrecedence[valeurTmp-1][valeurTmp2-1]=1;
        printf("%d %d\n",valeurTmp,valeurTmp2);
    }

    for(int i=0;i<(*tailleTab);i++)
    {
        for(int j=0;j<(*tailleTab);j++)
        {
            printf("%d ",InfoTab->matricePrecedence[i][j]);
        }
        printf("\n");
    }
    fclose(fichierPrecedences);


    fichierTempsDeCyle = fopen(nomFichierTempsDeCycle,"r"); // ouverture du fichier
    if (fichierTempsDeCyle == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }
    sscanf(ligne, "%d",tempsDeCyle);
    printf("%d\n",*tempsDeCyle);

    fclose(fichierTempsDeCyle);



}