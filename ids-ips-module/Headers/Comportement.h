#ifndef _COMPORTEMENT_
#define _COMPORTEMENT_

#define TAILLE 150

// path vers la liste des fichiers contaminés
#define pathListeContamine "Analyses/listeContamination.txt"

//path vers fichiers analyses
#define pathAnalyse "Analyses/Analyse.txt"
#define pathAnalyseGlobale "Analyses/AnalyseGlobale.txt"
#define pathNouvelleAnalyseGlobale "Analyses/NouvelleAnalyseGlobale.txt"



int nombreLignes(char nomFichier[TAILLE]);
int detecterDateDiff(char nomFichier1[TAILLE],char nomFichier2[TAILLE]);
int detecterCheminDiff(char nomFichier[TAILLE],char nomFichier2[TAILLE]);
void remplacementDateDansFichier(char nomFichier1[TAILLE],char nomFichier2[TAILLE],int ligneAChanger);
void lireToutesLesLignesDansFichier(char nomFichier[TAILLE]);
int search_in_File_Sans_Traitement(char *pathFile, char *str);
int ligne_chaine_dans_fichier(char str[],char path[TAILLE]);
void creerFichierAnalyse();


#endif
