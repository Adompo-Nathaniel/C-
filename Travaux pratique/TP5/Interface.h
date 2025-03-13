#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdio.h>
#include <string.h>
#include "GeomBase.h"
#include "Surface.h"
#include "Curve.h"
#include "Figure.h"

void tailleImage(int *hauteur, int *largeur, float *ratio_hauteur, float *ratio_largeur, int etat);

void transformationMaj(char *str);

float max(float a, float b);

void sauvegardeForme(Figure& fig, Figure** tab_fig, int* taille_tab);

void choixCouleur(Color *couleur);
void choixCentre(float* x, float* y, int* hauteur, int* largeur);
void choixCoin(float* x, float* y, int* hauteur, int* largeur, float* longueur_x, float* longueur_y);
void choixLargeur(float* largeur);
void choixRayon(float* rayon);
void choixRayon_(float* rayon_x, float* rayon_y);
void choixLongueur(float* longueur);
void choixAngle(float* angle);
void choixHauteur(float* hauteur);
void choixEpaisseur(size_t* epaisseur);
void choixNbPoints(int* nombre_points, int forme);
void choixPoint(float* x, float* y, int* hauteur, int* largeur, int numero);

void ajoutForme(Figure& fig, Figure** tab_fig, int* taille_tab, int* hauteur, int* largeur);
void selectionForme(Figure& fig, int* hauteur, int* largeur, int* taille, int* tableau);
void supprimerForme(Figure& fig, int* hauteur, int* largeur, int* taille, int* tableau);
void modifierForme(Figure& fig, int* hauteur, int* largeur);

int selectionType(int etat);

void menuPrincipal(Figure& fig, char* nom_du_fichier, int *hauteur, int *largeur, float *ratio_hauteur, float *ratio_largeur, Figure** tab_fig, int *taille_tab_fig);


#endif // _INTERFACE_H_