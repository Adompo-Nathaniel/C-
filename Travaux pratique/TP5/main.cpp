#include <cstdio>
#include <iostream>
#include <string.h>
#include "GeomBase.h"
#include "Surface.h"
#include "Curve.h"
#include "SVG.h"
#include "Figure.h"
#include "Interface.h"

int main() {
	using namespace Geom2D;

	//Nom du fichier
	char src[64] = "";
	printf("\n Veuillez entrez le nom du fichier a enregistrer : ");
	scanf("%s",src);

	//Ajout de l'extension ".html" s'il n'y a pas d'extension ou svg
	int fichier = static_cast<int>(strlen(src));
	if(strcmp(src + fichier - 5, ".html") != 0 && strcmp(src + fichier - 4, ".svg") != 0) {
		strcat(src, ".html");
	}

	//Taille de l'image (minimun : 10*10)
	int largeur = 1000, hauteur = 1000;
	float flargeur = 1.0, fhauteur = 1.0;
	tailleImage(&hauteur,&largeur,&fhauteur,&flargeur,1);

	//Initialisation de la figure
	Figure fig({});

	//Tableau de figure
	Figure** tabFig = new Figure*[1];
	int tailleTabFig = 1;

	//Enregistrement du fichier avant le menu principal
	fig.ExportSVG(fig,src,hauteur,largeur,0);

	//Lancement du menu de l'interface
	menuPrincipal(fig,src,&hauteur,&largeur,&fhauteur,&flargeur,tabFig,&tailleTabFig);

	//Enregistrement automatique lors de la fermeture
	printf("\n Enregistrement automatique du fichier.\n");
	fig.ExportSVG(fig,src,hauteur,largeur,0);

	//Libéré la mémoire
	delete[] tabFig;

	return 0;

	/*
	Array::Static<Point, 4> lp1 = { { 1,2 },{ 3,4 },{ 5,6 },{ 7,8 } };
	Array::Static<Point, 4> lp2(lp1);
	// Point p = Array::Geometry::Center(lp1);
	Array::Geometry::Translate(lp1, Point(1.f,2.f));
	Array::Geometry::Rotate(lp1, 2.f);
	Array::Geometry::Scale(lp1, 3.f);
	std::cout << lp1 << std::endl;
	std::cout << lp2 << std::endl;
	lp1 = lp2;
	std::cout << lp1 << std::endl;

	Figure fig({
		new Surface::Disk({ 100,100 }, 50),
		new Surface::Polygon(6,{ 100,400 }, 80, Color::blue),
		new Surface::Triangle({ 200,200 }, 150, Color::yellow),
		new Surface::Rectangle({ 400, 200 }, 200, 300, Color::cyan),
		new Surface::Square({ 200,400 }, 300, Color::green),
		new Curve::Circle({ 600,400 }, 300, Color::green, 4),
		new Curve::Polyline(4,{ 500,500 }, 80, Color::blue, 2),
		new Curve::Segment({ 100,200 },{ 500,300 },Color::turquoise,6)
	});

	fig.Translate(Point{2,3});
	fig.Rotate(2.f);
	fig.Scale(2.f);

	fig.info();
	fig.save("test05.html");

	return 0;
	*/
}
