#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;

class Point{
    public:
        int x;
        int y;
        Point() : x(0),y(0){
            cout << "Constructeur par déf" <<endl;
        }
        Point(int xVal,int yVal) : x(xVal),y(yVal){
            cout << "Constructeur par initialisation " << endl;
        }
        void view(){
            cout << "Point : [" << x << "." << y << "]" << endl;
        }
};
