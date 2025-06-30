#ifndef UR1_H
#define UR1_H

#include <QDialog>
#include "QStringListModel"


namespace Ui {
class Ur1;
}

class Ur1 : public QDialog
{
    Q_OBJECT

public:
    explicit Ur1(QWidget *parent = nullptr);
    ~Ur1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ur1 *ui;
    QList<quint64> res1;
    QStringListModel * model;
};

#endif // UR1_H
