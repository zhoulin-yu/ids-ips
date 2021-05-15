#ifndef _COMPORTEMENT_
#define _COMPORTEMENT_

#define TAILLE 150

int nombreLignes(char nomFichier[TAILLE]);
int detecterDateDiff(char nomFichier1[TAILLE],char nomFichier2[TAILLE]);
int detecterCheminDiff(char nomFichier[TAILLE],char nomFichier2[TAILLE]);
void remplacementDateDansFichier(char nomFichier1[TAILLE],char nomFichier2[TAILLE],int ligneAChanger);
void lireToutesLesLignesDansFichier(char nomFichier[TAILLE]);

#endif