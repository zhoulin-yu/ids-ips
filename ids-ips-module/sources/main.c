#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//Inclusion des headers
#include "../Headers/Main.h"
//#include "../Headers/Recherche.h"
#include "../Headers/Signature.h"
#include "../Headers/Comportement.h"
#include "../Headers/Blocage.h"

//path vers baseVirale
#define pathBaseVirale "BaseVirale/basevirale.txt"
//** PREREQUIS BASE VIRAL: Chaque pattern de virus doit être sur une ligne **//

// path vers la liste des fichiers contaminés
#define pathListeContamine "Analyses/listeContamination.txt"

//path vers fichier analyse
#define pathAnalyse "Analyses/Analyse.txt"

// Cette fonction permet d'incrémenter un compteur de fichier infecté.
//retourne le nombre de fichier infecté
int count_threat()
{
    int cpt = 0;
    FILE *liste = fopen(pathListeContamine, "r");
    if (liste == NULL)
    {
        printf("can't open: %s\n", pathListeContamine);
        return (-1);
    }
    char data[1024];
    while (fgets(data, 1024, liste) != NULL)
    {
        cpt++;
    }
    return cpt;
}

char *search_and_keep_path(char *pathFile, int line)
{
    char *buf = malloc(1024);
    FILE *file;
    if ((file = fopen(pathFile, "r")) == NULL)
    {
        printf("open file fail");
    }
    for (int i = 0; !feof(file) && i < line; i++)
    {
        fgets(buf, 1024, file);
        if (i == line - 1)
        {
            char *tmp = NULL;
            //Cette condition nous permet de ne pas prendre en compte le retour à la ligne à la fin des lignes de la base virale.
            if (tmp = strstr(buf, "\n"))
            {
                *tmp = '\0';
            }
            return buf;
        }
    }
    return "";
}

void all_quarantine()
{
   char *pathInfecte= malloc(1024);
    int nombreVirus = count_threat();
    for(int i = 1; i<=nombreVirus; i++){
        pathInfecte = search_and_keep_path(pathListeContamine,i);
        quarantine_placement(pathInfecte);
    }
}


void all_block()
{
    char *pathInfecte = malloc(1024);
    int nombreVirus = count_threat();
    for (int i = 1; i <= nombreVirus; i++)
    {
        pathInfecte = search_and_keep_path(pathListeContamine, i);
        block_file(pathInfecte);
    }
}

int first_analysis()
{
    //recherche_global
    FILE *analyse = fopen(pathAnalyse, "r");
    if (analyse == NULL)
    {
        printf("can't open file: %s\n", pathAnalyse);
        return (-1);
    }
    char data[1024];
    char *tmp = NULL;

    while (fgets(data, 1024, analyse) != NULL)
    {
        if (tmp = strstr(data, "\n"))
        {
            *tmp = '\0';
        }
        search_virus_in_File(data);
    }
    if (analyse)
    {
        fclose(analyse);
    }
    return count_threat();
}

void main()
{
    printf("%s \n", pathAnalyse);
    int nombreVirus = first_analysis();
    printf("%d \n", nombreVirus);
    all_quarantine();
    all_block();
}