//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdbool.h"
#include "../include/fonction.h"

int ** lectureExclusion(int tailleMatriceExclusion, char *nomFichierExclusions)
{
    FILE *fichierExclusions = NULL;
    char ligne[10];
    int valeurTmp,valeurTmp2;
    int **MatriceExclusionARendre;

    printf("Taille de la matrice Exclusion: %d\n",tailleMatriceExclusion);

    fichierExclusions = fopen(nomFichierExclusions,"r"); // ouverture du fichier
    if (fichierExclusions == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    MatriceExclusionARendre = malloc(sizeof (int*)*(tailleMatriceExclusion+1));
    if (MatriceExclusionARendre == NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichierExclusions);
        free(MatriceExclusionARendre);
        exit(1);
    }
    for (int i=0;i<(tailleMatriceExclusion+1);i++)
    {
        MatriceExclusionARendre[i] = malloc(sizeof (int)*(tailleMatriceExclusion+1));
        if (MatriceExclusionARendre[i] ==NULL){
            printf("Erreur d'allocation de mémoire");
            fclose(fichierExclusions);
            free(MatriceExclusionARendre);
            exit(1);
        }
    }

    for(int i=0;i<(tailleMatriceExclusion+1);i++)
    {
        for(int j=0;j<(tailleMatriceExclusion+1);j++)
        {
            MatriceExclusionARendre[i][j]=0;
        }
    }
    printf("zef");

    while (fgets(ligne,tailleMatriceExclusion,fichierExclusions) != NULL){
        sscanf(ligne, "%d %d",&valeurTmp,&valeurTmp2);
        MatriceExclusionARendre[valeurTmp][valeurTmp2]=1;
        printf("%d %d\n",valeurTmp,valeurTmp2);
    }

    for(int i=0;i<(tailleMatriceExclusion+1);i++)
    {
        for(int j=0;j<(tailleMatriceExclusion+1);j++)
        {
            printf("%d ",MatriceExclusionARendre[i][j]);
        }
        printf("\n");
    }

    fclose(fichierExclusions);
    return MatriceExclusionARendre;
}

bool checkIfExclusion(int op1, int op2,int **MatriceExlcusion)
{
    return (MatriceExlcusion[op1][op2]==1||MatriceExlcusion[op2][op1]==1);
}