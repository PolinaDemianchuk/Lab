#ifndef UR3_H
#define UR3_H

#include <QDialog>
#include "QStringListModel"
namespace Ui {
class Ur3;
}

class Ur3 : public QDialog
{
    Q_OBJECT

public:
    explicit Ur3(QWidget *parent = nullptr);
    ~Ur3();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ur3 *ui;
    QList<quint64> res3;
    QStringListModel * model;
};

#endif // UR3_H
