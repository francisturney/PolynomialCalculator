#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Calculate;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //connect(ui->lineEdit_2,SIGNAL(returnPressed()),this,SLOT(Fgraph()));
    connect(ui->comboBox,SIGNAL(activated(int)),this,SLOT(Fgraph()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(lineIn()));


}
void MainWindow::lineIn()
{                                                     //OLD MAIN
    QString Input, test, result, error;
    ui->lineEdit_2->clear();
    Input = ui->lineEdit->text();
    ui->lineEdit->clear();

    string Cinput = Input.toStdString();
    ui->widget->recieveList(list);


    //main
    try
    {
        result = process(Cinput, list);
        ui->lineEdit_2->setText(result);
        cout << "WIDGET LIST AT F = " << list['f'-'a'];
    }
        catch (EXPRESSION_ERRORS e)
        {
            if ( IMAGINARY)
                error.append("Imaginary Number");
            if (IMPOSSIBLE)
                error.append("Impossible");
            ui->lineEdit_2->setText(error);
        }
        catch (ERROR e)
        {
            if(INVALID)
                error.append("Invalid");
            if(CANNOT_HAPPEN)
                error.append("Cannot happen");
            ui->lineEdit_2->setText(error);
        }
        catch (FRACTION_ERRORS e)
        {
            if(DIV_BY_ZERO)
                error.append("Cannot divide by zero");
            if(INVALID_FRACTION)
                error.append("Invalid fraction");
            ui->lineEdit_2->setText(error);
        }
     ui->widget->recieveList(list);
     this->Fgraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Fgraph()
{
    ui->widget->setFunc(ui->comboBox->currentIndex());
    ui->widget->update();
}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    qDebug()<< "in horizontal sliderchanged";
}
