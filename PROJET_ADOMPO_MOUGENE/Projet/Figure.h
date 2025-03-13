#ifndef _FIGURE_H_
#define _FIGURE_H_
#include "GeomBase.h"
#include "Grawink.h"
#include "Array.h"
////////////////////////////////////////////////////////////////////////////////////////
///  Figure

class Figure : public Array::Dynamic<Geom2D::Base*>, public GrawEditor  {
protected:
	static const size_t	DefaultSize = 16;
public:
	explicit Figure(size_t alloc = DefaultSize) : Dynamic(alloc) {}
	~Figure();
	Figure(const std::initializer_list<Geom2D::Base*> &list) : Dynamic(list) {}

	// void Add(Geom2D::Base *g) : hérité de Array::Dynamic
	// void Remove(size_t pos)   : hérité de Array::Dynamic

	void Translate(const Geom2D::Point &v);
	void Translate_(const Geom2D::Point &v, int i);

	void Scale(float s);
	void Scale_(float s, int i);

	void Rotate(float a);
	void Rotate_(float a, int i);

	void Resize_(float s);
	void Crop_(int hauteur, int largeur);

	void Recolor_(Color& color, int indice);

	void Remove_(int indice);
	void Add_(Figure& temp);

	void Comparaison(int type, int* tab_indice, int* taille_tab_fig);
	
	void VerificationType(int type, int* nombre);

	void Print_(int type);

	int GetSize();
	void info();

	// const Geom2D::Base* operator[](size_t i) const;   : hérité de dynamic
	// Geom2D::Base* operator[](size_t i);               : hérité de dynamic

	void save(const char *fname, int hauteur = 1000, int largeur = 1000, int type = 0);
	
};

#endif // _FIGURE_H_
