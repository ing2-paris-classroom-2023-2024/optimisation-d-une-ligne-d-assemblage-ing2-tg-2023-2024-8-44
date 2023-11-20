#include <stdio.h>
#include <stdlib.h>

void lecture(int **tabS1, int **tabS2, int *nbLignes){
    FILE *fichier = NULL;
    char ligne[10];
    int i=0;

    fichier = fopen("arete.txt", "r"); // Ouvrir le fichier en mode lecture et vérifier s'il s'ouvre
    if (fichier == NULL){
        printf("Erreur ouverture fichier");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { // Compter le nombre de lignes dans le fichier
        (*nbLignes)++;
    }

    // Allouer dynamiquement les tableaux en fonction de la taille
    *tabS1 = (int*)malloc((*nbLignes)*sizeof(int));
    *tabS2 = (int*)malloc((*nbLignes)*sizeof(int));

    // Retourner une erreur si l'allocation échoue
    if (*tabS1 ==NULL || *tabS2==NULL){
        perror("Erreur d'allocation de mémoire");
        fclose(fichier);
        free(*tabS1);
        free(*tabS2);
        exit(1);
    }

    // Réinitialiser le pointeur du fichier au début
    fseek(fichier, 0, SEEK_SET);

    // vérifier si la ligne n'est pas vide et si elle contient bien 2 entiers
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && i < *nbLignes) {
        if (sscanf(ligne, "%d %d", &(*tabS1)[i], &(*tabS2)[i]) == 2){
            i++;
        }
    }

    // Fermer le fichier
    fclose(fichier);
}

int main(){
    int *tabS1, *tabS2;
    int nbLignes = 0;

    lecture(&tabS1, &tabS2, &nbLignes);

    for (int i = 0; i < nbLignes; i++) {            //vérifier les données
        printf("%d %d\n", tabS1[i], tabS2[i]);
    }

    // Libérer la mémoire allouée dynamiquement
    free(tabS1);
    free(tabS2);

    return 0;
}
