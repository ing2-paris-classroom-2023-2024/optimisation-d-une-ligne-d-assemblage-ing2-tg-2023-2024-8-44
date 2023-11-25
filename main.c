//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "src/fonction.c"


void lecture(int **tabS1, int **tabS2, int *nbLignes, char *nomFichier)
{


    FILE *fichier = NULL;
    char ligne[10];
    int compteur=0;

    fichier = fopen(nomFichier,"r"); // ouverture du fichier
    if (fichier == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { //tant qu'on a des lignes on les additionne
        (*nbLignes)++;
    }

    // allocation dynamique
    *tabS1 = (int*)malloc((*nbLignes)*sizeof(int));
    *tabS2 = (int*)malloc((*nbLignes)*sizeof(int));

    // si problème avec les tableaux on sort du programme
    if (*tabS1 ==NULL || *tabS2==NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*tabS1);
        free(*tabS2);
        exit(1);
    }

    // réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL ){
        if (sscanf(ligne, "%d %d", &(*tabS1)[compteur], &(*tabS2)[compteur]) == 2){
            compteur++;
        }
    }

    fclose(fichier);
}


int main()
{
    int *tabPrecedence1, *tabPrecedence2;
    int *tabTempsCycle1, *tabTempsCycle2;
    int nbLignes = 0;
    char nomFichier[20];

    printf("Donnez le nom du fichier precedences:");
    scanf("%s", nomFichier);
    lecture(&tabPrecedence1, &tabPrecedence2, &nbLignes, nomFichier);
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
    return 0;
}