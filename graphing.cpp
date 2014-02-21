#include "graphing.h"
#include <QPainter>
#include <cmath>

using namespace std;
using namespace Calculate;

Graphing::Graphing(QWidget *parent) :
    QWidget(parent)
{
}
void Graphing::setFunc(int i)
{
        stringstream ss;
        //cout << "explist[i] "<< Explist[i];
        function = Explist[i];
        qDebug()<<"Funtion zone";
              cout<< "function is " <<function;
}

void Graphing::recieveList(expression list[])
{
    qDebug()<<"before list";
    cout << " Widget f = " << list['f' - 'a'];
    int i = 0;
    for(i = 0; i < 26; i ++)
    {
           Explist[i] = list[i];
    //cout << "list i = " << list[i]<< "Explist = " <<Explist[i];
    }

    //cout << "AFTER COPY F = " << list['f'-'a']<< "AFTER COPY F = " <<Explist['f'-'a'];
}

void Graphing::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //painter.drawLine(1,0,this->width(),this->height());

    int w = (this->width()),
            h = (this->height());
    //QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipRect(e->rect()); // this tells QPainter to restrict painting to only this rect

    painter.fillRect(0,0,this->width(),this->height(),Qt::white); //fills the background white

    QTransform transform;
    transform.translate(-2200,-2200);
    transform.scale((5000/w), 5000/h);
    painter.setTransform(transform);
    painter.translate(w/2,h/2); // origin


    painter.setPen(QPen(Qt::black,.2));
    painter.drawLine(0,-h/2,0,h/2);//y axis
    painter.drawText(5,-h/2 + 10,"Y");

    painter.drawLine(-w/2,0,w/2,0);//x axis
    painter.drawText(w/2 - 5,10,"X");



    painter.setPen(QPen(Qt::red,.2));
    QList<QPolygonF> curves;
    int index = 0, x;
    curves.append(QPolygonF());

    //fraction newF((long long)1,1LL);
    fraction ans;// = function.evaluate(newF)
    //cout << "ans = " << ans;
    //if(0)
    //{
    //fraction Lwidth((long long)-w,2LL), Rwidth((long long)w, 2LL), i, increment(1LL, 4LL);
    for(double i = (double)-w/2; i< (double)w/2; i+=.03125)
        {
            try
            {
             fraction Feval= i;
             ans.setErrorW(1);
             ans = function.evaluateGr(Feval);
             //cout << "\n               ans.num          =" << ans.num() << "     ans.denom()        "
             //     << ans.denom()<< endl;
             double intNum(ans.num()), intDenom(ans.denom());
             long double ansD = (intNum)/(intDenom);
             //cout << "\n                         double ans =                    " << ansD;
                 curves[index].append(QPointF((float)(3.*i),-(float)(ansD*3.)));
            }
            catch(EXPRESSION_ERRORS e)
            {
                if(curves[index].size() == 0)
                    continue;
                else
                    curves.append(QPolygonF());
                    index ++;
            }
        }
    //}

    foreach(QPolygonF curve, curves)
    {
        painter.drawPolyline(curve);
    }
}

