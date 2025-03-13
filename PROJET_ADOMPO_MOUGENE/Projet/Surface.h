#ifndef _SURFACE_H_
#define _SURFACE_H_
#include <iostream>
#include <cassert>
#include "GeomBase.h"
#include "SVG.h"
#include "Array.h"

namespace Geom2D {
	namespace Surface {
		////////////////////////////////////////////////////////////////////////////////////////
		// interface FillProperty
		class Fill {
		protected:
			Color   fill_color;
		public:
			explicit Fill(const Color &c = Color::defaut) : fill_color(c) {}
			void setFillColor(const Color &color) { fill_color = color; }
			const Color &getFillColor() const { return fill_color; }
			friend std::ostream& operator<<(std::ostream& s, const Fill& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Fill& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Surface
		class Base :
			public Geom2D::Base,
			public Fill {
		protected:
		public:
			Base() : Geom2D::Base(), Fill() {}
			Base(const Color &color) : Fill(color) {}
			Base(const Point &, const Color &col = Color::defaut) : Fill(col) {}	// le premier paramètre est inutilisé, pas besoin de le nommer.
			virtual ~Base() {}
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Disk
		class Disk :
			public Surface::Base {
		protected:
			Point center;
			float radius;
		public:
			Disk(const Point &xy, float r, const Color &c = Color::defaut) :
				Base(xy,c), center(xy), radius(r) {}
			Disk() : Disk({0,0}, 0.0f, Color::defaut) {}
			virtual ~Disk() {}
			virtual std::ostream &info(std::ostream &stream) const;
			virtual void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { radius *= s; }
			void Resize(float s) override { radius *= s; }
			Point Center() { return center; }
			void Rotate(float) override {}	// ne rien faire : omission du nom du paramètre (évite un warning "unused parameter")
			int getType() { return 5; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Disk& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Disk& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Oval
		class Oval :
			public Surface::Base {
		protected:
			Point center;
			float a, b, angle;
		public:
			Oval(const Point &xy, float _a, float _b, const Color &c = Color::defaut) :
				Base(xy,c), center(xy), a(_a), b(_b) { angle = 0.0f; }
			virtual ~Oval() {}
			virtual std::ostream &info(std::ostream &stream) const;
			virtual void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) override { center += v; }
			void Scale(float s) override { a *= s; b *= s; }
			void Resize(float s) override { a *= s; b *= s; }
			Point Center() { return center; }
			void Rotate(float ang) override { angle = ang; }
			int getType() { return 6; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Oval& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Oval& p);
		};


		////////////////////////////////////////////////////////////////////////////////////////
		//  Polygon
		class Polygon : public Surface::Base, public Array::Fixed<Point> {
		public:
			Polygon(std::size_t npoints, const Point &centre, float size, const Color &c = Color::defaut);
			Polygon(const std::initializer_list<Point> &list, const Color &c = Color::defaut);
			virtual ~Polygon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s)            { Array::Geometry::Scale(*this,s); }
			void Resize(float s)            { Array::Geometry::Resize(*this,s); }
			void Rotate(float a)           { Array::Geometry::Rotate(*this,a); }
			Point Center() { return Array::Geometry::Center(*this); }
			int getType() { return 7; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Polygon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Polygon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Triangle
		class Triangle : public Surface::Base, public Array::Static<Point,3> {
		public:
			// `cent` est le centre du triangle et `size` la distance entre les sommets et le centre.
			Triangle(const Point &cent, float size, const Color &col = Color::defaut) :
				Base(cent,col), Array::Static<Point,3>()
				{ Array::Geometry::FillnGon(*this,cent,size); }
			Triangle(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,3>(list) {}
			virtual ~Triangle() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point Center() { return Array::Geometry::Center(*this); }
			int getType() { return 8; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Triangle& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Triangle& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Pentagon
		class Pentagon : public Surface::Base, public Array::Static<Point,5> {
		public:
			// `cent` est le centre du pentagon et `size` la distance entre les sommets et le centre.
			Pentagon(const Point &cent, float size, const Color &col = Color::defaut) :
				Base(cent,col), Array::Static<Point,5>()
				{ Array::Geometry::FillnGon(*this,cent,size); }
			Pentagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,5>(list) {}
			virtual ~Pentagon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point Center() { return Array::Geometry::Center(*this); }
			int getType() { return 9; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Pentagon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Pentagon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Hexagon
		class Hexagon : public Surface::Base, public Array::Static<Point,6> {
		public:
			// `cent` est le centre du triangle et `size` la distance entre les sommets et le centre.
			Hexagon(const Point &cent, float size, const Color &col = Color::defaut) :
				Base(cent,col), Array::Static<Point,6>()
				{ Array::Geometry::FillnGon(*this,cent,size); }
			Hexagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,6>(list) {}
			virtual ~Hexagon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			Point Center() { return Array::Geometry::Center(*this); }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			int getType() { return 10; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Hexagon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Hexagon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Heptagon
		class Heptagon : public Surface::Base, public Array::Static<Point,7> {
		public:
			// `cent` est le centre du triangle et `size` la distance entre les sommets et le centre.
			Heptagon(const Point &cent, float size, const Color &col = Color::defaut) :
				Base(cent,col), Array::Static<Point,7>()
				{ Array::Geometry::FillnGon(*this,cent,size); }
			Heptagon(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,7>(list) {}
			virtual ~Heptagon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			Point Center() { return Array::Geometry::Center(*this); }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			int getType() { return 11; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Heptagon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Heptagon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Octogon
		class Octogon : public Surface::Base, public Array::Static<Point,8> {
		public:
			// `cent` est le centre de l'octogone et `size` la distance entre les sommets et le centre.
			Octogon(const Point &cent, float size, const Color &col = Color::defaut) :
				Base(cent,col), Array::Static<Point,8>()
				{ Array::Geometry::FillnGon(*this,cent,size); }
			Octogon(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,8>(list) {}
			virtual ~Octogon() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			Point Center() {return Array::Geometry::Center(*this); }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			int getType() { return 12; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Octogon& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Octogon& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  Rectangle
		class Rectangle : public Surface::Base {
		protected:
			Point corner;
			float width, height;
			float rotate;
		public:
			Rectangle(const Point &xy, float w, float h, const Color &c)
				: Base(c), corner(xy), width(w), height(h), rotate(0.f) {}
			virtual ~Rectangle() {};
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { corner += v; }
			void Scale(float s) { width *= s; height *= s; }
			void Resize(float s) { width *= s; height *= s; }
			void Rotate(float a) { rotate += a; }
			Rectangle *real_type() { return this; }
			Point Center() { return corner; }
			int getType() { return 13; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Rectangle& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Rectangle& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		///  Square
		class Square : public Rectangle {
		public:
			Square(const Point &xy, float s, const Color &c)
				: Rectangle(xy, s, s, c) {}
			virtual ~Square() {};
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			int getType() { return 14; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Square& d);
			friend SVG::stream& operator<<(SVG::stream& s, const Square& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		///  Losange
		class Losange : public Surface::Base, public Array::Static<Point,4> {
		protected:
			Point center;
			float diagonal1, diagonal2;
		public:
			Losange(const Point &c, float diag1, float diag2, const Color &col = Color::defaut) :
				Base(c,col), Array::Static<Point,4>()
				{ 
					this->center = c;
					this->diagonal1 = diag1;
					this->diagonal2 = diag2;
					Array::Geometry::FillLosange(*this, c, diag1, diag2); 
				}
			Losange(const std::initializer_list<Point> &list, const Color &col = Color::defaut) :
				Base(col), Array::Static<Point,4>(list) {}
			virtual ~Losange() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream &stream) const { stream << *this; }
			void Translate(const Point &v) { Array::Geometry::Translate(*this,v); }
			void Scale(float s) { Array::Geometry::Scale(*this,s); }
			void Resize(float s) { Array::Geometry::Resize(*this,s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this,a); }
			Point Center() { return center; }
			int getType() { return 15; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Losange& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Losange& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		///  Parallelogram
		class Parallelogramme : public Surface::Base, public Array::Static<Point, 4> {
		protected:
			Point center;
			float width, height, angle;
		public:
			Parallelogramme(const Point& c, float w, float h, float a, const Color& col = Color::defaut) :
				Base(c, col), Array::Static<Point, 4>(),
				center(c), width(w), height(h), angle(a)
			{
				Array::Geometry::FillParallelogramme(*this, c, w, h, a);
			}
			Parallelogramme(const std::initializer_list<Point>& list, const Color& col = Color::defaut) :
				Base(col), Array::Static<Point, 4>(list) {}
			virtual ~Parallelogramme() {}
			std::ostream& info(std::ostream& stream) const;
			void write(SVG::stream& stream) const { stream << *this; }
			void Translate(const Point& v) { Array::Geometry::Translate(*this, v); }
			void Scale(float s) { Array::Geometry::Scale(*this, s); }
			void Resize(float s) { Array::Geometry::Resize(*this, s); }
			void Rotate(float a) { Array::Geometry::Rotate(*this, a); }
			Point Center() { return center; }
			int getType() { return 16; }
			void setColor(Color couleur) override { setFillColor(couleur); }
			friend std::ostream& operator<<(std::ostream& s, const Parallelogramme& p);
			friend SVG::stream& operator<<(SVG::stream& s, const Parallelogramme& p);
		};

		////////////////////////////////////////////////////////////////////////////////////////
		//  inline definitions

		// polygon
		inline Polygon::Polygon(std::size_t npts, const Point &cent, float size, const Color &color) :
			Base(color), Array::Fixed<Point>(npts) {
				Array::Geometry::FillnGon(*this,cent,size);
		}
		inline Polygon::Polygon(const std::initializer_list<Point> &list, const Color &color) :
			Base(color), Array::Fixed<Point>(list) {}
	}
}

#endif // _SURFACE_H_
