#include "ur1.h"
#include "ui_ur1.h"
#include<QLineEdit>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDebug>
#include <QDir>
Ur1::Ur1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ur1)
{
    ui->setupUi(this);
}

Ur1::~Ur1()
{
    delete ui;
}

void Ur1::on_pushButton_clicked()
{
     QTextStream out(stdout);
    int x = ui->lineEdit_2->text().toInt();
    int a = ui->lineEdit_5->text().toInt();
    int c = ui->lineEdit_4->text().toInt();
    int y1 =a*x+c;
    res1.append(y1);
    model = new QStringListModel(this);
    QStringList List1;
    for (int i = 0; i < res1.size(); i++)
    {
        List1 << QString::number(res1.at(i));
    }

    model->setStringList(List1);

    ui->listView->setModel(model);


    QFile fileOut1("D:\\qt projects\\Uravnenie\\res1.txt");

    if(fileOut1.open(QIODevice::WriteOnly))
    {
        QTextStream writeStream(&fileOut1);

        for (int i = 0; i < res1.size(); i++)
        {
            writeStream << QString::number(res1.at(i));
            qDebug() << "Успешно сохранено";
        }

        fileOut1.close();
    }


}


