#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Inclusion du header de Signature
#include "../Headers/Signature.h"

//fonction qui met en minuscule et qui enlève les espaces dans la chaine de caractère
//retourne un char sans espace en minuscule
char *string_treatment(char *chain)
{
    int i, j = 0;
    int a = strlen(chain);
    char *newChain = malloc(1024);

    if (newChain == NULL)
    {
        exit(0);
    }

    for (i = 0; i < a; i++)
    {
        if (chain[i] != ' ')
        {
            newChain[j++] = tolower(chain[i]);
        }
    }
    return newChain;
}

//Cette fonction permet de rechercher une chaine de caractère dans un fichier.
//retourne le nombre de fois que le string est présent dans le fichier
int search_in_File(char *pathFile, char *str)
{
    int line_num = 1;
    int find_result = 0;
    char data[1024];

    FILE *file = fopen(pathFile, "r");
    if (file == NULL)
    {
        return (-1);
    }

    while (!feof(file))
    {
        fgets(data, 1024, file);
        char *dataTraite = string_treatment(data);
        char *strTraite = string_treatment(str);
        if (strstr(dataTraite, strTraite) != NULL)
        {
            // printf("Suspect element on line: %d\n", line_num);
            find_result++;
        }
        line_num++;
    }

    if (file)
    {
        fclose(file);
    }
    return find_result;
}

//cette fonction permet d'extraire chaque pattern de virus de notre base virale.
//retourne une ligne d'un fichier sans les retours à la ligne
char *search_and_keep_line(char *pathFile, int line)
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
            string_treatment(buf);
            return buf;
        }
    }
    return "";
}

// cette fonction permet de rechercher les patterns de la base virale dans un fichier donnée.
//retourne nombre de fois que le virus est présent dans un fichier et ajoute le path dans le fichier listeContamination.txt
int search_virus_in_File(char *pathFile)
{
    int i = 1;
    int nombreVirusPresent = 0;
    FILE *baseVirale = fopen(pathBaseVirale, "r");
    if (baseVirale == NULL)
    {
        printf("Base virale inexistante: %s", pathBaseVirale);
        return (-1);
    }

    FILE *liste = fopen(pathListeContamine, "a");

    while (search_and_keep_line(pathBaseVirale, i) != "")
    {
        if (search_in_File(pathFile, search_and_keep_line(pathBaseVirale, i)) > 0)
        {
            nombreVirusPresent++;
        }
        i++;
    }

    //Si path non présent dans fichier liste, ajout de celui ci
    if ((nombreVirusPresent > 0) && (search_in_File(pathListeContamine, pathFile) == 0))
    {
        fprintf(liste, pathFile);
        fprintf(liste, "\n");
    }

    if (baseVirale)
    {
        fclose(baseVirale);
    }

    if (liste)
    {
        fclose(liste);
    }
    return nombreVirusPresent;
}

// void main()
// {
//     char pattern[] = "printf(\"virus 3, le toxic\\n\");";
//     char path[] = "../Tests/fichierContamine";
//     char path2[] = "../Tests/fichierClean";

// int nombre = search_in_File(path, pattern);
// printf("%s", pattern);
// printf("%d", nombre);
// printf("%s------------------------\n", search_and_keep_line(pathBaseVirale, 5));
// char ligne2[1024];
// printf("%s", search_and_keep_line(pathBaseVirale, 2));
// strcpy(ligne2, search_and_keep_line(pathBaseVirale, 5));
// printf("%s", ligne2);
// char *ligne;
// ligne = search_and_keep_line(pathBaseVirale, 1);
// printf("%s", ligne);
// strcpy(ligne2, search_and_keep_line(pathBaseVirale, 2));
// printf(ligne2);

// printf("*********Recherche dans un fichier contaminé**********\n");

// printf("%d virus trouvé /5\n", search_virus_in_File(path));

// printf("**********Recherche dans un fichier clean************\n");
// printf("%d virus trouvé / 0\n", search_virus_in_File(path2));

//    search_and_keep_line(pathBaseVirale, 2);
// }