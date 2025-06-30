#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

struct Phone
{
    short phoneNumber;
    string lastName;
    double cost;

    Phone(short num = 0, const string& name = "", double c = 0.0)
        : phoneNumber(num), lastName(name), cost(c) {}

    bool operator>(const Phone& other)
    {
        return phoneNumber > other.phoneNumber;
    }

    friend ostream& operator<<(ostream& os, Phone& owner)
    {
        os << owner.phoneNumber << " " << owner.lastName << " " << owner.cost;
        return os;
    }

    friend istream& operator>>(istream& in, Phone& owner)
    {

        in >> owner.phoneNumber;
        in >> owner.lastName;
        in >> owner.cost;
        return in;
    }
};


class Phones
{
private:
    struct Node
    {

        Phone data;
        Node* next;
        Node* prev;

        Node(const Phone& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int sizen;

public:
    Phones() : head(nullptr), tail(nullptr), sizen(0) {}

    ~Phones()
    {
        clear();
    }

    bool empty() const
    {
        return sizen == 0;
    }

    int size() const
    {
        return sizen;
    }

    void Save(const string& filename) 
    {

        ofstream file(filename);
        Node* current = head;
        while (current)
        {
            file << current->data << endl;
            current = current->next;
        }
    }

    void Load(const string& filename)
    {
        ifstream file(filename);

        clear();

        Phone value;
        while (file >> value)
        {
            push_back(value);
        }
    }

    void sort()
    {
        bool swapped = true;
        while (swapped)
        {
            swapped = false;
            Node* current = head;

            while (current && current->next)
            {
                if (current->data > current->next->data)
                {
                    swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        }
    }

    void push_back(const Phone& value)
    {
        Node* newNode = new Node(value);

        if (empty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        sizen++;
    }

    void push_front(const Phone& value)
    {
        Node* newNode = new Node(value);

        if (empty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        sizen++;
    }

    void pop_back()
    {


        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
        }
        else
        {
            Node* newTail = tail->prev;
            newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }

        sizen--;
    }

    void pop_front()
    {
        if (empty())
        {
            throw out_of_range("Список пуст");
        }

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node* newHead = head->next;
            newHead->prev = nullptr;
            delete head;
            head = newHead;
        }

        sizen--;
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    void insert(int index, const Phone& value)
    {

        if (index == 0)
        {
            push_front(value);
        }
        else if (index == sizen)
        {
            push_back(value);
        }
        else
        {
            Node* current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }

            Node* newNode = new Node(value);

            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;

            sizen++;
        }
    }

    void erase(int index)
    {


        if (index == 0)
        {
            pop_front();
        }
        else if (index == sizen - 1)
        {
            pop_back();
        }
        else
        {
            Node* current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;

            delete current;
            sizen--;
        }
    }

    void print() const
    {
        if (empty())
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr)
        {
            cout << "Номер: " << current->data.phoneNumber
                << " Фамилия: " << current->data.lastName
                << " Стоимость: " << current->data.cost << endl;
            current = current->next;
        }
    }
};