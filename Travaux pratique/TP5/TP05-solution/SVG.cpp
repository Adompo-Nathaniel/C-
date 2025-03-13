#include "SVG.h"

void SVG::stream::write_header(bool PureSVG) {
	if (!PureSVG) *this << "<!DOCTYPE html>" << std::endl;
	*this << "<svg width=\"1000\" height=\"1000\">" << std::endl;
}

void SVG::stream::write_trailer() {
	*this << "</svg>" << std::endl;
}

void SVG::stream::close() {
	if (is_open()) {
		write_trailer();
		std::ofstream::close();   // close hérité
	}
}

bool SVG::stream::open(const char *fname, bool PureSVG) {
	close(); // c'est toujours la surcharge
	std::ofstream::open(fname, std::ios::out | std::ios::trunc); // open hérité
	bool status = is_open();
	if (status) write_header(PureSVG);
	return status;
}

SVG::stream::stream(const char *fname, bool PureSVG) :
	std::ofstream(fname, std::ios::out | std::ios::trunc) {
	if (is_open()) write_header(PureSVG);
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
