#include "term.h"

const long long int negONE = -1, ONE = 1, ZERO = 0;


term::term()
{
    next = NULL;
    before = NULL;
}

term::term(term& x)
{
    copy(x);
}


term::term(fraction c, fraction p)
{
    coeff =  c;
    power = p;
    if(!valid())
        throw INVALID;
}

term::~term()
{
    next = NULL;
    before = NULL;
}

term& term::operator=(term&other)
{
    if(this != &other)
        copy(other);
    return *this;
}

fraction term::evaluate(fraction &x)
{
    fraction answer;
    answer = coeff*(x^power);
    return answer;
}

term term::derivative()
{
    coeff *= power;
    power -= ONE;
}

void term::setTerm(const fraction c, const fraction p)
{
    coeff = c;
    power = p;
}
void term::setNext(term* newNext)
{
    next = newNext;
}
void term::setBefore(term* newBefore)
{
    before = newBefore;
}

fraction& term::getCoeff()
{
    return coeff;
}


fraction& term::getPower()
{
    return power;
}

term*& term::link()
{
    return next;
}

term*& term::bLink()
{
    return before;
}

void term::copy(term& x)
{
    coeff = x.coeff;
    power = x.power;
    next = x.link();
    before = x.bLink();
}

bool term::valid()
{
    return coeff.denom() != 0 && power.denom() != 0;
}

term operator+(term& x, term& y)
{
    if(x.power != y.power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff + y.coeff, x.power);
    return ans;
}


term operator-(term& x, term& y)
{
    if(x.power != y.power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff - y.coeff, x.power);
    return ans;
}


term operator*(term& x, term& y)
{
    term ans(x.coeff * y.coeff, x.power + y.power);
    return ans;
}

ostream& operator<<(ostream& out, const term other)
{
    if(other.coeff < ZERO)
        out<<" - ";
    else
        if (out.tellp() != 0)
        {
            out<<" + ";
        }

    //cout <<" other.coefficent =" << other.coeff;
    fraction temp = abs(other.coeff);
    fraction temp2 = (other.power);
    //cout << "\nabs value = " << temp <<endl;
    //if (!((temp == ONE) && (temp2 == ZERO)))
    out<<abs(other.coeff);

    //cout <<"in fract out coef = " << other.coeff;

    if(other.power != ZERO)
      out<<"X^"<<other.power;
    return out;
}


istream& operator>>(istream& in, term &other)
{
    char junk;
    in>>other.coeff>>junk>>junk>>other.power;
    //cout << "\nother.power = " << other.power << " junk = " << junk << " other.coeff " << other.coeff << endl;
    //cin >> junk;
    return in;
}
