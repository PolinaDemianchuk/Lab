#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int id;
    const int nextid=1000;
    static int kolich;
public:
    Vehicle() : id(nextid + kolich) { kolich++; }

    virtual void info() const = 0;

    int ID() { return id; }

    static int kolvo()
    {
        return kolich;
    }

    virtual ~Vehicle() { kolich--; }
};

int Vehicle::kolich = 0;

class Koleso
{
private:
    double rad;
public:
    Koleso(double r) : rad(r) {}
    double getrad() const
    {
        return rad;
    }
};

class Car : public Vehicle
{
protected:
    string brand;
    Koleso kol;
    int price;
    const int carid=1000;
public:
    Car(string b, int p, double k) : brand(b), price(p), kol(k)
    {
        id = carid + kolich;
    }

    ~Car() {}

    void info() const
    {
        cout << "ID: " << id << endl;
        cout << "Бренд: " << brand << endl;
        cout << "Цена: " << price << endl;
        cout << "Радиус колеса: " << kol.getrad() << endl;
        cout << endl;
    }

    
};


class Truck : public Car
{
private:
    double gruz;
    const int truckid = 1000;
public:
    Truck(string b, double p, int r, double g) : Car(b, p, r), gruz(g) 
    { 
        id = truckid + kolich;
    }

    void info() const
    {
        cout << "ID: " << id << endl;
        cout << "Бренд: " << brand << endl;
        cout << "Цена: " << price << endl;
        cout << "Радиус колеса: " << kol.getrad() << endl;
        cout << "Грузоподъемность: " << gruz << endl;
        cout << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Ru");
    Car car("BMW", 12000, 0.5);
    Truck truck1("БелАз", 52300, 2.2, 7700);
    Truck truck2("МАЗ", 46000, 1.3, 4500);

    car.info();
    
    truck1.info();
    
    truck2.info();
    

    cout << "Количество транспортных средств: " << Car::kolvo();
    return 0;
}

