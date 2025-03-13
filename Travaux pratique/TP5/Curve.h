#ifndef _CURVE_H_
#define _CURVE_H_
#include <iostream>
#include <cassert>
#include "GeomBase.h"
#include "SVG.h"
#include "Array.h"

// Les classes définies dans ce fichier représentent les traits des dessins
// (segment de droite), notamment les circonférences (contours de cercle,
// contour de polygone régulier).

namespace Geom2D {
	namespace Curve {
		////////////////////////////////////////////////////////////////////////////////////////
		// interface FillProperty
		class Stroke {
		protected:
			Color	stroke_color;
			size_t	stroke_width;
		public:
			explicit Stroke(const Color &c = Color::defaut, size_t width=1) :
				stroke_color(c), stroke_width(width) {}
			void setStrokeColor(const Color &color) { stroke_color = color; }
			void setStrokeWidth(size_t width) { stroke_width = width; }
			const Stroke &getStroke() const { return *this; }
			friend std::ostream& operator<<(std::ostream& s, const Stroke& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Stroke& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Surface
		class Base :
			public Geom2D::Base,
			public Stroke {
		public:
			Base() : Geom2D::Base(), Stroke() {}
			Base(const Color &col, size_t width=1) : Stroke(col,width) {}
			virtual ~Base() {}
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Circle
		class Circle :
			public Curve::Base {
		protected:
			Point center;
			float radius;
		public:
			Circle(const Point &xy, float r, const Color &color = Color::defaut, size_t width = 1) :
				Base(color, width), center(xy), radius(r) {}
			virtual ~Circle() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			Point Center() { return center; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { radius *= s; }
			void Resize(float s) override { radius *= s; }
			void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")
			int getType() override { return 1;}
			void setColor(Color couleur) override { setStrokeColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Circle& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Circle& p);
		};
		
		////////////////////////////////////////////////////////////////////////////////////////
		//  Ellipse
		class Ellipse : public Curve::Base {
		protected:
			Point center;
			float a, b, angle;
		public:
			Ellipse(const Point &xy, float a_, float b_, const Color &color = Color::defaut, size_t width = 1) :
				Base(color, width), center(xy), a(a_), b(b_) { angle = 0.0f; }
			virtual ~Ellipse() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			Point Center() { return center; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { a *= s; b *= s; }
			void Resize(float s) override { a *= s; b *= s; }
			void Rotate(float a) override { angle = a; }
			int getType() override{ return 2;}
			void setColor(Color couleur) override { setStrokeColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Ellipse& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Ellipse& p);
		};
		

		////////////////////////////////////////////////////////////////////////////////////////
		//  Polyline
		class Polyline :
			public Curve::Base,
			public Array::Fixed<Point> {
		public:
			Polyline(std::size_t npoints, const Point &centre, float size, const Color &c = Color::defaut, size_t width = 1);
			Polyline(const std::initializer_list<Point> &list, const Color &c = Color::defaut, size_t width = 1);
			virtual ~Polyline() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point Center() { return Array::Geometry::Center(*this); }
			int getType() override{ return 3;}
			void setColor(Color couleur) override { setStrokeColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Polyline& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Polyline& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Segment
		class Segment :
			public Curve::Base,
			public Array::Static<Point,2> {
		public:
			Segment(const Point &p1, const Point &p2, const Color &col = Color::defaut, size_t width = 1) :
				Base(col, width), Array::Static<Point,2>({p1,p2}) {}
			Segment(const std::initializer_list<Point> &list, const Color &col = Color::defaut, size_t width = 1) :
				Base(col, width), Array::Static<Point,2>(list) {
				assert(list.size() == 2);
			}
			virtual ~Segment() {}
			std::ostream& info(std::ostream& stream) const { return stream << *this; }
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point Center() { return Array::Geometry::Center(*this); }
			int getType() override{ return 4;}
			void setColor(Color couleur) override { setStrokeColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Segment& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Segment& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  inline definitions

		// polyline
		inline Polyline::Polyline(std::size_t npts, const Point &cent, float size, const Color &color, size_t width) :
			Base(color,width), Array::Fixed<Point>(npts) {
				Array::Geometry::FillnGon(*this,cent,size);
			}
		inline Polyline::Polyline(const std::initializer_list<Point> &list, const Color &color, size_t width) :
			Base(color,width), Array::Fixed<Point>(list) {}

	}
}

#endif // _CURVE_H_
