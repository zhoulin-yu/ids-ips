#ifndef _MAIN_
#define _MAIN_

#include "Blocage.h"
#include "Signature.h"
#include "Comportement.h"
//#include "Recherche.h"

//path vers baseVirale
#define pathBaseVirale "BaseVirale/basevirale.txt"
//** PREREQUIS BASE VIRAL: Chaque pattern de virus doit être sur une ligne **//

// path vers la liste des fichiers contaminés
#define pathListeContamine "Analyses/listeContamination.txt"

int count_threat();
int first_analysis();
void all_quarantine();
char *search_and_keep_path(char *pathFile, int line);
void all_block();




#endif