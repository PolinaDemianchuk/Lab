#ifndef EQUATION_H
#define EQUATION_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class Equation;
}
QT_END_NAMESPACE

class Equation : public QMainWindow
{
    Q_OBJECT

public:
    Equation(QWidget *parent = nullptr);
    ~Equation();

private slots:
    void on_pushButton_clicked();

    void on_actionRun_triggered();

    void on_actionExit_triggered();
//protected:
    //void Press(QKeyEvent *e);


private:
    Ui::Equation *ui;
};
#endif // EQUATION_H
