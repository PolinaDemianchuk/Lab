#include "equation.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Equation w;
    w.show();
    return a.exec();
}
