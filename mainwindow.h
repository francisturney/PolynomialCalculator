#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include "fstream"
#include "cstdlib"
#include "expression.h"
#include <QApplication>
#include "graphing.h"
#include "calculate.h"

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow /*: public string : expression*/
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void lineIn();
    void Fgraph();
private slots:
    //void on_comboBox_activated( QString &arg1);
    //void Fgraph();

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    expression list[26];
};

#endif // MAINWINDOW_H
