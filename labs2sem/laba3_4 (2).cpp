#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.h>

using namespace std;


struct Element1;
struct Element2;
struct Element3;

struct Element1
{
public:
    char Name[50];
    int Count;
    char Addr[50];

    Element1()
    {
        strcpy(Addr, "");
        strcpy(Name, "");
        Count = 0;

    }

    friend ostream& operator<< (ostream& out, const Element1& m)
    {

        out << "Имя: " << m.Name << endl;
        out << "Количество книг: " << m.Count << endl;
        out << "Адрес: " << m.Addr << endl;

        return out;
    }

    friend istream& operator>> (istream& in, Element1& m)
    {


        in >> m.Name;

        in >> m.Count;

        in >> m.Addr;

        return in;
    }

    Element1& operator = (Element1& m)
    {
        strcpy(Addr, m.Addr);
        strcpy(Name, m.Name);
        Count = m.Count;

        return *this;
    }

    Element1& operator = (Element2& m);
    Element1& operator = (Element3& m);


    template<class T>
    Element1& operator = (T& m)
    {
        try
        {
            strcpy(Addr, m.Addr);
            strcpy(Name, m.Name);
            Count = m.Count;

        }
        catch (const exception& e)
        {
            cout << "Assignment error: " << e.what() << endl;
        }
        return *this;
    }


    template<class T>
    bool operator == (T& m)
    {
        return (strcmp(Addr, m.Addr) == 0);
    }


    bool operator < (Element1& m2)
    {
        if (strcmp(Name, m2.Name) > 0)
            return true;
        else return false;
    }
};

struct Element2
{
    char Name[50];
    char Addr[50];


    friend istream& operator>> (istream& in, Element2& m)
    {

        in >> m.Name;
        in >> m.Addr;

        return in;
    }

    friend ostream& operator<< (ostream& out, const Element2& m)
    {

        out << "Имя сдавшего студента: " << m.Name << endl;
        out << "Адрес: " << m.Addr << endl;

        return out;
    }

    Element2& operator = (Element2& m)
    {
        strcpy(Addr, m.Addr);
        strcpy(Name, m.Name);

        return *this;
    }


    template<class T>
    bool operator == (T& m)
    {
        try
        {
            return (strcmp(Name, m.Name) == 0);
        }
        catch (const exception& e)
        {
            cout << "Comparison error: " << e.what() << endl;
            return false;
        }
    }


    bool operator < (Element2& m2)
    {
        if (strcmp(Addr, m2.Addr) > 0)
            return true;
        else return false;
    }
};

struct Element3
{
    char Name[50];
    char Addr[50];

    int Count;

    Element3()
    {
        strcpy(Name, "");
        strcpy(Addr, "");

        Count = 0;
    }

    friend istream& operator>> (istream& in, Element3& m)
    {


        in >> m.Name;

        in >> m.Count;

        in >> m.Addr;
        return in;
    }

    friend ostream& operator<< (ostream& out, const Element3& m)
    {

        out << "Имя не сдавшего: " << m.Name << endl;
        out << "Количество книг не сдано: " << m.Count << endl;
        out << "Адрес: " << m.Addr << endl;
        return out;
    }

    Element3& operator = (Element3& m)
    {
        strcpy(Name, m.Name);
        strcpy(Addr, m.Addr);
        Count = m.Count;
        return *this;
    }

    Element3& operator = (Element1& m)
    {
        strcpy(Name, m.Name);
        strcpy(Addr, m.Addr);
        Count = m.Count;
        return *this;
    }


    template<class T>
    bool operator == (T& m)
    {
        try
        {
            return (strcmp(Name, m.Name) == 0);
        }
        catch (const exception& e)
        {
            cout << "Comparison error: " << e.what() << endl;
            return false;
        }
    }


    bool operator < (Element3& m2)
    {
        if (strcmp(Name, m2.Name) > 0)
            return true;
        else return false;
    }
};



template<class T>
class MASSIV
{
    int count;
    T* mas;

public:

    MASSIV()
    {
        mas = NULL;
        count = 0;
    }

    MASSIV(int n)
    {
        count = n;
        mas = new T[n];
    }


    ~MASSIV()
    {
        if (mas)
            delete[] mas;
    }


    int GetCount()
    {
        return count;
    }


    void SetCount(int k)
    {
        count = k;
    }


    void WriteData(const char* s)
    {
        fstream out;
        out.open(s, ofstream::out | ofstream::binary);
        if (!out.is_open())
        {
            cout << "Open file failed.\n";
        }
        else
        {
            int i = 0;
            while (i < count)
            {
                out.write((char*)&mas[i], sizeof(T));
                i++;
            }
            out.close();
        }
    }


    void WriteTextData(const char* s)
    {
        fstream out;
        out.open(s, ofstream::out);
        if (!out.is_open())
        {
            cout << "Open file failed.\n";
        }
        else
        {
            int i = 0;
            while (i < count)
            {
                out << mas[i];
                i++;
            }
            out.close();
        }
    }


    void ReadData(const char* s)
    {
        fstream in;
        in.open(s, ofstream::in | ofstream::binary);
        if (!in.is_open())
        {
            cout << "Open file failed.\n";
            return;
        }

        if (mas)
            delete[] mas;

        mas = new T[100];
        int i = 0;
        in.seekg(0, ios::beg);

        while (!in.eof() && in.read((char*)&mas[i], sizeof(T)))
        {
            i++;
        }

        count = i;
        in.close();
    }

    void ReadTextData(const char* s)
    {
        fstream in;
        in.open(s, ofstream::in);
        if (!in.is_open())
        {
            cout << "Open file failed.\n";
            return;
        }

        if (mas)
            delete[] mas;

        mas = new T[100];
        int i = 0;

        while (!in.eof())
        {
            in >> mas[i];
            if (in.fail())
                break;
            i++;
        }

        count = i;
        in.close();
    }

    friend istream& operator>> (istream& in, MASSIV& m)
    {
        int n;
        cout << "Количество элементов: ";
        in >> n;

        m.mas = new T[n];
        m.count = n;

        for (int i = 0; i < n; i++)
        {
            cout << "Введите элемент " << i + 1 << ":" << endl;
            in >> m.mas[i];
        }

        return in;
    }


    friend ostream& operator<< (ostream& out, const MASSIV& m)
    {
        out << "--------СТУДЕНТЫ :" << endl;
        for (int j = 0; j < m.count; j++)
        {
            out << m.mas[j] << endl;
        }
        return out;
    }


    T& operator[] (int m)
    {
        return mas[m];
    }


    template<class T2>
    MASSIV& operator = (MASSIV <T2>& m)
    {

        count = m.GetCount();
        mas = new T[count];

        for (int i = 0; i < count; i++)
        {
            mas[i] = m[i];
        }

        return *this;
    }


    void Sort()
    {
        cout << endl << "---------------СОРТИРОВКА    " << endl << endl;

        T t;
        for (int i = 0; i < count - 1; i++)
            for (int j = i + 1; j < count; j++)
                if (mas[i] < mas[j])
                {
                    t = mas[i];
                    mas[i] = mas[j];
                    mas[j] = t;
                }
    }


    template<class T1, class T2>
    void SUBTRACTION(MASSIV<T1>& x, MASSIV<T2>& y)
    {
        int k = 0;
        bool found;
        cout << endl << "---------------НЕ СДАВШИЕ КНИГИ—--- " << endl << endl;

        mas = new T[x.GetCount()];

        for (int i = 0; i < x.GetCount(); i++)
        {
            found = false;
            for (int j = 0; j < y.GetCount(); j++)
            {
                if (x[i] == y[j])
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                mas[k] = x[i];
                k++;
            }
        }

        count = k;
    }


    template<class A>
    friend void Search(MASSIV<A>& arr, int k);
};


template<class A>
void Search(MASSIV<A>& arr, int k)
{

    cout << "Студенты, которые взяли болле, чем " << k << " книг:" << endl;
    cout << endl;
    bool found = false;

    for (int i = 0; i < arr.count; i++)
    {
        if (arr.mas[i].Count > k)
        {
            cout << arr.mas[i] << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Не найдено таких студентов" << endl;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_ALL, "ru");

    MASSIV <Element1> M;
    /*  M.WriteData("Dannye.txt");*/
      //M.WriteTextData("Dannye.txt");
     /* M.ReadData("Element1.txt");*/
    M.ReadTextData("Dannye.txt");
    M.Sort();
    cout << M;//(1)

    int k;
    cout << "Введите количество книг для поиска: ";
    cin >> k;
    Search(M, k);

    MASSIV <Element2> K;
    K.ReadTextData("Dannye1.txt");
    K.Sort();
    cout << K;
    /*  K.ReadData("Element2.txt");
      K.WriteData("Element2.txt");*/
      /*   K.WriteTextData("Dannye1.txt");*/
         //cout << K[2]; //(1) (2)
         //cout << K;//(1)
    MASSIV <Element3> R(M.GetCount());

    R.SUBTRACTION(M, K);
    cout << R;
    R.Sort();
    MASSIV <Element3> K2;
    K2 = R;
    cout << K2;


    return 1;


}