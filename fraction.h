#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <QDebug>

enum FRACTION_ERRORS {DIV_BY_ZERO, INVALID_FRACTION};

using namespace std;


class fraction
{
    public:
        fraction();
        fraction(long long int n,long long int d);
        fraction(long long int n);
        fraction(double v);
        fraction(const fraction &other);
        fraction& operator=(const fraction &other);
        fraction& operator+=(fraction &other);
        fraction& operator-=( fraction &other);
        fraction& operator*=( fraction &other);
        fraction& operator/=( fraction &other);
        fraction& operator^=( fraction &other);
        fraction& operator=(long long int other);
        fraction& operator+=(long long int other);
        fraction& operator-=(long long int other);
        fraction& operator*=(long long int other);
        fraction& operator/=(long long int other);
        fraction& operator^=(long long int other);
        fraction& operator=(double other);
        fraction& operator+=(double other);
        fraction& operator-=(double other);
        fraction& operator*=(double other);
        fraction& operator/=(double other);
        fraction& operator^=(double other);

        void display();
        long long int& num();
        long long int& denom();
        void newValue(long long int n,long long int d);
        int sayErrorW();
        void setErrorW(int e);
        void doubleInitializeL(double d);
        fraction powLPresision(fraction x, fraction y);

        friend
        ostream& operator<<(ostream &out, const fraction &x);

        friend
        istream& operator>>(istream &in, fraction &x);

        friend
        const fraction& operator+(const fraction &x, const fraction &y);

        friend
        fraction& operator-(fraction &x, fraction &y);

        friend
        fraction& operator*(fraction &x, fraction &y);

        friend
        fraction& operator/(fraction &x, fraction &y);

        friend
        fraction& operator^(fraction &x, fraction &y);

  //For long long integers
        friend
        fraction& operator+(fraction &x, long long int y);

        friend
        fraction& operator-(fraction &x, long long int y);

        friend
        fraction& operator*(fraction &x, long long int y);

        friend
        fraction& operator/(fraction &x, long long int y);

        friend
        fraction& operator^(fraction &x, long long int y);

        friend
        fraction& operator+(long long int x, fraction &y);

        friend
        fraction& operator-(long long int x, fraction &y);

        friend
        fraction& operator*(long long int x, fraction &y);

        friend
        fraction& operator/(long long int x, fraction &y);

        friend
        fraction& operator^(long long int x, fraction &y);

 //For doubles and  float
        friend
        fraction& operator+(fraction &x, double y);

        friend
        fraction& operator-(fraction &x, double y);

        friend
        fraction& operator*(fraction &x, double y);

        friend
        fraction& operator/(fraction &x, double y);

        friend
        fraction& operator^(fraction &x, double y);

        friend
        fraction& operator+(double x, fraction &y);

        friend
        fraction& operator-(double x, fraction &y);

        friend
        fraction& operator*(double x, fraction &y);

        friend
        fraction operator/(double x, fraction &y);

        friend
        fraction& operator^(double x, fraction &y);


//Comparison operators -- fraction to fraction
        friend
        bool operator==(const fraction &x,const fraction &y);

        friend
        bool operator<=(const fraction &x,const  fraction &y);

        friend
        bool operator<(const fraction &x,const  fraction &y);

        friend
        bool operator>(const fraction &x, const fraction &y);

        friend
        bool operator>=(const fraction &x,const  fraction &y);

        friend
        bool operator!=(const fraction &x, const fraction &y);

//Comparison operators -- fraction to long long integer and visa versa
        friend
        bool operator==(const fraction &x, long long int y);

        friend
        bool operator<=(const fraction &x,long long int y);

        friend
        bool operator<(const fraction &x,long long int y);

        friend
        bool operator>(const fraction &x, long long int y);

        friend
        bool operator>=(const fraction &x,long long int y);

        friend
        bool operator!=(const fraction &x,long long int y);

        friend
        bool operator==(long long int x,const fraction &y);

        friend
        bool operator<=(long long int x,const  fraction &y);

        friend
        bool operator<(long long int x,const  fraction &y);

        friend
        bool operator>(long long int x, const fraction &y);

        friend
        bool operator>=(long long int x,const  fraction &y);

        friend
        bool operator!=(long long int x, const fraction &y);


//Comparison operators -- fraction to double and visa versa
        friend
        bool operator==(const fraction &x, double y);

        friend
        bool operator<=(const fraction &x,double y);

        friend
        bool operator<(const fraction &x,double y);

        friend
        bool operator>(const fraction &x, double y);

        friend
        bool operator>=(const fraction &x,double y);

        friend
        bool operator!=(const fraction &x,double y);

        friend
        bool operator==(double x,const fraction &y);

        friend
        bool operator<=(double x,const  fraction &y);

        friend
        bool operator<(double x,const  fraction &y);

        friend
        bool operator>(double x, const fraction &y);

        friend
        bool operator>=(double x,const  fraction &y);

        friend
        bool operator!=(double x, const fraction &y);

        friend
        const fraction abs(fraction x);

    private:
        long long int numerator, denominator;
        int errorWink;

        void reduce();
        long long int gcd(long long int p,long long int q);
        void makeNew(long long int n, long long int d);
        void doubleInitialize(double d);
};

#endif // FRACTION_H
