#include <string>
#include "SVGstream.h"
#include "PointsArray.c++"



class ReallocatablePointsArray : public PointsArray {
private:
    int tailleTabAlloue; // Taille allouée pour le tableau de points

public:
    ReallocatablePointsArray(int _taille) : PointsArray(_taille), tailleTabAlloue(_taille) {
        tabPoint = new Point[tailleTabAlloue];
    }
    //Constucteur par copie
    ReallocatablePointsArray(const PointsArray& other){
        
    }
    void addPoint(Point newPoint) {
        if (taille >= tailleTabAlloue) {
            // Si le tableau est plein, réallouer avec une taille plus grande
            int nouvelleTaille = tailleTabAlloue * 2; // Double la taille allouée
            Point* nouveauTabPoints = new Point[nouvelleTaille];

            // Copier les éléments de l'ancien tableau vers le nouveau
            for (int i = 0; i < taille; ++i) {
                nouveauTabPoints[i] = tabPoint[i];
            }

            // Libérer la mémoire de l'ancien tableau
            delete[] tabPoint;

            // Mettre à jour le pointeur et la taille allouée
            tabPoint = nouveauTabPoints;
            tailleTabAlloue = nouvelleTaille;
        }

        // Ajouter le nouveau point au tableau
        tabPoint[taille++] = newPoint;
    }
    //Assignation par copie
    ReallocatablePointsArray& operator=(const ReallocatablePointsArray& other) {
        if (this != &other) {

            taille = other.taille;
            tailleTabAlloue = other.tailleTabAlloue;

            if (tabPoint != nullptr) {
                delete[] tabPoint;
            }
            tabPoint = new Point[tailleTabAlloue];

            for (int i = 0; i < taille; ++i) {
                tabPoint[i] = other.tabPoint[i];
            }
        }
        return *this;
    }
};