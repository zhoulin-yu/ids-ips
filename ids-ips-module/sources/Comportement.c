#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusion du header de comportement
#include "../Headers/Comportement.h"


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

