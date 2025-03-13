#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <string>
#include "Figure.h"
#include "Curve.h"

//Destructeur
Figure::~Figure() {
	for (size_t i = 0; i < size(); i++) delete tab[i];
	// destruction du tableau assuré par le destructeur de Dynamic
}


//Transformation
void Figure::Translate(const Geom2D::Point &v) {
	for (size_t i = 0; i < size(); i++) tab[i]->Translate(v);
}

void Figure::Translate_(const Geom2D::Point &v, int i) {
	tab[i]->Translate(v);
}


void Figure::Scale(float s) {
	for (size_t i = 0; i < size(); i++) tab[i]->Scale(s);
}

void Figure::Scale_(float s, int i) {
	tab[i]->Scale(s);
}


void Figure::Rotate(float a) {
	for (size_t i = 0; i < size(); i++) tab[i]->Rotate(a);
}

void Figure::Rotate_(float a, int i) {
	tab[i]->Rotate(a);
}


//Modification de la taille
void Figure::Resize_(float s) {
	for (size_t i = 0; i < size(); i++) tab[i]->Resize(s);
}

void Figure::Crop_(int hauteur, int largeur) {
	for (size_t i = 0; i < size(); i++) {
		//printf("%f, %f\n", tab[i]->Center().getx(), tab[i]->Center().gety());
		if (tab[i]->Center().getx() > static_cast<float>(largeur) || tab[i]->Center().getx() < 0.0 || tab[i]->Center().gety() < 0.0 ||tab[i]->Center().gety() > static_cast<float>(hauteur)) {
			Remove(i);
		}
	}
}


//Modification de la taille
void Figure::Recolor_(Color& color, int indice) {
	tab[indice]->setColor(color);
}


void Figure::Remove_(int indice) {
	Remove(indice);
}

void Figure::Add_(Figure& temp) {
	Array::Dynamic<Geom2D::Base *>::Add(temp.tab[0]);
}


//Taille
int Figure::GetSize() {
	return  static_cast<int>(size());
}


//Comparaison du type d'une forme
void Figure::Comparaison(int type, int* tab_indice, int* taille_tab_fig) {
	int indice = 0;
	for (size_t i = 0; i < size(); i++) {
		if (tab[i]->getType() == type || type == 0) {
			tab_indice[indice] =  static_cast<int>(i);
			indice ++;
		}
	}
	*taille_tab_fig = indice;
}


void Figure::VerificationType(int type, int* nombre) {
	for (size_t i = 0; i < size(); i++) {
		if (tab[i]->getType() == type || type == 0) {
			(*nombre)++;
		}
	}
}


//Affichage en fonction du type
void Figure::Print_(int type) {
	using namespace std;
	string tableauDeChaines[] = {"Cercle", "Ellipse", "Polyligne", "Segment", "Disque", "Ovale", "Polygone", "Triangle", "Pentagone", "Hexagone", "Heptagone", "Octogone", "Rectangle", "Carre", "Losange", "Parallelogramme", "Etoile", "Soleil", "Flocon", "Coeur", "Fleur", "Pikachu"};

	int nombre = 0;
	VerificationType(type, &nombre);

	//Affichage des formes du type
	if (nombre>0) {
		printf("\n%s (%d) :\n", tableauDeChaines[type-1].c_str(), nombre);

		for (size_t i = 0; i < size(); i++) {
			if (tab[i]->getType() == type) {
				std::cout << std::setw(2) << " - "<< i << " : ";
				tab[i]->info(std::cout);
				std::cout << std::endl;
			}
		}
	}
}


//Informations de la figure
void Figure::info() {
	for (size_t i = 0; i < size(); i++) {
		std::cout << std::setw(2) << "- "<< i << " : ";
		tab[i]->info(std::cout);
		std::cout << std::endl;
	}
}


// sauvegarde
void Figure::save(const char *fname, int hauteur, int largeur, int type) {
	SVG::stream   output(fname, false, hauteur, largeur);

	for (size_t i = 0; i < size(); i++) {
		if (type == 0 || tab[i]->getType() == type) {
			tab[i]->write(output);
		}
	}

	output.close();
}



////////////////////////////////////////////////////////////////////////////////

// Ajoute un nouveau objet au canevas
GrawEditor& GrawEditor::Add(Figure& figure, Figure& temp) {
	figure.Add_(temp);
	return *this;
}


/*
// Annule le dernier ajout d'objet
GrawEditor& GrawEditor::Undo();

// Réinsère le dernier objet supprimé
GrawEditor& GrawEditor::Redo();
*/

// Supprime un objet du canevas
GrawEditor& GrawEditor::Delete(Figure& figure, int indice) {
	figure.Remove_(indice);
	return *this;
}

// Redimensionne le canevas
GrawEditor&  GrawEditor::Resize(Figure& figure, float ratio) {
	figure.Resize_(ratio);
	return *this;
}

// Redimensionne le canevas en supprimant les objets extérieurs */
GrawEditor& GrawEditor::Crop(Figure& figure, int hauteur, int largeur) {
	figure.Crop_(hauteur, largeur);
	return *this;	
}

GrawEditor& GrawEditor::Print(Figure& figure, int type) {
	figure.Print_(type);
	return *this;
}

GrawEditor& GrawEditor::ExportSVG(Figure& figure, const char *fname, int hauteur, int largeur, int type) {
	figure.save(fname, hauteur, largeur, type);
	return *this;
}

GrawEditor& GrawEditor::Select(Figure& figure, int type, int* tab_indice, int* taille_tab_indice) {
	figure.Comparaison(type, tab_indice, taille_tab_indice);
	return *this;
}




//template <typename Shape> Shape *GetNew();

