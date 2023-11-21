#include <stdio.h>
#include <stdlib.h>

void lecture(int **tabS1, int **tabS2, int *nbLignes){
    FILE *fichier = NULL;
    char ligne[10];
    int compteur=0;

    fichier = fopen("arete.txt","r"); // ouverture du fichier
    if (fichier == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { //tant qu'on a des lignes on les additionne
        (*nbLignes)++;
    }

    // Allouer dynamiquement les tableaux en fonction de la taille
    *tabS1 = (int*)malloc((*nbLignes)*sizeof(int));
    *tabS2 = (int*)malloc((*nbLignes)*sizeof(int));

    // Retourner une erreur si l'allocation échoue
    if (*tabS1 ==NULL || *tabS2==NULL){
        printf("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*tabS1);
        free(*tabS2);
        exit(1);
    }

    // Réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL ){
        if (sscanf(ligne, "%d %d", &(*tabS1)[compteur], &(*tabS2)[compteur]) == 2){
            compteur++;
        }
    }

    // Fermer le fichier
    fclose(fichier);
}

int main(){
    int *tabS1, *tabS2;
    int nbLignes = 0;

    lecture(&tabS1, &tabS2, &nbLignes);

    for (int i=0; i<nbLignes; i++){            //vérifier les données
        printf("%d %d\n", tabS1[i], tabS2[i]);
    }
    printf("\nNombre de lignes: %d\n", nbLignes);

    //libérer la memoire
    free(tabS1);
    free(tabS2);

    return 0;
}
