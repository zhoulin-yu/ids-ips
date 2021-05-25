#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusion du header de comportement
#include "../Headers/Comportement.h"
#include "../Headers/Signature.h"



int detecterCheminDiff(char nomFichier[TAILLE],char nomFichier2[TAILLE])
{
	FILE* file1;
	FILE* file2;
	char chemin1[200];
	char chemin2[200];
	file1 = fopen(nomFichier,"r");
	file2 = fopen(nomFichier2,"r");

	int i = 1;
	fgets(chemin1,180,file1);
	fgets(chemin2,180,file2);
	
		
	while(1)
	{
		fgets(chemin1,180,file1);
		fgets(chemin2,180,file2);
		i++;
		if(feof(file1) || feof(file2))
			break;
		if(chemin1[0] == '\n' || chemin2[0] == '\n')
		{
			fgets(chemin1,180,file1);
			fgets(chemin2,180,file2);
		}
		if(strcmp(chemin1,chemin2) != 0) //vérifie si date1 et date 2 sont identiques si non -> retourne la ligne		
		{
			fclose(file1);fclose(file2);
			printf("ligne %d",i);
			return i;
		}		
		
	}
	fclose(file1);fclose(file2);
	return 0;
	

	
}


int nombreLignes(char nomFichier[TAILLE])
{
	FILE* file1;
	char t[200];
	int i = 0;
	file1 = fopen(nomFichier,"r");
	while (1)	
	{
		fgets(t,150,file1);
		if(feof(file1))
			break;
		i++;
	}
	fclose(file1);
	return i;
}

int detecterDateDiff(char nomFichier1[TAILLE],char nomFichier2[TAILLE]) //retourne la ligne précédente à la ligne de différence de dateou 0 si il n'y a pas de différence de date
{
	
	FILE* file1;
	FILE* file2;
	char date1[200];
	char date2[200];
	file1 = fopen(nomFichier1,"r");
	file2 = fopen(nomFichier2,"r");
	int i = 1;
	fgets(date1,180,file1);
	fgets(date2,180,file2);
	while(1)
	{
		fgets(date1,180,file1);
		fgets(date2,180,file2);
		i++;
		if(feof(file1) || feof(file2))
			break;
		if(date1[0] == '\n' || date2[0] == '\n')
		{
			fgets(date1,180,file1);
			fgets(date2,180,file2);
		}
		if(!strstr(strchr(date1,' '),strchr(date2,' '))) //vérifie si date1 et date 2 sont identiques si non -> retourne la ligne		
		{
			fclose(file1);fclose(file2);
			return i;
		}		
	}
	fclose(file1);fclose(file2);
	return 0;
}


void lireToutesLesLignesDansFichier(char nomFichier1[TAILLE])
{
	FILE* file1;
	char lignes[200];
	file1 = fopen(nomFichier1,"r");
	while(1)
	{
		fgets(lignes,200,file1);
		if(feof(file1))
			break;
		if(lignes[0] == '\n')
			printf(" ");

		printf("%s",lignes)	;


	}

}


void remplacementDateDansFichier(char nomFichier1[TAILLE],char nomFichier2[TAILLE],int ligneAChanger)
{
	FILE* file1;
	FILE* file2;
	char ligne1[200];
	char nouvelleDate[200];
	file1 = fopen(nomFichier1,"r+");
	file2 = fopen(nomFichier2,"r");
	int i = 0;
	while(i < ligneAChanger)
	{
		fgets(ligne1,180,file1);
		fgets(nouvelleDate,180,file2);	
		i++;	
	}
	
	fgets(nouvelleDate,180,file2);	
	strncpy(ligne1,nouvelleDate,strlen(nouvelleDate)-strlen(strchr(nouvelleDate,' ')));
	strchr(nouvelleDate,' ');
	strcat(ligne1,nouvelleDate);
	//fprintf(file1,"%s",ligne1);

}

int search_in_File_Sans_Traitement(char *pathFile, char *str)
{
    int line_num = 0;
    int find_result = -1;
    char data[1024];

    FILE *file = fopen(pathFile, "r");
    if (file == NULL)
    {
        return (-2);
    }

    while (1)
    {
        fgets(data, 1024, file);
		if(feof(file))
			break;
        if (strstr(data, str) != NULL)
        {
            //printf("Suspect element on line: %s\n", data);
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




void creerFichierAnalyse()
{
	FILE* new;
	FILE* comp;


	char old[TAILLE];
	char ligne[200];
	char ligneChemin[200];
	char ligneDate[200];

	comp = fopen(pathListeContamine,"w");
	new = fopen(pathNouvelleAnalyseGlobale,"r");

	strcpy(old,pathAnalyseGlobale);
	while(1)
	{
		fgets(ligne,200,new);		
	
		if(feof(new))
		{
			break;
		}


		strncpy(ligneChemin,ligne,strlen(ligne)-strlen(strchr(ligne,' ')));
		strcpy(ligneDate,strchr(ligne,' '));
		for(int i = 0;ligneDate[i+1] != '\0';i++)		
			ligneDate[i] = ligneDate[i+1];
		ligneDate[strlen(ligneDate)-1] = '\0';
		
		if(search_in_File_Sans_Traitement(old,ligneChemin) != -1)
		{		
			printf("%d", search_in_File_Sans_Traitement(old,ligneDate));
			if(search_in_File_Sans_Traitement(old,ligneDate) != -1)
			{
				fprintf(comp,"%s\n",ligneChemin);
			}
		}

		

	}


}

