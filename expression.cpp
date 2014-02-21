#include "expression.h"

const long long int negONE = -1, ONE = 1;

expression::expression()
{
    myExpression = NULL;
}

expression::~expression()
{
    zero();
}

expression::expression(const expression &other)
{
    copy(other);
}

expression& expression::operator=(const expression &other)
{
    if(this != &other)
    {
        zero();
        copy(other);
    }
    return *this;
}
expression& expression::operator=(expression &other)
{
    cout<< "IN EXPRESSION OUT" << other << "END EXPRESSION" << endl;

    if(this != &other)
    {
        zero();
        copy(other);
    }
    return *this;
}

QString expression::qS()
{
    QString Qreturn("");
    stringstream ss;
    string temp;
    expression copy(*this);
    ss<<copy;
    getline(ss,temp);
    string test(temp);
    //cout << "HERE BEFORE TEMP = " << *this << "temp = " << temp;
    qDebug()<< " TEST = " << Qreturn.fromStdString(temp);
    Qreturn = Qreturn.fromStdString(test);
    return Qreturn;
}


expression& expression::operator<<(term &input)
{
    term *newTerm = new term(input);
    term *searchPtr = myExpression;
    if (myExpression == NULL)																					//empty expression
    {
        myExpression = newTerm;
        return *this;
    }
    else
    {
        while (searchPtr != NULL)
        {
//			cout << "\nsearchptr not null\n";

            if (searchPtr->getPower() == newTerm->getPower())													//same power term
            {
//				cout << "\n\nin same power\n";
                searchPtr->setTerm(searchPtr->getCoeff() + newTerm->getCoeff(), searchPtr->getPower());
                return *this;
            }

            if (newTerm->getPower() > searchPtr->getPower())													//bigger power new term
            {

                if(searchPtr == myExpression)																	//bigger at head/myExpression
                {
                    newTerm->setNext(searchPtr);
                    searchPtr->setBefore(newTerm);
                    myExpression = newTerm;
                    return *this;
                }
                else																							//bigger in the middle of expression
                {
                    (searchPtr->bLink())->setNext(newTerm);
                    searchPtr->setBefore(newTerm);
                    newTerm->setNext(searchPtr);
                    newTerm->setBefore(searchPtr->bLink());
                    return *this;
                }
            }
//		else
//			cout << "\n search ptr link 1= " << *(searchPtr->link());

        if (searchPtr->link() == NULL)
        {
//			cout << "\nin searchptr link is null/ *searchptr = " << *searchPtr <<" \n";
            searchPtr->setNext(newTerm);
//			cout << "\n search ptr link = " << *(searchPtr->link());

            newTerm->setBefore(searchPtr);
//			cout << "\n newTerm bLink = " << *(newTerm->bLink()) << endl;
            return *this;
        }
        searchPtr = searchPtr->link();
        }
    }
    return *this;
}
bool expression::is_head(term Head)
{
    if(myExpression == &Head);
        return true;

    return false;
}


expression& expression::operator<<(string &input)
{
    term nextTerm;
    stringstream ss;
    ss<<input;
    while(ss>>nextTerm)
        *this<<nextTerm;
    return *this;
}


expression& expression::operator>>(string &output)
{
    stringstream ss;
    term *head = this->myExpression;
    while(head)
    {
        ss<<*head;
        head = head->link();
    }
    ss>>output;
    return *this;
}
bool expression::used()
{
    if (myExpression == NULL)
        return false;
    else
        return true;
}
void expression::clear()
{
    zero();
}

void expression::copy(const expression &other)
{
    term *otherHead = other.myExpression, *end;
    if(otherHead != NULL)
    {
        term * newCopiedTerm = new term(*otherHead);
        myExpression = end = newCopiedTerm;
        otherHead = otherHead->link();

        while(otherHead != NULL)
        {
            newCopiedTerm = new term(*otherHead);
            end->setNext(newCopiedTerm);
            end = end->link();
            otherHead = otherHead->link();
        }
    }
}

void expression::zero()
{
    term *bye;
    while(myExpression)
    {
        bye = myExpression;
        myExpression = myExpression->link();
        delete bye;
    }
}

ostream& operator<<(ostream &out,const expression &p)
{
    term *head = p.myExpression;
    while(head != NULL)
    {
        out<<*head;
        head = head->link();
    }
    out << endl;
    return out;
}
void expression::parseIncoming(string &input)
{
    for(int i = 0; i < input.size(); i++)
    {
        while(input[i] == ' ')
            input.erase(i,1);
        input[i] = tolower(input[i]);
    }
    input=input.substr(2);
    int i;
    bool in_num;
    for(i = 0; i < input.size(); i ++)
    {

        switch (what_is(input[i]))
        {
            case 'x':
                if(in_num == false)
                {
                    input.insert(i, "1");
                    i ++;
                }
                if (input[i +1] != '^')
                {
                    input.insert(i + 1, "^1");
                    i+=2;
                }
                in_num = false;
                break;

            case '^':
                for (i = i+1; (is_num(input[i]) || input[i] == '/' || input [i] == '-') && i < input.size(); i ++)
                    {}																				//exponent
                    break;
            case '+':
            case '-':
                if(in_num == true)
                {
                    input.insert(i, "x^0");
                    i += 3;
                    in_num = false;
                }
                break;
            case '0':
                if(in_num == false)
                    in_num = true;
                break;

            default:
                break;
        }
    }
    if (in_num)
    {
        input.insert(input.size(), "x^0");
    }


}


istream& operator>>(istream &in, expression &p)
{
    string toBeParsed;
    getline(in,toBeParsed);
    for(int i = 0; i < toBeParsed.size(); i++)
    {
        while(toBeParsed[i] == ' ')
            toBeParsed.erase(i,1);
        toBeParsed[i] = tolower(toBeParsed[i]);
    }
    if(toBeParsed.size()<3)
        return in;
    p.parseIncoming(toBeParsed);
    stringstream ss;
    ss<<toBeParsed;

    term newTerm;
    while(!ss.eof())
    {
        ss >> newTerm;
        p<<newTerm;
        //cout << endl << "new term = " << newTerm << endl;
    }
    //cout << endl << "expression = " << p << endl;
    return in;
}
const expression operator+(const expression& x,const expression& y)
{
    expression tempEx1 = x, tempEx2 = y;                                       //Created new expressions so wont edit old ones
    term *term1 = tempEx1.myExpression;
    term *term2 = tempEx2.myExpression;
    term temp[100];                                                             //array of Terms
    expression resultExp;
    int i=0;
    do{
        //cout <<"begin of dowhile loop\n";
        if(term1 == NULL || term2 == NULL)                                      //Check for NULL pointers first
        {
            //cout<< "\n In one term is null";
            if(term2 == NULL && term1 != NULL)                                  //pull term 1 down
            {
                temp[i].setTerm(term1->getCoeff(), term1->getPower());
                term1=term1->link();
            }
            if(term1 == NULL && term2 !=NULL)                                   //pull tern 2 down
            {
                temp[i].setTerm(term2->getCoeff(),term2->getPower());
                term2=term2->link();
            }
        }
        else
        {
            if(term1->getPower() == term2->getPower())
            {
                const fraction tempF = term1->getCoeff() + term2->getCoeff();
                temp[i].setTerm(tempF,term1->getPower());
                term1 = term1->link();
                term2 = term2->link();
            }
            else
                if(term1->getPower() > term2->getPower())
                {
                    //cout << "\nin term 1 greater\n";

                    temp[i].setTerm(term1->getCoeff(),term1->getPower());
                    term1 = term1->link();
                }
            else
                if(term2->getPower() > term1->getPower())
                {
                    cout << "\nin term 2 greater\n";
                    temp[i].setTerm(term2->getCoeff(),
                                     term2->getPower());
                    term2 = term2->link();
                }
        }
        //cout << "\n end of while loop\n";
        i++;
    }while(!(term1 == NULL && term2 == NULL));
    //cout << "\nout of while loop\n";
    term* tempPtr;
    for(int j=0;j<i-1;j++)
    {
        tempPtr = &temp[j+1];
        temp[j].setNext(tempPtr);
    }
    resultExp.myExpression = &temp[0];
    //cout << "\nresult expression = "<< resultExp <<endl;
    const expression extract(resultExp);                                //create a constant expression that can be returned
    return extract;

}

expression operator*(const expression &x, const expression &y)
{
    expression expOut, tempX = x, tempY = y;
    term temp[100];
    term* term1 = tempX.myExpression;
    term* term2 = tempY.myExpression;
    int i=0,j=0;

    while(term1 != NULL)
    {
        while(term2 != NULL)
        {
            temp[i].setTerm(term1->getCoeff() * term2->getCoeff(),
                                term1->getPower()+term2->getPower());
            term2 = term2->link();
            i++;
        }
        term1 = term1->link();
        term2 = tempY.myExpression;
    }
    for(j=0;j<i;j++)
    {
        expOut << temp[j];
    }
    return expOut;
}

const expression operator-(const expression &x, const expression &y)
{
    expression tempEx1 = x, tempEx2 = y;                                       //Created new expressions so wont edit old ones
    term *term1 = tempEx1.myExpression;
    term *term2 = tempEx2.myExpression;
    term temp[100];
    expression resultExp;
    int i=0;
    do{
        //cout <<"begin of dowhile loop\n";
        if(term1 == NULL || term2 == NULL)                                      //Check for NULL pointers first
        {
            //cout<< "\n In one term is null";
            if(term2 == NULL && term1 != NULL)                                  //pull term 1 down
            {
                temp[i].setTerm((term1->getCoeff()), term1->getPower());
                term1=term1->link();
            }
            if(term1 == NULL && term2 !=NULL)                                   //pull tern 2 down
            {
                temp[i].setTerm(term2->getCoeff(),term2->getPower());
                term2=term2->link();
            }
        }
        else
        {
            if(term1->getPower() == term2->getPower())
            {
                temp[i].setTerm(term1->getCoeff() - term2->getCoeff(),
                                 term1->getPower());
                term1 = term1->link();
                term2 = term2->link();
            }
            else
                if(term1->getPower() > term2->getPower())
                {
                    temp[i].setTerm(term1->getCoeff(),
                                     term1->getPower());
                    term1 = term1->link();
                }
                else
                    if(term2->getPower() > term1->getPower())
                    {

                        temp[i].setTerm((negONE*term2->getCoeff()),
                                         term2->getPower());
                        term2 = term2->link();
                    }
         }
        i++;
    }while(term1 != NULL || term2 != NULL);

    term* tempPtr;
    for(int j=0;j<i-1;j++)
    {
        tempPtr = &temp[j+1];
        temp[j].setNext(tempPtr);
    }
    resultExp.myExpression = &temp[0];
    const expression extract(resultExp);                                //create a constant expression that can be returned
    return extract;
}
fraction expression::evaluate(fraction &x)
{

    long long int zero = 0,one=1,two=2,neg=-1;


    fraction ans(zero),coefficient,power, tempX = x, tempPow, temp, subAns;
    fraction ZERO(zero),ONE(one),TWO(two),NEG(neg);
    term *term1 = this->myExpression;
    while(term1 != NULL)
    {
        coefficient = term1->getCoeff();
        power = term1->getPower();
        //cout<<"coeff: "<<coefficient<<endl;


        if(tempX < ZERO && (power.denom()%2 == 0))
               throw IMAGINARY;
        if (x == zero && term1->getPower() < zero)
            throw IMPOSSIBLE;
        tempPow = tempX^power;
        subAns = coefficient*(tempPow);
        ans += subAns;
        //cout <<" sub ans = " << subAns;

        term1 = term1->link();


    }

    return ans;
}
fraction expression::evaluateGr(fraction &x)
{

    long long int zero = 0,one=1,two=2,neg=-1;


    fraction ans(zero),coefficient,power, tempX = x, tempPow, temp, subAns;
    fraction ZERO(zero),ONE(one),TWO(two),NEG(neg);
    term *term1 = this->myExpression;
    ans.setErrorW(1);
    while(term1 != NULL)
    {
        coefficient = term1->getCoeff();
        power = term1->getPower();
        //cout<<"coeff: "<<coefficient<<endl;
        if(tempX < ZERO && (power.denom()%2 == 0))
              throw IMAGINARY;
        if (x == zero && term1->getPower() < zero)
            throw IMPOSSIBLE;
        tempPow = tempPow.powLPresision(tempX, power);
        subAns = coefficient*(tempPow);
        ans += subAns;
        term1 = term1->link();
    }

    return ans;
}
expression expression::derivative(int x)
{
    expression ans,temp = *this;
    const int count(x);
    term *tempTerm = temp.myExpression;
    int i;
    for(i=0;i<count;i++)
    {
        while(tempTerm != NULL)
        {
            tempTerm->derivative();
            tempTerm = tempTerm->link();
        }
        tempTerm = temp.myExpression;
    }
    return temp;
}

char expression ::what_is(char i)
{
    if (is_num(i))
        return '0';
    else
        return i;
}
bool expression::is_num(char lineI)
{
    int i;
    char numbers[11] = "0123456789";
    for (i = 0; numbers[i] != NULL; i ++)
        if (lineI == numbers[i])
            return true;
    return false;
}
