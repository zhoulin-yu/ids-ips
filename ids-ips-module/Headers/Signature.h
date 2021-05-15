#ifndef _SIGNATURE_
#define _SIGNATURE_

//path vers baseVirale
#define pathBaseVirale "../BaseVirale/basevirale.txt"
//** PREREQUIS BASE VIRAL: Chaque pattern de virus doit être sur une ligne **//

// path vers la liste des fichiers contaminés
#define pathListeContamine "../Analyses/listeContamination.txt"

char *string_treatment(char *chain);
int search_in_File(char *pathFile, char *str);
char *search_and_keep_line(char *pathFile, int line);
int search_virus_in_File(char *pathFile);


#endif