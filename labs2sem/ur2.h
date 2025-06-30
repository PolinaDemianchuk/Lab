#ifndef UR2_H
#define UR2_H

#include <QDialog>
#include "QStringListModel"
namespace Ui {
class Ur2;
}

class Ur2 : public QDialog
{
    Q_OBJECT

public:
    explicit Ur2(QWidget *parent = nullptr);
    ~Ur2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ur2 *ui;
    QList<quint64> res2;
    QStringListModel * model;
};

#endif // UR2_H
