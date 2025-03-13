#ifndef _FIGURE_H_
#define _FIGURE_H_
#include "GeomBase.h"
#include "Array.h"
////////////////////////////////////////////////////////////////////////////////////////
///  Figure

class Figure : public Array::Dynamic<Geom2D::Base*> {
protected:
	static const size_t	DefaultSize = 16;
public:
	explicit Figure(size_t alloc = DefaultSize) : Dynamic(alloc) {}
	~Figure();
	Figure(const std::initializer_list<Geom2D::Base*> &list) : Dynamic(list) {}
	// void Add(Geom2D::Base *g) : hérité de Array::Dynamic
	// void Remove(size_t pos)   : hérité de Array::Dynamic
	void Translate(const Geom2D::Point &v);
	void Scale(float s);
	void Rotate(float a);
	void info();
	// const Geom2D::Base* operator[](size_t i) const;   : hérité de dynamic
	// Geom2D::Base* operator[](size_t i);               : hérité de dynamic
	void save(const char *fname);
};

#endif // _FIGURE_H_
