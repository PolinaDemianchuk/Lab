#include <QList>
#include <QVector>
#include <ctime>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QStringList>

using namespace std;

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);

    srand(time(NULL));
    setlocale(LC_ALL, "ru");

    QList<int> array = {1, 5, 3, 6};

    qDebug()<<array;
    int n=2;
    qDebug() << "Elemnt number : "<<n;

    if (n < 1 || n > array.size())
    {
        qDebug() << "Incorrect number" ;
        return 1;
    }

    int zero = qCountLeadingZeroBits(quint64(array[n-1]));
    qDebug() << "number of zeros " << ": " << zero;

    sort(array.begin(),array.end());
    qDebug()<<array;

    std::list<int> stdarray(array.begin(), array.end());

     return a.exec();

}
