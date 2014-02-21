#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "fraction.h"

using namespace std;

enum ERROR {INVALID, CANNOT_HAPPEN};

class term
{
    public:
        term();
        term(fraction c,fraction p);
        ~term();
        term(term& other);
        term& operator=(term&other);
        fraction evaluate(fraction &x);
        term derivative();
        void setTerm(const fraction c,const fraction p);
        void setNext(term* newNext);
        void setBefore(term* newBefore);
        fraction& getCoeff();
        fraction& getPower();
        term*& link();
        term*& bLink();

        friend
        term operator+(term& x, term& y);

        friend
        term operator-(term& x, term& y);

        friend
        term operator*(term& x, term& y);

        friend
        ostream& operator<<(ostream& out, const term other);

        friend
        istream& operator>>(istream& in, term &other);

    private:

        fraction coeff, power;
        term *next;
        term *before;
        void copy(term& other);
        bool valid();


};


#endif // TERM_H
