#include "ur3.h"
#include "ui_ur3.h"
#include <QFile>
#include <QDebug>
Ur3::Ur3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ur3)
{
    ui->setupUi(this);
}

Ur3::~Ur3()
{
    delete ui;
}

void Ur3::on_pushButton_clicked()
{
    int x = ui->lineEdit->text().toInt();
    int a = ui->lineEdit_4->text().toInt();
    int b = ui->lineEdit_3->text().toInt();
    int c = ui->lineEdit_5->text().toInt();
    int d = ui->lineEdit_6->text().toInt();
    int y3 =a*x*x*x+b*x*x+c*x+d;
    res3.append(y3);
    model = new QStringListModel(this);
    QStringList List3;
    for (int i = 0; i < res3.size(); i++)
    {
        List3 << QString::number(res3.at(i));
    }

    model->setStringList(List3);

    ui->listView->setModel(model);

    QFile fileOut3("D:\\qt projects\\Uravnenie\\res3.txt");

    if(fileOut3.open(QIODevice::WriteOnly))
    {
        QTextStream writeStream(&fileOut3);

        for (int i = 0; i < res3.size(); i++)
        {
            writeStream << QString::number(res3.at(i));
            qDebug() << "Успешно сохранено";
        }

        fileOut3.close();
    }
}

