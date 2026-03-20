#include <iostream>
#include <cmath> // Για την abs() (απόλυτη τιμή)

#ifndef CONTEST
#include "babyratio.hpp"
#endif

using namespace std;

//constructor
rational::rational (int n, int d) {
    int g = rational::gcd(n, d);

    n = (n/g);
    d = (d/g);

    nom = n;
    den = d;

    if (den < 0) {
        nom = -nom; 
        den = -den; 
    }
}

//add a/b + c/d
rational rational::add (rational r) {
    int new_nom = (nom * r.den) + (den * r.nom); // new nom
    int new_den = den * r.den; // new den

    return rational(new_nom, new_den);
}

//sub a/b - c/d
rational rational::sub (rational r) {
    int new_nom = (nom * r.den) - (den * r.nom); // new nom
    int new_den = den * r.den; // new den

    return rational(new_nom, new_den);
}

//mul a/b * c/d
rational rational::mul (rational r) {
    int new_nom = nom * r.nom;
    int new_den = den * r.den;

    return rational(new_nom, new_den);
}

//div a/b / c/d
rational rational::div (rational r) {
    int new_nom = nom * r.den;
    int new_den = den * r.nom;

    return rational(new_nom, new_den);
}

void rational::print() {
    if (den == 1) {
        cout << nom;
    }
    else {
    cout << nom << "/" << den;
    }
}

int rational::gcd(int a, int b){
    a = abs(a);
    b = abs(b);

    while (a>0 && b>0) {
        if (a > b) a = a % b;
        else b = b % a;
    }

    return a + b;

}

