#include "SVG.h"
#include "Curve.h"

namespace Geom2D {
	namespace Curve {
		// stroke
		std::ostream& operator<<(std::ostream& s, const Stroke& p) {
			return s << "stroke=" << p.stroke_color << ",width=" << p.stroke_width;
		}

		SVG::stream& operator<<(SVG::stream& s, const Stroke& p) {
			const Color col_none = Color(Color::none);
			return s << " stroke=" << quoted(p.stroke_color)
				<< " stroke-width=" << quoted(p.stroke_width)
				<< " fill=" << quoted(col_none);
		}

		// Circle
		std::ostream& operator<<(std::ostream& s, const Circle& d) {
			return s << "Circle[center=" << d.center << ",radius=" << d.radius
				<< "," << d.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Circle& p) {
    		return s << "<circle"
             	<< " cx=" << quoted(p.center.getx()) << " cy=" << quoted(p.center.gety())
             	<< " r=" << quoted(p.radius)
             	<< " stroke=" << quoted(p.stroke_color)  // Ajoutez la couleur de la bordure ici
             	<< " stroke-width=" << quoted(p.stroke_width)  // Ajoutez la largeur de la bordure si nécessaire
             	<< "/>\n";
}


		// Ellipse
		std::ostream& operator<<(std::ostream& s, const Ellipse& d) {
			return s << "Ellipse[center=" << d.center << ",a=" << d.a << ",b=" << d.b
				<< "," << d.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Ellipse& p) {
			std::string transform = "rotate(";
			transform += std::to_string(p.angle);
			transform += ",";
			transform += std::to_string(p.center.getx());
			transform += ",";
			transform += std::to_string(p.center.gety());
			transform += ")";

			return s << "<ellipse"
				<< " cx=" << quoted(p.center.getx()) << " cy=" << quoted(p.center.gety())
				<< " rx=" << quoted(p.a) << " ry=" << quoted(p.b)
				<< " stroke=" << quoted(p.stroke_color) 
             	<< " stroke-width=" << quoted(p.stroke_width) 
				<< " transform=" << quoted(transform.c_str())
				<< "/>\n";
		}

		// Polyline
		std::ostream& operator<<(std::ostream& s, const Polyline& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "Polyline[nVertex=" << p.size() << "," << pp << "," << p.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Polyline& p) {
			const Array::Fixed<Point> &pp = p;
			return s << "<polyline"
				<< " points=" << quoted(pp)
				<< " stroke=" << quoted(p.stroke_color)
             	<< " stroke-width=" << quoted(p.stroke_width) 
				<< "/>\n";
		}

		// Segment
		std::ostream& operator<<(std::ostream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "Segment[" << pp << "," << p.getStroke() << "]";
		}

		SVG::stream& operator<<(SVG::stream& s, const Segment& p) {
			const Array::Static<Point,2>  &pp = p;
			return s << "<polyline"
				<< " points=" << quoted(pp)
				<< " stroke=" << quoted(p.stroke_color) 
             	<< " stroke-width=" << quoted(p.stroke_width) 
				<< "/>\n";
		}

	}
}
