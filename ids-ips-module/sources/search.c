//#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "../Headers/search.h"


char dir[100] = ""; //fichier du rapport d'exe


void writeDataChDate (const char *fpath, char* time){
  printf("file exe find %s\n",fpath);
  FILE *data = fopen(dir,"a");
   if(data != NULL){
    fprintf(data, "%s %s",fpath,time );
    fclose(data);
   } 
   else perror("writeData file data");
}

void writeDataCh (const char *fpath){
  printf("file exe find %s\n",fpath);
  FILE *data = fopen(dir,"a");
   if(data != NULL){
    fprintf(data, "%s \n",fpath);
    fclose(data);
   } 
   else perror("writeData file data");
}


int search_info_and_exeChDate(const char *fpath, const struct stat *sb,int tflag)
   {   	

   	if(tflag==FTW_F){
   		struct stat sb;
   		stat(fpath,&sb);
         FILE* data;

   		if(sb.st_mode & S_IXUSR) 
         {
            writeDataChDate(fpath,ctime(&sb.st_mtime));
         }
   	}
    return 0;           /* To tell nftw() to continue */
}


int search_info_and_exeCh(const char *fpath, const struct stat *sb,int tflag)
   {   	

   	if(tflag==FTW_F){
   		struct stat sb;
   		stat(fpath,&sb);
         FILE* data;

   		if(sb.st_mode & S_IXUSR) 
         {
            writeDataCh(fpath);
         }
   	}
    return 0;           /* To tell nftw() to continue */
}



int lancementAnalyse(int argc, char *argv[])
{
  FILE *data = NULL; // pointeur pour le fichier texte
  time_t timer = time(NULL); 
  struct tm *local = localtime(&timer); //pour les noms de dossier
  int flags = 0; // nftw function()
  
  if(strcmp(argv[0],"/")==0)
  {
      struct stat buffer;
      int exist = stat("Analyses/analyseGlobale",&buffer);
      
      if(exist == -1)
       {         
        snprintf(dir,sizeof(dir),"Analyses/analyseGlobale");
         data = fopen(dir,"w");
         if(data != NULL);
         else perror("file data global");
         if (nftw((argc < 2) ? "." : argv[0], search_info_and_exeChDate, 20, flags) == -1) {
         perror("nftw");
         exit(EXIT_FAILURE);
         }            

      }
       else
      {
         snprintf(dir,sizeof(dir),"Analyses/nouvelleAnalyseGlobale");
         data = fopen(dir,"w");
         if(data != NULL);
         else perror("file data global");

         if (nftw((argc < 2) ? "." : argv[0], search_info_and_exeChDate, 20, flags) == -1) {
         perror("nftw");
         exit(EXIT_FAILURE);
         }

      }


      snprintf(dir,sizeof(dir),"Analyses/Analyse");
      data = fopen(dir,"w");
      if (nftw((argc < 2) ? "." : argv[0], search_info_and_exeCh, 20, flags) == -1) {
      perror("nftw");
      exit(EXIT_FAILURE);
      }
      return 1;
      exit(EXIT_SUCCESS);
      }
	else
   {
      snprintf(dir,sizeof(dir),"Analyses/nouvelleAnalyseLocale");
      //printf("\n\nfichier %s \n\n",dir);
      data = fopen(dir,"w");
      if(data != NULL);
      else perror("file data local");

      if (nftw((argc < 2) ? "." : argv[0], search_info_and_exeChDate, 20, flags) == -1) {
      perror("nftw");
      exit(EXIT_FAILURE);
      }

      snprintf(dir,sizeof(dir),"Analyses/analyse.txt");
      data = fopen(dir,"w");
      if (nftw((argc < 2) ? "." : argv[0], search_info_and_exeCh, 20, flags) == -1) {
      perror("nftw");
      exit(EXIT_FAILURE);
      }
      return 0;
      exit(EXIT_SUCCESS);

	}
     

}




