#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include "metody.h"

using namespace std;



int main() 
{
    setlocale(LC_ALL, "Ru");
    Phones phoneBook;
    int choice = 0;

    while (true) 
    {
        cout << "Меню:"<<endl;
        cout << "1. Добавить владельца" << endl;
        cout << "2. Удалить владельца" << endl;
        cout << "3. Показать всех владельцев" << endl;
        cout << "4. Сохранить в файл" << endl;
        cout << "5. Загрузить из файла" << endl;
        cout << "6. Отсортировать по номеру" << endl;
        cout<<  "7. Очистить всех владельцев" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: " << endl;
        cin >> choice;

        try 
        {
            switch (choice) 
            {
            case 1: 
            {
                short num;
                string name;
                double cost;
                int index;

                cout << "Введите индекс: ";
                cin >> index;
                
                cout << "Введите номер телефона: ";
                cin >> num;
               
                cout << "Введите фамилию: ";
                cin >> name;

                cout << "Введите стоимость: ";
                cin >> cost;

                phoneBook.insert(index, Phone(num, name, cost));

                cout << "Владелец добавлен."<<endl;
                break;
            }
            case 2: 
            {
                int index;
                cout << "Введите индекс для удаления: ";
                cin >> index;
                phoneBook.erase(index);
                cout << "Владелец удален."<<endl;
                break;
            }
            case 3:
                cout << "Список владельцев:" << endl;
                phoneBook.print();
                break;
            case 4:
                phoneBook.Save("phones.txt");
                cout << "Данные сохранены в файл." << endl;
                break;
            case 5:
                phoneBook.Load("phones.txt");
                cout << "Данные загружены из файла." << endl;
                break;
            case 6:
                phoneBook.sort();
                cout << "Список отсортирован по номеру телефона." << endl;
                break;
            case 7: 
                phoneBook.clear();
                cout << "Список очищен." << endl;
                break;
            
            case 0:
                return 0;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
        catch (const exception& e) 
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    return 0;
}