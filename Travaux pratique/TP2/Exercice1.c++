#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

struct Complex{
    public:
        double r;
        double i;
    //Constructeurs
    Complex() : r(0),i(0){
        cout << "Constructeur par déf" << endl;
    };
    Complex(double rI,double iI) : r(rI),i(iI){
        cout << "Constructeur double flottant" << endl;
    };
    Complex(double a) : r(a), i(a) {
        cout << "Constructeur avec un flottant" << endl;
    };
    Complex(Complex *c) : r(c->r), i(c->i){
        cout << "Constructeur par copie" << endl;
    };

    //Destructeur
    ~Complex(){
        cout << "Destructeur" << endl;
    };
    Complex& operator=(const Complex &z) {
    printf("Operator= (in=%p,out=%p)\n",&z,this);
    // faire ici l'affectation de z à l'objet courant comme indiqué dans le sujet
    
    this->i=z.i;
    this->r=z.r;

    return *this;
}
};

//Méthode
void view(Complex *c){
    cout << c->r << " + i" << c->i << endl;
};
float norm(Complex c){
    float norm;
    norm=c.i*c.i;
    norm=norm + (c.r*c.r);
    return sqrt(norm);
}
Complex sqr(Complex &z){
    z.i=z.i*z.i;
    z.r=z.r*z.r;
    return z;
}
int main(){
    Complex c1,c2;//,c3,c4;

    c1=Complex();

    c2=Complex(1.4,2.3);
    //c3=Complex(5.6);
    //c4=Complex(c3);
    view(&c1);
    view(&c2);
    //c1=c2;
    //c1=sqr(c2);
    Complex c3 = sqr(c2);
    view(&c3);
    


    cout << "La norme de chaque nombre complex" << endl;

    cout << norm(c1) << endl;
    cout << norm(c2) << endl;
    //cout << norm(c3) << endl;
    //cout << norm(c4) << endl;
    
    return(0);
}
