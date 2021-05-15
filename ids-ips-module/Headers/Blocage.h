#ifndef _BLOCAGE_
#define _BLOCAGE_

// path vers la liste des fichiers contaminés
#define pathListeContamine "../Analyses/listeContamination.txt"

char *search_name_of_file_in_path(char *pathFile);
int checkIfFileExists(const char *filename);
void quarantine_placement(char *pathFile);
void block_file(char *pathFile);

#endif