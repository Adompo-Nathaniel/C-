#include <cstdio>
#include <iostream>
#include <string.h>
#include "GeomBase.h"
#include "Surface.h"
#include "Curve.h"
#include "SVG.h"
#include "Figure.h"
#include "Interface.h"

//Programme principal
int main() {
	using namespace Geom2D;

	//Nom du fichier
	char nom_du_fichier[64] = "";
	printf("\nChoisir le nom du fichier a enregistrer : ");
	scanf("%s", nom_du_fichier);


	//Ajout automatique de l'extension ".html" s'il n'y a pas d'extension html ou svg
	int len_nom_du_fichier = static_cast<int>(strlen(nom_du_fichier));
	if (strcmp(nom_du_fichier + len_nom_du_fichier - 5, ".html") != 0 && strcmp(nom_du_fichier + len_nom_du_fichier - 4, ".svg") != 0) {
        strcat(nom_du_fichier, ".html");
    }


	//Taille de l'image (minimum : 10x10)
	int largeur = 1000, hauteur = 1000;
	float ratio_largeur = 1.0, ratio_hauteur = 1.0;
	tailleImage(&hauteur, &largeur, &ratio_hauteur, &ratio_largeur, 1);
	

	//Initialisation de la figure
	Figure fig({});


	//Tableau de figure
	Figure** tab_fig = new Figure*[1];
	int taille_tab_fig = 1;


	//Enregistrement avant le menu principal
	fig.ExportSVG(fig, nom_du_fichier, hauteur, largeur, 0);


	//Lancement du menu de l'editeur
	menuPrincipal(fig, nom_du_fichier, &hauteur, &largeur, &ratio_hauteur, &ratio_largeur, tab_fig, &taille_tab_fig);


	//Enregistrement automatique lors de la fermeture
	printf("\nEnregistrement automatique du fichier.\n");
	fig.ExportSVG(fig, nom_du_fichier, hauteur, largeur, 0);


	//Liberer la mémoire
	delete[] tab_fig;

	return 0;
}


//////////////////////////////////////////////////
//    Figure utilisée dans le compte rendu:    //
/*

	Figure fig({
		new Surface::Pikachu({ 500,500 }, 200)
		new Surface::Heptagon({ 100,100 }, 100, Color::red),
		new Surface::Disk({ 100,100 }, 50, Color::white),
		new Surface::SnowFlake({ 400,400 }, 100, Color::blue),
		new Surface::Triangle({ 450,120 }, 120, Color::pink),
		new Surface::Coeur({ 700,650 }, 200, Color::fuchsia),
		new Surface::Oval({ 200,300 }, 100, 50, Color::black),
		new Curve::Ellipse({ 200,300 }, 50, 100, Color::green, 15),
		new Surface::Losange({ 800,100 }, 120, 80, Color::orange),
		new Surface::Etoile({ 1100,400 }, 200, Color::darkolivegreen),
		new Surface::Flower({ 1000,600 }, 150, Color::violet),
		new Curve::Circle({ 650,350 }, 150, Color::turquoise, 5),
		new Surface::Sun({ 650,350 }, 100, Color::yellow),
		new Curve::Segment({ 200,50 }, { 300,120 }, Color::grey, 10),
		new Surface::Square({ 100,500 }, 100, Color::lime),
		new Surface::Rectangle({ 1200,50 }, 150, 250, Color::cyan),
		new Curve::Polyline({{ 420,600 }, { 500,630 }, { 410,700 }, { 350,500 }, { 420,600 }}, Color::steelblue, 4),
		new Surface::Parallelogramme({ 100,650 }, 140, 100, 15, Color::brown)
	});

*/


////////////////////////////////////////////////////////////////////
//    Créer un dossier pour ranger les figures SVG (Windows):    //

/*
	// Vérifier si le dossier "Fichiers SVG" existe et le créer s'il n'existe pas
	if (_mkdir("../Fichiers SVG") == -1 && errno != EEXIST) {
		// Erreur lors de la création du dossier
	}
*/