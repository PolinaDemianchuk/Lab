#include "ur2.h"
#include "ui_ur2.h"
#include <QFile>
#include <QDebug>
Ur2::Ur2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ur2)
{
    ui->setupUi(this);
}

Ur2::~Ur2()
{
    delete ui;
}

void Ur2::on_pushButton_clicked()
{
    int x = ui->lineEdit->text().toInt();
    int a = ui->lineEdit_5->text().toInt();
    int b = ui->lineEdit_3->text().toInt();
    int c = ui->lineEdit_4->text().toInt();
    int y2 =a*x*x+b*x+c;
    res2.append(y2);
    model = new QStringListModel(this);
    QStringList List2;
    for (int i = 0; i < res2.size(); i++)
    {
        List2 << QString::number(res2.at(i));
    }

    model->setStringList(List2);

    ui->listView->setModel(model);

    QFile fileOut2("D:\\qt projects\\Uravnenie\\res2.txt");

    if(fileOut2.open(QIODevice::WriteOnly))
    {
        QTextStream writeStream(&fileOut2);

        for (int i = 0; i < res2.size(); i++)
        {
            writeStream << QString::number(res2.at(i));
            qDebug() << "Успешно сохранено";
        }

        fileOut2.close();
    }
}

