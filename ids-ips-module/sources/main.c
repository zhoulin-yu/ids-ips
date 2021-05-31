#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//Inclusion des headers
#include "../Headers/Main.h"
#include "../Headers/search.h"
#include "../Headers/Signature.h"
#include "../Headers/Comportement.h"
#include "../Headers/Blocage.h"

//path vers baseVirale
#define pathBaseVirale "BaseVirale/basevirale.txt"
//** PREREQUIS BASE VIRAL: Chaque pattern de virus doit être sur une ligne **//

// path vers la liste des fichiers contaminés
#define pathListeContamine "Analyses/listeContamination.txt"

//path vers fichiers analyses
#define pathAnalyse "Analyses/analyse.txt"
#define pathAnalyseGlobale "Analyses/analyseGlobale.txt"
#define pathNouvelleAnalyseGlobale "Analyses/nouvelleAnalyseGlobale.txt"

// Cette fonction permet d'incrémenter un compteur de fichier infecté.
//retourne le nombre de fichier infecté
int count_threat()
{
    int cpt = 0;
    FILE *liste = fopen(pathListeContamine, "r");
    if (liste == NULL)
    {
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

    remove_analyse_and_listeContamine();
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

    remove_analyse_and_listeContamine();
}

//si analyse globale existe alors ce n'est pas la première analyse et on peut donc faire une analyse par comportement sinon on fait qu'une analyse par signature
int analysis_treatment()
{
    if(checkIfFileExists(pathAnalyseGlobale == 1)){


        //recherche_global
        //analyse par comportement
        char *arg[10];
        arg[0] = "/";
        int typeAnalyse = lancementAnalyse(2,"/");
        FILE *analyse = fopen(pathAnalyse, "r");
        if (analyse == NULL)
        {
            return (-1);
        }
        
        creerFichierAnalyse();
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
    } else {
        //recherche_global
        char *arg[10];
        //arg[0] = "/Users/Zhoulin/Dev/GUI/Electron/my-new-app/Tests";
        arg[0] = "/";
        int typeAnalyse = lancementAnalyse(2,arg);

        FILE *analyse = fopen(pathAnalyse, "r");
        if (analyse == NULL)
        {
            return (-1);
        }
        char data[1024];
        char *tmp = NULL;

        while (fgets(data, 1024, analyse) != NULL)
        {
            if (tmp = strstr(data, " \n"))
            {
                *tmp = '\0';
            }
            search_virus_in_File(data);
        }
        if (analyse)
        {
            fclose(analyse);
        }
    }
    
    return count_threat();
}

//fonction permettant de faire une analyse locale 
int local_analysis(char *arg[]){
    if(checkIfFileExists(pathAnalyseGlobale == 1)){

        //recherche_global
        //analyse par comportement
        
        int typeAnalyse = lancementAnalyse(2,arg);
        FILE *analyse = fopen(pathAnalyse, "r");
        if (analyse == NULL)
        {
            return (-1);
        }
        
        creerFichierAnalyse();
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
    } else {
        //recherche_global
        int typeAnalyse = lancementAnalyse(2,arg);

        FILE *analyse = fopen(pathAnalyse, "r");
        if (analyse == NULL)
        {
            return (-1);
        }
        char data[1024];
        char *tmp = NULL;

        while (fgets(data, 1024, analyse) != NULL)
        {
            if (tmp = strstr(data, " \n"))
            {
                *tmp = '\0';
            }
            search_virus_in_File(data);
        }
        if (analyse)
        {
            fclose(analyse);
        }
    }
    
    return count_threat();
        
}

void remove_analyse_and_listeContamine(){
    if (checkIfFileExists(pathAnalyse) == 1)
    {
        remove(pathAnalyse);
    }
    if (checkIfFileExists(pathListeContamine) == 1)
    {
        remove(pathListeContamine);
    }
} 



// void main()
// {
//     int nombreVirus = analysis_treatment();
//     printf("%d \n", nombreVirus);
//     //all_quarantine();
//     //all_block();
// }
