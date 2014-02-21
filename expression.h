#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdlib>
#include "term.h"
#include <QString>
#include <QDebug>

using namespace std;

enum EXPRESSION_ERRORS{IMAGINARY, IMPOSSIBLE};


class expression
{
    public:
        expression();
        ~expression();
        expression(const expression &other);
        expression& operator=(const expression &other);
        expression& operator=(expression &other);

        expression& operator<<(string &input);
        expression& operator<<(term &input);//localhost/Users/francisturney/Documents/PCC/CS3a/poly%20calc/poly%20calculater/expression.h
        expression& operator>>(string &output);
        QString qS();

        bool used();
        void clear();
        void parseIncoming(string& input);
        char what_is(char i);
        bool is_num(char lineI);
        bool is_head(term Head);


        fraction evaluate(fraction &x);
        fraction evaluateGr(fraction &x);

        expression derivative(int x);

        friend
        expression operator*(const expression &x, const expression &y);

        friend
        const expression operator+(const expression& x,const expression& y);


        friend
        const expression operator-(const expression &x, const expression &y);


        friend
        ostream& operator<<(ostream &out, const expression &p);

        friend
        istream& operator>>(istream &in, expression &p);


    private:
        term* myExpression;

        void copy(const expression &other);
        void zero();
};
#endif // EXPRESSION_H
