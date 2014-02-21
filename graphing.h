#ifndef GRAPHING_H
#define GRAPHING_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <QPen>
#include <QDebug>
#include <cstdlib>
#include "expression.h"
#include "mainwindow.h"
#include "cstdlib"

class Graphing : public QWidget
{
    Q_OBJECT
public:
    explicit Graphing(QWidget *parent = 0);
    void recieveList(expression list[]);
    void setFunc(int i);

signals:

public slots:

private:
    void paintEvent(QPaintEvent *e);
    expression Explist[26];
    expression function;
};

#endif // GRAPHING_H
