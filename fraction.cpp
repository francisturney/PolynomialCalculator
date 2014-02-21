#include "fraction.h"


fraction::fraction()
{
    numerator = 0;
    denominator = 1;
}
fraction::fraction(long long int n)
{
    long long int d =1;
    makeNew(n,d);
}

fraction::fraction(long long int n, long long int d)
{
    makeNew(n,d);
}

fraction::fraction(double v)
{
    doubleInitialize(v);
}

fraction::fraction(const fraction &other)
{
    numerator = other.numerator;
    denominator = other.denominator;
}
fraction& fraction::operator=(const fraction &other)
{
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

fraction& fraction::operator+=(fraction &other)
{
    *this = *this + other;
}

fraction& fraction::operator-=(fraction &other)
{
    *this = *this - other;
    return *this - other;
}

fraction& fraction::operator*=(fraction &other)
{
    fraction temp;
    temp = *this * other;
    *this = temp;
    return temp;

}

fraction& fraction::operator/=(fraction &other)
{

//    if(other == 0)
//        throw DIV_BY_ZERO;
//    return *this / other;
}

fraction& fraction::operator^=(fraction &other)
{
    return *this ^ other;
}

fraction& fraction::operator=(long long int other)
{
    numerator = other;
    denominator = 1;
    return *this;
}

fraction& fraction::operator+=(long long int other)
{
    return *this + other;
}

fraction& fraction::operator-=(long long int other)
{
    fraction temp = *this - other;
    *this = *this - other;
    return *this - other;
}

fraction& fraction::operator*=(long long int other)
{
    return *this * other;
    *this = *this * other;
}

fraction& fraction::operator/=(long long int other)
{

    if(other == 0)
        throw DIV_BY_ZERO;
    return (*this) / other;
}

fraction& fraction::operator^=(long long int other)
{
    *this = *this ^ other;
    return *this ^ other;
}

fraction& fraction::operator=(double other)
{
    doubleInitialize(other);
    *this = *this * other;
    return *this;
}

fraction& fraction::operator+=(double other)
{
    *this = *this + other;
    return *this + other;
}

fraction& fraction::operator-=(double other)
{
    *this = *this - other;
    return *this - other;
}

fraction& fraction::operator*=(double other)
{
    *this = *this * other;
    return *this * other;

}

fraction& fraction::operator/=(double other)
{
    if(other == 0.)
        throw DIV_BY_ZERO;
    return (*this) / other;
}

fraction& fraction::operator^=(double other)
{
    return *this ^ other;
}

void fraction::doubleInitialize(double d)
{
    long long int whole = ((long long int)d), bottom = 1;
    bool sign = false;
    if(d < 0)
    {
        sign = true;
        d = abs(d);
        whole = abs(whole);
    }
    d = (d) - (long double)whole;
    long long int i = 0;
    while ((d - (long long int)d) > 0. && i < 16)
    {
        i ++;
        d *= 10;
        bottom =  bottom * 10;
    }
    numerator = bottom*whole + (long long int)d;
    denominator = bottom;
    reduce();
    if(sign == true)
        numerator = numerator * (long long)-1;

}

void fraction::doubleInitializeL(double d)
{
    long long int whole = ((long long int)d), bottom = 1;
    bool sign = false;
    if(d < 0)
    {
        sign = true;
        d = abs(d);
        whole = abs(whole);
    }
    d = (d) - (long double)whole;
    long long int i = 0;
    while ((d - (long long int)d) > 0. && i < 8)
    {
        i ++;
        d *= 10;
        bottom =  bottom * 10;
    }
    numerator = bottom*whole + (long long int)d;
    denominator = bottom;
    reduce();
    if(sign == true)
        numerator = numerator * (long long)-1;

}
fraction fraction::powLPresision(fraction x, fraction y)
{
    bool sign = false;
    double power = (double(y.numerator)/double(y.denominator));             //exponent
    fraction zero;
    double num = double(x.numerator), denom = double(x.denominator);
    //cout << "num = " << num <<" denom = " << denom;
    if (num < 0. && y != zero && y.denominator%3 == 0)
    {
        num = abs(num);
        sign = true;
    }
    num = pow(num,power);                                                   //calculate
    denom =pow(denom,power);
    //cout <<"num power =" << num << "denom power" << denom;
    fraction numAns, denomAns;                                  //fractionize
    fraction answer;

    if (sign == true)
    {
        num *= -1.;
       // qDebug()<< " numerator was negetive";
    }
    numAns.doubleInitializeL((double)num);
    denomAns.doubleInitializeL((double)denom);
    answer = numAns/denomAns;                                               //divide out
    return answer;


}


void fraction::display()
{
    cout<<numerator<<"/"<<denominator;
}

long long int& fraction::num()
{
    return numerator;
}

long long int& fraction::denom()
{
    return denominator;
}

int fraction::sayErrorW()
{
    return errorWink;
}

void fraction::setErrorW(int e)
{
    errorWink = e;
}


void fraction::newValue(long long int n,long long int d)
{
    makeNew(n,d);
}

void fraction::makeNew(long long int n,long long int d)
{
    long long int zero =0;
    if(d == zero)
        throw INVALID_FRACTION;
    numerator = n;
    denominator = d;
    reduce();
}

void fraction::reduce()
{
    long long int div = gcd(abs(numerator),abs(denominator));
    numerator /= div;
    denominator /= div;
    if(denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
}

long long int fraction::gcd(long long int p,long long int q)
{
    return q == 0 ? p : gcd(q, p%q);
}


ostream& operator<<(ostream &out, const fraction &x)
{
    if (x.denominator == 1)
        out<<x.numerator;
    else
        out<<x.numerator<<"/"<<x.denominator;
    return out;
}

istream& operator>>(istream &in, fraction &x)
{
    char junk;
    x.numerator = 0;
    x.denominator = 1;
    if(in>>x.numerator)
      if(in.peek() == '/')
    {
        in>>junk;
        in>>x.denominator;
    }
    return in;
}


const fraction& operator+(const fraction &x, const fraction &y)
{
    fraction ans;
    ans.numerator = x.numerator*y.denominator + x.denominator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
//    cout << "xnum = "<< x.numerator << " ynum " << y.numerator << " x denom = " << x.denominator << " y denom " << y.denominator <<endl;
//    cout << "ans = " << ans <<endl;
    return ans;
}


fraction& operator-(fraction &x, fraction &y)
{
    fraction ans;
    ans.numerator = x.numerator*y.denominator - x.denominator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
    return ans;
}


fraction& operator*(fraction &x, fraction &y)
{
    fraction ans;
    ans.numerator = x.numerator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
    fraction extract(ans);
    return ans;
}


fraction& operator/(fraction &x, fraction &y)
{
    fraction ans;
    //cout << "    FRACX =     " << x << "      FRACT Y        " << y << endl;
    if(y.denominator == 0)
        throw DIV_BY_ZERO;
    ans.numerator = x.numerator*y.denominator;
    ans.denominator = x.denominator*y.numerator;
    ans.reduce();
    //cout << "            ans in divide =                " << ans << endl;
    return ans;
}

fraction& operator^(fraction &x, fraction &y)
{
    double power = (double(y.numerator)/double(y.denominator));             //exponent

    double num = double(x.numerator), denom = double(x.denominator);
    //cout << "num = " << num <<" denom = " << denom;
    num = pow(num,power);                                                   //calculate
    denom =pow(denom,power);
    //cout <<"num power =" << num << "denom power" << denom;
    fraction numAns(num), denomAns(denom);                                  //fractionize
    fraction answer;

    answer = numAns/denomAns;                                               //divide out
    return answer;
}

bool operator==(const fraction &x, const fraction &y)
{
    return x.numerator*y.denominator == x.denominator*y.numerator;
}

bool operator<=(const fraction &x,const  fraction &y)
{
    return x.numerator*y.denominator <= x.denominator*y.numerator;
}


bool operator<(const fraction &x, const fraction &y)
{
    return x.numerator*y.denominator < x.denominator*y.numerator;
}


bool operator>(const fraction &x,const  fraction &y)
{
    return !(x <= y);
}


bool operator>=(const fraction &x,const  fraction &y)
{
    return !(x < y);
}


bool operator!=(const fraction &x,const  fraction &y)
{
    return !(x == y);
}


//For long long integers

fraction& operator+(fraction &x, long long int y)
{
    fraction temp(y);
    fraction ans = x + temp;
    return ans;
}

fraction& operator-(fraction &x, long long int y)
{
    fraction temp(y);
    fraction ans = x - temp;
    return ans;
}

fraction& operator*(fraction &x, long long int y)
{
    fraction temp(y);
    fraction ans = x * temp;
    return ans;
}

fraction& operator/(fraction &x, long long int y)
{
    fraction temp(y);
    if(y == 0)
        throw DIV_BY_ZERO;
    static fraction ans = x / temp;
    return ans;
}
fraction& operator^(fraction &x, long long int y)
{
    fraction temp(y);
    static fraction ans = x ^ temp;
    return ans;
}

fraction& operator+(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp + y;
    return ans;
}

fraction& operator-(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp - y;
    return ans;
}

fraction& operator*(long long int x, fraction &y)
{
    fraction temp(x);
    fraction ans = temp * y;
    return ans;
}

fraction& operator/(long long int x, fraction &y)
{
    fraction temp(x);
    if(y.denominator == 0)
        throw DIV_BY_ZERO;
    fraction ans = temp / y;
    return ans;
}

fraction& operator^(long long int x, fraction &y)
{
    fraction temp(x);
    fraction ans = temp ^ y;
    return ans;
}

//For doubles and  float

fraction& operator+(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x + temp;
    return ans;
}

fraction& operator-(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x - temp;
    return ans;
}

fraction& operator*(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x * temp;
    return ans;
}

fraction& operator/(fraction &x, double y)
{
    fraction temp(y);
    if(y == 0.)
        throw DIV_BY_ZERO;
    static fraction ans = x / temp;
    return ans;
}

fraction& operator^(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x ^ temp;
    return ans;
}

fraction& operator+(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp + y;
    return ans;
}

fraction& operator-(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp - y;
    return ans;
}

fraction& operator*(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp * y;
    return ans;
}
fraction operator/(double x, fraction &y)
{
    fraction temp(x);
    if(y == 0.)
        throw DIV_BY_ZERO;
    static fraction ans = temp / y;
    return ans;
}

fraction& operator^(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp ^ y;
    return ans;
}

//Comparison operators -- fraction to long long integer and visa versa

bool operator==(const fraction &x, long long int y)
{
    fraction temp(y);
    return x == temp;
}

bool operator<=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x <= temp;
}

bool operator<(const fraction &x,long long int y)
{
    fraction temp(y);
    return x < temp;
}

bool operator>(const fraction &x, long long int y)
{
    fraction temp(y);
    return x > temp;
}

bool operator>=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x >= temp;
}

bool operator!=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x != temp;
}

bool operator==(long long int x,const fraction &y)
{
    fraction temp(x);
    return temp == y;
}
bool operator<=(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp <= y;
}

bool operator<(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp < y;
}

bool operator>(long long int x, const fraction &y)
{
    fraction temp(x);
    return temp > y;
}
bool operator>=(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp >= y;
}

bool operator!=(long long int x, const fraction &y)
{
    fraction temp(x);
    return y != temp;
}

//Comparison operators -- fraction to double and visa versa

bool operator==(const fraction &x, double y)
{
    fraction temp(y);
    return x == temp;
}
bool operator<=(const fraction &x,double y)
{
    fraction temp(y);
    return x <= temp;
}

bool operator<(const fraction &x,double y)
{
    fraction temp(y);
    return x < temp;
}

bool operator>(const fraction &x, double y)
{
    fraction temp(y);
    return x > temp;
}

bool operator>=(const fraction &x,double y)
{
    fraction temp(y);
    return x >=temp;
}

bool operator!=(const fraction &x,double y)
{
    fraction temp(y);
    return x != temp;
}

bool operator==(double x,const fraction &y)
{
    fraction temp(x);
    return temp == y;
}

bool operator<=(double x,const  fraction &y)
{
    fraction temp(x);
    return temp <= y;
}

bool operator<(double x,const  fraction &y)
{
    fraction temp(x);
    return temp < y;
}
bool operator>(double x, const fraction &y)
{
    fraction temp(x);
    return temp > y;
}

bool operator>=(double x,const  fraction &y)
{
    fraction temp(x);
    return temp >= y;
}


bool operator!=(double x, const fraction &y)
{
    fraction temp(x);
    return temp != y;
}


const fraction abs(fraction x)
{
    fraction temp;
    long long int negONE = -1, zero = 0;
    temp =(negONE *x);
    //cout << "\n temp = " << temp <<endl;
    const fraction extract(temp);
    return x < zero ? extract : x;
}
