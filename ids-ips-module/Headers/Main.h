#ifndef _MAIN_
#define _MAIN_

#include "Blocage.h"
#include "Signature.h"
#include "Comportement.h"
#include "search.h"

//path vers baseVirale
#define pathBaseVirale "BaseVirale/basevirale.txt"
//** PREREQUIS BASE VIRAL: Chaque pattern de virus doit être sur une ligne **//

// path vers la liste des fichiers contaminés
#define pathListeContamine "Analyses/listeContamination.txt"

//path vers fichiers analyses
#define pathAnalyse "Analyses/analyse.txt"
#define pathAnalyseGlobale "Analyses/analyseGlobale.txt"
#define pathNouvelleAnalyseGlobale "Analyses/nouvelleAnalyseGlobale.txt"

int count_threat();
int analysis_treatment();
int local_analysis(char *arg[]);
void all_quarantine();
char *search_and_keep_path(char *pathFile, int line);
void all_block();
void remove_analyse_and_listeContamine();




#endif