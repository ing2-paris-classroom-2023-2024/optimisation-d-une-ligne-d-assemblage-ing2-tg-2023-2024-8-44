#include "header.h"
#include "fonction.h"


void parcourirTempsDeCycleAvecExclusionEtPrecedence(int **MatriceExlcusion,int tailleMatriceExclusion, t_OpTempsDeCyle *OpStruct, int ordre, Stack * AllStation, float tempsDeCyle,int *nbStation, int *Tabtache, int nbTache) {



    int i=0;
    int a=0;
    initializeStack(&AllStation[i],tailleMatriceExclusion +1);


    while (!checkIfTabEmpty(Tabtache,nbTache))
    {
        if(a>nbTache)
        {
            i++;
//            printf("changement de station vers %d\n",i+1);
            realloc(AllStation,sizeof (Stack)*(i+1));
            initializeStack(&AllStation[i],tailleMatriceExclusion+1);
            a=0;
        }
        int operation = Tabtache[a];
        bool pushOp = 1;
        if(isEmpty(&AllStation[i]))
        {
//            printf("empty\n");
            if(push(&AllStation[i],operation,tempsDeCyle, GetTempsDeCycleToOp(OpStruct,operation,ordre),2))
            {
//                printf("push : %d\n",operation);
                Tabtache[a]=0;
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
//                    printf("push : %d\n",operation);
                    Tabtache[a]=0;
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



void precedenceEtExclusionEtTempsDeCycle()
{
    // Afficher les contraintes de précédence et temps de cycle

    FILE *pf =NULL;
    pf = fopen("../fileTexte/sauvegarde.txt","w");
    int *tabPrecedence1=NULL, *tabPrecedence2=NULL;
    int *opSommets=NULL;
    float *opTemps=NULL;
    int tempsCycle = 0, nbLignesPrecedence = 0, nbLignesOperations=0, nbLignesExclusions=0;
    int *sommets = NULL;

    /// LECTURE FICHIER ///
    lecture(&tabPrecedence1, &tabPrecedence2, &nbLignesPrecedence, &nbLignesOperations, &tempsCycle, &opSommets, &opTemps);


    ///DONNEES GRAPHE ///
    int ordre = nbLignesOperations;
    int taille = nbLignesPrecedence;
    int sommetMax = opSommets[nbLignesOperations-1];
    int **MatriceExclusion;

    t_OpTempsDeCyle *Opstruct;

    lectureExclusion(sommetMax,"../fileTexte/exclusions.txt",opSommets,ordre);
    Opstruct = malloc(sizeof (t_OpTempsDeCyle)*ordre);

    lectureTempsDeCycleOp(Opstruct);


    ///Creer la matrice d'exclusion///
    MatriceExclusion = lectureExclusion(sommetMax,"../fileTexte/exclusions.txt",opSommets,ordre);


    /// creer le graphe ///
    Graphe* graphe = creerGraphe(sommetMax+1);
    for (int i=0; i<taille; i++){ // Ajouter des arcs au graphe
        ajouterArc(graphe, tabPrecedence1[i], tabPrecedence2[i]);
    }



    /// TACHES ///
    Tache taches[sommetMax];
    //PrecedenceEtTempsSuitee(taches, opSommets, nbLignesOperations, opTemps, sommetMax, tabPrecedence1, tabPrecedence2, taille, tempsCycle);

    int* Tache;

    Tache = PrecedenceEtTempsPourExclusion(taches,opSommets,nbLignesOperations,opTemps,sommetMax,tabPrecedence1,tabPrecedence2,taille,tempsCycle);

    int nbStation=0;

    Stack * AllStation;
    AllStation = malloc(sizeof (Stack));
    realloc(AllStation,sizeof (Stack));

    //V2:
    parcourirTempsDeCycleAvecExclusionEtPrecedence(MatriceExclusion,sommetMax,Opstruct,ordre,AllStation,(float)tempsCycle,&nbStation,Tache,taille);
    for(int i=0;i<nbStation+1;i++)
    {
        printf("Station : %d\n",i+1);
        fprintf(pf,"station :%d\n",i+1);
        display(&AllStation[i],pf);
    }
    /// MULTI CONTRAINTE ///
    //PrecedenceCycleContrainte(taches, opSommets, nbLignesOperations, opTemps, sommetMax, tabPrecedence1, tabPrecedence2, tabExclusions1, tabExclusions2, taille, tempsCycle);


    /// MEMOIRE ///
    //libérer la memoire
    free(tabPrecedence1);
    free(tabPrecedence2);
    free(opSommets);
    free(opTemps);
    free(sommets);
    free(graphe);
    fclose(pf);
}

