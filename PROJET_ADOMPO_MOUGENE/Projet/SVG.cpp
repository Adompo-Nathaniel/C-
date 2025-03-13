#include "SVG.h"
#include <iostream>
#include <sstream>
#include <string> 

void SVG::stream::write_header(bool PureSVG, int hauteur, int largeur) {
	if (!PureSVG) *this << "<!doctype html>";
	*this << "<svg width=\"" << std::to_string(largeur) << "\" height=\"" << std::to_string(hauteur) << "\">\n";
}

void SVG::stream::write_trailer() {
	*this << "<\\svg>\n";
}

void SVG::stream::close() {
	if (is_open()) {
		write_trailer();
		std::ofstream::close();   // close hérité
	}
}

bool SVG::stream::open(const char *fname, bool PureSVG, int hauteur, int largeur) {
	close(); // c'est toujours la surcharge
	std::ofstream::open(fname, std::ios::out | std::ios::trunc); // open hérité
	bool status = is_open();
	if (status) write_header(PureSVG, hauteur, largeur);
	return status;
}

SVG::stream::stream(const char *fname, bool PureSVG, int hauteur, int largeur) : std::ofstream(fname, std::ios::out | std::ios::trunc) {
	if (is_open()) write_header(PureSVG, hauteur, largeur);
}

SVG::stream::~stream() {
	close();
}

template <typename T> static inline SVG::stream& write_into_stream(SVG::stream& s, T val) {
	std::ofstream &f = s;
	f << val;
	return s;
}

SVG::stream& SVG::operator<<(SVG::stream& s, const char *str) { return write_into_stream(s, str); }
SVG::stream& SVG::operator<<(SVG::stream& s, const float val) { return write_into_stream(s, val); }
SVG::stream& SVG::operator<<(SVG::stream& s, const std::size_t val) { return write_into_stream(s, val); }
