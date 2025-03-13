#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

class Second{
    public :
    int seconde;

    Second() : seconde(0){
        cout << "Constructeur par déf" << endl;
    }
    Second(int sec) : seconde(sec){
        cout << "Constructeur avec un entier" << endl;
    }
    Second(const Second& s) : seconde(s.seconde%60){
        cout << "Constructeur par copie" << endl;
    }
    int getSecond(){
        return seconde;
    }
    int setSecond(int s){
        return seconde=s;
    }
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Second& s) {
        return os << s.seconde << "s";
    }
    bool operator<(const Second& s) const {
        return seconde < s.seconde;
    }
    bool operator==(const Second& s) const {
        return seconde == s.seconde;
    }
};
class Minute{
    public : 
    int minute;

    Minute() : minute(0){
        cout << "Constructeur par déf" << endl;
    }
    Minute(int min) : minute(min){
        cout << "Construtcteur avec un entier" << endl;
    }
    Minute(const Minute& m) :  minute(m.minute%60){
        cout << "Constructeur par copie" << endl;
    }
    Minute(const Second& s) : minute(s.seconde/3600){
        cout << "Constructeur à partir d'une instance de seconde" << endl;
    }
    int getMinute(){
        return minute;
    }
    int setMinute(int min){
        return minute=min;
    }
    Second seconds() const{
        return Second(minute*60);
    }
    friend std::ostream& operator<<(std::ostream& os, const Minute& m){
        return os << m.minute << "m";
    }
    bool operator<(const Minute& m){
        return minute < m.minute;
    }
    bool operator==(const Minute& m){
        return minute == m.minute;
    }
};

int main(){

    Second s1(140);
    Second s2(s1);
    Second s3(3666);

    Minute m1(75);
    Minute m2(m1);
    Minute m3(s3);
    
    Second s4 = m1.seconds();


    cout << "Valeur de s1 = " << s1 << endl;
    cout << "Valeur de s2 = " << s2 << endl;
    cout << "Valeur de s4 = " << s4 << endl;
    
    cout << "Valeur de m1 = " << m1 << endl;
    cout << "Valeur de m2 = " << m2 << endl;
    cout << "Valeur de m3 = " << m3 << endl;

    s1.setSecond(19);
    
    m1.setMinute(45);
    
    cout << "Nouvelle valeur de s1 = " << s1 << endl;

    cout << "Nouvelle valeur de m1 = " << m1 << endl;

    cout << "Valeur de s1 = " << s1 << endl;
    cout << "Valeur de s2 = " << s2 << endl;

    cout << "Valeur de m1 = " << m1 << endl;
    cout << "Valeur de m2 = " << m2 << endl;
    if (s1==s2){
        cout << "s1 et s2 sont pareil " << endl;
    }else{
        cout << "s1 et s2 ne sont pas pareil" << endl;
        if (s1<s2){
            cout << "s2 est plus grand que s1" << endl;
        }else{
            cout << "s1 est plus grand que s2" << endl;
        }
    }
    if (m1==m2){
        cout << "m1 et m2 sont pareil " << endl;
    }else{
        cout << "m1 et m2 ne sont pas pareil " << endl;
        if(m1<m2){
            cout << "m2 est plus grand que m1 " << endl;
        }else{
            cout << "m1 est plus grand que m2 " << endl;
        }
    }


    return 0;

}