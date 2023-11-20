//
// Created by mathe on 11/11/2023.
//
#include "stdio.h"
#include "fonction.h"
int main()
{
    printf("hello world");
    return 0;
}
void readExclusionConstraints(t_Exclusion *exclusionConstrainte, int *numConstrainte) {
    FILE *file = fopen("contraintes.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    *numConstraints = 0;
    while (fscanf(file, "%d %d", &exclusionContrainte[*numContrainte].operation1,
                  &exclusionContrainte[*numConstrainte].operation2) == 2)
    {
        (*numConstrainte)++;
    }

    fclose(file);
}