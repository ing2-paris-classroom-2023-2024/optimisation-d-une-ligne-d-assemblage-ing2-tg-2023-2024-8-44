///
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "../include/fonction.h"

bool checkIfOpExist(const int *tabOpExistant, int ordre, int opToCheck)
{
    for(int i=0;i<ordre;i++)
    {
        if(opToCheck ==  tabOpExistant[i])
        {
            return true;
        }
    }
    return false;
}

int ** lectureExclusion(int tailleMatriceExclusion, char *nomFichierExclusions, int *tabOpExistant, int ordre)
{
    FILE *fichierExclusions = NULL;
    char ligne[10];
    int valeurTmp,valeurTmp2;
    int **MatriceExclusionARendre;

//    printf("Taille de la matrice Exclusion: %d\n",tailleMatriceExclusion);

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
            if(checkIfOpExist(tabOpExistant,ordre,i)&&(checkIfOpExist(tabOpExistant,ordre,j)))
            {
                MatriceExclusionARendre[i][j]=0;
            }
            else
            {
                MatriceExclusionARendre[i][j] = -1;
            }
        }
    }

    while (fgets(ligne,tailleMatriceExclusion,fichierExclusions) != NULL){
        sscanf(ligne, "%d %d",&valeurTmp,&valeurTmp2);
        MatriceExclusionARendre[valeurTmp][valeurTmp2]=1;
//        printf("%d %d\n",valeurTmp,valeurTmp2);
    }

    fclose(fichierExclusions);
    return MatriceExclusionARendre;
}

bool checkIfExclusion(int op1, int op2,int **MatriceExlcusion)
{
    return (MatriceExlcusion[op1][op2]==1||MatriceExlcusion[op2][op1]==1);
}

//push test ef
float GetTempsDeCycleToOp(t_OpTempsDeCyle *Opstruct, int opToCheck, int ordre)
{
    for(int i=0;i<ordre;i++)
    {
        if(opToCheck == Opstruct[i].idOp)
        {
            return Opstruct[i].tempsDeCycle;
        }
    }
    return 0;
}

//Test de push

void parcourirExclusionToutSeul(int **MatriceExlcusion,int tailleMatriceExclusion,t_stations *stations, int *tabOpExistant, int ordre) {
    int degres[tailleMatriceExclusion + 1];
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {

        //Permet de mettre les degres des  operations non exitstance a -1
        if (MatriceExlcusion[i][i]==-1)
        {
            degres[i] = -1;
        }
        else
        {
            degres[i] = 0;
            for (int j = 0; j <= tailleMatriceExclusion; ++j) {
                if (checkIfExclusion(i, j, MatriceExlcusion) == 1) {
                    degres[i]++;
                };

            }
        }
        printf("opération %d degrés %d\n", i, degres[i]);
    }
    // Trie des indices en fonction des degrés (ordre décroissant)
    int indices[tailleMatriceExclusion + 1];
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        indices[i] = i;
    }

    for (int i = 0; i < tailleMatriceExclusion; ++i) {
        for (int j = i + 1; j <= tailleMatriceExclusion; ++j) {
            if (degres[indices[j]] > degres[indices[i]]) {
                // Échange des indices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Affichage des opérations triées par ordre décroissant de degrés
    printf("Opérations triées par ordre décroissant de degrés :\n");
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        printf("Opération %d -> Degré %d\n", indices[i], degres[indices[i]]);
    }
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        int operation = indices[i];  // Récupérer l'opération après le tri
        //si l'opération n'existe pas nous la mettons dans une station spéciale
        if(degres[operation]==0||degres[operation]==-1){
            stations[operation].id=-1;
        }


        // Mise à jour des stations pour les opérations suivantes
        for (int j = i + 1; j <= tailleMatriceExclusion; ++j) {
            int autreOperation = indices[j];
            // Récupérer l'opération après le tri
            if (checkIfExclusion(operation, autreOperation, MatriceExlcusion) == 1&& stations[autreOperation].id == 1) {
                if(stations[operation].id>1){
                    for (int k = 0; k <=operation ; ++k) {
                        if (checkIfExclusion(operation-k, autreOperation, MatriceExlcusion) == 1){
                            stations[autreOperation].id = stations[operation].id+1 ;
                        }
                        else{
                            stations[autreOperation].id = stations[operation].id-1;
                        }
                        printf("%d\n",k);
                    }
                    printf("sortie\n");
                }
                else{
                    stations[autreOperation].id =stations[operation].id+1 ; // Attribuer une nouvelle station pour l'opération exclue
                }

            }
        }

    }
}

bool checkIfTabEmpty(const int *tab,int taille)
{
    for(int i=0;i<taille;i++)
    {
        if(tab[i]!=0)
        {
            return false;
        }
    }
    return true;
}


void parcourirTempsDeCycleAvecExclusion(int **MatriceExlcusion,int tailleMatriceExclusion, t_OpTempsDeCyle *OpStruct, int ordre, Stack * AllStation, float tempsDeCyle,int *nbStation) {
    int degres[tailleMatriceExclusion + 1];
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {

        //Permet de mettre les degres des  operations non exitstance a -1
        if (MatriceExlcusion[i][i]==-1)
        {
            degres[i] = -1;
        }
        else
        {
            degres[i] = 0;
            for (int j = 0; j <= tailleMatriceExclusion; ++j) {
                if (checkIfExclusion(i, j, MatriceExlcusion) == 1) {
                    degres[i]++;
                };

            }
        }
    }
    // Trie des indices en fonction des degrés (ordre décroissant)
    int indices[tailleMatriceExclusion + 1];
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        if(degres[i]==-1)
        {
            indices[i]=0;
        }
        else
        {
            indices[i] = i;
        }
    }

    for (int i = 0; i < tailleMatriceExclusion; ++i) {
        for (int j = i + 1; j <= tailleMatriceExclusion; ++j) {
            if (degres[indices[j]] > degres[indices[i]]) {
                // Échange des indices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    int i=0;
    int a=0;
    initializeStack(&AllStation[i],tailleMatriceExclusion +1);


    while (!checkIfTabEmpty(indices,tailleMatriceExclusion))
    {
        if(a>tailleMatriceExclusion)
        {
            i++;
//            printf("changement de station vers %d\n",i+1);
            realloc(AllStation,sizeof (Stack)*(i+1));
            initializeStack(&AllStation[i],tailleMatriceExclusion+1);
            a=0;
        }
        int operation = indices[a];
        bool pushOp = 1;
        if(isEmpty(&AllStation[i]))
        {
//            printf("empty\n");
            if(push(&AllStation[i],operation,tempsDeCyle, GetTempsDeCycleToOp(OpStruct,operation,ordre),2))
            {
                indices[a]=0;
            }
            a++;
        }
        else
        {
            for(int j=0;j<AllStation[i].nbOpe;j++)
            {
                if(checkIfExclusion(operation,AllStation[i].operation[j],MatriceExlcusion))
                {

                    pushOp=0;
                    a++;
                    break;
                }
            }
            if(pushOp)
            {
                if(push(&AllStation[i],operation,tempsDeCyle, GetTempsDeCycleToOp(OpStruct,operation,ordre),2))
                {
                    indices[a]=0;
                }
                a++;
            }
            else
            {
                if(isFull(&AllStation[i],tempsDeCyle, GetTempsDeCycleToOp(OpStruct,operation,ordre)))
                {
                    i++;
//                    printf("changement de station vers %d\n",i+1);
                    realloc(AllStation,sizeof (Stack)*(i+1));
                    initializeStack(&AllStation[i],tailleMatriceExclusion+1);
                    a=0;
                }

            }
//            printf("%d\n",a);
        }
    }
    *nbStation=i;
}
///ALGORITHME DE WELSH POWELL
void parcourirExclusion(int **MatriceExlcusion,int tailleMatriceExclusion,t_stations *stations, t_OpTempsDeCyle *OpStruct, int ordre)
{
    int degres[tailleMatriceExclusion + 1];//tableau comportant le degrés des operations
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {

        //Permet de mettre les degres des  operations non exitstance a -1
        if (MatriceExlcusion[i][i]==-1)
        {
            degres[i] = -1;
        }
        else
        {
            degres[i] = 0;
            for (int j = 0; j <= tailleMatriceExclusion; ++j) {
                if (checkIfExclusion(i, j, MatriceExlcusion) == 1) {
                    degres[i]++;// affectation des degrés a chaque opération en fonction des exclusions
                };

            }
        }
        printf("opération %d degrés %d\n", i, degres[i]);
    }
    // Trie des indices en fonction des degrés (ordre décroissant)
    int indices[tailleMatriceExclusion + 1];
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        indices[i] = i;
    }

    for (int i = 0; i < tailleMatriceExclusion; ++i) {
        for (int j = i + 1; j <= tailleMatriceExclusion; ++j) {
            if (degres[indices[j]] > degres[indices[i]]) {
                // Échange des indices afin de mettre les opération au degrés les plus forts en premier
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    // Affichage des opérations triées par ordre décroissant de degrés
    printf("Opérations triées par ordre décroissant de degrés :\n");
    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        printf("Opération %d -> Degré %d\n", indices[i], degres[indices[i]]);
    }
    int operation=0;
    float currentStation=stations[operation].tempsDeCycle;

    for (int i = 0; i <= tailleMatriceExclusion; ++i) {
        operation = indices[i];  // Récupérer l'opération après le tri
        //si l'opération n'existe pas nous la mettons dans une station spéciale
        if(degres[operation]==-1){
            stations[operation].id=-1;
        }
        //currentStation+=GetTempsDeCycleToOp(OpStruct,operation,ordre);
        //printf("\n%f\n", currentStation);

        // Mise à jour des stations pour les opérations suivantes
        for (int j = i + 1; j <= tailleMatriceExclusion; ++j) {
            int autreOperation = indices[j];
            // Récupérer l'opération après le tri
            if (checkIfExclusion(operation, autreOperation, MatriceExlcusion) == 1&& stations[autreOperation].id == 1) {
                if(stations[operation].id>1){
                    for (int k = 0; k <=operation ; ++k) {
                        if (checkIfExclusion(operation-k, autreOperation, MatriceExlcusion) == 1){
                            stations[autreOperation].id = stations[operation].id+1 ;
                        }
                        else{
                            stations[autreOperation].id = stations[operation].id-1;//attribuer la station précdente si l'opération n'y a aucune exclusion
                        }
                    }
                }
                else{
                    stations[autreOperation].id =stations[operation].id+1 ; // Attribuer une nouvelle station pour l'opération exclue
                }

            }
        }

    }
}