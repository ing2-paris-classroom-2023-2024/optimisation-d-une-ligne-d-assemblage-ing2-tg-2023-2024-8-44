//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "precedencesEtTemps.c"


void lecture(int **tabS1, int **tabS2, int *nbLignes, char *nomFichier)
{
    FILE *fichier = NULL;
    char ligne[10];
    int compteur=0;
    int nbLignesLecture = 0;

    int *tabS1Lecture, *tabS2Lecture;


    fichier = fopen(nomFichier,"r"); // ouverture du fichier
    if (fichier == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne,1000,fichier)!=NULL) { //tant qu'on a des lignes on les additionne
        (nbLignesLecture)++;
    }

    *nbLignes = nbLignesLecture;
    // allocation dynamique
    tabS1Lecture = malloc((nbLignesLecture+1)*sizeof(int));
    tabS2Lecture = malloc((nbLignesLecture+1)*sizeof(int));



    // si problème avec les tableaux on sort du programme
    if (tabS1Lecture ==NULL || tabS2Lecture==NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(tabS1);
        free(tabS2);
        exit(1);
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, 1000, fichier) != NULL){
        sscanf(ligne, "%d %d", &tabS1Lecture[compteur], &tabS2Lecture[compteur]);
        compteur++;
    }
    *tabS1 = tabS1Lecture;
    *tabS2 = tabS2Lecture;
    fclose(fichier);
}


int main()
{
    int *tabPrecedence1 , *tabPrecedence2 = NULL;
    int *tabTempsCycle1 = NULL, *tabTempsCycle2 = NULL;
    int nbLignes = 0;
    char nomFichier[20];

    printf("Donnez le nom du fichier precedences:");
    scanf("%s", nomFichier);
    lecture(&tabPrecedence1, &tabPrecedence2, &nbLignes, nomFichier);
    printf("%d\n",nbLignes);
    for (int i=0; i<nbLignes; i++){            //vérifier les données
        printf("%d %d\n", tabPrecedence1[i], tabPrecedence2[i]);
    }
    printf("\nNombre de lignes: %d\n", nbLignes);
    nbLignes = 0;

    printf("Donnez le nom du fichier temps de cycle:");
    scanf("%s", nomFichier);
    lecture(&tabTempsCycle1, &tabTempsCycle2, &nbLignes, nomFichier);
    for (int i=0; i<nbLignes; i++){            //vérifier les données
        printf("%d %d\n", tabPrecedence1[i], tabPrecedence2[i]);
    }
    printf("\nNombre de lignes: %d\n", nbLignes);

    //libérer la memoire
    free(tabPrecedence1);
    free(tabPrecedence2);
    printf("ca grand ;ere");
    printf("test");
    printf("test232");
    return 0;
}