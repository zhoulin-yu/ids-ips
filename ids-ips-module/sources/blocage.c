#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

//Inclusion du header de Blocage
#include "../Headers/Main.h"

//cette fonction a pour but de récupéré le nom du fichier dans un chemin d'accès
//retourne le nom du fichier.
char *search_name_of_file_in_path(char *pathFile)
{
    size_t size = strlen(pathFile);
    char *fileName = malloc(size * sizeof(char) + 1);
    strcpy(fileName, pathFile);
    fileName = strrchr(fileName, '/');
    size_t sizeFileName = strlen(fileName);

    for (int i = 0; i < sizeFileName; i++)
    {
        fileName[i] = fileName[i + 1];
    }

    return fileName;
}

//cette fonction permet de vérifier si le fichier existe
//retourne 1 s'il existe et 0 s'il existe pas
int checkIfFileExists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}

// cette fonction va permettre de mettre en quarantaine les fichiers contaminés en leur retirant la fonction éxécutable et lecture
//retourne rien mais fait de la gestion de fichier
void quarantine_placement(char *pathFile)
{
    char *quarantine = "../quarantaine/";
    if (checkIfFileExists(pathFile) == 1)
    {
        chmod(pathFile, 0000000);
        char *fileName = search_name_of_file_in_path(pathFile);
        int fullsize = strlen(quarantine) + 1 + strlen(fileName) + 1;
        char *newPath = malloc(fullsize);
        strcat(newPath, quarantine);
        strcat(newPath, "/");
        strcat(newPath, fileName);
        rename(pathFile, newPath);
    }
    else
    {
        printf("fichier inexistant \n");
    }
}

//cette fonction détruira le fichier contaminé s'il existe
//retourne rien mais fait de la gestion de fichier
void block_file(char *pathFile)
{
    if (checkIfFileExists(pathFile) == 1)
    {
        remove(pathFile);
    }
    else
    {
        printf("fichier inexistant \n");
    }
}

void main()
{
    FILE *fileTest1 = fopen("../Tests/fileTest", "a");
    FILE *fileTest2 = fopen("../Tests/fileTest2", "a");

    block_file("../Tests/fileTest");
    quarantine_placement("../Tests/fileTest2");
    char *name = search_name_of_file_in_path(pathListeContamine);
    printf("%s", name);
}