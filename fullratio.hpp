#ifndef FULLRATIO_HPP
#define FULLRATIO_HPP

#include <iostream>

class rational {
public:
    rational (int n, int d=1);

    friend rational operator + (const rational &x, const rational &y);
    friend rational operator - (const rational &x, const rational &y);
    friend rational operator * (const rational &x, const rational &y);
    friend rational operator / (const rational &x, const rational &y);
    
    friend std::ostream & operator << (std::ostream &out, const rational &x);

private:
    int nom, den;
    static int gcd (int a, int b);
};

#endif