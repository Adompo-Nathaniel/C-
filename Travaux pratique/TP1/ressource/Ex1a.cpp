#include <cstdio>
#include <iostream>
/*
Ce que l'ont sait :trash:///TP2.2/Exercice2.cpp
    (int 123;)
    -Pour une rvalue-ref = int&&
    -Pour une lvalue-ref = int&
    -Pour une lvalue = 123
    -Pour une rvalue = i
*/
int fun1a(int  x) {
    x++;
    return x;
}

int fun1b(int &x) {
    x++;
    return x;
}

int fun1c(int &&x) {
    x++;
    return x;
}

int fun1d(int *x) {
    (*x)++;
    return *x;
}

int main() {
    // constante
    int i=4;
    int *ptr;
    ptr=&i;
    fun1a(4);
    fun1b(i);//fun1b(4); ici on donne une rvalue alors que la fonction attends une lvalue ref soit une truc commme i avec i=4;
    fun1c(4);
    fun1d(ptr);//fun1d(&4); ici on donne une adresse alors que la fonction attend un pointeur il faudrais plutôt définir un *ptr avec ptr=&i;

    // variable sans modificateur
    i = 4;
    fun1a(i);
    fun1b(i);
    fun1c(4);//fun1c(i); ici on donne une lvalue alors que la fonction elle attends une rvalue ref, on devrait ici lui donné une rvalue comme 4 par exemple
    fun1d(&i);

    // variable non modifiable
    const int j = 4;
    int k;
    k=j;
    fun1a(j);
    fun1b(k);//fun1b(j);pareil que en haut
    fun1c(4);//fun1c(j); pareil que en haut 
    fun1d(ptr);//fun1d(&j); pareil que en haut

    // référence sur une lvalue
    k = i;
    fun1a(k);
    fun1b(k);
    fun1c(4);//fun1c(k); pareil que en haut
    fun1d(&k);

    // référence sur une lvalue constante
    const int &m = i;
    int l=m;
    fun1a(m);
    fun1b(l);//fun1b(m);pareil que haut
    fun1c(4);//fun1c(m);pareil que en haut
    fun1d(&l);//fun1d(&m);pareil que en haut

    // référence sur une rvalue
    fun1a(i+4);
    i=i+4;
    fun1b(i);//fun1b(i+4);
    fun1c(i+4);
    fun1d(&i);

    return EXIT_SUCCESS;
}
