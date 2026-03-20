#include <iostream>
#include <cmath> 

#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

//constructor
rational::rational (int n, int d) {
    int g = rational::gcd(n, d);

    nom = (n/g);
    den = (d/g);

     if (den < 0) {
        nom = -nom; 
        den = -den; 
    }    

}

//+
rational operator + (const rational &x, const rational &y) {
    int new_nom = (x.nom * y.den) + (x.den * y.nom);
    int new_den = (x.den * y.den);

    return rational(new_nom, new_den);
}

//-
rational operator - (const rational &x, const rational &y) {
    int new_nom = (x.nom * y.den) - (x.den * y.nom);
    int new_den = (x.den * y.den);

    return rational(new_nom, new_den);
}

//*
rational operator * (const rational &x, const rational &y) {
    int new_nom = (x.nom * y.nom);
    int new_den = (x.den * y.den);

    return rational(new_nom, new_den);
}

// /
rational operator / (const rational &x, const rational &y) {
    int new_nom = (x.nom * y.den);
    int new_den = (x.den * y.nom);

    return rational(new_nom, new_den);
}

ostream & operator << (ostream &out, const rational &x) {
    if (x.den == 1) {
        out << x.nom;
    }
    else {
        out << x.nom << "/" << x.den;
    }

    return out;
}

int rational::gcd (int a, int b) {
    a = abs(a); 
    b = abs(b);
    while (a > 0 && b > 0) {
        if (a > b) a = a % b;
        else b = b % a;
    }
    return a + b;
}