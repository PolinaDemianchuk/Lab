#include "equation.h"
#include "ui_equation.h"
#include "ur1.h"
#include "ur2.h"
#include "ur3.h"
#include <QStatusBar>
#include <QMessageBox>
#include "QLabel"


Equation::Equation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Equation)
{
    ui->setupUi(this);

}

Equation::~Equation()
{
    delete ui;
}

void Equation::on_pushButton_clicked()
{
    Ur1 *urav1;
    urav1 = new Ur1(this);
    urav1->setWindowTitle("4x+8");

    Ur2 *urav2;
    urav2 = new Ur2(this);
    urav2->setWindowTitle("2x^2+5x+13");

    Ur3 *urav3;
    urav3 = new Ur3(this);
    urav3->setWindowTitle("7x^3+8x^2+x-11");


    if (ui->radioButton->isChecked())
        urav1->show();


    if (ui->radioButton_2->isChecked())
        urav2->show();


    if (ui->radioButton_3->isChecked())
        urav3->show();
}

void Equation::on_actionRun_triggered()
{
    statusBar()->showMessage(tr("Save"));

}

void Equation::on_actionExit_triggered()
{
    QApplication::exit();
}



