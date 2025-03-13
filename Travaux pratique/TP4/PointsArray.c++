#include <string>
#include "SVGstream.h"
#include "color.h"
#include "Geometrie.c++"


class PointsArray {
protected:
    int taille;
    Point* tabPoint;

public:
    PointsArray(){
        taille=10;
        tabPoint[taille];
        cout << "Constructeur par défaut" << endl;
    }
    PointsArray(int _taille) : taille(_taille) {
        tabPoint = new Point[taille]; 
        cout << "Constructeur par initialisation" << endl;
    }

    ~PointsArray() {
        delete[] tabPoint;
    }
    //Constructeur par copie
    PointsArray(const PointsArray& other){
        taille = other.taille;
        for(int i=0;i<taille;i++){
            tabPoint[i]= other.tabPoint[i];
        }
        cout << "Constructeur par copie" << endl;
    }
    //Assignation par copie
    PointsArray& operator=(const PointsArray& other){
        if(this != &other){
            taille= other.taille;
            if(tabPoint!=nullptr){
                delete[] tabPoint;
            }
            tabPoint = new Point[taille];

            for(int i=0;i<taille;i++){
                tabPoint[i]=other.tabPoint[i];
            }
        }
        return *this;
    }
};

