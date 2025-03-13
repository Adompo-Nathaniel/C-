#include <string>
#include "SVGstream.h"
#include "color.h"

const char* Color::name[] = { "red", "white", "yellow", "orange", "turquoise", "violet", "pink", "green", "grey", "cyan", "blue", "brown" };

using namespace std;
namespace constantes {
    constexpr float pi_f = 3.14159265358979323846f;
}
struct Point{
    int x,y;
    inline Point() : x(0),y(0){
        cout << "Constructeur par déf" <<endl;
    }

    inline Point(int xVal,int yVal) : x(xVal),y(yVal){
        cout << "Constructeur par initialisation " << endl;
    }

    inline void view(){
        cout << "Point : [" << x << "." << y << "]" << endl;
    }

    inline void set(float u, float v) {
        x = u; y = v; 
    }
    // Utilisé pour facilité l'écriture de la translation
    inline void operator+=(const Point &p) {
        x += p.x;
        y += p.y; 
    }
    friend inline std::ostream& operator<<(std::ostream& s, const Point& p) {
        // format vers la sortie standard
        return s << "(" << p.x << "," << p.y << ")";
    }
    friend inline SVGstream& operator<<(SVGstream& s, const Point& p) {
        // format vers le fichier SVG
        s << "" << p.x << "," << p.y;
        return s;
    }
};

class Transform{
    public: using Vector = Point;
        virtual void Rotate(float angle)=0;
        virtual void Translate(const Vector &v)=0;
        virtual void Scale(float scale)=0;
};
class Geom2D: public Transform{
    public:
        // tous les constructeurs sont ceux par défaut
        virtual std::ostream& info(std::ostream&) const = 0;
        virtual SVGstream& write(SVGstream&) const = 0;
        virtual ~Geom2D();
        // L'opérateur ne peut pas être virtuel, car il s'agit d'un fonction
        // externe (une méthode de la classe std::ostream). On définit une
        // méthode Geom2D::info() virtuelle, laquelle est appellée par
        // l'opérateur <<, permettant la surcharge dans les classes dérivées.
        friend std::ostream& operator<<(std::ostream& s, const Geom2D *g) {
            // format vers la sortie standard
            return g->info(s);
        }
        friend SVGstream& operator<<(SVGstream& s, const Geom2D *g) {
            return g->write(s);
        }
};
Geom2D::~Geom2D() = default;

class Fill{
    protected:
        Color fillcolor;
    public:
        explicit Fill(const Color &c = Color::red);

        void setFillColor(const Color &c){
            fillcolor=c;
        }
};
Fill::Fill(const Color &c) : fillcolor(c) {}
class Surface : public Fill, public Geom2D {
    public:
        Surface() : Fill(),Geom2D(){}
        explicit Surface(const Color &c):Fill(c){};
        void Translate(const Vector &) override {} 
        void Rotate(float) override {} 
        void Scale(float) override {}
        virtual float area() = 0;
        virtual ~Surface();
};
Surface::~Surface()= default;

class Disc : public Surface {
    protected:
        Point center;
        float radius;
    public:
        Disc(const Point &xy, float r, const Color &c): Surface(c), center(xy), radius(r){}

    float area(){
        return constantes::pi_f*radius*radius;
    }

    virtual ~Disc() {};

    void Translate(const Vector &v)override {
        center += v;
    }
    void Scale(float s){
        radius *= s;
    }
    std::ostream& info(std::ostream& s) const override {
            return s << "Disk[center=" << center << ",radius=" << radius << "]" << std::endl;
    }
    SVGstream& write(SVGstream &s) const override {
        // format SVG: <circle cx="..." cy="..." r="..." fill="..." />
        s << "<circle cx=\""<<center.x<<"\" cy=\""<<center.y<<"\" r=\""<<radius<<"\" fill=\""<<fillcolor<<"\"/>\n";
        return s;
    }
    friend std::ostream& operator<<(std::ostream& s, const Disc& d) { return d.info(s); }
    friend SVGstream& operator<<(SVGstream& s, const Disc& d) { return d.write(s); }
};  

class Rectangle : public Surface{
    protected:
        Point corner;
        float width, height;
        float rotate;
    public:
        explicit Rectangle(const Point &xy, float w, float h, const Color &c)
            : Surface(c), corner(xy), width(w), height(h), rotate(0.f) {}

        float area() { return width*height; }

        virtual ~Rectangle() {};

        void Translate(const Point &v) override {
             corner += v; 
        }
        void Scale(float s) override {
            width *= s; height *= s; 
        }
        void Rotate(float a) override {
            rotate += a; 
        }

        Rectangle *real_type() {
            return this; 
        }

        std::ostream& info(std::ostream& s) const override {
            return s << "Rectangle[center="
                        << Point(corner.x + width/2.f,corner.y +height/2.f) 
                        <<",width="<< width
                        <<", height="<< height
                        <<"]" << std::endl;
        }
        SVGstream& write(SVGstream &s) const override {
            // format SVG: <rect x="..." y="..." width="..." height="..." fill="..." transform="(rotate(angle x,y) />
            s << "<rect x=\""<<corner.x<<"\" y="<<corner.y<<"\" width=\""<<width<<"\" height=\""<<height<<"\" fill=\""<<fillcolor<<"\"/>"
                // Faire output comme dans Disk (donc output de corner pour x et y, puis width, height, ...)
                ;
            if (rotate) {
                // Rotation du rectangle par son centre géométrique (= croisement des diagonales :)
                // format SVG : transform="rotate(angle cx,cy)"
                //   où `angle` correspond à la rotation souhaitée
                //      `cx,cy` correspond aux coordonnées du centre de rotation
                Point center(corner.x + width/2.f, corner.y + height/2.f);
                s << " transform=\"rotate("<<rotate<<"+"<<center<<")\"";
            }
            s << "/>\n";
            return s;
        }
        friend std::ostream& operator<<(std::ostream& s, const Rectangle& r) { return r.info(s); }
        friend SVGstream& operator<<(SVGstream& s, const Rectangle& r) { return r.write(s);}
};
class Square : public Rectangle {
    public:
        explicit Square(const Point &xy, float s, const Color &c):Rectangle(xy, s, s, c) {}
        virtual ~Square() {};

        std::ostream& info(std::ostream& s) const override {
            return s << "Square[center="
                        << Point(corner.x + width/2.f,corner.y +height/2.f) 
                        <<",width="<< width
                        <<", height="<< height
                        <<"]" << std::endl;
        }
        friend std::ostream& operator<<(std::ostream& s, const Square& r) { return r.info(s); }
        friend SVGstream& operator<<(SVGstream& s, const Square& r) { return r.write(s); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Test01() {
    using namespace std;
    cout << "Test 1: redirection directe d'objets sur le flux de sortie" << endl;
    cout << "\t" << Rectangle({ 40,40 }, 100, 200, Color::yellow);

    Disc d(Point(50, 50), 30, Color::blue);
    cout << "\t" << d;
}

/// Test écriture au format SVG
void Test02() {
    std::string  svgfile("test01.html");
    std::cout << "Test 2: écriture directe d'objets dans un fichier svg" << std::endl;
    std::cout << "\t" << "génération svg dans " << svgfile << std::endl;
    SVGstream    svg(svgfile.c_str());
    svg << Disc(Point(50, 50), 30, Color::blue);
    svg << Rectangle({ 40,40 }, 100, 200, Color::yellow);
    svg << Square({ 80,80 }, 150, Color::brown);
    svg.close();
}



/// Test sous forme polymorphique
void Test03() {
    std::cout << "Test 3: idem test 1 et 2 avec utilisation d'objets sous forme polymorphique" << std::endl;
    const int nGeoms = 3;
    Geom2D   *Geoms[nGeoms] = {
        new Disc({ 400, 400 }, 240, Color::blue),
        new Rectangle({ 40,40 }, 100, 200, Color::orange),
        new Square({ 280,280 }, 150, Color::green)
    };


    // affichage
    for(int i=0;i<nGeoms;i++) std::cout << "\t" << Geoms[i];

    // écriture dans un fichier
    std::string  svgfile("test02.html");
    SVGstream    svg(svgfile.c_str());
    std::cout << "\t" << "génération svg dans " << svgfile << std::endl;
    for(int i=0;i<nGeoms;i++) svg << Geoms[i];
    svg.close();
}
int main() {
    Test01();
    Test02();
    Test03();
    return 0;
}
